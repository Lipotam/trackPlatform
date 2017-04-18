import serial

class SerialPort:
    def __init__(self, port):
        self.init_port(port)
        self.set_baundrate(9600)

    def init_port(self, port):
        self.serial_port = serial.Serial(port)

    def set_baundrate(self, baundrate):
        self.serial_port.baudrate = baudrate

    def write(self, msg):
        self.serial_port.write(msg)

    def read(self):
        self.serial_port.read(size=1)
