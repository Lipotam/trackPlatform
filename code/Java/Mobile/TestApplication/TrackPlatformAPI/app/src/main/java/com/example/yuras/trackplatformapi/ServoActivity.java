package com.example.yuras.trackplatformapi;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.support.v7.widget.Toolbar;
import android.util.Log;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;

public class ServoActivity extends AppCompatActivity {
    private int angleX;
    private int angleY;

    public TrackPlatform trackPlatform;

    private Handler handler;
    private StringBuilder stringBuilder;
    private String receivedMessage;

    Button up, down, left, right;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_servo);
        Toolbar toolbar = (Toolbar) findViewById(R.id.toolbar);
        setSupportActionBar(toolbar);

        getSupportActionBar().setDisplayHomeAsUpEnabled(true);

        up = (Button)findViewById(R.id.up_button);
        left = (Button)findViewById(R.id.left_button);
        right = (Button)findViewById(R.id.right_button);
        down = (Button)findViewById(R.id.down_button);

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
                        String[] arr = receivedMessage.split(";");
                        angleX = Integer.valueOf(arr[0]);
                        angleY = Integer.valueOf(arr[1]);
                        Log.d(Constants.TAG, "Angles: " + String.valueOf(angleX) + " " + String.valueOf(angleY));
                    }
                }
            }
        };



        up.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                while (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    trackPlatform.send(ServoCommands.SET_VERTICAL_ANGLE.getValue() + angleY + ";");
                    angleY += 1;
                    if (angleY > 255) {
                        angleY = 255;
                    }
                }/* else if (motionEvent.getAction() == MotionEvent.ACTION_UP) {
                    //trackPlatform.send(ServoCommands.SET_HORIZONTAL_ANGLE.getValue() + (angleX) + ";");
                    //trackPlatform.send(ServoCommands.SET_VERTICAL_ANGLE.getValue() + (angleY) + ";");
                }*/
                trackPlatform.send(ServoCommands.GET_ANGLES.getValue());
                Log.d(Constants.TAG, "Angles: " + angleX + "  " + angleY);
                return false;
            }
        });

        left.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                while (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    trackPlatform.send(ServoCommands.SET_HORIZONTAL_ANGLE.getValue() + angleX + ";");
                    angleX -= 1;
                    if (angleY < 0) {
                        angleY = 0;
                    }
                } /*else if (motionEvent.getAction() == MotionEvent.ACTION_UP){
                    //trackPlatform.send(ServoCommands.SET_HORIZONTAL_ANGLE.getValue() + (angleX) + ";");
                    //trackPlatform.send(ServoCommands.SET_VERTICAL_ANGLE.getValue() + (angleY) + ";");
                }*/
                trackPlatform.send(ServoCommands.GET_ANGLES.getValue());
                Log.d(Constants.TAG, "Angles: " + angleX + "  " + angleY);
                return false;
            }
        });

        right.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                while (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    trackPlatform.send(ServoCommands.SET_HORIZONTAL_ANGLE.getValue() + angleX + ";");
                    angleX += 1;
                    if (angleX > 255) {
                        angleX = 255;
                    }
                } /*else if (motionEvent.getAction() == MotionEvent.ACTION_UP){
                    //trackPlatform.send(ServoCommands.SET_HORIZONTAL_ANGLE.getValue() + (angleX) + ";");
                    //trackPlatform.send(ServoCommands.SET_VERTICAL_ANGLE.getValue() + (angleY) + ";");
                }*/
                trackPlatform.send(ServoCommands.GET_ANGLES.getValue());
                Log.d(Constants.TAG, "Angles: " + angleX + "  " + angleY);
                return false;
            }
        });

        down.setOnTouchListener(new View.OnTouchListener() {
            @Override
            public boolean onTouch(View view, MotionEvent motionEvent) {
                while (motionEvent.getAction() == MotionEvent.ACTION_DOWN) {
                    trackPlatform.send(ServoCommands.SET_VERTICAL_ANGLE.getValue() + angleY + ";");
                    angleY -= 1;
                    if (angleY < 0) {
                        angleY = 0;
                    }
                }
/*                } else if (motionEvent.getAction() == MotionEvent.ACTION_UP){
                    //trackPlatform.send(ServoCommands.SET_HORIZONTAL_ANGLE.getValue() + (angleX) + ";");
                    //trackPlatform.send(ServoCommands.SET_VERTICAL_ANGLE.getValue() + (angleY) + ";");
                }*/
                trackPlatform.send(ServoCommands.GET_ANGLES.getValue());
                Log.d(Constants.TAG, "Angles: " + angleX + "  " + angleY);
                return false;
            }
        });

        trackPlatform = new TrackPlatform(this, handler);
    }

    @Override
    protected void onResume() {
        super.onResume();
        trackPlatform.connect();

        trackPlatform.send(ServoCommands.GET_ANGLES.getValue());
    }

    @Override
    public void onPause() {
        super.onPause();

        trackPlatform.disconnect();
    }


/*    public void turnServoUp(View v) {
        trackPlatform.send(ServoCommands.SET_VERTICAL_ANGLE.getValue() + (angleY + 1));
    }

    public void turnServoDown(View v) {
        trackPlatform.send(ServoCommands.SET_VERTICAL_ANGLE.getValue() + (angleY - 1));
    }

    public void turnServoLeft(View v) {
        trackPlatform.send(ServoCommands.SET_HORIZONTAL_ANGLE.getValue() + (angleX - 1));
    }

    public void turnServoRight(View v) {
        trackPlatform.send(ServoCommands.SET_HORIZONTAL_ANGLE.getValue() + (angleX + 1));
    }*/
}
