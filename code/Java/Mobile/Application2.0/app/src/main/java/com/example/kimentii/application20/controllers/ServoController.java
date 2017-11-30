package com.example.kimentii.application20.controllers;

import com.example.kimentii.application20.api.API;
import com.example.kimentii.application20.connectors.BluetoothConnector;
import com.example.kimentii.application20.settings.Settings;

public class ServoController {
    public static final int MAX_ANGLE = 180;
    public static final int MIN_ANGLE = 0;


    private int angleXY;
    private int angleXZ;

    public ServoController() {
        angleXY = 0;
        angleXZ = 0;
    }

    public void turnUpOnOneDegree() {
        BluetoothConnector bluetoothConnector = BluetoothConnector.getInstance();
        API api = Settings.getInstance().getApi();
        if (angleXZ + 1 <= 180) {
            bluetoothConnector.write(api.getSetAngleCommand(++angleXZ, API.XZ));
        }
    }

    public void turnRightOnOneDegree() {
        BluetoothConnector bluetoothConnector = BluetoothConnector.getInstance();
        API api = Settings.getInstance().getApi();
        if (angleXY + 1 <= 180) {
            bluetoothConnector.write(api.getSetAngleCommand(++angleXY, API.XY));
        }
    }

    public void turnLeftOnOneDegree() {
        BluetoothConnector bluetoothConnector = BluetoothConnector.getInstance();
        API api = Settings.getInstance().getApi();
        if (angleXY - 1 >= 0) {
            bluetoothConnector.write(api.getSetAngleCommand(--angleXY, API.XY));
        }
    }

    public void turnDownOnOneDegree() {
        BluetoothConnector bluetoothConnector = BluetoothConnector.getInstance();
        API api = Settings.getInstance().getApi();
        if (angleXZ - 1 >= 0) {
            bluetoothConnector.write(api.getSetAngleCommand(--angleXZ, API.XZ));
        }
    }
}
