package com.example.kimentii.application20.connectors;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import com.example.kimentii.application20.constants.Constants;
import com.example.kimentii.application20.settings.Settings;
import com.example.kimentii.application20.wrappers.LanguageWrapper;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.lang.reflect.Method;

public class BluetoothConnector extends Thread {
    public static final String TAG = "TAG";

    private static BluetoothConnector bluetoothConnector;
    private BluetoothSocket bluetoothSocket;
    private Handler handler;
    private boolean isConnected = false;
    private DataInputStream dataInputStream;
    private DataOutputStream dataOutputStream;


    private BluetoothConnector() {
    }

    public void connect() {
        BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        BluetoothDevice device = bluetoothAdapter.getRemoteDevice(Constants.BLUETOOTH_MAC);
        try {
            bluetoothSocket = createBluetoothSocket(device);
            bluetoothAdapter.cancelDiscovery();
            bluetoothSocket.connect();
            Log.d(TAG, "connected to the device");
        } catch (IOException e) {
            e.printStackTrace();
            Log.d(TAG, "Can't connect to the device.");
            setConnected(false);
            return;
        }
        try {
            dataInputStream = new DataInputStream(bluetoothSocket.getInputStream());
            dataOutputStream = new DataOutputStream(bluetoothSocket.getOutputStream());
        } catch (IOException e) {
            e.printStackTrace();
        }
        setConnected(true);
        start();
    }

    private BluetoothSocket createBluetoothSocket(BluetoothDevice device) throws IOException {
        BluetoothSocket socket = null;
        try {
            Method m = device.getClass().getMethod(
                    "createRfcommSocket", new Class[]{int.class});

            socket = (BluetoothSocket) m.invoke(device, 1);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return socket;
    }

    public void write(String message) {
        try {
            if (isConnected()) {
                synchronized (dataOutputStream) {
                    dataOutputStream.writeUTF(message);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public void write(byte[] message) {
        try {
            if (isConnected()) {
                synchronized (dataOutputStream) {
                    dataOutputStream.write(message);
                }
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static BluetoothConnector getInstance() {
        if (bluetoothConnector == null) {
            bluetoothConnector = new BluetoothConnector();
        }
        return bluetoothConnector;
    }

    public synchronized void setConnected(boolean connected) {
        isConnected = connected;
    }

    public synchronized boolean isConnected() {
        return isConnected;
    }

    public void setHandler(Handler handler) {
        synchronized (handler) {
            this.handler = handler;
        }
    }

    @Override
    public void run() {
        Log.d(TAG, "Bluetooth Connector started.");
        byte buf[] = new byte[50];
        while (true) {
            try {
                dataInputStream.read(buf,0, 50);
                Log.d(TAG, new String(buf));
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}
