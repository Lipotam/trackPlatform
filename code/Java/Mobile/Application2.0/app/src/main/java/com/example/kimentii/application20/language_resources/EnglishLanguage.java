package com.example.kimentii.application20.language_resources;


import com.example.kimentii.application20.wrappers.LanguageWrapper;

import java.util.ListResourceBundle;

public class EnglishLanguage extends ListResourceBundle {
    @Override
    protected Object[][] getContents() {
        Object[][] resources = new Object[24][2];
        int i = 0;
        resources[i][0] = LanguageWrapper.NO_CONNECTION;
        resources[i++][1] = "no connection";
        resources[i][0] = LanguageWrapper.CONNECTED;
        resources[i++][1] = "connected";

        // main menu activity
        resources[i][0] = LanguageWrapper.MOTION_BUTTON;
        resources[i++][1] = "motion";
        resources[i][0] = LanguageWrapper.SERVO_BUTTON;
        resources[i++][1] = "servo";
        resources[i][0] = LanguageWrapper.SENSORS_BUTTON;
        resources[i++][1] = "sensors";
        resources[i][0] = LanguageWrapper.SETTINGS_BUTTON;
        resources[i++][1] = "settings";
        resources[i][0] = LanguageWrapper.EXIT_BUTTON;
        resources[i++][1] = "exit";

        // motion activity
        resources[i][0] = LanguageWrapper.FORWARD_BUTTON;
        resources[i++][1] = "forward";
        resources[i][0] = LanguageWrapper.RIGHT_BUTTON;
        resources[i++][1] = "right";
        resources[i][0] = LanguageWrapper.LEFT_BUTTON;
        resources[i++][1] = "left";
        resources[i][0] = LanguageWrapper.BACK_BUTTON;
        resources[i++][1] = "back";
        resources[i][0] = LanguageWrapper.STOP_BUTTON;
        resources[i++][1] = "stop";

        // servo activity
        resources[i][0] = LanguageWrapper.UP_SERVO_BUTTON;
        resources[i++][1] = "up";
        resources[i][0] = LanguageWrapper.RIGHT_SERVO_BUTTON;
        resources[i++][1] = "right";
        resources[i][0] = LanguageWrapper.LEFT_SERVO_BUTTON;
        resources[i++][1] = "left";
        resources[i][0] = LanguageWrapper.DOWN_SERVO_BUTTON;
        resources[i++][1] = "down";

        // sensors activity
        resources[i][0] = LanguageWrapper.DISTANCE_SENSORS;
        resources[i++][1] = "Distance sensors";
        resources[i][0] = LanguageWrapper.LINE_SENSORS;
        resources[i++][1] = "Line sensors";
        resources[i][0] = LanguageWrapper.FIRST_SENSOR;
        resources[i++][1] = "First sensor";
        resources[i][0] = LanguageWrapper.SECOND_SENSOR;
        resources[i++][1] = "Second sensor";
        resources[i][0] = LanguageWrapper.THIRD_SENSOR;
        resources[i++][1] = "Third sensor";
        resources[i][0] = LanguageWrapper.FOURTH_SENSOR;
        resources[i++][1] = "Fourth sensor";
        resources[i][0] = LanguageWrapper.FIFTH_SENSOR;
        resources[i++][1] = "Fifth sensor";

        // settings activity
        resources[i][0] = LanguageWrapper.LANGUAGE;
        resources[i++][1] = "Language";

        return resources;
    }
}
