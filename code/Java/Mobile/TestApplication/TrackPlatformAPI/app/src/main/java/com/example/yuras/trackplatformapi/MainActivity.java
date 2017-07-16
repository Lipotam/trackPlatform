package com.example.yuras.trackplatformapi;

import android.content.Intent;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private TrackPlatform trackPlatform;
    private Handler handler;

    private TextView textView;
    private EditText editText;
    private Button button;

    private StringBuilder stringBuilder;
    private String receivedMessage;
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        /*textView = (TextView) findViewById(R.id.text_from_bt);
        editText = (EditText) findViewById(R.id.edit_text);
        button = (Button) findViewById(R.id.send_button);

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                trackPlatform.send(String.valueOf(MovingCommands.FORWARD.getValue()));
            }
        });

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
                    }
                }
            }
        };*/

        //trackPlatform = new TrackPlatform(this, handler);
    }

    @Override
    protected void onResume() {
        super.onResume();
        //trackPlatform.connect();
    }

    @Override
    public void onPause() {
        super.onPause();
        //trackPlatform.disconnect();
    }

    public void movingActivity(View v) {
        startActivity(new Intent(this, MovingActivity.class));
    }

    public void sensorsActivity(View v) {
        startActivity(new Intent(this, SensorsActivity.class));
    }

    public void servoActivity(View v) {
        startActivity(new Intent(this, ServoActivity.class));
    }
}
