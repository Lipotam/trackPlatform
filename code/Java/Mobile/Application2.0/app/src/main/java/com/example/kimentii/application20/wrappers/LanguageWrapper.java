package com.example.kimentii.application20.wrappers;

import java.util.ResourceBundle;

public class LanguageWrapper {
    public static final String RUSSIAN = "RUSSIAN";
    public static final String ENGLISH = "ENGLISH";
    public static final String NO_CONNECTION = "no connection";
    public static final String CONNECTED = "connected";

    // main menu buttons
    public static final String MOTION_BUTTON = "motion button";
    public static final String SERVO_BUTTON = "servo button";
    public static final String SENSORS_BUTTON = "sensors button";
    public static final String SETTINGS_BUTTON = "settings button";
    public static final String EXIT_BUTTON = "exit button";

    // motion activity buttons
    public static final String FORWARD_BUTTON = "forward button";
    public static final String RIGHT_BUTTON = "right button";
    public static final String LEFT_BUTTON = "left button";
    public static final String BACK_BUTTON = "back button";
    public static final String STOP_BUTTON = "stop button";

    // servo activity buttons
    public static final String UP_SERVO_BUTTON = "up servo button";
    public static final String RIGHT_SERVO_BUTTON = "right servo button";
    public static final String LEFT_SERVO_BUTTON = "left servo button";
    public static final String DOWN_SERVO_BUTTON = "down servo button";

    // sensors activity
    public static final String DISTANCE_SENSORS = "distance sensors";
    public static final String LINE_SENSORS = "line sensors";
    public static final String FIRST_SENSOR = "first sensor";
    public static final String SECOND_SENSOR = "second sensor";
    public static final String THIRD_SENSOR = "third sensor";
    public static final String FOURTH_SENSOR = "fourth sensor";
    public static final String FIFTH_SENSOR = "fifth sensor";

    // settings activity
    public static final String LANGUAGE = "language";

    private ResourceBundle languageResourceBundle;

    public LanguageWrapper(String language) {
        setLanguage(language);
    }

    public void setLanguage(String language) {
        if (language.equals(RUSSIAN)) {
            languageResourceBundle = ResourceBundle.getBundle("com.example.kimentii.application20.language_resources.RussianLanguage");
        } else {
            languageResourceBundle = ResourceBundle.getBundle("com.example.kimentii.application20.language_resources.EnglishLanguage");
        }
    }

    public String getViewString(String key) {
        return languageResourceBundle.getString(key);
    }
}
