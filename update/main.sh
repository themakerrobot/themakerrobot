#!/bin/bash
# echo openpibo OS version is "$(cat /home/pi/.OS_VERSION)"

# F_VERSION="220921v3"
# T_VERSION="220921v4"


# sudo pkill python3
# sudo pkill node

# sudo echo "#20:255,0,0!" >/dev/ttyS0

# cd /home/pi
# sudo pip3 install -U openpibo-python
# sudo pip3 install python-multipart
# sudo npm install --save multer

# sudo echo "#20:0,255,0!" >/dev/ttyS0

# wget -O openpibo-tools.zip https://github.com/themakerrobot/openpibo-tools/archive/refs/tags/${T_VERSION}.zip
# wget -O openpibo-files.zip https://github.com/themakerrobot/openpibo-files/archive/refs/tags/${F_VERSION}.zip

# sudo mv openpibo-files openpibo-files-tmp
# sudo mv openpibo-tools openpibo-tools-tmp

# unzip openpibo-files.zip
# unzip openpibo-tools.zip

# mv openpibo-files-${F_VERSION} openpibo-files
# mv openpibo-tools-${T_VERSION} openpibo-tools

# sudo chown pi:pi -R openpibo-files openpibo-tools
# sudo rm openpibo-files.zip openpibo-tools.zip
# sudo echo "#20:0,0,255!" >/dev/ttyS0

# sudo shutdown -r now &
# sudo rm /home/pi/update -f

# cat /dev/null > /etc/default/shellinabox
# echo 'SHELLINABOX_DAEMON_START=1' >> /etc/default/shellinabox
# echo 'SHELLINABOX_PORT=50001' >> /etc/default/shellinabox
# echo 'SHELLINABOX_USER=pi' >> /etc/default/shellinabox
# echo 'SHELLINABOX_GROUP=pi' >> /etc/default/shellinabox
# echo 'SHELLINABOX_ARGS="--no-beep --disable-ssl --disable-ssl-menu"' >> /etc/default/shellinabox
