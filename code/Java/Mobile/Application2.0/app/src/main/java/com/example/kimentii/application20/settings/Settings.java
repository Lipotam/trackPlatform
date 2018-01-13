package com.example.kimentii.application20.settings;

import com.example.kimentii.application20.api.API;
import com.example.kimentii.application20.api.API1;
import com.example.kimentii.application20.api.API2;
import com.example.kimentii.application20.api.API3;
import com.example.kimentii.application20.api.API4;
import com.example.kimentii.application20.connectors.BluetoothConnector;
import com.example.kimentii.application20.constants.Constants;
import com.example.kimentii.application20.wrappers.LanguageWrapper;

public class Settings {
    private LanguageWrapper languageWrapper;
    private API api;
    private static Settings settings;

    private Settings() {
        languageWrapper = new LanguageWrapper(LanguageWrapper.ENGLISH);
        api = new API4();
    }

    public static Settings getInstance() {
        if (settings == null) {
            settings = new Settings();
        }
        return settings;
    }

    public LanguageWrapper getLanguageWrapper() {
        return languageWrapper;
    }

    public API getApi() {
        return api;
    }

    public void setApi(Constants.ApiEnum api) {
        switch (api) {
            case API1:
                this.api = new API1();
                break;
            case API2:
                this.api = new API2();
                break;
            case API3:
                this.api = new API3();
                break;
            case API4:
                this.api = new API4();
                break;
        }
    }
}
