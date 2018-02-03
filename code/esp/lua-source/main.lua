print("Hello from LUA & arduino")

wifi.setmode(wifi.STATIONAP)
cfg={}
cfg.ssid="ESPTEST"
cfg.pwd="0987654321"
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
  sv:listen(333, function(conn)
    conn:on("receive", receiver)
    conn:send("Hello!")
  end)
end
 
print("Started.")

cfg=nil
collectgarbage()
