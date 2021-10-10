#!/bin/bash

VERSION='#20211010v1'

echo "OS update" $VERSION
echo -n "Remove config.js? [y/N] "
read
if [[ ! "$REPLY" =~ ^(yes|y|Y)$ ]]; then
  echo "Not removed config.json"
else
  echo "Removed config.json"
  rm /home/pi/config.json
fi

echo -n "Update openpibo-python package? [y/N] "
read
if [[ ! "$REPLY" =~ ^(yes|y|Y)$ ]]; then
  echo "Not update openpibo-python"
else
  echo "Update openpibo-python package"
  pip3 install --upgrade openpibo-python -y
fi

echo -n "Update MIC setting? [y/N] "
read
if [[ ! "$REPLY" =~ ^(yes|y|Y)$ ]]; then
  echo "Not update MIC setting"
else
  echo "Update openpibo-python package"
  MODEL=$(tr -d '\0' </proc/device-tree/model)
  echo $MODEL "detected"
if [[ $MODEL == *"Pi 3"* ]];then
cat > /etc/modprobe.d/snd-i2smic-rpi.conf<<EOF
options snd-i2smic-rpi rpi_platform_generation=1
EOF
fi
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
