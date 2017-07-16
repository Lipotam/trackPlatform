package com.example.yuras.trackplatformapi;

public enum ServoCommands {
    SET_HORIZONTAL_ANGLE("\003\001"),
    SET_VERTICAL_ANGLE("\003\002"),
    GET_ANGLES("\003\004");

    private final String value;

    ServoCommands(String value) {
        this.value = value;
    }

    public String getValue() {
        return value;
    }
}
