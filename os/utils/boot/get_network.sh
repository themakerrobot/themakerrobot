#!/bin/bash
# 20220503

_SN=$(grep "Serial" /proc/cpuinfo | awk '{print $3}')
SN=${_SN: -8}
W0=$(ifconfig wlan0 2>/dev/null| grep "inet " | awk '{print $2}') || true
if [ "$W0" = "" ];then
  S0=""	
else
  S0=$(iw wlan0 info | grep ssid | awk '{print $2}') || true
fi
W1=$(ifconfig wlan1 2>/dev/null| grep "inet " | awk '{print $2}') || true
if [ "$W1" = "" ];then
  S1=""
else
  S1=$(iw wlan0 info | grep ssid | awk '{print $2}') || true
fi

echo $W0,$S0,$W1,$S1,$SN
