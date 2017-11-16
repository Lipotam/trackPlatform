package com.example.kimentii.application20.activities;

import android.content.Intent;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;

import com.example.kimentii.application20.R;

public class MainActivity extends AppCompatActivity {

    private Button motionButton;
    private Button servoButton;
    private Button sensorsButton;
    private Button settingsButton;
    private Button exitButton;

    class Listener implements View.OnClickListener {
        Intent intent;

        @Override
        public void onClick(View v) {
            switch (v.getId()) {
                case R.id.motion_button:
                    intent = new Intent(getApplicationContext(), MotionActivity.class);
                    startActivity(intent);
                    break;
                case R.id.servo_button:
                    intent = new Intent(getApplicationContext(), ServoActivity.class);
                    startActivity(intent);
                    break;
                case R.id.sensors_button:
                    intent = new Intent(getApplicationContext(), SensorsActivity.class);
                    startActivity(intent);
                    break;
                case R.id.settings_button:
                    intent = new Intent(getApplicationContext(), SettingsActivity.class);
                    startActivity(intent);
                    break;
                case R.id.exit_button:
                    break;
            }
        }
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
        motionButton.setOnClickListener(listener);
        servoButton.setOnClickListener(listener);
        sensorsButton.setOnClickListener(listener);
        settingsButton.setOnClickListener(listener);
        exitButton.setOnClickListener(listener);
    }

}
