import serial
import json
from logger import *

set_logging(3)

def main():
    try:
        arduino = serial.Serial('/dev/ttyACM0', 9600)
        log('arduino connected')
    except:
        log('arduino not found, exiting...', 3)
        return

    # main loop
    while True:
        try:
            inputs = json.loads(arduino.readline())
            log(inputs)
        except (json.decoder.JSONDecodeError, UnicodeDecodeError):
            log('couln\'t parse json for some reason idunno, will try again', 2)

if __name__ == '__main__':
    main()
