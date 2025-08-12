from machine import Pin, SPI
import ST7735

# Initialize LCD
spi = SPI(0, baudrate=8000000, polarity=0, phase=0, sck=Pin(18), mosi=Pin(19), miso=Pin(16))
lcd = ST7735.ST7735(spi, rst=6, ce=17, dc=3)
backlight = Pin(2, Pin.OUT)

# Turn backlight on
backlight.high()
lcd.reset()
lcd.begin()

# Fills the screen with a green color
#lcd.fill_screen(lcd.rgb_to_565(r, g, b))

# Dimensions de l'écran
SCREEN_WIDTH = 160
SCREEN_HEIGHT = 128

# Taille police par défaut
CHAR_WIDTH = 8
CHAR_HEIGHT = 16

# Texte à afficher
line1 = "Qui pour me donner des"
line2 = "cours gratuits ? "

# Fonction pour calculer X centré
def center_x(text):
    return (SCREEN_WIDTH - len(text) * CHAR_WIDTH) // 2

# Calcul positions Y pour centrer verticalement
total_text_height = CHAR_HEIGHT * 2  # 2 lignes
start_y = (SCREEN_HEIGHT - total_text_height) // 2

y1 = start_y
y2 = start_y + CHAR_HEIGHT

# Affichage
lcd.fill_screen(lcd.rgb_to_565(0, 255, 0))
lcd.p_string(center_x(line1), y1, line1)
lcd.p_string(center_x(line2), y2, line2)