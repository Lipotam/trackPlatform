package com.example.kimentii.trackplatformwifimodule;

enum MovingCommands {
    FORWARD("\001\001"),
    LEFT("\001\002"),
    RIGHT("\001\003"),
    BACK("\001\004"),
    STOP("\001\005");

    private final String value;

    MovingCommands(String value) {
        this.value = value;
    }

    public String getValue() {
        return value;
    }
}
