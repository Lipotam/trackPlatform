wifi.setmode(wifi.STATIONAP)
local cfg={}
cfg.ssid="TrackPlatformWiFi"
cfg.pwd="1234567890"
cfg_tcp_port = 333
wifi.ap.config(cfg)
 
--Create Server
sv=net.createServer(net.TCP)
 
function receiver(sck, data)    
  -- Print received data
  print(data)
  -- Send reply
  sck:send("Recived: "..data)
end
 
if sv then
  sv:listen(cfg_tcp_port, function(conn)
  -- todo: rewrite
    conn:on("receive", receiver)
    conn:send("Hello!")
  end)
end
 
print("Wi-Fi was configured")

cfg=nil
collectgarbage()
