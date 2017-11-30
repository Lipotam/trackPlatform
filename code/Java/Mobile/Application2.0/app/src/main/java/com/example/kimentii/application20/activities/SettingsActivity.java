package com.example.kimentii.application20.activities;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Spinner;
import android.widget.TextView;

import com.example.kimentii.application20.R;
import com.example.kimentii.application20.connectors.BluetoothConnector;
import com.example.kimentii.application20.constants.Constants;
import com.example.kimentii.application20.settings.Settings;
import com.example.kimentii.application20.wrappers.LanguageWrapper;

import java.util.Set;

import javax.xml.datatype.DatatypeConstants;

public class SettingsActivity extends AppCompatActivity {
    public static final String TAG = "TAG";
    public static final int RUSSIAN_LANGUAGE_POSITION = 0;
    public static final int ENGLISH_LANGUAGE_POSITION = 1;
    public static final int API1_POSITION = 0;
    public static final int API2_POSITION = 1;
    public static final int API3_POSITION = 2;
    public static final int API4_POSITION = 3;


    private TextView languageTextView;
    private TextView connectionStateTextView;
    private Spinner languageSpinner;
    private Spinner apiSpinner;

    private BluetoothConnector bluetoothConnector;

    private void setLocaleLanguage() {
        if (bluetoothConnector != null && bluetoothConnector.isConnected()) {
            connectionStateTextView.setText(Settings.getInstance().getLanguageWrapper().
                    getViewString(LanguageWrapper.CONNECTED));
        } else {
            connectionStateTextView.setText(Settings.getInstance().getLanguageWrapper().
                    getViewString(LanguageWrapper.NO_CONNECTION));
        }
        languageTextView.setText(Settings.getInstance().getLanguageWrapper().
                getViewString(LanguageWrapper.LANGUAGE));
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_settings);
        ActionBar actionBar = getSupportActionBar();
        actionBar.setHomeButtonEnabled(true);
        actionBar.setDisplayHomeAsUpEnabled(true);

        Handler handler = new Handler() {
            @Override
            public void handleMessage(Message msg) {
                super.handleMessage(msg);
            }
        };
        bluetoothConnector = BluetoothConnector.getInstance();
        bluetoothConnector.setHandler(handler);

        connectionStateTextView = (TextView) findViewById(R.id.connection_state_tv_settings_activity);
        languageTextView = (TextView) findViewById(R.id.language_tv);
        setLocaleLanguage();

        languageSpinner = (Spinner) findViewById(R.id.language_spinner);
        apiSpinner = (Spinner) findViewById(R.id.api_spinner);

        if (Settings.getInstance().getLanguageWrapper().getLanguage() == LanguageWrapper.RUSSIAN) {
            languageSpinner.setSelection(RUSSIAN_LANGUAGE_POSITION);
        } else {
            languageSpinner.setSelection(ENGLISH_LANGUAGE_POSITION);
        }

        languageSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                if (position == RUSSIAN_LANGUAGE_POSITION) {
                    Log.d(TAG, "Russian was set.");
                    Settings.getInstance().getLanguageWrapper().setLanguage(LanguageWrapper.RUSSIAN);
                    setLocaleLanguage();
                } else {
                    Log.d(TAG, "English was set.");
                    Settings.getInstance().getLanguageWrapper().setLanguage(LanguageWrapper.ENGLISH);
                    setLocaleLanguage();
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });

        apiSpinner.setSelection(Settings.getInstance().getApi().getApiEnum().getValue() - 1);
        apiSpinner.setOnItemSelectedListener(new AdapterView.OnItemSelectedListener() {
            @Override
            public void onItemSelected(AdapterView<?> parent, View view, int position, long id) {
                switch (position) {
                    case API1_POSITION:
                        Settings.getInstance().setApi(Constants.ApiEnum.API1);
                        break;
                    case API2_POSITION:
                        Settings.getInstance().setApi(Constants.ApiEnum.API2);
                        break;
                    case API3_POSITION:
                        Settings.getInstance().setApi(Constants.ApiEnum.API3);
                        break;
                    case API4_POSITION:
                        Settings.getInstance().setApi(Constants.ApiEnum.API4);
                        break;
                }
            }

            @Override
            public void onNothingSelected(AdapterView<?> parent) {

            }
        });
    }
}
