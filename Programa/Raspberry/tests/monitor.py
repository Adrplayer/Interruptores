import serial
import time

com = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, timeout=1, write_timeout=1)
print(com.name)

if __name__ == '__main__':
    while True:
        time.sleep(1)
        raw_string_b = com.readline()
        if raw_string_b != b'':
            raw_string_s = raw_string_b.decode()
            print(raw_string_b)
            print(raw_string_s)
    com.close()
