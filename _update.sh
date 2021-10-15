#!/bin/bash

MODEL=$(tr -d '\0' </proc/device-tree/model)
echo $MODEL "detected"
if [[ $MODEL == *"Pi 3"* ]];then
  PIMODEL_SELECT=1
fi
if [[ $MODEL == *"Pi 4"* ]];then
  PIMODEL_SELECT=2
fi

git clone https://github.com/adafruit/Raspberry-Pi-Installer-Scripts.git

# Build and install the module
cd Raspberry-Pi-Installer-Scripts/i2s_mic_module
make clean
make
make install

  cat > /etc/modules-load.d/snd-i2smic-rpi.conf<<EOF
snd-i2smic-rpi
EOF
  cat > /etc/modprobe.d/snd-i2smic-rpi.conf<<EOF
options snd-i2smic-rpi rpi_platform_generation=$PIMODEL_SELECT
EOF

echo "Done..."
cd ../../
rm -rf Raspberry-Pi-Installer-Scripts

echo -n "REBOOT NOW? [y/N] "
read
if [[ ! "$REPLY" =~ ^(yes|y|Y)$ ]]; then
  echo "Exiting without reboot."
  exit 0
fi

echo "Reboot started..."
reboot
exit 0
