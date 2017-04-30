from serial_api import SerialPort
import menu
import controller

def select_port():
    port = input('Port: ')
    return port

def main():
    serial_port = SerialPort(select_port())
    while 1:
        menu.show_menu()
        command = input("Choose: ")
        controller.handle(serial_port, int(command))

if __name__ == '__main__':
    main()
