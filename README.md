# RobotinoLib

<img src="https://ip.festo-didactic.com/InfoPortal/Robotino/Images/4_Robotino.jpg" alt="drawing" width="200"/>

diese beste, check it out

## What is this?

This library is a wrapper around the Festo Robotino API 2. The goal is to make working with the Festo Robotino as easy as possible.

## Building

### Windows
<details>
<summary>Installation instructions for Windows 64-bit</summary>

#### Requirements

 - [Microsoft Visual Studio 2019](https://visualstudio.microsoft.com/de/downloads/) - Other IDEs can be used by editing `generate-win.bat`
 - [git](https://git-scm.com/downloads) - Recommended for cloning the repository
 - [Robotino API 2](https://wiki.openrobotino.org/index.php?title=API2) - Here is the direct [download link](https://packages.openrobotino.org/windows/robotino-api2/msvc-142/robotino_api2-amd64-msvc-142-1.1.14.exe) for Windows 64-bit, Visual Studio 2019

#### Cloning the repository (using git)

##### Part 1:
 - In the File Explorer, navigate to the target directory, a location where it can stay without being deleted accidentally  
   (e.g. `C:\dev\` or `Documents`, not the `Download` folder)
 - Type `cmd` in the address bar at the top and press Enter, a command line should pop up
 - Paste this command in the command line and press Enter:  
 `git clone --recursive https://github.com/HerrNamenlos123/RobotinoLib.git` 
 - When the command has finished, close the console and navigate to the new `RobotinoLib` folder in the File Explorer
 
##### Part 2:
 - Now, double-click the file `generate-win.bat`, this will generate everything and open Visual Studio for you
 - Finally, in Visual Studio, build the project `BUILD_ALL` in the project explorer
 - After compilation, the library is ready to use. Check out the [RobotinoTemplate](https://github.com/HerrNamenlos123/RobotinoTemplate) for instructions on how to use it.

#### Downloading the ZIP-file (without git)

##### Part 1:
 - Download this repository's zip-file by using the green button at the top of this page
 - Extract the zip file to a location where it can stay without being deleted accidentally  
   (e.g. `C:\dev\` or `Documents`, not the `Download` folder)
   
 - Once this has finished, navigate to the extracted folder and continue with [part 2](#Part-2)
 
</details>

### Linux
<details>
<summary>Installation instructions for Linux distributions</summary><br \>

This library was tested on Debian 11
 
#### Requirements

 - git: `sudo apt install git`
 - make: `sudo apt install build-essential`
 - Qt5: `sudo apt install qtbase5-dev qtchooser qt5-qmake qtbase5-dev-tools`

#### Building

 - Navigate to a working directory and clone:  
 `git clone --recursive https://github.com/HerrNamenlos123/RobotinoLib.git`
 - Generate the project files: `./generate-linux.sh`
 - Build the library: `cd build` and `make`
 - Install the library: `cd ..` and `sudo ./install-linux.sh`
 - Now the the library is ready to use. Check out the [RobotinoTemplate](https://github.com/HerrNamenlos123/RobotinoTemplate) for instructions on how to use it.

</details>
