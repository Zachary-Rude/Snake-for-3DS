#include <citro2d.h>
#include <3ds.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#define SCREEN_WIDTH  400
#define SCREEN_HEIGHT 240

#define GAME_OVER 0
#define RUNNING 1
#define EXIT 2
#define PAUSED 3

struct Vector2
{
	float x, y;
};

struct Food
{
	u32 color;
	struct Vector2 position;
};

struct Snake
{
	int length;
	u32 color;
	struct Vector2 positions[1000];
	struct Vector2 headPositon;
	int dx;
	int dy;
	int speed;
};

struct Game
{
	u32 clrClear;
	u32 wallColor;
	int score;
	int highscore;
	int status;
	double drawTime;
	C3D_RenderTarget* top;
	C3D_RenderTarget* bottom;
	C2D_TextBuf dynamicBuf;
	C2D_Text scoreText[4];
	C2D_Text pausedText[4];
};

struct Game game;
struct Snake snake;
struct Food food;

void drawWalls();
void initGame();
void initSnake();
void drawSnake();
void input();
void moveSnake();
void drawTopScreen();
void drawBottomScreen();
void addScore();
void spawnFood();
void drawFood();
void checkCollision();
void saveHighscore();

void drawTopScreen()
{
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(game.top, game.clrClear);
	C2D_SceneBegin(game.top);
	moveSnake();
	checkCollision();
	drawWalls();
	drawSnake();
	drawFood();
	if (game.status == PAUSED) {
	  char buf[160];
	  snprintf(buf, sizeof(buf), "Paused");
	  C2D_TextParse(&game.pausedText, game.dynamicBuf, buf);
	  C2D_TextOptimize(&game.pausedText);
	  C2D_DrawText(&game.pausedText, C2D_AlignCenter | C2D_WithColor, 0, 0, 10, 1, 1, C2D_Color32(255, 255, 255, 255));
	}
	C3D_FrameEnd(0);
}

void drawBottomScreen()
{
	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(game.bottom, C2D_Color32(0, 0, 0, 1));
	C2D_SceneBegin(game.bottom);
	C2D_TextBufClear(game.dynamicBuf);
	char buf[160];
	snprintf(buf, sizeof(buf), "Score: %d", game.score);
	C2D_TextParse(&game.scoreText, game.dynamicBuf, buf);
	C2D_TextOptimize(&game.scoreText);
	C2D_DrawText(&game.scoreText, C2D_AlignCenter | C2D_WithColor, 65, 0, 0, 1, 1, C2D_Color32(255, 255, 255, 255));

	snprintf(buf, sizeof(buf), "Highscore: %d", game.highscore);
	C2D_TextParse(&game.scoreText, game.dynamicBuf, buf);
	C2D_TextOptimize(&game.scoreText);
	C2D_DrawText(&game.scoreText, C2D_AlignLeft | C2D_WithColor, 65, 33, 0, 1, 1, C2D_Color32(255, 255, 255, 255));

	C3D_FrameEnd(0);
}

void initGame()
{
	game.highscore = 0;
	game.clrClear = C2D_Color32(0, 0, 0, 1);
	game.wallColor = C2D_Color32(0, 0, 0, 255);
	game.score = 0;
	game.status = RUNNING;
}

int isOverlapping(struct Vector2 l1, struct Vector2 r1, struct Vector2 l2, struct Vector2 r2) {
   if (l1.x > r2.x || l2.x > r1.x)
      return 0;
   if (l1.y < r2.y || l2.y < r1.y)
      return 0;
   return 1;
}

