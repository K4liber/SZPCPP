#!/bin/bash

sudo apt-get install gcc build-essential libwxbase3.0-dev libwxgtk3.0-dev
tar zxf winusb-1.0.11.tar.gz
cd winusb-1.0.11/src
sed -i -- 's#wxStandardPaths().GetInstallPrefix()#wxStandardPaths::Get().GetInstallPrefix()#g' findFile.cpp
sed -i -- 's#wxStandardPaths().GetDataDir()#wxStandardPaths::Get().GetDataDir()#g' findFile.cpp
cd ..
./configure
make
sudo make install
cd ..
rm -rf winusb-1.0.11
