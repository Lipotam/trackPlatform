package com.example.kimentii.application20.api;


import com.example.kimentii.application20.constants.Constants;

public class API4 extends API {

    public API4() {
        apiEnum = Constants.ApiEnum.API4;
    }

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

    // не тещено
    @Override
    public byte[] getDisconnectCommand() {
        byte command[] = {(byte) 0x02, Constants.Controllers.COMMUNICATION_CONTROLLER_ID.getValue(),
                Constants.Communication.STOP_COMMUNICATION.getValue(), (byte) 0x00, (byte) 0x00};
        CRC16Modbus crc = new CRC16Modbus();
        crc.update(command, 0, 3);
        command[command.length - 2] = (byte) ((crc.getValue() & 0x000000ff));
        command[command.length - 1] = (byte) ((crc.getValue() & 0x0000ff00) >>> 8);
        return command;
    }

    @Override
    public byte[] getMoveForwardCommand() {
        byte command[] = {(byte) 0x04, Constants.Controllers.MOVEMENT_CONTROLLER_ID.getValue(),
                Constants.Movement.FORWARD_WITH_SPEED.getValue(), (byte) '5', (byte) '0',
                (byte) 0x00, (byte) 0x00};
        CRC16Modbus crc = new CRC16Modbus();
        crc.update(command, 0, command.length - 2);
        command[command.length - 2] = (byte) ((crc.getValue() & 0x000000ff));
        command[command.length - 1] = (byte) ((crc.getValue() & 0x0000ff00) >>> 8);
        return command;
    }

    @Override
    public byte[] getMoveRightCommand() {
        byte command[] = {(byte) 0x04, Constants.Controllers.MOVEMENT_CONTROLLER_ID.getValue(),
                Constants.Movement.TURN_IN_CLOCK_ARROW_DIRECTION.getValue(), (byte) '5', (byte) '0',
                (byte) 0x00, (byte) 0x00};
        CRC16Modbus crc = new CRC16Modbus();
        crc.update(command, 0, command.length - 2);
        command[command.length - 2] = (byte) ((crc.getValue() & 0x000000ff));
        command[command.length - 1] = (byte) ((crc.getValue() & 0x0000ff00) >>> 8);
        return command;
    }

    @Override
    public byte[] getMoveLeftCommand() {
        byte command[] = {(byte) 0x05, Constants.Controllers.MOVEMENT_CONTROLLER_ID.getValue(),
                Constants.Movement.TURN_IN_CLOCK_ARROW_DIRECTION.getValue(), (byte) '-', (byte) '5',
                (byte) '0', (byte) 0x00, (byte) 0x00};
        CRC16Modbus crc = new CRC16Modbus();
        crc.update(command, 0, command.length - 2);
        command[command.length - 2] = (byte) ((crc.getValue() & 0x000000ff));
        command[command.length - 1] = (byte) ((crc.getValue() & 0x0000ff00) >>> 8);
        return command;
    }

    @Override
    public byte[] getMoveBackCommand() {
        byte command[] = {(byte) 0x05, Constants.Controllers.MOVEMENT_CONTROLLER_ID.getValue(),
                Constants.Movement.FORWARD_WITH_SPEED.getValue(), (byte) '-', (byte) '5',
                (byte) '0', (byte) 0x00, (byte) 0x00};
        CRC16Modbus crc = new CRC16Modbus();
        crc.update(command, 0, command.length - 2);
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
    public byte[] getGetAngleCommand() {
        return new byte[0];
    }

    // не тещено
    @Override
    public byte[] getSetAngleCommand(int angle, int surface) {
        byte angleBytes[] = String.valueOf(angle).getBytes();
        byte prefix[] = {Constants.Controllers.SERVO_CONTROLLER_ID.getValue(),
                0x05};
        byte command[] = new byte[angleBytes.length + prefix.length + 3];
        command[0] = (byte) (angleBytes.length + prefix.length);
        for (int i = 0; i < prefix.length; i++) {
            command[i + 1] = prefix[i];
        }
        for (int i = 0; i < angleBytes.length; i++) {
            command[i + prefix.length + 1] = prefix[i];
        }
        CRC16Modbus crc = new CRC16Modbus();
        crc.update(command, 0, angleBytes.length + prefix.length + 1);
        command[command.length - 2] = (byte) ((crc.getValue() & 0x000000ff));
        command[command.length - 1] = (byte) ((crc.getValue() & 0x0000ff00) >>> 8);
        return command;
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
