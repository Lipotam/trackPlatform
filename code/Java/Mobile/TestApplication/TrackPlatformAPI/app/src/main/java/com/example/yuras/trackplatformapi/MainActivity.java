package com.example.yuras.trackplatformapi;

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import java.io.IOException;
import java.lang.reflect.Method;

public class MainActivity extends AppCompatActivity {
    private final static int RECEIVE_MESSAGE = 1;
    private final static String ADDRESS = "20:16:04:11:37:56";

    private TextView textView;
    private EditText editText;
    Handler h;

    private BluetoothAdapter btAdapter = null;
    private BluetoothSocket btSocket = null;
    private StringBuilder sb = new StringBuilder();

    private ConnectedThread mConnectedThread;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        textView = (TextView) findViewById(R.id.text_from_bt);
        editText = (EditText) findViewById(R.id.edit_text);

        h = new Handler() {
            public void handleMessage(Message msg) {
                System.out.println("In handler reader");
                switch (msg.what) {
                case RECEIVE_MESSAGE:
                    System.out.println("Receive message");
                    byte[] readBuf = (byte[]) msg.obj;
                    String strIncom = new String(readBuf, 0, msg.arg1);
                    sb.append(strIncom);
                    int endOfLineIndex = sb.indexOf("\r\n");
                    if (endOfLineIndex > 0) {
                        String sbprint = sb.substring(0, endOfLineIndex);
                        sb.delete(0, sb.length());
                        textView.setText(sbprint);
                    }
                    break;
                }
            }
        };

        btAdapter = BluetoothAdapter.getDefaultAdapter();
        checkBtState();

        /*if (bluetooth == null) {
            Toast.makeText(this, "Device does not support Bluetooth", Toast.LENGTH_LONG).show();
        }

        if (!bluetooth.isEnabled()) {
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }*/

        /*try {
            device = bluetooth.getRemoteDevice("20:16:04:11:37:56");

            Method m = device.getClass().getMethod(
                    "createRfcommSocket", new Class[]{int.class});

            clientSocket = (BluetoothSocket) m.invoke(device, 1);
            clientSocket.connect();

        } catch (IOException e) {
            Log.d("BLUETOOTH", e.getMessage());
        } catch (SecurityException e) {
            Log.d("BLUETOOTH", e.getMessage());
        } catch (NoSuchMethodException e) {
            Log.d("BLUETOOTH", e.getMessage());
        } catch (IllegalArgumentException e) {
            Log.d("BLUETOOTH", e.getMessage());
        } catch (IllegalAccessException e) {
            Log.d("BLUETOOTH", e.getMessage());
        } catch (InvocationTargetException e) {
            Log.d("BLUETOOTH", "InvocationTargetException");
        }*/
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

    @Override
    protected void onResume() {
        super.onResume();

        BluetoothDevice device = btAdapter.getRemoteDevice(ADDRESS);
        try {
            btSocket = createBluetoothSocket(device);
        } catch (IOException e) {
            errorExit("FatalError", "in onResume");
        }

        btAdapter.cancelDiscovery();

        Log.d("BLUETOOTH", "Connecting");
        try {
            btSocket.connect();
            Log.d("BLUETOOTH", "Connecting ok");
        } catch (IOException e) {
            try {
                btSocket.close();
            } catch (IOException e2) {
                errorExit("Fatal Error", "In onResume(): to close socket during connection failure" + e2.getMessage() + ".");
            }
        }

        Log.d("BLUETOOTH", "Create Socket");

        mConnectedThread = new ConnectedThread(btSocket, h);
        mConnectedThread.start();
    }

    @Override
    public void onPause() {
        super.onPause();

        Log.d("BLUETOOTH", "...In onPause()...");

        try     {
            btSocket.close();
        } catch (IOException e2) {
            errorExit("Fatal Error", "In onPause() and failed to close socket." + e2.getMessage() + ".");
        }
    }

    private void checkBtState() {
        if(btAdapter == null) {
            errorExit("Fatal Error", "Bluetooth not support");
        } else {
            if (btAdapter.isEnabled()) {
                Log.d("BLUETOOTH", "...Bluetooth ON...");
            } else {
                Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
                startActivityForResult(enableBtIntent, 1);
            }
        }
    }

    private void errorExit(String title, String message){
        Toast.makeText(getBaseContext(), title + " - " + message, Toast.LENGTH_LONG).show();
        finish();
    }

    public void sendText(View v) {
        mConnectedThread.write(editText.getText().toString());
    }

    /*public void sendText(View view) {
        try {
            OutputStream outStream = clientSocket.getOutputStream();
            outStream.write("TrackPlatformApi\n".getBytes());
        } catch (IOException e) {
            Log.d("BLUETOOTH", e.getMessage());
        }
    }*/
}
