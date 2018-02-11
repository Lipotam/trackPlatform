print("Configuring Wi-Fi")

local cfg={}
cfg.ssid="TrackPlatformWiFi"
cfg.pwd="1234567890"
cfg_tcp_port = 333

global_socket = nil

-- configure access point
wifi.setmode(wifi.STATIONAP)
wifi.ap.config(cfg)

local ip = wifi.ap.getip()
print("AP IP: " .. ip)
print("AP port: " .. cfg_tcp_port)

-- create TCP server
server = net.createServer(net.TCP)

function receiver(socket, data)
  -- received data UART sending
  uart_write(data)
end

function wifi_write(data)
  if not global_socket then
    print("ERROR: wi-fi socket is null")
  else
    global_socket:send(data)
  end
end

function connected_callback(socket)
  global_socket = socket

  -- set diode flashing sequence
  gpio_seq_cfg_us = {600000, 100000, 200000, 100000}

--  print("Connected")
end

function disconnected_callback(socket)
  -- set diode flashing sequence
  gpio_seq_cfg_us = DEFAULT_GPIO_SEQ
  
--  print("Disonnected")
end

if server then
  server:listen(cfg_tcp_port,
    function(socket)
      socket:on("receive", receiver)
      socket:on("connection", connected_callback)
      socket:on("disconnection", disconnected_callback)
    end
  )
else
  print("ERROR: Cannot create TCP server")
end

print("Wi-Fi was configured")

cfg=nil
collectgarbage()
