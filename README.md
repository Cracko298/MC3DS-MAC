# MC3DS-MAC
- **A 3DS (Nintendo 3DS) Homebrew Application that converts Material Attribute Files from MC-3DS Edition to  .json**

## Usage:
- **After downloading and installing the compiled .cia/.3dsx Open the application once to create a folder on the system SDHC Card.**
- **Then copy over your Material Attribute Files (.material, .material3ds, .images, .dat, .mat) in the newly created: "[mc3ds_files](https://github.com/Cracko298/MC3DS-MAC)" Folder.**
- **Enter the Application again, and now each file should have a newer generated file with the extension of ".json".**

## Download(s):
- **Download Standalone .cia [Here](https://github.com/Cracko298/MC3DS-MAC/releases/download/v1.2.2/MC3DS-MAC.cia).**
- **Download HB Launcher .3dsx [Here](https://github.com/Cracko298/MC3DS-MAC/releases/download/v1.2.2/MC3DS-MAC.3dsx).**
- **Download Source .elf File [Here](https://github.com/Cracko298/MC3DS-MAC/releases/download/v1.2.2/MC3DS-MAC.elf).**

### Don't have an SD Reader or a FTP Server?
- **I have you covered, Click [Here](https://raw.githubusercontent.com/Cracko298/MC3DS-MAC/main/imgs/frame.png) for a <ins>Direct QR-Code</ins> Download.**

## Building:
- **Requires Devkitpro v3.0.3 or higher and the Basic 3DS SDK from it.**

### Banner:
```
.\bannertool.exe makebanner -i "banner_ico.png" -ca "banner.bcwav" -o "banner.bnr"
```
### Icon (SMDH):
```
.\bannertool.exe makesmdh -s "MC3DS-MAC" -l "MC Material Attribute Converter" -p "Cracko298" -i "pack.png" -o "icon.smdh"
```
### Sound:
```
.\cwavtool.exe -i banner.wav -e pcm8 -o banner.bcwav
```
### MakeRom
```
.\makerom.exe -f cia -o MC3DS-MAC.cia -elf MC3DS-MAC.elf -rsf files.rsf -icon icon.smdh -banner banner.bnr -major 1 -minor 2 -micro 2
```

## Requirement(s):
- **A Homebrewed/Hacked 3DS Console with access to CFW and a Title Installer, or Homebrew Launcher.**
- **An SDHC Card that's being used for your 3DS Games.**
- **Material Attribute Files for Converting into .JSON Format.**

## Credit(s):
- **[Cracko298](https://github.com/Cracko298) Development of this Homebrew Application.**
- **Steveice10 for [bannertool](https://github.com/Steveice10/bannertool).**
- **PabloMK7 for [cwavtool](https://github.com/PabloMK7/cwavtool).**
- **3DSGuy for [Project_CTR (makerom)](https://github.com/3DSGuy/Project_CTR).**
