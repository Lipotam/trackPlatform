package com.example.kimentii.application20.language_resources;


import com.example.kimentii.application20.wrappers.LanguageWrapper;

import java.util.ListResourceBundle;

public class EnglishLanguage extends ListResourceBundle {
    @Override
    protected Object[][] getContents() {
        Object[][] resources = new Object[1][2];
        resources[0][0] = LanguageWrapper.NO_CONNECTION;
        resources[0][1] = "no connection";
        return resources;
    }
}
