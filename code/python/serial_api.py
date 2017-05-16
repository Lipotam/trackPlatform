import serial

class SerialPort:
    def __init__(self, port):
        self.init_port(port)
        self.set_baudrate(9600)

    def init_port(self, port):
        self.serial_port = serial.Serial(port, timeout=1)

    def set_baudrate(self, baudrate):
        self.serial_port.baudrate = baudrate

    def write(self, msg):
        self.serial_port.write(msg.encode('utf-8'))

    def read(self):
        tdata = self.serial_port.readline()
        return tdata.decode('utf-8')
