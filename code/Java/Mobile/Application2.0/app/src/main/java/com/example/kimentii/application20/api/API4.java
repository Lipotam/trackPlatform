package com.example.kimentii.application20.api;


import com.example.kimentii.application20.constants.Constants;

public class API4 implements API {

    @Override
    public byte[] getConnectCommand() {
        byte command[] = {(byte) 0x03, Constants.Controllers.COMMUNICATION_CONTROLLER_ID.getValue(),
                Constants.Communication.START_COMMUNICATION.getValue(), Constants.ApiEnum.API4.getValue(),
                (byte) 0x00, (byte) 0x00};
        CRC16Modbus crc = new CRC16Modbus();
        crc.update(command, 0, 4);
        command[command.length - 2] = (byte) ((crc.getValue() & 0x000000ff));
        command[command.length - 1] = (byte) ((crc.getValue() & 0x0000ff00) >>> 8);
        return command;
    }

    @Override
    public byte[] getDisconnectCommand() {
        return new byte[0];
    }

    @Override
    public byte[] getMoveForwardCommand() {
        byte command[] = {(byte) 0x03, Constants.Controllers.MOVEMENT_CONTROLLER_ID.getValue(),
                0x06, (byte) 50,
                (byte) 0x00, (byte) 0x00};
        CRC16Modbus crc = new CRC16Modbus();
        crc.update(command, 0, 4);
        command[command.length - 2] = (byte) ((crc.getValue() & 0x000000ff));
        command[command.length - 1] = (byte) ((crc.getValue() & 0x0000ff00) >>> 8);
        return command;
    }

    @Override
    public byte[] getMoveRightCommand() {
        byte command[] = {(byte) 0x03, Constants.Controllers.MOVEMENT_CONTROLLER_ID.getValue(),
                0x0A, 50, (byte) 0x00, (byte) 0x00};
        CRC16Modbus crc = new CRC16Modbus();
        crc.update(command, 0, 4);
        command[command.length - 2] = (byte) ((crc.getValue() & 0x000000ff));
        command[command.length - 1] = (byte) ((crc.getValue() & 0x0000ff00) >>> 8);
        return command;
    }

    @Override
    public byte[] getMoveLeftCommand() {
        byte command[] = {(byte) 0x03, Constants.Controllers.MOVEMENT_CONTROLLER_ID.getValue(),
                0x0A, -50, (byte) 0x00, (byte) 0x00};
        CRC16Modbus crc = new CRC16Modbus();
        crc.update(command, 0, 4);
        command[command.length - 2] = (byte) ((crc.getValue() & 0x000000ff));
        command[command.length - 1] = (byte) ((crc.getValue() & 0x0000ff00) >>> 8);
        return command;
    }

    @Override
    public byte[] getMoveBackCommand() {
        byte command[] = {(byte) 0x03, Constants.Controllers.MOVEMENT_CONTROLLER_ID.getValue(),
                0x06, (byte) -50,
                (byte) 0x00, (byte) 0x00};
        CRC16Modbus crc = new CRC16Modbus();
        crc.update(command, 0, 4);
        command[command.length - 2] = (byte) ((crc.getValue() & 0x000000ff));
        command[command.length - 1] = (byte) ((crc.getValue() & 0x0000ff00) >>> 8);
        return command;
    }

    @Override
    public byte[] getStopCommand() {
        byte command[] = {(byte) 0x02, Constants.Controllers.MOVEMENT_CONTROLLER_ID.getValue(),
                0x05, (byte) 0x00, (byte) 0x00};
        CRC16Modbus crc = new CRC16Modbus();
        crc.update(command, 0, 3);
        command[command.length - 2] = (byte) ((crc.getValue() & 0x000000ff));
        command[command.length - 1] = (byte) ((crc.getValue() & 0x0000ff00) >>> 8);
        return command;
    }

    @Override
    public byte[] getTurnUpServoCommand() {
        return new byte[0];
    }

    @Override
    public byte[] getTurnRightServoCommand() {
        return new byte[0];
    }

    @Override
    public byte[] getTurnLeftServoCommand() {
        return new byte[0];
    }

    @Override
    public byte[] getTurnDownServoCommand() {
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
    public byte[] getChangeApiCommand(int i) {
        return new byte[0];
    }
}