void checkCollision()
{
	struct Vector2 l1;
	l1.x = food.position.x - 5;
	l1.y = food.position.y + 5;
	struct Vector2 r1;
	r1.x = food.position.x + 5;
	r1.y = food.position.y - 5;
	struct Vector2 l2;
	l2.x = snake.headPositon.x - 5;
	l2.y = snake.headPositon.y + 5;
	struct Vector2 r2;
	r2.x = snake.headPositon.x + 5;
	r2.y = snake.headPositon.y - 5;

	if(isOverlapping(l1, r1, l2, r2))
	{
		addScore();
		spawnFood();
	}

	if(snake.headPositon.x == 20 || snake.headPositon.x == SCREEN_WIDTH - 20)
	{
		game.status = GAME_OVER;
	}
	if(snake.headPositon.y == 20 || snake.headPositon.y == SCREEN_HEIGHT - 20)
	{
		game.status = GAME_OVER;
	}

	for(int i = 0; i < snake.length; i++)
	{
		if(snake.headPositon.x == snake.positions[i].x && snake.headPositon.y == snake.positions[i].y)
		{
			game.status = GAME_OVER;
		}
	}
}

int isFoodSpawnValid(int x, int y)
{
	struct Vector2 l1;
	l1.x = x - 2.5;
	l1.y = y + 2.5;
	struct Vector2 r1;
	r1.x = x + 2.5;
	r1.y = y - 2.5;
	struct Vector2 l2;
	l2.x = snake.headPositon.x - 5;
	l2.y = snake.headPositon.y + 5;
	struct Vector2 r2;
	r2.x = snake.headPositon.x + 5;
	r2.y = snake.headPositon.y - 5;

	if(isOverlapping(l1, r1, l2, r2))
	{
		return 0;
	}

	for(int i = 0; i < snake.length; i++)
	{
		l2.x = snake.positions[i].x - 20;
		l2.y = snake.positions[i].y + 20;
		struct Vector2 r2;
		r2.x = snake.positions[i].x + 20;
		r2.y = snake.positions[i].y - 20;
		if(isOverlapping(l1, r1, l2, r2))
		{
			return 0;
		}
	}

	return 1;
}

void spawnFood()
{
	srand(time(0));
	int x = 0;
	int y = 0;
	do
	{
 		x = (rand() % ((SCREEN_WIDTH - 40) - 40 + 1)) + 40;
		y = (rand() % ((SCREEN_HEIGHT - 40) - 40 + 1)) + 40;;

		food.position.x = x;
		food.position.y = y;
		food.color = C2D_Color32(255, 0, 0, 255);
	} while (!isFoodSpawnValid(x, y));
}

void drawFood()
{
	C2D_DrawRectSolid(food.position.x, food.position.y, 0, 10, 10, food.color);
}

void initSnake()
{
	snake.length = 5;
	snake.headPositon.x = 200;
	snake.headPositon.y = 120;
	snake.color = C2D_Color32(0, 255, 0, 255);
	snake.dx = 10;
	snake.dy = 0;
	snake.speed = 6;

	for(int i = 0; i < snake.length; i++)
	{
		snake.positions[i].x = 190 - (i * 10);
		snake.positions[i].y = 120;
	}
}

void drawSnake()
{
	C2D_DrawRectSolid(snake.headPositon.x, snake.headPositon.y, 0, 10, 10, snake.color);

	for(int i = 0; i < snake.length; i++)
	{
		C2D_DrawRectSolid(snake.positions[i].x, snake.positions[i].y, 0, 10, 10, snake.color);
	}
}

