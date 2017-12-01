package com.example.kimentii.application20.connectors;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.Handler;
import android.util.Log;

import com.example.kimentii.application20.constants.Constants;
import com.example.kimentii.application20.settings.Settings;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.lang.reflect.Method;

public class BluetoothConnector extends Thread {
    public static final String TAG = "TAG";

    private static BluetoothConnector bluetoothConnector;
    private BluetoothSocket bluetoothSocket;
    private Handler handler;
    private volatile boolean isConnected = false;
    private volatile boolean isRepeat = false;
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

    private synchronized boolean isRepeat() {
        return isRepeat;
    }

    private synchronized void setRepeat(boolean repeat) {
        isRepeat = repeat;
    }

    public void setHandler(Handler handler) {
        synchronized (handler) {
            this.handler = handler;
        }
    }

    @Override
    public void run() {
        Log.d(TAG, "Bluetooth Connector started.");
        write(Settings.getInstance().getApi().getConnectCommand(Settings.getInstance().getApi().getApiEnum()));
        byte buf[] = new byte[100];
        setRepeat(true);
        while (isRepeat()) {
            try {
                int dataSize = dataInputStream.read();
                byte buf2[] = new byte[dataSize];
                for (int j = 0; j < dataSize; j++) {
                    buf2[j] = dataInputStream.readByte();
                }
                // read CTC
                dataInputStream.read();
                dataInputStream.read();
                String str = "";
                String strChar = "";
                for (int i = 0; i < dataSize; i++) {
                    str += String.format("%02x ", buf2[i]);
                    strChar += String.format("%c", (char) buf2[i]);
                }
                Log.d(TAG, str);
                Log.d(TAG, strChar);

            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void disconnect() {
        write(Settings.getInstance().getApi().getDisconnectCommand());
        try {
            if (bluetoothSocket != null) {
                bluetoothSocket.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        setRepeat(false);
    }
}
