package com.example.kimentii.application20.activities;

import android.app.Activity;
import android.os.Bundle;
import android.support.v7.app.ActionBar;
import android.support.v7.app.AppCompatActivity;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.Spinner;
import android.widget.TextView;

import com.example.kimentii.application20.R;
import com.example.kimentii.application20.settings.Settings;
import com.example.kimentii.application20.wrappers.LanguageWrapper;

import javax.xml.datatype.DatatypeConstants;

public class SettingsActivity extends AppCompatActivity {
    public static final String TAG = "TAG";
    public static final int RUSSIAN_LANGUAGE_POSITION = 0;
    public static final int ENGLISH_LANGUAGE_POSITION = 1;


    private TextView languageTextView;
    private Spinner languageSpinner;
    private Spinner apiSpinner;

    private void setLocaleLanguage() {
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
    }
}
