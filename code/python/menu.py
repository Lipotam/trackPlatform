import sys

def menu(serial_port):
    while 1:
        print("1 - Move Forward\n")
        print("2 - Move Left\n")
        print("3 - Move Right\n")
        print("4 - Move Back\n")
        print("0 - Exit\n")
        command = input("Choose: ")
        handle(serial_port, int(command))

def handle(serial_port, command):
    if command == 0:
      sys.exit(0)

    switcher = {
        1: '\001\001',
        2: '\001\002',
        3: '\001\003'
    }
    serial_port.write(switcher.get(command))
