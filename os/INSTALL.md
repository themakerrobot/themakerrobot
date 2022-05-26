+ 운영체제 이미지
  - Raspberry Pi OS Lite
  - https://downloads.raspberrypi.org/raspios_lite_armhf/images/raspios_lite_armhf-2020-12-04/2020-12-02-raspios-buster-armhf-lite.zip

+ 설치 방법
  - git clone https://github.com/themakerrobot/openpibo-os
  - sudo ./install.sh

+ 라즈베리파이 설정
  - sudo raspi-config
    + Localisation Options
      - Change Locale: ko_KR.UTF-8 UTF-8
      - Change Time Zone: Asia / Seoul
    + Interfacing Options
      - Camera Enable
      - SSH Enable
      - VNC Enable
      - SPI Enable
      - Serial
        + Would you like a login shell to be accessible over serial? No
        + Would you like the serial port hardware to be enabled? Yes
    + Advanced Options
      - Audio: 2. Headphones

+ 기타 설정
  - wifi 
    + 절전해제
      - echo "options 8192cu rtw_power_mgnt=0 rtw_enusbss=0" > /etc/modprobe.d/8192cu.conf
    + 간헐적 끊김?
      - /etc/wpa_supplicant/wpa_supplicant.conf > country=GB로 변경
  - bluetooth
    + 비활성화
      - sudo systemctl disable hciuart.service
      - sudo service bluetooth stop
      - sudo update-rc.d bluetooth stop
      - sudo update-rc.d bluetooth remove
  - usb extension
    + mount
      - sudo apt install usbmount -y
      - /etc/usbmount/usbmount.conf 수정 (FS_MOUNTOPTIONS="" --> FS_MOUNTOPTIONS="-fstype=vfat,iocharset=utf8")
      - /lib/systemd/system/udev.service (PrivateMounts=yes --> PrivateMounts=no)
  - splash 설정
    + sudo cp samplelogo.png /usr/share/plymouth/themes/pix/splash.png
  - 마이크 설정 참고
    + .asoundrc
      - local -> /home/pi/.asoundrc
      - global -> /etc/asound.conf  #/usr/share/alsa/alsa.conf
  - 마이크 볼륨 설정
    + sudo ./control_mic_volume.sh

+ 부팅 시, 초기화
  - rc.local
<pre><code>
_IP=$(hostname -I) || true
if [ "$_IP" ]; then
  printf "My IP address is %s\n" "$_IP"
fi
/home/pi/openpibo/utils/boot/start.sh  <-- 추가
exit 0
</code></pre>
