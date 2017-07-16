package com.example.yuras.trackplatformapi;

/**
 * Created by yuras on 17.05.2017.
 */

public enum LineSensorsCommands {
    DISTANCE_SENSOR("\002\001"),
    DISTANCE_SENSORS_ALL("\002\002"),
    LINE_SENSOR("\002\003"),
    LINE_SENSORS_ALL("\002\004");

    private final String value;

    LineSensorsCommands(String value) {
        this.value = value;
    }

    public String getValue() {
        return value;
    }
}
