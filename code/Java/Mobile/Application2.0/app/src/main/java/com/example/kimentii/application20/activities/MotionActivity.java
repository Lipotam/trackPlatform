package com.example.kimentii.application20.activities;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.example.kimentii.application20.R;
import com.example.kimentii.application20.api.API4;
import com.example.kimentii.application20.connectors.BluetoothConnector;
import com.example.kimentii.application20.controllers.MotionController;
import com.example.kimentii.application20.settings.Settings;
import com.example.kimentii.application20.wrappers.LanguageWrapper;

public class MotionActivity extends AppCompatActivity {

    private Button forwardButton;
    private Button rightButton;
    private Button leftButton;
    private Button backButton;
    private Button stopButton;
    private TextView connectionStateTextView;

    private BluetoothConnector bluetoothConnector;
    private MotionController motionController;

    private void setLocaleLanguage() {
        if (bluetoothConnector != null && bluetoothConnector.isConnected()) {
            connectionStateTextView.setText(Settings.getInstance().getLanguageWrapper().
                    getViewString(LanguageWrapper.CONNECTED));
        } else {
            connectionStateTextView.setText(Settings.getInstance().getLanguageWrapper().
                    getViewString(LanguageWrapper.NO_CONNECTION));
        }
        forwardButton.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.FORWARD_BUTTON));
        rightButton.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.RIGHT_BUTTON));
        leftButton.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.LEFT_BUTTON));
        backButton.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.BACK_BUTTON));
        stopButton.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.STOP_BUTTON));
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_motion);
        ActionBar actionBar = getSupportActionBar();
        actionBar.setHomeButtonEnabled(true);
        actionBar.setDisplayHomeAsUpEnabled(true);

        Handler handler = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                super.handleMessage(msg);

            }
        };
        bluetoothConnector = BluetoothConnector.getInstance();
        bluetoothConnector.setHandler(handler);

        forwardButton = (Button) findViewById(R.id.forward_button);
        rightButton = (Button) findViewById(R.id.right_button);
        leftButton = (Button) findViewById(R.id.left_button);
        backButton = (Button) findViewById(R.id.back_button);
        stopButton = (Button) findViewById(R.id.stop_button);
        connectionStateTextView = (TextView) findViewById(R.id.connection_state_tv_motion_activity);
        setLocaleLanguage();

        motionController = new MotionController();
        View.OnTouchListener touchListener = new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    switch (view.getId()) {
                        case R.id.forward_button:
                            motionController.moveForward();
                            break;
                        case R.id.right_button:
                            motionController.moveRight();
                            break;
                        case R.id.left_button:
                            motionController.moveLeft();
                            break;
                        case R.id.back_button:
                            motionController.moveBack();
                            break;
                        case R.id.stop_button:
                            motionController.stop();
                            break;
                    }
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    motionController.stop();
                }
                return false;
            }
        };
        forwardButton.setOnTouchListener(touchListener);
        rightButton.setOnTouchListener(touchListener);
        leftButton.setOnTouchListener(touchListener);
        backButton.setOnTouchListener(touchListener);
        stopButton.setOnTouchListener(touchListener);
    }
}
