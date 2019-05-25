import serial
import json
import _thread
from flask import Flask
from flask_restful import Resource, Api
from logger import *

set_logging(3)
app = Flask(__name__)
api = Api(app)
inputs = None

def main():
    global inputs

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

class InputAPI(Resource):
    def get(self):
        return {
                'usonic' : inputs['usonic'],
                'ldr' : inputs['ldr'],
                'temp' : inputs['temp'],
                'joyx' : inputs['joyx'],
                'joyy' : inputs['joyy'],
                'button' : inputs['button']
               }

def api_thread():
    app.run(host='0.0.0.0', port=5000, debug=True)

if __name__ == '__main__':
    api.add_resource(InputAPI, '/')
    api_thread()
    _thread.start_new_thread(main, ())
