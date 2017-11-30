package com.example.kimentii.application20.constants;

public interface Constants {
    String BLUETOOTH_MAC = "20:16:04:11:37:56";

    enum ApiEnum {
        API1((byte) 0x01),
        API2((byte) 0x02),
        API3((byte) 0x03),
        API4((byte) 0x04);

        private byte value;

        ApiEnum(byte value) {
            this.value = value;
        }

        public byte getValue() {
            return value;
        }
    }

    enum Controllers {
        MOVEMENT_CONTROLLER_ID((byte) 0x01),
        SENSORS_CONTROLLER_ID((byte) 0x02),
        SERVO_CONTROLLER_ID((byte) 0x03),
        COMMUNICATION_CONTROLLER_ID((byte) 0x04);


        private byte value;

        Controllers(byte value) {
            this.value = value;
        }

        public byte getValue() {
            return value;
        }
    }

    enum Sensors {
        DISTANCE_SENSOR((byte) 0x01),
        DISTANCE_SENSOR_ALL((byte) 0x02),
        LINE_SENSOR((byte) 0x03),
        LINE_SENSOR_ALL((byte) 0x04);


        private byte value;

        Sensors(byte value) {
            this.value = value;
        }

        public byte getValue() {
            return value;
        }
    }

    enum Servo {
        SET_HORIZONTAL_ANGLE((byte) 0x01),
        SET_VERTICAL_ANGLE((byte) 0x02),
        SET_HORIZONTAL_VERTICAL_ANGLES((byte) 0x03),
        GET_COORDINATES((byte) 0x04),
        SET_ANGLE((byte) 0x05),
        GET_ANGLE((byte) 0x06);
        private byte value;

        Servo(byte value) {
            this.value = value;
        }

        public byte getValue() {
            return value;
        }
    }

    enum Movement {
        FORWARD((byte) 0x01),
        LEFT((byte) 0x02),
        RIGHT((byte) 0x03),
        BACK((byte) 0x04),
        STOP((byte) 0x05),
        FORWARD_WITH_SPEED((byte) 0x06),
        TURN_IN_CLOCK_ARROW_DIRECTION((byte) 0x0A);


        private byte value;

        Movement(byte value) {
            this.value = value;
        }

        public byte getValue() {
            return value;
        }
    }

    enum Communication {
        START_COMMUNICATION((byte) 0x01),
        STOP_COMMUNICATION((byte) 0x02),
        REFRESH_CONNECTION((byte) 0x03);

        private byte value;

        Communication(byte value) {
            this.value = value;
        }

        public byte getValue() {
            return value;
        }
    }

    enum Messages {
        MESSAGES_READ(1);

        private int value;

        Messages(int value) {
            this.value = value;
        }

        public int getValue() {
            return value;
        }
    }
}
