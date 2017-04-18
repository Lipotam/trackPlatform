from serial_api import SerialPort
import menu

def select_port():
    port = input('Port: ')
    return port

def main():
    serial_port = SerialPort(select_port())
    menu.menu(serial_port)

if __name__ == '__main__':
    main()
