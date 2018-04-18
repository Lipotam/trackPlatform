local time_to_wait = 5000
local timer_num = 0
print ( "Waiting to rewrite scripts in " .. time_to_wait .. " ms ...")
tmr.register (timer_num, time_to_wait, tmr.ALARM_SINGLE,
    function (t)
        print ( "Starting esp8266...")
        dofile ("main.lua")
    end
)
tmr.start (timer_num)

collectgarbage()
