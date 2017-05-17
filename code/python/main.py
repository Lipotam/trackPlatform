from serial_api import SerialPort
import menu
import _thread

def select_port():
    port = input('Port: ')
    return port

def main():
    serial_port = SerialPort(select_port())
    _thread.start_new_thread(read, (serial_port, ))
    while 1:
        menu.show_menu()
        command = input("Choose: ")
        menu.choose_menu(int(command), serial_port)

def read(serial_port):
    while 1:
        print(serial_port.read())

if __name__ == '__main__':
    main()
