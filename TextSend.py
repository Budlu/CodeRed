import serial
import time

from twilio.rest import Client

# Sends text to phone number sendTo with content msg
def send_text(sendTo, msg):
    account_sid = 'AC46368bace24b8dd3f7290ecca8d6e664'
    auth_token = 'ab08351b6999fc8f3123da18e1b60332'
    client = Client(account_sid, auth_token)

    message = client.messages.create(body=msg, from_='+12513151614', to=sendTo)

# More functionality for when the fire is detected can be added here
def arduino_activated(pn, msg):
    send_text(pn, msg)
    
BAUD_RATE = 9600
PORT = "COM3"
BYTESIZE = 8
TIMEOUT = 5

serialPort = serial.Serial(port=PORT, baudrate=BAUD_RATE, timeout=TIMEOUT)

PHONE_NUMBER = '+17166501231'
MESSAGE = "Your house is on fire."

# Possible improvement: External machine sends data to Arduino, indicating that it is connected.
# Arduino responds with WAIT_TIME and ACTIVE_FLAG, meaning variables can be held in one place.
WAIT_TIME = 1
ACTIVE_FLAG = 'b'

while(True):
    # Reads current flag
    data = serialPort.read(1)
    character = data.decode("ASCII")

    if (character == ACTIVE_FLAG):
        arduino_activated(PHONE_NUMBER, MESSAGE)
        break
        
    time.sleep(WAIT_TIME)

serialPort.close()
