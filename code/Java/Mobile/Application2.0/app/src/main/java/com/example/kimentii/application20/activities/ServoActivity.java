package com.example.kimentii.application20.activities;

import android.app.Activity;
import android.os.Bundle;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.widget.Button;

import com.example.kimentii.application20.R;
import com.example.kimentii.application20.settings.Settings;
import com.example.kimentii.application20.wrappers.LanguageWrapper;

public class ServoActivity extends AppCompatActivity {

    private Button upButton;
    private Button rightButton;
    private Button leftButton;
    private Button downButton;

    private void setLocaleLanguage() {
        upButton.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.UP_SERVO_BUTTON));
        rightButton.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.RIGHT_SERVO_BUTTON));
        leftButton.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.LEFT_SERVO_BUTTON));
        downButton.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.DOWN_SERVO_BUTTON));
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_servo);
        ActionBar actionBar = getSupportActionBar();
        actionBar.setHomeButtonEnabled(true);
        actionBar.setDisplayHomeAsUpEnabled(true);
        upButton = (Button) findViewById(R.id.up_sero_button);
        rightButton = (Button) findViewById(R.id.right_servo_button);
        leftButton = (Button) findViewById(R.id.left_servo_button);
        downButton = (Button) findViewById(R.id.down_servo_button);
        setLocaleLanguage();
    }
}
