package com.example.kimentii.application20.controllers;


import com.example.kimentii.application20.api.API;
import com.example.kimentii.application20.connectors.BluetoothConnector;
import com.example.kimentii.application20.settings.Settings;

public class SensorsController {

    public void getDataFromDistanceSensors() {
        BluetoothConnector bluetoothConnector = BluetoothConnector.getInstance();
        API api = Settings.getInstance().getApi();
        bluetoothConnector.write(api.getInfoFromAllDistanceSensorsCommand());
    }

    public void getDataFromLineSensors() {
        BluetoothConnector bluetoothConnector = BluetoothConnector.getInstance();
        API api = Settings.getInstance().getApi();
        bluetoothConnector.write(api.getInfoFromAllLineSensorsCommand());
    }
}
