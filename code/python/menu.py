import sys
import router_controller
from commands import controllers

def choose_menu(menu_id, serial_port):
    if(menu_id == 0):
        sys.exit(0)
    if(menu_id == 1):
        return show_movement_menu(serial_port)
    if(menu_id == 2):
        return show_sensors_menu(serial_port)
    if(menu_id == 3):
        return show_servo_menu(serial_port)

def show_menu():
    print("1 - Moving\n")
    print("2 - Sensors\n")
    print("3 - Servo\n")
    print("0 - Exit\n")

def show_movement_menu(serial_port):
    while 1:
        print("1 - Move Forward\n")
        print("2 - Move Left\n")
        print("3 - Move Right\n")
        print("4 - Move Back\n")
        print("5 - Stop\n")
        print("6 - Move Forward (set speed)\n")
        print("7 - Move Forward (set time)\n")
        print("8 - Move Back (set speed)\n")
        print("9 - Set track speed (choose track, set speed)\n")
        print("0 - Back\n")
        command = input("Choose: ")
        if(int(command) == 0):
            return
        router_controller.handle(serial_port, int(command), controllers.get('movement'))


def show_sensors_menu(serial_port):
    while 1:
        print("1 - Get distance from single sensor\n")
        print("2 - Get distance from all sensors\n")
        print("3 - Get line from single sensor\n")
        print("4 - Get lines from single sensor\n")
        print("0 - Back\n")
        command = input("Choose: ")
        if(int(command) == 0):
            return
        router_controller.handle(serial_port, int(command), controllers.get('sensors'))

def show_servo_menu(serial_port):
    while 1:
        print("1 - Set horizontal angle\n")
        print("2 - Set vertical angle\n")
        print("3 - Set horizontal and vertical angles\n")
        print("4 - Get coordinates\n")
        print("0 - Back\n")
        command = input("Choose: ")
        if(int(command) == 0):
            return
        router_controller.handle(serial_port, int(command), controllers.get('servo'))
