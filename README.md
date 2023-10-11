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
![QR code to install Snake for 3DS](data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAA6EAAAOhAQMAAAA9lTFpAAAAAXNSR0IArs4c6QAAAARnQU1BAACxjwv8YQUAAAAGUExURQAAAP///6XZn90AAAAJcEhZcwAADsMAAA7DAcdvqGQAAAUMSURBVHja7d1BbiI5FAZgIxYsOUKO0kcLR+MoHCFLFhGe7gJjP1NB6mg8waPv36RCsD8vn57tSso/kAN1cKijQx0d6uhQR4c6OtTRoY4OdXSoo0MdHeroUEeHOjrU0aGODnV0qKNDHZ0fVk/pIbvlDyltl5/HPx/dH3P+XL7z/uf3c31scn6ccUulUqlUKpVKnUwNwy6Lusz/Ox9h8K+6lsPjSk91Lb+/2IRKpVKpVCqVOqN6KYPfqxoSi9RlLZuw6KZIPd+W97BSKpVKpVKpVOrUau6G3R+X7uX+NjZSb/VTKpVKpVKpVOr/UC3dy1wXsK873Otq+jfqYSqVSqVSqVTqq6hNmu7ltU/5q6pLPm/TbXKX0+3T862EbRZNpVKpVCqVSp1N7bMLNej64+E2/9vqYx8qlUqlUqlU6lTqeo71u7FlWT493JZXytH8WOOuhEqlUqlUKpX6l2rT/VsOFF63nfuTh7m0FEsfsTm4WK449zXitlyLplKpVCqVSqVOrZZhzfz9Y67UbvUx3aj7mK+6l1QqlUqlUqnU11XDxeTmXvM2d2lOKa5UsyvDP6hUKpVKpVKpk6pLdnXya/sxdC9jkboPVNjsTv0Xm71yKpVKpVKpVOokag7txzJZ6i6qXBMq0/Ske9m0OfNqZUqlUqlUKpVKfWX11M2wKfMvP5tjjM1rcNJXarM8KpVKpVKpVOrUangJ9qVOul1dwLVePaS0soCyw72UsKm/gU2lUqlUKpVKnUTNtRxtLs007cdmhuaxqM0pyCalhN13RSqVSqVSqVQqdQr1VN+leKov0jl+3bK87nA3b9zJ7az3hOFbKpVKpVKpVOpMavnu7rEybW7KrMxwX2lJfGFPOC5JpVKpVCqVSp1KXdnhfrJF3TyuV6ab/jL2kUqlUqlUKpU6o5rqd8t/81tyf81OX2WWx12gSmXapJyczFQqlUqlUqnU76lNTuHOShgWX4MT95r7e83nvuG43r2kUqlUKpVKpb6s2mwWp9pSLHvNJdt+37ivQeNMy/BMpVKpVCqVSp1XDS+8SaXKTI8Ja7m3LHNbpMa95hRWSqVSqVQqlUqdSb3n0G52P5SjxzpZ6V6ewmNY3kqoVCqVSqVSqbOpp7BxXdSVRuYyPtVt7Wfq85syVCqVSqVSqdRXVMsMqb/q0qh1uuuojxSz6WcqK+2vRVOpVCqVSqVSp1BLZVquQ6d+h7uo5VWJn7f/s9K0Oe+Lzm1h2wynUqlUKpVKpU6l5kot7ceHY4ylE/kRFnBIMXGzu1y7zuGRSqVSqVQqlTqJeqrDllwKVeYPW9Q57HCn0PE8pbX8yplKpVKpVCqVOpm6noY63obvQ5XZq+fVDfL+kUqlUqlUKpU6hbpSTzbtx+t5x+ZEY1U39ZdL3/ws29rxMjaVSqVSqVQq9TvqeztdPFBYCsPPsKx9qBGXnL+68pK+2mumUqlUKpVKpb62einzvT+qJbFIbc4wluFvdS1LmjbklkqlUqlUKpU6v9qUo8uBws/VveZ4hnHJplKpDs9UKpVKpVKp1PnVXKkmpcr8uHU8z333ssk362EqlUqlUqlU6quoTWJluv9qAeHOSvO4dmelHUWlUqlUKpVKnUPtswv1ZNOyDFXmpexwP8n+SWVKpVKpVCqVSn1Z9T8NdXSoo0MdHeroUEeHOjrU0aGODnV0qKNDHR3q6FBHhzo61NGhjg51dKijQx2dH1Hz4R9UOQxAPPafJAAAAABJRU5ErkJggg==)
