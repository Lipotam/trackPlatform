import sys
from commands import commands

def handle(serial_port, command):
    if command == 0:
      sys.exit(0)

    serial_port.write(commands.get(command))
