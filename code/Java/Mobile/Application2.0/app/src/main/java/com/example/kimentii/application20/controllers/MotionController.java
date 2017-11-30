package com.example.kimentii.application20.controllers;

import com.example.kimentii.application20.api.API;
import com.example.kimentii.application20.connectors.BluetoothConnector;
import com.example.kimentii.application20.settings.Settings;

public class MotionController {
    public void moveForward() {
        BluetoothConnector bluetoothConnector = BluetoothConnector.getInstance();
        API api = Settings.getInstance().getApi();
        bluetoothConnector.write(api.getMoveForwardCommand());
    }

    public void moveRight() {
        BluetoothConnector bluetoothConnector = BluetoothConnector.getInstance();
        API api = Settings.getInstance().getApi();
        bluetoothConnector.write(api.getMoveRightCommand());

    }

    public void moveLeft() {
        BluetoothConnector bluetoothConnector = BluetoothConnector.getInstance();
        API api = Settings.getInstance().getApi();
        bluetoothConnector.write(api.getMoveLeftCommand());
    }

    public void moveBack() {
        BluetoothConnector bluetoothConnector = BluetoothConnector.getInstance();
        API api = Settings.getInstance().getApi();
        bluetoothConnector.write(api.getMoveBackCommand());
    }

    public void stop() {
        BluetoothConnector bluetoothConnector = BluetoothConnector.getInstance();
        API api = Settings.getInstance().getApi();
        bluetoothConnector.write(api.getStopCommand());
    }

}
