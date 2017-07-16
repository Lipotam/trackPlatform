package com.example.yuras.trackplatformapi;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Handler;
import android.util.Log;
import android.widget.Toast;

import java.io.IOException;
import java.lang.reflect.Method;

public class TrackPlatform implements Constants {
    private Activity activity;
    private Handler handler;
    private BluetoothAdapter btAdapter = null;
    private BluetoothSocket btSocket = null;
    private ConnectedThread connectedThread;

    public TrackPlatform(Activity activity, Handler handler) {
        btAdapter = BluetoothAdapter.getDefaultAdapter();
        this.handler = handler;
        this.activity = activity;
    }

    public void connect() {
        checkBtState();
        BluetoothDevice device = btAdapter.getRemoteDevice(Constants.BLUETOOTH_MAC);
        try {
            btSocket = createBluetoothSocket(device);
        } catch (IOException e) {
            Log.d(TAG, e.getMessage());
        }

        btAdapter.cancelDiscovery();
        try {
            btSocket.connect();
            Log.d(TAG, "Connecting: Ok");
        } catch (IOException e) {
            try {
                btSocket.close();
            } catch (IOException e2) {
                errorExit("Fatal Error", "In onResume(): to close socket during connection failure" + e2.getMessage() + ".");
            }
        }

        connectedThread = new ConnectedThread(btSocket, handler);
        connectedThread.start();
    }

    public void disconnect() {
        try {
            btSocket.close();
            connectedThread.cancel();
        } catch (IOException e) {
            errorExit("Fatal Error", "In onPause() and failed to close socket." + e.getMessage() + ".");
        }
    }

    public void send(String msg) {
        connectedThread.write(msg);
    }

    private void checkBtState() {
        if(btAdapter == null) {
            errorExit("Fatal Error", "Bluetooth not support");
        } else {
            if (btAdapter.isEnabled()) {
                Log.d(Constants.TAG, "...Bluetooth ON...");
            } else {
                Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                activity.startActivityForResult(enableBtIntent, 1);
            }
        }
    }

    private void errorExit(String title, String message){
        Toast.makeText(activity.getBaseContext(), title + " - " + message, Toast.LENGTH_LONG).show();
        activity.finish();
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
}
