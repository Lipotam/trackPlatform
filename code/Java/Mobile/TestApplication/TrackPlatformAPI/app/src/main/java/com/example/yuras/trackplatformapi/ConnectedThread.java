package com.example.yuras.trackplatformapi;

import android.bluetooth.BluetoothSocket;
import android.os.Handler;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class ConnectedThread extends Thread {
    private static final int RECEIVE_MESSAGE = 1;

    private final InputStream mmInStream;
    private final OutputStream mmOutStream;
    private final Handler handler;

    public ConnectedThread(BluetoothSocket socket, Handler handler) {
        InputStream tmpIn = null;
        OutputStream tmpOut = null;
        this.handler = handler;

        try {
            tmpIn = socket.getInputStream();
            tmpOut = socket.getOutputStream();
        } catch (IOException e ) {
            e.printStackTrace();
        }

        mmInStream = tmpIn;
        mmOutStream = tmpOut;
    }

    public void run() {
        byte[] buffer = new byte[1024];
        int bytes;

        while (true) {
            try {
                bytes = mmInStream.read(buffer);
                handler.obtainMessage(RECEIVE_MESSAGE, bytes, -1, buffer).sendToTarget();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    public void write(String message) {
        Log.d("BLUETOOTH", "Data to send: " + message);
        byte[] msgBuffer = message.getBytes();
        try {
            mmOutStream.write(msgBuffer);
        } catch (IOException e) {
            Log.d("BLUETOOTH", "Error data send");
        }
    }
}
