#!/bin/bash
# Script accepts arguments
# ./init_dev.sh CMAKE_BUILD_TYPE CMAKE_MODULE_PATH CMAKE_INSTALL_PREFIX

# Snag the name of this file
this_filename=`basename "$0"`
HOME=`pwd`
CURRENT_USER=`whoami`
BUILD_TYPE=${1:-Debug}
MODULE_PATH=${2:-/usr/local/cmake/modules}
INSTALL_PREFIX=${3:-/usr/local}

export PATH=$PATH:$NDDSHOME/bin

echo -e "START $this_filename\n"

function buildAndInstall() {
  mkdir -p $HOME/build/$1
  cd $HOME/build/$1
  cmake $HOME/$1 -DCMAKE_BUILD_TYPE=$BUILD_TYPE -DCMAKE_MODULE_PATH=$MODULE_PATH -DCMAKE_INSTALL_PREFIX=$INSTALL_PREFIX  || exit 1
  make  || exit 1
  sudo make install  || exit 1
}

# Installed neccessary development packages
sudo apt-get install g++ cmake libpq-dev socat postgresql

# Deploy CMake modules
sudo cp -r Shared/cmake $INSTALL_PREFIX

# Build and deploy libpqxx
cd $HOME/libpqxx-3.1.1
./configure --enable-shared || exit 1
sudo make install || exit 1

# Build and deploy log4cplus
cd $HOME/log4cplus-1.0.4.3
./configure --enable-shared || exit 1
sudo make install || exit 1

# Build and install projects
echo "Building DICES Data Information Model"
buildAndInstall Shared/DicesDim

echo ""
echo "Building DICES Framework (Common)"
buildAndInstall Shared/DicesFramework-Common

echo ""
echo "Building DICES Framework (Communication)"
buildAndInstall Shared/DicesFramework-Communication

echo ""
echo "Building DICES Framework (Core)"
buildAndInstall Shared/DicesFramework-Core

echo ""
echo "Building DICES Framework (Utilities)"
buildAndInstall Shared/DicesFramework-Utilities

echo ""
echo "Building DICES Framework (Deprecated)"
buildAndInstall Shared/DicesFramework-Deprecated

echo ""
echo "Building DICES Framework (Test)"
buildAndInstall Shared/DicesFramework-Test

echo -e "\nEND $this_filename\n"
