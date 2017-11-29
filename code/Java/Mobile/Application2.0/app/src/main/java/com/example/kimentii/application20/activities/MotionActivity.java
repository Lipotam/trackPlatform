package com.example.kimentii.application20.activities;

import android.app.Activity;
import android.os.Bundle;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.widget.Button;

import com.example.kimentii.application20.R;
import com.example.kimentii.application20.settings.Settings;
import com.example.kimentii.application20.wrappers.LanguageWrapper;

public class MotionActivity extends AppCompatActivity {

    private Button forwardButton;
    private Button rightButton;
    private Button leftButton;
    private Button backButton;
    private Button stopButton;

    private void setLocaleLanguage() {
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
        forwardButton = (Button) findViewById(R.id.forward_button);
        rightButton = (Button) findViewById(R.id.right_button);
        leftButton = (Button) findViewById(R.id.left_button);
        backButton = (Button) findViewById(R.id.back_button);
        stopButton = (Button) findViewById(R.id.stop_button);
        setLocaleLanguage();

    }
}
