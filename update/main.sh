#!/bin/bash
echo openpibo OS version is "$(cat /home/pi/.OS_VERSION)"


VERSION="220905v1"

cd /home/pi

sudo pip3 install python-multipart
sudo npm install --save multer

sudo rm openpibo-files openpibo-tools -rf
wget https://github.com/themakerrobot/themakerrobot/releases/download/220905v1/openpibo-files-${VERSION}.zip
wget https://github.com/themakerrobot/themakerrobot/releases/download/220905v1/openpibo-tools-${VERSION}.zip
unzip openpibo-files-${VERSION}.zip
unzip openpibo-tools-${VERSION}.zip
sudo chown pi:pi -R openpibo-files openpibo-tools
sudo rm openpibo-files-${VERSION}.zip openpibo-tools-${VERSION}.zip

sudo shutdown -r now
