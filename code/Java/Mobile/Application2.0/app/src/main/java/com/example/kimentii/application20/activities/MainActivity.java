package com.example.kimentii.application20.activities;

import android.bluetooth.BluetoothAdapter;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import com.example.kimentii.application20.R;
import com.example.kimentii.application20.connectors.BluetoothConnector;
import com.example.kimentii.application20.settings.Settings;
import com.example.kimentii.application20.wrappers.LanguageWrapper;

public class MainActivity extends AppCompatActivity {

    public static final String TAG = "TAG";
    private static final int REQUEST_ENABLE_BT = 1;

    private Button motionButton;
    private Button servoButton;
    private Button sensorsButton;
    private Button settingsButton;
    private Button exitButton;
    private TextView connectionStateTextView;

    private BluetoothConnector bluetoothConnector;

    class Listener implements View.OnClickListener {
        Intent intent;

        @Override
        public void onClick(View v) {
            switch (v.getId()) {
                case R.id.motion_button:
                    intent = MotionActivity.newIntent(getApplicationContext());
                    startActivity(intent);
                    break;
                case R.id.servo_button:
                    intent = ServoActivity.newIntent(getApplicationContext());
                    startActivity(intent);
                    break;
                case R.id.sensors_button:
                    intent = SensorsActivity.newIntent(getApplicationContext());
                    startActivity(intent);
                    break;
                case R.id.settings_button:
                    intent = SettingsActivity.newIntent(getApplicationContext());
                    startActivity(intent);
                    break;
                case R.id.exit_button:
                    try {
                        if (bluetoothConnector != null) {
                            bluetoothConnector.disconnect();
                            bluetoothConnector.join();
                        }
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    }
                    finish();
                    break;
            }
        }
    }

    private void updateConnectionStateView() {
        if (bluetoothConnector != null && bluetoothConnector.isConnected()) {
            connectionStateTextView.setText(Settings.getInstance().getLanguageWrapper().
                    getViewString(LanguageWrapper.CONNECTED));
        } else {
            connectionStateTextView.setText(Settings.getInstance().getLanguageWrapper().
                    getViewString(LanguageWrapper.NO_CONNECTION));
        }
    }

    private void setLocaleLanguage() {
        updateConnectionStateView();
        // buttons
        motionButton.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.MOTION_BUTTON));
        servoButton.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.SERVO_BUTTON));
        sensorsButton.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.SENSORS_BUTTON));
        settingsButton.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.SETTINGS_BUTTON));
        exitButton.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.EXIT_BUTTON));
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        Listener listener = new Listener();
        motionButton = (Button) findViewById(R.id.motion_button);
        servoButton = (Button) findViewById(R.id.servo_button);
        sensorsButton = (Button) findViewById(R.id.sensors_button);
        settingsButton = (Button) findViewById(R.id.settings_button);
        exitButton = (Button) findViewById(R.id.exit_button);
        connectionStateTextView = (TextView) findViewById(R.id.connection_state_tv_main_activity);
        motionButton.setOnClickListener(listener);
        servoButton.setOnClickListener(listener);
        sensorsButton.setOnClickListener(listener);
        settingsButton.setOnClickListener(listener);
        exitButton.setOnClickListener(listener);
        setLocaleLanguage();


        BluetoothAdapter bluetoothAdapter = BluetoothAdapter.getDefaultAdapter();
        if (bluetoothAdapter == null) {
            connectionStateTextView.setText(R.string.have_no_bluetooth_module);
            Log.d(TAG, "You have no bluetooth.");
        }
        if (bluetoothAdapter != null && bluetoothAdapter.isEnabled()) {
            Handler handler = new Handler() {
                @Override
                public void handleMessage(Message msg) {
                    super.handleMessage(msg);

                }
            };
            bluetoothConnector = BluetoothConnector.getInstance();
            bluetoothConnector.connect();
            bluetoothConnector.setHandler(handler);
            updateConnectionStateView();
        } else {
            // Bluetooth выключен. Предложим пользователю включить его.
            Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
            startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
        }

    }

    @Override
    protected void onResume() {
        super.onResume();
        setLocaleLanguage();
    }

    @Override
    protected void onActivityResult(int requestCode, int resultCode, Intent data) {
        super.onActivityResult(requestCode, resultCode, data);
        if (requestCode == REQUEST_ENABLE_BT && requestCode == RESULT_OK) {
            Log.d(TAG, "Bluetooth connected");
            Handler handler = new Handler() {
                @Override
                public void handleMessage(Message msg) {
                    super.handleMessage(msg);

                }
            };
            bluetoothConnector = BluetoothConnector.getInstance();
            bluetoothConnector.connect();
            bluetoothConnector.setHandler(handler);
            updateConnectionStateView();
        }
    }

}
