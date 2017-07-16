package com.example.yuras.trackplatformapi;

import android.bluetooth.BluetoothSocket;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;

import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class ConnectedThread extends Thread implements Constants {
    private final InputStream mmInStream;
    private final OutputStream mmOutStream;
    private final Handler handler;
    private BluetoothSocket socket;

    public ConnectedThread(BluetoothSocket socket, Handler handler) {
        InputStream tmpIn = null;
        OutputStream tmpOut = null;
        this.handler = handler;
        this.socket = socket;

        try {
            tmpIn = socket.getInputStream();
        } catch (IOException e) {
            Log.e(TAG, "Error occurred when creating input stream", e);
        }
        try {
            tmpOut = socket.getOutputStream();
        } catch (IOException e) {
            Log.e(TAG, "Error occurred when creating output stream", e);
        }

        mmInStream = tmpIn;
        mmOutStream = tmpOut;
    }

    public void run() {
        byte[] buffer = new byte[1024];
        int numBytes;

        while (true) {
            try {
                numBytes = mmInStream.read(buffer);
                Message readMsg = handler.obtainMessage(Constants.MESSAGE_READ, numBytes, -1, buffer);
                readMsg.sendToTarget();
            } catch (IOException e) {
                Log.d(TAG, "Input stream was disconnected", e);
                break;

            }
        }
    }

    public void write(String message) {
        Log.d("BLUETOOTH", "Data to send: " + message);
        byte[] msgBuffer = message.getBytes();
        try {
            mmOutStream.write(msgBuffer);
            Message writtenMsg = handler.obtainMessage(
                    Constants.MESSAGE_WRITE, -1, -1, msgBuffer);
            writtenMsg.sendToTarget();

        } catch (IOException e) {
            Log.e(TAG, "Error occurred when sending data", e);

//            Message writeErrorMsg =
//                    handler.obtainMessage(Constants.MESSAGE_TOAST);
//            Bundle bundle = new Bundle();
//            bundle.putString("toast",
//                    "Couldn't send data to the other device");
//            writeErrorMsg.setData(bundle);
//            handler.sendMessage(writeErrorMsg);

        }
    }

    public void cancel() {
        try {
            socket.close();
        } catch (IOException e) {
            Log.e(TAG, "Could not close the connect socket", e);
        }
    }

}
