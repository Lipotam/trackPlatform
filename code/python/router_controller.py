import sys
from commands import controllers
import movement_controller
import sensors_controller
import servo_controller

def handle(serial_port, command, controller_id):
    sendable_command = controller_id
    command_part_from_controller = ''
    if(controller_id == controllers.get('movement')):
        command_part_from_controller = movement_controller.handle(command)
    if(controller_id == controllers.get('sensors')):
        command_part_from_controller = sensors_controller.handle(command)
    if(controller_id == controllers.get('servo')):
        command_part_from_controller = servo_controller.handle(command)
    sendable_command += command_part_from_controller
    serial_port.write(sendable_command)
