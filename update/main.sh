#!/bin/bash
echo openpibo OS version is "$(cat /home/pi/.OS_VERSION)"

F_VERSION="220905v1"
T_VERSION="220905v1"

cd /home/pi

sudo pip3 install python-multipart
sudo npm install --save multer

sudo rm openpibo-files openpibo-tools -rf
wget https://github.com/themakerrobot/themakerrobot/releases/download/${F_VERSION}/openpibo-files-${F_VERSION}.zip
wget https://github.com/themakerrobot/themakerrobot/releases/download/${T_VERSION}/openpibo-tools-${T_VERSION}.zip
unzip openpibo-files-${F_VERSION}.zip
unzip openpibo-tools-${T_VERSION}.zip
sudo chown pi:pi -R openpibo-files openpibo-tools
sudo rm openpibo-files-${F_VERSION}.zip openpibo-tools-${T_VERSION}.zip

sudo shutdown -r now
