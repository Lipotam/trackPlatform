dofile("uart_config.lua")
dofile("wifi_config.lua")
 
print("ESP8266 was started")

uart.write(uart_id, "I'm ready, Milord!")

collectgarbage()
