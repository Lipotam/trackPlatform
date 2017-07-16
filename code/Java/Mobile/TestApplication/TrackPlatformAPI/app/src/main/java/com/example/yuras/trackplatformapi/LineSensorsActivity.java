package com.example.yuras.trackplatformapi;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.View;
import android.widget.TextView;

public class LineSensorsActivity extends AppCompatActivity {
    Handler handler;
    TrackPlatform trackPlatform;

    StringBuilder stringBuilder;
    String receivedMessage;
    String arr[];

    TextView[] textViews;

    TextView textView1;
    TextView textView2;
    TextView textView3;
    TextView textView4;
    TextView textView5;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_distance_sensors);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        arr = new String[5];
        textViews = new TextView[5];

        textView1 = (TextView) findViewById(R.id.first_line_sensor_tv);
        textView2 = (TextView) findViewById(R.id.second_line_sensor_tv);
        textView3 = (TextView) findViewById(R.id.third_line_sensor_tv);
        textView4 = (TextView) findViewById(R.id.fourth_line_sensor_tv);
        textView5 = (TextView) findViewById(R.id.fifth_line_sensor_tv);

        //textViews[0] = (TextView) findViewById(R.id.first_line_sensor_tv);
        //textViews[1] = (TextView) findViewById(R.id.second_line_sensor_tv);
        //textViews[2] = (TextView) findViewById(R.id.third_line_sensor_tv);
        //textViews[3] = (TextView) findViewById(R.id.fourth_line_sensor_tv);
        //textViews[4] = (TextView) findViewById(R.id.fifth_line_sensor_tv);

        stringBuilder = new StringBuilder();

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
                        arr = receivedMessage.split(";");
                        for(int i = 0; i < 5; i++) {
                            Log.d(Constants.TAG, arr[i]);
                            //textViews[i].setText(arr[i]);
                        }
                        textView1.setText(String.valueOf(arr[0]));
                        textView2.setText(arr[1]);
                        textView3.setText(arr[2]);
                        textView4.setText(arr[3]);
                        textView5.setText(arr[4]);
                    }
                    trackPlatform.send(LineSensorsCommands.LINE_SENSORS_ALL.getValue());
                }
            }
        };

        trackPlatform = new TrackPlatform(this, handler);
    }

    @Override
    protected void onResume() {
        super.onResume();
        trackPlatform.connect();
        trackPlatform.send(LineSensorsCommands.LINE_SENSORS_ALL.getValue());
    }

    @Override
    public void onPause() {
        super.onPause();
        trackPlatform.disconnect();
    }
}
