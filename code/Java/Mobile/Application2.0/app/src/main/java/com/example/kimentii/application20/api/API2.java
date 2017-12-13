package com.example.kimentii.application20.api;

import com.example.kimentii.application20.constants.Constants;

public class API2 extends API {

    public API2() {
        apiEnum = Constants.ApiEnum.API2;
    }

    @Override
    public byte[] getConnectCommand(Constants.ApiEnum api) {
        return new byte[0];
    }

    @Override
    public byte[] getDisconnectCommand() {
        return new byte[0];
    }

    @Override
    public byte[] getReconnectCommand() {
        return new byte[0];
    }

    @Override
    public byte[] getMoveForwardCommand() {
        return new byte[0];
    }

    @Override
    public byte[] getMoveRightCommand() {
        return new byte[0];
    }

    @Override
    public byte[] getMoveLeftCommand() {
        return new byte[0];
    }

    @Override
    public byte[] getMoveBackCommand() {
        return new byte[0];
    }

    @Override
    public byte[] getStopCommand() {
        return new byte[0];
    }

    @Override
    public byte[] getGetAngleCommand() {
        return new byte[0];
    }

    @Override
    public byte[] getSetAngleCommand(int angle, char surface) {
        return new byte[0];
    }

    @Override
    public byte[] getInfoFromDistanceSensorCommand(int i) {
        return new byte[0];
    }

    @Override
    public byte[] getInfoFromLineSensorCommand(int i) {
        return new byte[0];
    }

    @Override
    public byte[] getInfoFromAllDistanceSensorsCommand() {
        return new byte[0];
    }

    @Override
    public byte[] getInfoFromAllLineSensorsCommand() {
        return new byte[0];
    }

}