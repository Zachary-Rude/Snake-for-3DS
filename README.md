# Snake for 3DS
This is a basic 3DS homebrew version of Snake.
You start moving slowly, and as you gain more points, you start to move faster.

## Building
> [!IMPORTANT]
> On Windows, `make` should be run in the devkitPro shell.

To build Snake, run `make`. This will build a .3dsx file that can be launched through the Homebrew Launcher. It will also generate a .elf file.
<br>
If you want to build a .cia file that can be installed through an app like FBI and launched through the HOME Menu, run this command:

```
makerom -f cia -o snake.cia -DAPP_ENCRYPTED=false -rsf game.rsf -target t -exefslogo -elf snake_3ds-main.elf -icon icon.icn -banner banner.bnr
```

> [!NOTE]
> On Windows, you can run the above command either in a Command Prompt or Powershell window, or in the devkitPro shell.

## Install
Go to the releases for this repository, and download either the .cia or .3dsx for the latest version.
<br>
You can also use FBI to scan the QR code below to install this game more quickly.
![QR code to install Snake for 3DS](/qr-code.png)
