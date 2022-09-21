#!/bin/bash
echo openpibo OS version is "$(cat /home/pi/.OS_VERSION)"

F_VERSION="220905v1"
T_VERSION="220921v1"

cd /home/pi

sudo pip3 install -U openpibo-python
sudo pip3 install python-multipart
sudo npm install --save multer

wget -O openpibo-tools.zip https://github.com/themakerrobot/openpibo-tools/archive/refs/tags/${T_VERSION}.zip
wget -O openpibo-files.zip https://github.com/themakerrobot/openpibo-files/archive/refs/tags/${F_VERSION}.zip

sudo rm openpibo-files openpibo-tools -rf
unzip openpibo-files.zip
unzip openpibo-tools.zip

mv openpibo-files-${F_VERSION} openpibo-files
mv openpibo-tools-${T_VERSION} openpibo-tools

sudo chown pi:pi -R openpibo-files openpibo-tools
sudo rm openpibo-files.zip openpibo-tools.zip

sudo shutdown -r now
