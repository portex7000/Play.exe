# Play.exe
Custom "media player" designed mostly for batch scripts to play audio

## How to use:
First, put `play.exe` into `C:\Windows`, `C:\Windows\System32` or any directory that in in the `%path%` variable. Then, in you batch file, type `play <audiofile.mp3> <volume> <L or l for loop>`. To stop playing (for example when you want to end the loop), type `taskkill /im play.exe /f` into the command prompt, or kill `play.exe` using task manager.

## Installer:
Coming soon
