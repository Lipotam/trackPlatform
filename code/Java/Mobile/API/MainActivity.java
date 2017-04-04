package com.example.yuras.trackplatformapi;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {
    private TrackPlatform trackPlatform;

    private TextView textView;
    private EditText editText;
    private Button button;
    
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        trackPlatform = new TrackPlatform(this);

        textView = (TextView) findViewById(R.id.text_from_bt);
        editText = (EditText) findViewById(R.id.edit_text);
        button = (Button) findViewById(R.id.send_button);

        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                trackPlatform.send(editText.getText().toString());
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

}
