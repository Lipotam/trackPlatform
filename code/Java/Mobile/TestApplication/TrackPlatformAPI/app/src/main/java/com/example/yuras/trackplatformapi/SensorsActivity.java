package com.example.yuras.trackplatformapi;

import android.content.Intent;
import android.os.Bundle;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;
import android.widget.Button;

public class SensorsActivity extends AppCompatActivity {
    Button lineSensorsButton;
    Button distanceSensorsButton;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_sensors);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        lineSensorsButton = (Button) findViewById(R.id.line_activity_button);
        distanceSensorsButton = (Button) findViewById(R.id.distance_activity_button);
    }

    public void setLineSensorsButton(View v) {
        startActivity(new Intent(this, LineSensorsActivity.class));
    }

    public void setDistanceSensorsButton(View v) {
        startActivity(new Intent(this, DistanceSensorsActivity.class));
    }
}
