# 20220517
import time,json,subprocess,os
from openpibo.oled import Oled
from openpibo.device import Device

def disp(v):
  wip, ssid, sn = v[2] if v[0] == "" else v[0], v[3] if v[1] == "" else v[1], v[4]
  o.set_font(size=12)
  o.draw_text((0, 5), f'SN: {sn}')
  o.draw_text((0,25), f'I P: {wip.strip()}')
  o.draw_text((0,45), f'AP: {ssid}')
  o.show()

if __name__ == "__main__":
  try:
    with open('/home/pi/config.json', 'r') as f:
      tmp = json.load(f)
      Device().send_raw('#23:{}!'.format(tmp['eye']))
  except Exception as ex:
      pass

  try:
    o = Oled()
    o.clear()
    o.set_font(size=20)
    o.draw_text((5,20), 'THE MAKER')
    o.show()
    
    os.system('gpio mode 7 out;gpio write 7 1;/boot/wifi-ap-sta start')

    text = 'PIBO ROBOT'
    for i in range(1,11):
      o.clear()
      o.set_font(size=i*2-2)
      o.draw_text((10,20), text[10-i:])
      o.show()
      time.sleep(0.3)
    time.sleep(5)
    o.clear()

    for i in range(1,15):
      data = subprocess.check_output(['/boot/get_network.sh']).decode('utf-8').strip('\n').split(',')
      if data[0] != '' or data[2] != '':
        break

      o.draw_text((15,20), 'Ready... ({})'.format(i))
      o.show()
      time.sleep(1.7)
      o.clear()
      time.sleep(0.3)
    disp(data)
  except Exception as ex:
    with open('/home/pi/boot_errmsg', 'w') as f:
      f.write(f'[{time.ctime()}]\n{ex}')
