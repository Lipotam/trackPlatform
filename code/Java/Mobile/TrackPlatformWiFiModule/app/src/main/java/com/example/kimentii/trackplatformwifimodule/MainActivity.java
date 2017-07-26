package com.example.kimentii.trackplatformwifimodule;

import android.app.Activity;
import android.os.Bundle;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.GridLayout;
import android.widget.RelativeLayout;
import android.widget.Toast;

import java.util.concurrent.Semaphore;

public class MainActivity extends Activity implements View.OnClickListener, View.OnTouchListener {

    private String ip;
    private int port;
    WiFiModule wiFiModule;
    EditText ipEditText;
    EditText portEditText;
    RelativeLayout relativeLayout;
    Semaphore semaphore;
    Toast toast;
    Button connectButton;
    Button menuButton;
    Button forwardButton, backButton, rightButton, leftButton, stopButton;

    public void loadMenu() {
        if (relativeLayout != null) relativeLayout.removeAllViews();
        setContentView(R.layout.activity_main);
        relativeLayout = (RelativeLayout) findViewById(R.id.menu);
        connectButton = (Button) findViewById(R.id.connect_button);
        connectButton.setOnClickListener(this);
        ipEditText = (EditText) findViewById(R.id.ip);
        portEditText = (EditText) findViewById(R.id.port);

    }

    public void loadMoveButtons() {
        if (relativeLayout != null) relativeLayout.removeAllViews();
        connectButton = null;
        setContentView(R.layout.move_buttons);
        relativeLayout = (RelativeLayout) findViewById(R.id.move_buttons);
        menuButton = (Button) findViewById(R.id.menu_button);
        forwardButton = (Button) findViewById(R.id.forward_button);
        backButton = (Button) findViewById(R.id.back_button);
        rightButton = (Button) findViewById(R.id.right_button);
        leftButton = (Button) findViewById(R.id.left_button);
        stopButton = (Button) findViewById(R.id.stop_button);
        menuButton.setOnClickListener(this);
        forwardButton.setOnTouchListener(this);
        backButton.setOnTouchListener(this);
        rightButton.setOnTouchListener(this);
        leftButton.setOnTouchListener(this);
        stopButton.setOnTouchListener(this);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        relativeLayout = (RelativeLayout) findViewById(R.id.menu);
        connectButton = (Button) findViewById(R.id.connect_button);
        connectButton.setOnClickListener(this);
        ipEditText = (EditText) findViewById(R.id.ip);
        portEditText = (EditText) findViewById(R.id.port);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.connect_button:
                semaphore = new Semaphore(1);
                semaphore.tryAcquire();
                toast = Toast.makeText(getApplicationContext(), "", Toast.LENGTH_LONG);
                ip = ipEditText.getText().toString();
                port = Integer.parseInt(portEditText.getText().toString());
                wiFiModule = new WiFiModule(ip, port, toast, semaphore);
                wiFiModule.execute();
                try {
                    semaphore.acquire();
                } catch (Exception e) {
                    e.printStackTrace();
                }
                if (wiFiModule.isConnected())
                    loadMoveButtons();
                break;
            case R.id.menu_button:
                loadMenu();
                break;
        }
    }

    @Override
    public boolean onTouch(View v, MotionEvent motionEvent) {
        switch (v.getId()) {
            case R.id.forward_button:
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    wiFiModule.moveForward();
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    wiFiModule.stopMoving();
                }
                break;
            case R.id.back_button:
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    wiFiModule.moveBack();
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    wiFiModule.stopMoving();
                }
                break;
            case R.id.right_button:
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    wiFiModule.moveRight();
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    wiFiModule.stopMoving();
                }
                break;
            case R.id.left_button:
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    wiFiModule.moveLeft();
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    wiFiModule.stopMoving();
                }
                break;
            case R.id.stop_button:
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    wiFiModule.stopMoving();
                }
                break;
        }
        return false;
    }
}
