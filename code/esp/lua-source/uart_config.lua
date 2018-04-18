print("Configuring UART")

uart_id = 0
local uart_callback_name = "data"          -- do not change text, otherwise app will crash
local uart_delim_num = 13
local uart_escape_num = 10

local cfg = {}
cfg.id = uart_id
cfg.speed = 115200
cfg.databits = 8
cfg.parity = uart.PARITY_NONE
cfg.stopbits = uart.STOPBITS_1
cfg.echo = 0    -- disable uart echo

local handshake = {}
handshake.first = "I'm ready, Milord!"
handshake.second = "Sir"
handshake.third = "Yes, Sir"

local is_handshake_made = false
local handshake_timer_num = 2
local handshake_timer_period_ms = 10000

local escape = {}
-- 13 -> 10 11
escape[string.char(uart_delim_num)] = string.char(uart_escape_num, 11)
-- 10 -> 10 10
escape[string.char(uart_escape_num)] = string.char(uart_escape_num, uart_escape_num)

function table_invert(t)
    local s={}
    for k,v in pairs(t) do
      s[v]=k
    end
    return s
end
local invert_escape = table_invert(escape)

uart.setup(cfg.id,
    cfg.speed,
    cfg.databits,
    cfg.parity,
    cfg.stopbits,
    cfg.echo
)

function uart_write(data)
    -- escaping string
    data = string.gsub(data, ".",
        function(pattern)
            local res = escape[pattern]
            if not res then
                res = pattern
            end

            return res
        end
    )

    -- write to serial port
    uart.write(uart_id, data .. string.char(uart_delim_num))

    collectgarbage()
end

local function handshake_manager()
    if not is_handshake_made then
        uart_write(handshake.first)
        tmr.register(handshake_timer_num, handshake_timer_period_ms, tmr.ALARM_SINGLE,
            handshake_manager)
        tmr.start(handshake_timer_num)
    end
end

function uart_decive_ready_callback()
    handshake_manager()
end

-- protocol parsing callback
function uart_protocol_parser(data)
    local delim_string = string.char(uart_delim_num)
    if string.sub(data, -1) ~= delim_string then
        print("Protocol error")
    else
        data = string.gsub(data, delim_string, "")
        data = string.gsub(data, string.char(uart_delim_num) .. ".",
            function(pattern)
                return invert_escape[pattern]
            end
        )
    end

    delim_string = nil
    return data
end

-- protocol callback
function uart_connected_callback(data)
    data = uart_protocol_parser(data)

    wifi_write(data)
end

-- only handshake callback
function uart_callback(data)
    data = uart_protocol_parser(data)
    if data==(handshake.second) then
        is_handshake_made = true
        uart_write(handshake.third)

        -- unregister callback function
        uart.on(uart_callback_name)

        -- register new callback
        uart.on(uart_callback_name, string.char(uart_delim_num), uart_connected_callback, 0)
    end
end

uart.on(uart_callback_name, string.char(uart_delim_num), uart_callback, 0)

print("UART was configured")

cfg = nil
collectgarbage()
