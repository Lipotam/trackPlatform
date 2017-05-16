import sys
from commands import commands
from commands import delimetr

def handle(serial_port, command):
    if command == 0:
      sys.exit(0)
    sendable_command = commands.get(command)
    if(command == 6 or command == 8):
        sendable_command += choose_speed()
    if(command == 7):
        sendable_command += choose_time()
    if(command == 9):
        sendable_command += choose_track()
        sendable_command += choose_speed()
    serial_port.write(sendable_command)

def choose_time():
    return str(input("Input time(ms): ")) + delimetr

def choose_speed():
    return str(input("Input speed(0-255): "))  + delimetr

def choose_track():
    return str(input("Choose track(0 - left, 1 - right): ")) + delimetr
