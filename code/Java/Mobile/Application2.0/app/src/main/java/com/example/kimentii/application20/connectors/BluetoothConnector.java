package com.example.kimentii.application20.connectors;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Handler;
import android.util.Log;

import java.io.IOException;
import java.lang.reflect.Method;

public class BluetoothConnector extends Thread {
    public static final String TAG = "TAG";

    private static BluetoothConnector mBluetoothConnector;
    private BluetoothSocket bluetoothSocket;
    private Handler handler;


    private BluetoothConnector(BluetoothSocket bluetoothSocket) {
        bluetoothSocket = bluetoothSocket;
    }

    public static BluetoothConnector getInstance(Handler handler, BluetoothSocket bluetoothSocket) {
        if (mBluetoothConnector == null) {
            mBluetoothConnector = new BluetoothConnector(bluetoothSocket);
        }
        return mBluetoothConnector;
    }

    public static BluetoothConnector getInstance(Handler handler) {
        if (mBluetoothConnector != null) {
            mBluetoothConnector.setHandler(handler);
        }
        return mBluetoothConnector;
    }

    public void setHandler(Handler handler) {
        handler = handler;
    }

    @Override
    public void run() {
        Log.d(TAG, "Bluetooth Connector started.");

        super.run();
    }

    public boolean isConnected() {
        return false;
    }
}
