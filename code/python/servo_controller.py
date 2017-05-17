from commands import delimetr
from commands import servo_commands


def handle(command):
    sendable_command = servo_commands.get(command)
    if(command == 1 or command == 2):
        sendable_command += choose_angle()
    if(command == 3):
        sendable_command += choose_angle()
        sendable_command += choose_angle()
    return sendable_command

def choose_angle():
    return str(input("Input angle: ")) + delimetr
