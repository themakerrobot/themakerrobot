#!/bin/bash
VERSION="OPENPIBO_230321_V1"
OPENPIBO_OS_VERSION="230321v1"
OPENPIBO_FILES_VERSION="230320v1"

PRIO_OS_VER=$(cat /home/pi/.OS_VERSION)
PRIO_TOOLS_VER=$(cat /home/pi/openpibo-os/VERSION)
PRIO_FILES_VER=$(cat /home/pi/openpibo-files/VERSION)

sudo echo "#20:200,200,200!" > /dev/ttyS0
sleep 0.5

REBOOT="FALSE"
if [ "$PRIO_OS_VER" != "$VERSION" ]
then
  sudo pip3 install -U openpibo-python
  echo $VERSION > /home/pi/.OS_VERSION
  REBOOT="TRUE"
fi

if [ "$PRIO_TOOLS_VER" != "$OPENPIBO_OS_VERSION" ]
then
  cd /home/pi
  wget -O openpibo-os.zip https://github.com/themakerrobot/openpibo-os/archive/refs/tags/$OPENPIBO_OS_VERSION.zip
  unzip openpibo-os.zip
  sudo rm -rf openpibo-os openpibo-os.zip
  mv openpibo-os-$OPENPIBO_OS_VERSION openpibo-os
  REBOOT="TRUE"
fi

if [ "$PRIO_FILES_VER" != "$OPENPIBO_FILES_VERSION" ]
then
  cd /home/pi
  wget -O openpibo-files.zip https://github.com/themakerrobot/openpibo-files/archive/refs/tags/$OPENPIBO_FILES_VERSION.zip
  unzip openpibo-files.zip
  sudo rm -rf openpibo-files openpibo-files.zip
  mv openpibo-files-$OPENPIBO_FILES_VERSION openpibo-files
  REBOOT="TRUE"
fi

SHELLINABOX_CHECK=$(shellinaboxd --version)
if [ "$?" != "0" ]
then
  sudo apt-get install shellinabox -y
  sudo rm -rf /etc/default/shellinabox
  echo 'SHELLINABOX_DAEMON_START=1' >> /home/pi/shellinabox
  echo 'SHELLINABOX_PORT=50001' >> /home/pi/shellinabox
  echo 'SHELLINABOX_USER=pi' >> /home/pi/shellinabox
  echo 'SHELLINABOX_GROUP=pi' >> /home/pi/shellinabox
  echo 'SHELLINABOX_ARGS="--no-beep --disable-ssl --disable-ssl-menu"' >> /home/pi/shellinabox
  sudo mv -f /home/pi/shellinabox /etc/default/shellinabox
  REBOOT="TRUE"
fi

sudo rm -rf /home/pi/update
if [ "$REBOOT" = "TRUE" ]
then
  sudo echo "#20:150,50,50!" > /dev/ttyS0
  sleep 0.5
  sudo echo "#20:0,0,0!" > /dev/ttyS0
  sleep 0.5
  sudo echo "#20:150,50,50!" > /dev/ttyS0
  sleep 0.5
  sudo echo "#20:0,0,0!" > /dev/ttyS0
  sudo shutdown -r now
else
  sudo echo "#20:50,50,150!" > /dev/ttyS0
  sleep 0.5
  sudo echo "#20:0,0,0!" > /dev/ttyS0
  sleep 0.5
  sudo echo "#20:50,50,150!" > /dev/ttyS0
  sleep 0.5
  sudo echo "#20:0,0,0!" > /dev/ttyS0
fi
