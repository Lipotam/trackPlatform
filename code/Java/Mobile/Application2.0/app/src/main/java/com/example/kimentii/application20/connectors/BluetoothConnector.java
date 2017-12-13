package com.example.kimentii.application20.connectors;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import com.example.kimentii.application20.constants.Constants;
import com.example.kimentii.application20.settings.Settings;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.lang.reflect.Method;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

// необзодимо переработать отсылку команд. ГУИ должно добавлять команду в буфер, а поток со
// связью должен брать команды из очереди и выполнять их
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
        Thread autoConnector = new Thread() {
            private int DELAY_TIME_IM_MS = 4000;

            @Override
            public void run() {
                while (isRepeat()) {
                    write(Settings.getInstance().getApi().getReconnectCommand());
                    try {
                        for (int i = 0; i < 5; i++) {
                            synchronized (dataInputStream) {
                                dataInputStream.read();
                            }
                        }
                        Thread.sleep(DELAY_TIME_IM_MS);
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
            }
        };
        autoConnector.start();
        while (isRepeat()) {
            try {
                int dataSize;
                byte buf2[];
                synchronized (dataInputStream) {
                    dataSize = dataInputStream.read();
                    buf2 = new byte[dataSize];
                    for (int j = 0; j < dataSize; j++) {
                        buf2[j] = dataInputStream.readByte();
                    }
                    // read CTC
                    dataInputStream.read();
                    dataInputStream.read();
                }
                String str = "";
                String strChar = "";
                for (int i = 0; i < dataSize; i++) {
                    str += String.format("%02x ", buf2[i]);
                    strChar += String.format("%c", (char) buf2[i]);
                }
                Log.d(TAG, str);
                Log.d(TAG, strChar);
                if (strChar.equals("OK")) {
                    continue;
                } else if (strChar.equals("ERROR")) {
                    continue;
                } else {
                    Pattern p = Pattern.compile("([0-9]{1,3})(;)" +
                            "([0-9]{1,3})(;)" + "([0-9]{1,3})(;)" + "([0-9]{1,3})(;)" + "([0-9]{1,3})");
                    Matcher matcher = p.matcher(strChar);
                    if (matcher.find()) {
                        Log.d(TAG, "GOOOOOOOOD");
                        Log.d(TAG, "Group count: " + matcher.groupCount());
                        int data[] = new int[5];
                        for (int i = 0, j = 1; i < 5; i++, j += 2) {
                            data[i] = Integer.parseInt(matcher.group(j));
                        }
                        if (matcher.group(1).equals("1") || matcher.group(1).equals("0")) {
                            Message message = handler.obtainMessage(Constants.Messages.MESSAGES_READ_LINE_SENSORS_VALUES.getValue(),
                                    data.length, -1, data);
                            message.sendToTarget();
                        } else {
                            Message message = handler.obtainMessage(Constants.Messages.MESSAGES_READ_DISTANCE_SENSORS_VALUES.getValue(),
                                    data.length, -1, data);
                            message.sendToTarget();
                        }
                    }
                }
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
