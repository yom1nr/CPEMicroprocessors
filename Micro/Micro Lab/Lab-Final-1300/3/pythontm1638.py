# TinyPICO / ESP32
import tm1638
from machine import Pin
tm = tm1638.TM1638(stb=Pin(19), clk=Pin(18), dio=Pin(5))

# every 2nd LED on
tm.leds(0b01010101)

# all LEDs off
tm.leds(0)

# segments
#tm.show('cool')
tm.show('b6515652')
#tm.number(-1234567)
#tm.number('6515652')
tm.number(5678,4)
tm.hex(0xdeadbeef)

# dim both LEDs and segments
tm.brightness(0)

# all LEDs and segments off
tm.clear()

# get which buttons are pressed on LED&KEY module
tm.keys()

# get which buttons are pressed on QYF-TM1638 module
tm.qyf_keys()