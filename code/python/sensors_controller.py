from commands import delimetr
from commands import sensors_commands


def handle(command):
    sendable_command = sensors_commands.get(command)
    if(command == 1):
        sendable_command += choose_distance()
    if(command == 3):
        sendable_command += choose_line()
    return sendable_command

def choose_line():
    return str(input("Choose line(1-5): ")) + delimetr

def choose_distance():
    return str(input("Choose distance sensor(1-5): "))  + delimetr
