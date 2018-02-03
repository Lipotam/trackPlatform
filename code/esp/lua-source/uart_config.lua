print("Configuring UART")

uart_id = 0
uart_callback_name = "data"          -- do not rename, otherwise app will crash
uart_delim = "\n"

local cfg = {}
cfg.id = uart_id
cfg.speed = 115200
cfg.databits = 8
cfg.parity = uart.PARITY_NONE
cfg.stopbits = uart.STOPBITS_1
cfg.echo = 0    -- disable uart echo

uart.setup(cfg.id, 
    cfg.speed,
    cfg.databits,
    cfg.parity,
    cfg.stopbits,
    cfg.echo
)

function uart_callback(data)
    -- todo: rewrite
    print("receive from uart:", data)
    if data=="quit\r\n" then
      uart.on(uart_callback_name) -- unregister callback function
    end
end

uart.on(uart_callback_name, uart_delim, uart_callback, 0)

print("UART was configured")

cfg = nil
uart_callback = nil
collectgarbage()
