package com.example.kimentii.application20.activities;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.widget.Button;
import android.widget.TextView;

import com.example.kimentii.application20.R;
import com.example.kimentii.application20.connectors.BluetoothConnector;
import com.example.kimentii.application20.settings.Settings;
import com.example.kimentii.application20.wrappers.LanguageWrapper;

public class SensorsActivity extends AppCompatActivity {

    BluetoothConnector bluetoothConnector;
    private TextView distanceSensorsTV;
    private TextView lineSensorsTV;
    private TextView connectionStateTextView;

    // distance sensors
    private TextView firstDistanceSensorTV;
    private TextView secondDistanceSensorTV;
    private TextView thirdDistanceSensorTV;
    private TextView fourthDistanceSensorTV;
    private TextView fifthDistanceSensorTV;

    // line sensors
    private TextView firstLineSensorTV;
    private TextView secondLineSensorTV;
    private TextView thirdLineSensorTV;
    private TextView fourthLineSensorTV;
    private TextView fifthLineSensorTV;

    private void setLocaleLanguage() {
        if (bluetoothConnector != null && bluetoothConnector.isConnected()) {
            connectionStateTextView.setText(Settings.getInstance().getLanguageWrapper().
                    getViewString(LanguageWrapper.CONNECTED));
        } else {
            connectionStateTextView.setText(Settings.getInstance().getLanguageWrapper().
                    getViewString(LanguageWrapper.NO_CONNECTION));
        }
        distanceSensorsTV.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.DISTANCE_SENSORS));
        lineSensorsTV.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.LINE_SENSORS));

        // distance sensors
        firstDistanceSensorTV.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.FIRST_SENSOR));
        secondDistanceSensorTV.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.SECOND_SENSOR));
        thirdDistanceSensorTV.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.THIRD_SENSOR));
        fourthDistanceSensorTV.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.FOURTH_SENSOR));
        fifthDistanceSensorTV.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.FIRST_SENSOR));

        // line  sensors
        firstLineSensorTV.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.FIRST_SENSOR));
        secondLineSensorTV.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.SECOND_SENSOR));
        thirdLineSensorTV.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.THIRD_SENSOR));
        fourthLineSensorTV.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.FOURTH_SENSOR));
        fifthLineSensorTV.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.FIFTH_SENSOR));

    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sensors);
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

        connectionStateTextView = (TextView) findViewById(R.id.connection_state_tv_sensors_activity);
        distanceSensorsTV = (TextView) findViewById(R.id.distance_sensors_tv);
        lineSensorsTV = (TextView) findViewById(R.id.line_sensors_tv);

        // distance sensors
        firstDistanceSensorTV = (TextView) findViewById(R.id.first_distance_sensor_tv);
        secondDistanceSensorTV = (TextView) findViewById(R.id.second_distance_sensor_tv);
        thirdDistanceSensorTV = (TextView) findViewById(R.id.third_distance_sensor_tv);
        fourthDistanceSensorTV = (TextView) findViewById(R.id.fourth_distance_sensor_tv);
        fifthDistanceSensorTV = (TextView) findViewById(R.id.fifth_distance_sensor_tv);

        // line sensors
        firstLineSensorTV = (TextView) findViewById(R.id.first_line_sensor_tv);
        secondLineSensorTV = (TextView) findViewById(R.id.second_line_sensor_tv);
        thirdLineSensorTV = (TextView) findViewById(R.id.third_line_sensor_tv);
        fourthLineSensorTV = (TextView) findViewById(R.id.fourth_line_sensor_tv);
        fifthLineSensorTV = (TextView) findViewById(R.id.fifth_line_sensor_tv);

        setLocaleLanguage();
    }
}
