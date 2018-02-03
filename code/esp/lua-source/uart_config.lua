print("Configuring UART")

uart_id = 0

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

print("UART was configured.")

cfg = nil
collectgarbage()
