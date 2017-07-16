package com.example.yuras.trackplatformapi;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.view.View;

public class DistanceSensorsActivity extends AppCompatActivity {
    Handler handler;

    StringBuilder stringBuilder;
    String receivedMessage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_distance_sensors);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        handler = new Handler() {
            public void handleMessage(Message msg) {
                if (msg.what == Constants.MESSAGE_READ) {
                    byte[] readBuf = (byte[]) msg.obj;
                    String strIncom = new String(readBuf, 0, msg.arg1);
                    stringBuilder.append(strIncom);
                    int endOfLineIndex = stringBuilder.indexOf("\r\n");
                    if (endOfLineIndex > 0) {
                        receivedMessage = stringBuilder.substring(0, endOfLineIndex);
                        stringBuilder.delete(0, stringBuilder.length());
                    }
                }
            }
        };
    }
}
