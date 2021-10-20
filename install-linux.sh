#!/bin/bash
set -e		# exit on error

if [ "$EUID" -ne 0 ]
  then echo "Installation script must be run as root! Make sure to use sudo!"
  exit
fi

# Replace the generator here
_generator=gmake
_projectname=RobotinoLib

# ===================================================================
echo Installing project $_projectname

SCRIPT_DIR="$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )"

"$SCRIPT_DIR/premake5/linux/premake5" install --file="$SCRIPT_DIR/premake5.lua" --projectname=$_projectname

echo -e "\e[32mInstallation successful\e[0m"
