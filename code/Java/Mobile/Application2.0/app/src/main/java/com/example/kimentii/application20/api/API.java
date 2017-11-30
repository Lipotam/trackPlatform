package com.example.kimentii.application20.api;


import com.example.kimentii.application20.constants.Constants;

public abstract class API {

    protected Constants.ApiEnum apiEnum;

    public Constants.ApiEnum getApiEnum() {
        return apiEnum;
    }

    // communication
    public abstract byte[] getConnectCommand();

    public abstract byte[] getDisconnectCommand();


    // motion activity
    public abstract byte[] getMoveForwardCommand();

    public abstract byte[] getMoveRightCommand();

    public abstract byte[] getMoveLeftCommand();

    public abstract byte[] getMoveBackCommand();

    public abstract byte[] getStopCommand();

    // servo activity
    public abstract byte[] getTurnUpServoCommand();

    public abstract byte[] getTurnRightServoCommand();

    public abstract byte[] getTurnLeftServoCommand();

    public abstract byte[] getTurnDownServoCommand();

    // sensors activity
    public abstract byte[] getInfoFromDistanceSensorCommand(int i);

    public abstract byte[] getInfoFromLineSensorCommand(int i);

    // API
    public abstract byte[] getChangeApiCommand(int i);
}
