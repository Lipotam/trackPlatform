package com.example.yura.bluetooth;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import java.io.IOException;
import java.io.OutputStream;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import android.app.Activity;
import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Toast;
import android.widget.Button;

public class MainActivity extends Activity implements View.OnClickListener {

    Button sendCharBtn;

    BluetoothSocket clientSocket;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        sendCharBtn = (Button) findViewById("sendCharBtn");

        redButton.setOnClickListener(this);

        String enableBT = BluetoothAdapter.ACTION_REQUEST_ENABLE;
        startActivityForResult(new Intent(enableBT), 0);

        BluetoothAdapter bluetooth = BluetoothAdapter.getDefaultAdapter();

        try {
            BluetoothDevice device = bluetooth.getRemoteDevice("b8:76:3f:53:8d:72");

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
            Log.d("BLUETOOTH", e.getMessage());
        }

        Toast.makeText(getApplicationContext(), "CONNECTED", Toast.LENGTH_LONG).show();

    }

    @Override
    public void onClick(View v) {
	try {
            outStream.write("Test string");
        } catch (IOException e) {
            Log.d("BLUETOOTH", e.getMessage());
        }
    }
}
