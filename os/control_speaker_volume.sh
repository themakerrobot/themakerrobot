#!/bin/bash

function WARN() {
  echo "$1, sudo ./control_speaker_volume.sh VOLUME(0-100)"
}

if [ -z "$1" ]; then
  WARN "Require VOLUME"
  exit -1
fi

# Check is_num()
RET=${1//[0-9]/}
if [ -n "$RET" ]; then
  WARN "VOLUME must be number"
  exit 0
fi

if [ $1 -gt 100 ]; then
  WARN "VOLUME <= 100"
  exit 0
fi

amixer -c Headphones sset Headphone $1%