void moveSnake()
{
	if(game.status == RUNNING)
	{
	  for(int i = snake.length - 1; i >= 0; i--)
	  {
		  snake.positions[i].x = snake.positions[i - 1].x;
	    snake.positions[i].y = snake.positions[i - 1].y;
    }	  
	  snake.positions[0].x = snake.headPositon.x;
	  snake.positions[0].y = snake.headPositon.y;
	  snake.headPositon.x += snake.dx;
	  snake.headPositon.y += snake.dy;
	}
}
void input()
{
	hidScanInput();
	u32 kDown = hidKeysDown();
	if(kDown & KEY_UP)
	{
		if(snake.dy != 10 && game.status == RUNNING)
		{
			snake.dx = 0;				
			snake.dy = -10;
		}
	}
	if(kDown & KEY_CPAD_UP)
	{
		if(snake.dy != 10 && game.status == RUNNING)
		{
			snake.dx = 0;				
			snake.dy = -10;
		}
	}
	if(kDown & KEY_DOWN)
	{
		if(snake.dy != -10 && game.status == RUNNING)
		{
			snake.dx = 0;
			snake.dy = 10;
		}
	}
	if(kDown & KEY_CPAD_DOWN)
	{
		if(snake.dy != -10 && game.status == RUNNING)
		{
			snake.dx = 0;
			snake.dy = 10;
		}
	}
	if(kDown & KEY_RIGHT)
	{
		if(snake.dx != -10 && game.status == RUNNING)
		{
			snake.dx = 10;
			snake.dy = 0;
		}
	}
	if(kDown & KEY_RIGHT)
	{
		if(snake.dx != -10 && game.status == RUNNING)
		{
			snake.dx = 10;
			snake.dy = 0;
		}
	}
	if(kDown & KEY_CPAD_RIGHT && game.status == RUNNING)
	{
		if(snake.dx != -10)
		{
			snake.dx = 10;
			snake.dy = 0;
		}
	}
	if(kDown & KEY_LEFT && game.status == RUNNING)
	{
		if(snake.dx != 10)
		{
			snake.dx = -10;
			snake.dy = 0;
		}
	}	
	if(kDown & KEY_CPAD_LEFT && game.status == RUNNING)
	{
		if(snake.dx != 10 && game.status == RUNNING)
		{
			snake.dx = -10;
			snake.dy = 0;
		}
	}
	if(hidKeysUp() & KEY_START)
	{
		if (game.status == RUNNING)
		{
			game.status = PAUSED;
		}
		else if (game.status == PAUSED)
		{
			game.status = RUNNING;
		}
		
	}
}

void addScore()
{
	snake.positions[snake.length].x = snake.positions[snake.length - 1].x;
	snake.positions[snake.length].y = snake.positions[snake.length - 1].y;

	snake.length += 1;
	game.score += 1;
	if(game.score > game.highscore)
	{
		game.highscore = game.score;
	}
	for(int i = 0; i < 4; i++)
	{
		if(game.score == 3 * (i + 1))
		{
			snake.speed -= 1;
		}
	}
}

void drawWalls()
{
	//left wall
	C2D_DrawRectSolid(0, 0, 0, 10, SCREEN_HEIGHT, game.wallColor);
	//right wall
	C2D_DrawRectSolid(SCREEN_WIDTH - 10, 0, 0, 10, SCREEN_HEIGHT, game.wallColor);
	//upper wall
	C2D_DrawRectSolid(20, SCREEN_HEIGHT - 10, 0, SCREEN_WIDTH - 20, 10, game.wallColor);
	//lower wall
	C2D_DrawRectSolid(10, 0, 0, SCREEN_WIDTH - 20, 10, game.wallColor);
}

void saveHighscore()
{
	if(game.score > game.highscore)
	{
		game.highscore = game.score;
	}
}


int main(int argc, char* argv[]) {
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	initGame();
	initSnake();
	spawnFood();

	game.top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	game.bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

	game.dynamicBuf = C2D_TextBufNew(4096);

	while (aptMainLoop())
	{
		if(game.status == EXIT)
			break;

		if(game.status == GAME_OVER)
		{
			saveHighscore();
			game.score = 0;
			initSnake();
			spawnFood();
			game.status = RUNNING;
		}

		input();
		drawTopScreen();
		drawBottomScreen();
		int wait = snake.speed;
		while(wait--)
		{
			gspWaitForVBlank();
		}
	}

	C2D_Fini();
	C3D_Fini();
	gfxExit();
	return 0;
}