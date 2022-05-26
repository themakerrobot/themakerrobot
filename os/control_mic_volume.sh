#!/bin/bash

# sudo alsamixer --> F6 --> snd_rpi_i2s_card --> F5 
arecord -D dmic_sv -c2 -r 44100 -f S32_LE -d 1 -t wav -V streo -v file.wav
rm file.wav

#cn=`arecord -l | grep sndrpii2scard`
#cn="${cn:5:1}"
#echo -e "\n\n ## I2S CARD Number is " $cn
#amixer -c $cn sset Boost 196
amixer -c sndrpii2scard sset Boost 77%
