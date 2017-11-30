package com.example.kimentii.application20.api;


import com.example.kimentii.application20.constants.Constants;

public abstract class API {
    public static final int XY = 1;
    public static final int XZ = 2;

    protected Constants.ApiEnum apiEnum;

    public Constants.ApiEnum getApiEnum() {
        return apiEnum;
    }

    // communication
    public abstract byte[] getConnectCommand(Constants.ApiEnum api);

    public abstract byte[] getDisconnectCommand();


    // motion activity
    public abstract byte[] getMoveForwardCommand();

    public abstract byte[] getMoveRightCommand();

    public abstract byte[] getMoveLeftCommand();

    public abstract byte[] getMoveBackCommand();

    public abstract byte[] getStopCommand();

    // servo activity
    public abstract byte[] getGetAngleCommand();

    public abstract byte[] getSetAngleCommand(int angle, char surface);

    // sensors activity
    public abstract byte[] getInfoFromDistanceSensorCommand(int i);

    public abstract byte[] getInfoFromLineSensorCommand(int i);

    // API
    public abstract byte[] getChangeApiCommand(int i);
}
