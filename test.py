# Import Python System Libraries
import time
# Import Blinka Libraries
import busio
from digitalio import DigitalInOut, Direction, Pull
import board
# Import RFM9x
import adafruit_rfm9x
import matplotlib.pyplot as plt
import matplotlib.animation as animation
from matplotlib import style
style.use('fivethirtyeight')

fig = plt.figure()
axl = fig.add_subplot(1,1,1)

def animate(graphdata, i):
    axl.clear()
    axl.plot(graph_data,i)
    
ani = animation.FuncAnimation(fig, animate, interval = 1)
plt.show()
# Configure LoRa Radio
CS = DigitalInOut(board.CE1)
RESET = DigitalInOut(board.D25)
spi = busio.SPI(board.SCK, MOSI=board.MOSI, MISO=board.MISO)
rfm9x = adafruit_rfm9x.RFM9x(spi, CS, RESET, 921.2)
rfm9x.tx_power = 14
prev_packet = None
i=0;
while True:
    packet = None
    i=i+1
    packet = rfm9x.receive()
    print(packet);
    animate(graphdata, i)

