#!/bin/bash
VERSION="OPENPIBO_230204_V2"
OPENPIBO_OS_VERSION="230204v2"
OPENPIBO_FILES_VERSION="230204v1"
PRIO_VER=$(cat /home/pi/.OS_VERSION)

if [ "$PRIO_VER" != "$VERSION" ]
then
  sudo echo "#20:200,50,50!" > /dev/ttyS0
  sleep 0.5
  sudo echo "#20:0,0,0!" > /dev/ttyS0
  sleep 0.5
  sudo echo "#20:200,50,50!" > /dev/ttyS0

  sudo apt-get install shellinabox -y
  sudo pip3 install -U openpibo-python

  cd /home/pi
  wget -O openpibo-os.zip https://github.com/themakerrobot/openpibo-os/archive/refs/tags/$OPENPIBO_OS_VERSION.zip
  unzip openpibo-os.zip
  sudo rm -rf openpibo-os openpibo-os.zip
  mv openpibo-os-$OPENPIBO_OS_VERSION openpibo-os

  wget -O openpibo-files.zip https://github.com/themakerrobot/openpibo-files/archive/refs/tags/$OPENPIBO_FILES_VERSION.zip
  unzip openpibo-files.zip
  sudo rm -rf openpibo-files openpibo-files.zip
  mv openpibo-files-$OPENPIBO_FILES_VERSION openpibo-files

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
