package com.example.yuras.trackplatformapi;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.design.widget.FloatingActionButton;
import android.support.design.widget.Snackbar;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;

public class MovingActivity extends AppCompatActivity {
    TrackPlatform trackPlatform;
    Handler handler;

    Button forward, back, right, left, stop;

    StringBuilder stringBuilder;
    String receivedMessage;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_moving);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        forward = (Button)findViewById(R.id.forward_button);
        left = (Button)findViewById(R.id.left_button);
        right = (Button)findViewById(R.id.right_button);
        back = (Button)findViewById(R.id.back_button);
        stop = (Button)findViewById(R.id.stop_button);

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

        trackPlatform = new TrackPlatform(this, handler);

        forward.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    trackPlatform.send(MovingCommands.FORWARD.getValue());
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    trackPlatform.send(MovingCommands.STOP.getValue());
                }
                return false;
            }
        });

        left.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    trackPlatform.send(MovingCommands.LEFT.getValue());
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP){
                    trackPlatform.send(MovingCommands.STOP.getValue());
                }
                return false;
            }
        });

        right.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    trackPlatform.send(MovingCommands.RIGHT.getValue());
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP){
                    trackPlatform.send(MovingCommands.STOP.getValue());
                }
                return false;
            }
        });

        back.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                if (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    trackPlatform.send(MovingCommands.BACK.getValue());
                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP){
                    trackPlatform.send(MovingCommands.STOP.getValue());
                }
                return false;
            }
        });
    }

    @Override
    protected void onResume() {
        super.onResume();
        trackPlatform.connect();
    }

    @Override
    public void onPause() {
        super.onPause();
        trackPlatform.disconnect();
    }

    public void onStopClick(View v) {
        trackPlatform.send(MovingCommands.STOP.getValue());
    }

}
