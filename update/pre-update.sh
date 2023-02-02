#!/bin/bash
VER=$(cat /home/pi/.OS_VERSION)

if [ "$VER" != "OPENPIBO_230201" ]
then
  sudo apt install shellinabox -y
  sudo pip3 install -U openpibo-python

  wget -O openpibo-os.zip https://github.com/themakerrobot/openpibo-os/archive/refs/tags/230201v1.zip
  unzip openpibo-os.zip
  sudo rm -rf openpibo-os openpibo-os.zip
  mv openpibo-os-230201v1 openpibo-os

  sudo rm -rf /etc/default/shellinabox
  echo 'SHELLINABOX_DAEMON_START=1' >> /home/pi/shellinabox
  echo 'SHELLINABOX_PORT=50001' >> /home/pi/shellinabox
  echo 'SHELLINABOX_USER=pi' >> /home/pi/shellinabox
  echo 'SHELLINABOX_GROUP=pi' >> /home/pi/shellinabox
  echo 'SHELLINABOX_ARGS="--no-beep --disable-ssl --disable-ssl-menu"' >> /home/pi/shellinabox
  sudo mv -f /home/pi/shellinabox /etc/default/shellinabox

  echo "OPENPIBO_230201" > /home/pi/.OS_VERSION
fi
sudo rm -rf /home/pi/update
