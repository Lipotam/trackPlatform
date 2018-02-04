print("Configuring UART")

uart_id = 0
local uart_callback_name = "data"          -- do not change text, otherwise app will crash
local uart_delim = "\n"

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

-- TODO: move handshake messages to config

function uart_write(data)
    -- TODO: escape adding
    uart.write(uart_id, data..uart_delim)
end

function uart_decive_ready_callback()
    uart.write(uart_id, "I'm ready, Milord!"..uart_delim)
    -- TODO: add timer
    -- TODO:rewrite to custom write
end

-- protocol callback
function uart_protocol_callback(data)
    
    --TODO
end

-- only handshake callback
function uart_callback(data)
    if data==("Sir"..uart_delim) then
        uart.write(uart_id, "Yes, Sir"..uart_delim)
        uart.on(uart_callback_name) -- unregister callback function
        -- TODO: register new callback
    end
end

uart.on(uart_callback_name, uart_delim, uart_callback, 0)

print("UART was configured")

cfg = nil
uart_callback_name = nil
uart_delim = 
collectgarbage()
