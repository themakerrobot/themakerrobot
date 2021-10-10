#!/bin/bash

VERSION='#20211010v1'

echo "OS update" $VERSION
echo -n "Remove config.js? [y/N] "
read
if [[ ! "$REPLY" =~ ^(yes|y|Y)$ ]]; then
  echo "not Removed config.json"
else
  echo "Removed config.json"
  rm /home/pi/config.json
fi

echo "Update openpibo-python"
#pip3 install --upgrade openpibo-python -y

MODEL=$(tr -d '\0' </proc/device-tree/model)
echo $MODEL "detected"
if [[ $MODEL == *"Pi 3"* ]];then
  cat > /etc/modprobe.d/snd-i2smic-rpi.conf<<EOF
options snd-i2smic-rpi rpi_platform_generation=1
EOF
fi

echo -n "REBOOT NOW? [y/N] "
read
if [[ ! "$REPLY" =~ ^(yes|y|Y)$ ]]; then
  echo "Exiting without reboot."
  exit 0
fi

echo "Reboot started..."
reboot
exit 0
