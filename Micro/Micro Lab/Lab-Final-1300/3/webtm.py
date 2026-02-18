from machine import Pin
import network
import socket
import time
import tm1638

# Initialize TM1638
tm = tm1638.TM1638(stb=Pin(19), clk=Pin(18), dio=Pin(5))

# WiFi credentials
ssid = 'Tucklyz'
password = 'pond17399'

tm.show('b6515652')
tm.number(5678,4)
tm.hex(0xdeadbeef)

wlan = network.WLAN(network.STA_IF)

# Function to connect to Wi-Fi network
def cnctWifi():
    wlan.active(True)
    print('Attempting to connect to the network...')
    wlan.connect(ssid, password)        
    max_wait = 10
    while max_wait > 0 and not wlan.isconnected():
        max_wait -= 1
        print('waiting for connection...')
        time.sleep(1)
    
    # Manage connection errors
    if not wlan.isconnected():
        print('Network Connection has failed')
    else:
        print('Connected to the network successfully.')
        status = wlan.ifconfig()
        print('Enter this address in browser = ' + status[0])

# HTML + CSS for webpage
html = """<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>MicroPython Web Server</title>
  <style>
    html { font-family: Arial; display: inline-block; margin: 0px auto; text-align: center; }
    h1 { font-family: Arial; color: #2551cc; }
    .button1, .button2 {
      -webkit-border-radius: 10; -moz-border-radius: 10; border-radius: 10px;
      font-family: Arial; color: #ffffff; font-size: 30px;
      padding: 10px 20px 10px 20px; text-decoration: none; display: inline-block; margin: 5px;
    }
    .button1 { background: #339966; }
    .button2 { background: #993300; }
  </style>
</head>
<body>
  <h1>MicroPython Web Server</h1>
  <p>GPIO States:</p>
  <p>GPIO 1 - State: %s</p>
  <p>
    <a href="/GPIO1/on"><button class="button1">GPIO 1 ON</button></a>
    <a href="/GPIO1/off"><button class="button2">GPIO 1 OFF</button></a>
  </p>
  <p>GPIO 2 - State: %s</p>
  <p>
    <a href="/GPIO2/on"><button class="button1">GPIO 2 ON</button></a>
    <a href="/GPIO2/off"><button class="button2">GPIO 2 OFF</button></a>
  </p>
  <p>GPIO 3 - State: %s</p>
  <p>
    <a href="/GPIO3/on"><button class="button1">GPIO 3 ON</button></a>
    <a href="/GPIO3/off"><button class="button2">GPIO 3 OFF</button></a>
  </p>
  <p>GPIO 4 - State: %s</p>
  <p>
    <a href="/GPIO4/on"><button class="button1">GPIO 4 ON</button></a>
    <a href="/GPIO4/off"><button class="button2">GPIO 4 OFF</button></a>
  </p>
  <p>GPIO 5 - State: %s</p>
  <p>
    <a href="/GPIO5/on"><button class="button1">GPIO 5 ON</button></a>
    <a href="/GPIO5/off"><button class="button2">GPIO 5 OFF</button></a>
  </p>
  <p>GPIO 6 - State: %s</p>
  <p>
    <a href="/GPIO6/on"><button class="button1">GPIO 6 ON</button></a>
    <a href="/GPIO6/off"><button class="button2">GPIO 6 OFF</button></a>
  </p>
  <p>GPIO 7 - State: %s</p>
  <p>
    <a href="/GPIO7/on"><button class="button1">GPIO 7 ON</button></a>
    <a href="/GPIO7/off"><button class="button2">GPIO 7 OFF</button></a>
  </p>
  <p>GPIO 8 - State: %s</p>
  <p>
    <a href="/GPIO8/on"><button class="button1">GPIO 8 ON</button></a>
    <a href="/GPIO8/off"><button class="button2">GPIO 8 OFF</button></a>
  </p>
</body>
</html>
"""

# Connect to Wi-Fi
cnctWifi()

# Set up socket for web server
addr = socket.getaddrinfo('0.0.0.0', 80)[0][-1]
s = socket.socket()
s.bind(addr)
s.listen(1)

print('listening on', addr)

# Initial GPIO states
GPIO_states = ["OFF"] * 8

# Main loop for handling client requests
while True:
    if not wlan.isconnected():
        print("Connection failed. Trying to reconnect")
        wlan.disconnect()
        cnctWifi()
    if wlan.isconnected():
        try:
            cl, addr = s.accept()
            print('client connected from', addr)
            request = cl.recv(1024)
            print(request)

            request = str(request)
            for i in range(1, 9):
                GPIO_on = request.find('/GPIO{}/on'.format(i))
                GPIO_off = request.find('/GPIO{}/off'.format(i))
                
                if GPIO_on == 6:
                    tm.led(i-1, 1)
                    GPIO_states[i-1] = "ON"

                if GPIO_off == 6:
                    tm.led(i-1, 0)
                    GPIO_states[i-1] = "OFF"

            response = html % tuple(GPIO_states)
            cl.send('HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n')
            cl.send(response)
            cl.close()

        except Exception as e:
            print("Error:", e)
    time.sleep(0.1)
