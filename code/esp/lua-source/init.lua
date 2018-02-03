print ( "Waiting ...")
tmr.register (0, 5000, tmr.ALARM_SINGLE, function (t) tmr.unregister (0); print ( "Starting ..."); dofile ("main.lua") end)
tmr.start (0)
