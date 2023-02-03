#!/bin/bash
VERSION="OPENPIBO_230203_V1"

PRIO_VER=$(cat /home/pi/.OS_VERSION)

if [ "$PRIO_VER" != "$VERSION" ]
then
  sudo echo "#20:200,50,50!" > /dev/ttyS0
  sleep 0.5
  sudo echo "#20:0,0,0!" > /dev/ttyS0
  sleep 0.5
  sudo echo "#20:200,50,50!" > /dev/ttyS0

  sudo apt install shellinabox -y
  sudo pip3 install -U openpibo-python

  cd /home/pi
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

  echo $VERSION > /home/pi/.OS_VERSION
  sudo echo "#20:0,0,0!" > /dev/ttyS0
  sudo rm -rf /home/pi/update
  sudo shutdown -r now
else
  sudo echo "#20:50,200,50!" > /dev/ttyS0
  sleep 0.5
  sudo echo "#20:0,0,0!" > /dev/ttyS0
  sleep 0.5
  sudo echo "#20:50,200,50!" > /dev/ttyS0
  sleep 0.5
  sudo echo "#20:0,0,0!" > /dev/ttyS0
  sudo rm -rf /home/pi/update
fi
