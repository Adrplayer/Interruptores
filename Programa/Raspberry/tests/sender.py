import serial.rs485
import time

com = serial.rs485.RS485(port='/dev/ttyUSB0', baudrate=9600)

print(com.name)

if __name__ == '__main__':
    com.rs485_mode = serial.rs485.RS485Settings(rts_level_for_rx=True,rts_level_for_tx=False)
    com.write('EEEEf'.encode())
    print("sended")
    time.sleep(1)

    com.close()
