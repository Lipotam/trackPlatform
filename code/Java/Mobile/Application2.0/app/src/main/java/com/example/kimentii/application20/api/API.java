package com.example.kimentii.application20.api;


public interface API {

    // communication
    byte[] getConnectCommand();
    byte[] getDisconnectCommand();


    // motion activity
    byte[] getMoveForwardCommand();
    byte[] getMoveRightCommand();
    byte[] getMoveLeftCommand();
    byte[] getMoveBackCommand();
    byte[] gteStopCommand();

    // servo activity
    byte[] getTurnUpServoCommand();
    byte[] getTurnRightServoCommand();
    byte[] getTurnLeftServoCommand();
    byte[] getTurnDownServoCommand();

    // sensors activity
    byte[] getInfoFromDistanceSensorCommand(int i);
    byte[] getInfoFromLineSensorCommand(int i);

    // API
    byte[] getChangeApiCommand(int i);
}
