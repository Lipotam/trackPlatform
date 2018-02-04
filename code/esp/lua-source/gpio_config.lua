print("Configuring GPIO")

-- use GPIO2 pin (with pin num = 4)
diode_pin = 4
gpio.mode(diode_pin, gpio.OUTPUT)
gpio.write(diode_pin, gpio.LOW)

print("GPIO was configured")

collectgarbage()
