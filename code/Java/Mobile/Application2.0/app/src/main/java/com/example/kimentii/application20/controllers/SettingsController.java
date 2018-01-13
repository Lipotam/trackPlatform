package com.example.kimentii.application20.controllers;

import com.example.kimentii.application20.api.API;
import com.example.kimentii.application20.connectors.BluetoothConnector;
import com.example.kimentii.application20.constants.Constants;
import com.example.kimentii.application20.settings.Settings;

public class SettingsController {
    public void changeAPI(Constants.ApiEnum apiEnum) {
        BluetoothConnector bluetoothConnector = BluetoothConnector.getInstance();
        API api = Settings.getInstance().getApi();
        bluetoothConnector.write(api.getDisconnectCommand());
        bluetoothConnector.write(api.getConnectCommand(apiEnum));
    }
}
