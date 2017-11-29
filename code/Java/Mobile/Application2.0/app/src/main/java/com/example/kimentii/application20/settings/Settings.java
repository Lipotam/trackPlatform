package com.example.kimentii.application20.settings;

import com.example.kimentii.application20.connectors.BluetoothConnector;
import com.example.kimentii.application20.wrappers.LanguageWrapper;

public class Settings {
    private LanguageWrapper languageWrapper;
    private static Settings settings;

    private Settings() {
        languageWrapper = new LanguageWrapper(LanguageWrapper.ENGLISH);
    }

    public static Settings getInstance() {
        if (settings == null) {
            settings = new Settings();
        }
        return settings;
    }

    public LanguageWrapper getLanguageWrapper(){
        return languageWrapper;
    }

}
