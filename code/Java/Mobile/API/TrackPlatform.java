package com.example.yuras.trackplatformapi;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.widget.Toast;

import java.io.IOException;
import java.lang.reflect.Method;

public class TrackPlatform {
    private final static String BLUETOOTH_MAC = "20:16:04:11:37:56";
    private final static String TAG = "BLUETOOTH";
    private final static int RECEIVE_MESSAGE = 1;

    private Activity activity;

    private Handler handler;
    private StringBuilder stringBuilder;
    private BluetoothAdapter btAdapter = null;
    private BluetoothSocket btSocket = null;
    private ConnectedThread connectedThread;
    private String receivedMessage;

    public TrackPlatform(Activity activity) {
        btAdapter = BluetoothAdapter.getDefaultAdapter();
        checkBtState();

        this.activity = activity;

        handler = new Handler() {
            public void handleMessage(Message msg) {
                if (msg.what == RECEIVE_MESSAGE) {
                    byte[] readBuf = (byte[]) msg.obj;
                    String strIncom = new String(readBuf, 0, msg.arg1);
                    stringBuilder.append(strIncom);
                    int endOfLineIndex = stringBuilder.indexOf("\r\n");
                    if (endOfLineIndex > 0) {
                        receivedMessage = stringBuilder.substring(0, endOfLineIndex);
                        stringBuilder.delete(0, stringBuilder.length());
                    }
                }
            }
        };
    }

    public void connect() {
        BluetoothDevice device = btAdapter.getRemoteDevice(BLUETOOTH_MAC);
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
            connectedThread.join();
        } catch (IOException | InterruptedException e) {
            errorExit("Fatal Error", "In onPause() and failed to close socket." + e.getMessage() + ".");
        }
    }

    public void send(String msg) {
        connectedThread.write(msg);
    }

    public String receive() {
        return receivedMessage;
    }

    private void checkBtState() {
        if(btAdapter == null) {
            errorExit("Fatal Error", "Bluetooth not support");
        } else {
            if (btAdapter.isEnabled()) {
                Log.d("BLUETOOTH", "...Bluetooth ON...");
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
