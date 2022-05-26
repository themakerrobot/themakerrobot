from ssd1306_oled import *
from PIL import ImageFont, Image, ImageDraw


spi = busio.SPI(11, 10, 9)
rst_pin = digitalio.DigitalInOut(board.D24) # any pin!
cs_pin = digitalio.DigitalInOut(board.D8)    # any pin!
dc_pin = digitalio.DigitalInOut(board.D23)    # any pin!

#font_path = "your font_path"
oled = ssd1306.SSD1306_SPI(128,64, spi, dc_pin, rst_pin, cs_pin)
#font = ImageFont.truetype(font_path, 15)

#image = Image.new("1", (128,64))
#draw = ImageDraw.Draw(image)
#draw.text((5,5), "Good morning", font=font, fill=255)

image = Image.open("clear.png").convert("1")
oled.image(image)

oled.show()
