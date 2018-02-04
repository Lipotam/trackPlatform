-- configure modules
dofile("gpio_config.lua")
dofile("uart_config.lua")
dofile("wifi_config.lua")
 
print("ESP8266 was started")

uart_decive_ready_callback()

collectgarbage()
