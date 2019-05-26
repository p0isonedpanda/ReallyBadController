import serial
import mysql.connector as mariadb
import json
from logger import *
import settings

set_logging(3)

def main():
    # connect to arduino
    try:
        arduino = serial.Serial('/dev/ttyACM0', 9600)
        log('arduino connected')
    except:
        log('arduino not found, exiting...', 3)
        return

    # connect to mariadb
    try:
        conn = mariadb.connect(user=settings.username, password=settings.password, database="badcontroller")
        cursor = conn.cursor(buffered=True)
        log('connected to mariadb')
    except:
        log('couldn\'t connect to mariadb, exiting...', 3)
        return

    # main loop
    while True:
        try:
            inputs = json.loads(arduino.readline())
            log(inputs)
            
            query = 'UPDATE inputs SET usonic = ' + str(inputs['usonic'])
            query += ', ldr = ' + str(inputs['ldr'])
            query += ', temp = ' + str(inputs['temp'])
            query += ', joyx = ' + str(inputs['joyx'])
            query += ', joyy = ' + str(inputs['joyy'])
            query += ', button = ' + str(inputs['button'])
            cursor.execute(query)
            conn.commit()

        except (json.decoder.JSONDecodeError, UnicodeDecodeError):
            log('couln\'t parse json for some reason idunno, will try again', 2)

if __name__ == '__main__':
    main()
