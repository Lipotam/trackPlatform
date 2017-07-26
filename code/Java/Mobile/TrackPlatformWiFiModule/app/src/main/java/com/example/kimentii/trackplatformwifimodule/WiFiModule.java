package com.example.kimentii.trackplatformwifimodule;

import android.os.AsyncTask;
import android.widget.Toast;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.net.InetAddress;
import java.net.InetSocketAddress;
import java.net.Socket;
import java.util.concurrent.Semaphore;

public class WiFiModule extends AsyncTask<Void, String, Void> {

    private final String TOAST = "toast";
    private String ip;
    private int port;
    private volatile boolean isConnected;
    private Toast toast;
    private Socket clientSocket;
    private Semaphore semaphore;
    private DataInputStream inputStream;
    private
    DataOutputStream outputStream;

    WiFiModule(String ip, int port, Toast toast, Semaphore semaphore) {
        this.ip = ip;
        this.port = port;
        this.toast = toast;
        this.semaphore = semaphore;
    }

    public void moveForward() {
        try {
            outputStream.writeUTF(MovingCommands.FORWARD.getValue());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void moveBack() {
        try {
            outputStream.writeUTF(MovingCommands.BACK.getValue());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void moveRight() {
        try {
            outputStream.writeUTF(MovingCommands.RIGHT.getValue());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void moveLeft() {
        try {
            outputStream.writeUTF(MovingCommands.LEFT.getValue());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void stopMoving() {
        try {
            outputStream.writeUTF(MovingCommands.STOP.getValue());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private void connect() {
        try {
            semaphore.tryAcquire();
            System.out.println("Trying connect to server.");
            clientSocket = new Socket();
            clientSocket.connect(new InetSocketAddress(ip, port), 3000);
            System.out.println("Connected to server.");
            onProgressUpdate(TOAST, "Connected.");
            inputStream = new DataInputStream(clientSocket.getInputStream());
            outputStream = new DataOutputStream(clientSocket.getOutputStream());
            isConnected = true;
            semaphore.release();
        } catch (Exception e) {
            e.printStackTrace();
            onProgressUpdate(TOAST, "Can't connect.");
            isConnected = false;
        }
    }

    boolean isConnected() {
        return isConnected;
    }

    @Override
    protected Void doInBackground(Void... params) {
        connect();
        if (!isConnected) return null;
        while (true) {
            try {
                String message = inputStream.readUTF();
                System.out.println("mes:" + message);
            } catch (Exception e) {
                e.printStackTrace();
                break;
            }
        }
        return null;
    }

    @Override
    protected void onProgressUpdate(String... strings) {
        super.onProgressUpdate(strings);
        switch (strings[0]) {
            case TOAST:
                if (toast != null) {
                    toast.setText(strings[1]);
                    toast.show();
                }
                break;
        }
    }
}
