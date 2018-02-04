print("Configuring GPIO")

DEFAULT_GPIO_SEQ = {1000000, 5000}
gpio_seq_cfg_us = DEFAULT_GPIO_SEQ

-- use GPIO2 pin (with pin num = 4)
local diode_pin = 4
gpio.mode(diode_pin, gpio.OUTPUT)

-- asynchronous diode flashes 
local function start_gpio()
    gpio.serout(diode_pin, gpio.HIGH, gpio_seq_cfg_us, 1, start_gpio)
end

-- start flashes
start_gpio()

print("GPIO was configured")

collectgarbage()
