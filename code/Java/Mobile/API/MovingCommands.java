package com.example.yuras.trackplatformapi;

enum MovingCommands {
    FORWARD('\001'),
    LEFT('\002'),
    RIGHT('\003'),
    BACK('\004'),
    STOP('\005');

    private final char value;

    MovingCommands(char value) {
        this.value = value;
    }

    public char getValue() {
        return value;
    }
}
