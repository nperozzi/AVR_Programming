
BOSS_SITE = "http://www.cartalk.com/content/boss-redirect"
XKCD = "http://xkcd.com/353/"

SERIAL_PORT = "COM7"
BAUD_RATE = 9600

import serial
import webbrowser

sp = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout = 5)
sp.flush()

while(1):
    response = sp.read(1)
    if response == "0":
        print ("Got OK Byte. Waiting for button press.")
    elif response == b"X":   #the b indicates that it is a binary char
        print ("Got Boss Byte! Alarm!")
        webbrowser.open(BOSS_SITE)
    else:
        print ("Got nothing. Still waiting.")
