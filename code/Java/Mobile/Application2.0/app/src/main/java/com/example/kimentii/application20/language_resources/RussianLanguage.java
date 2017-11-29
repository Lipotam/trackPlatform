package com.example.kimentii.application20.language_resources;

import com.example.kimentii.application20.wrappers.LanguageWrapper;

import java.util.ListResourceBundle;

public class RussianLanguage extends ListResourceBundle {
    @Override
    protected Object[][] getContents() {
        Object[][] resources = new Object[23][2];
        resources[0][0] = LanguageWrapper.NO_CONNECTION;
        resources[0][1] = "нет подключения";
        resources[1][0] = LanguageWrapper.CONNECTED;
        resources[1][1] = "подключен";

        // main menu activity
        resources[2][0] = LanguageWrapper.MOTION_BUTTON;
        resources[2][1] = "движение";
        resources[3][0] = LanguageWrapper.SERVO_BUTTON;
        resources[3][1] = "сервоприводы";
        resources[4][0] = LanguageWrapper.SENSORS_BUTTON;
        resources[4][1] = "сенсоры";
        resources[5][0] = LanguageWrapper.SETTINGS_BUTTON;
        resources[5][1] = "настройки";
        resources[6][0] = LanguageWrapper.EXIT_BUTTON;
        resources[6][1] = "выход";

        // motion activity
        resources[7][0] = LanguageWrapper.FORWARD_BUTTON;
        resources[7][1] = "вперед";
        resources[8][0] = LanguageWrapper.RIGHT_BUTTON;
        resources[8][1] = "вправо";
        resources[9][0] = LanguageWrapper.LEFT_BUTTON;
        resources[9][1] = "влеов";
        resources[10][0] = LanguageWrapper.BACK_BUTTON;
        resources[10][1] = "назад";
        resources[10][0] = LanguageWrapper.STOP_BUTTON;
        resources[10][1] = "стоп";

        // servo activity
        resources[11][0] = LanguageWrapper.UP_SERVO_BUTTON;
        resources[11][1] = "вверх";
        resources[12][0] = LanguageWrapper.RIGHT_SERVO_BUTTON;
        resources[12][1] = "вправо";
        resources[13][0] = LanguageWrapper.LEFT_SERVO_BUTTON;
        resources[13][1] = "влево";
        resources[14][0] = LanguageWrapper.DOWN_SERVO_BUTTON;
        resources[14][1] = "вниз";

        // sensors activity
        resources[15][0] = LanguageWrapper.DISTANCE_SENSORS;
        resources[15][1] = "Датчики расстояния";
        resources[16][0] = LanguageWrapper.LINE_SENSORS;
        resources[16][1] = "Дитчики линии";
        resources[17][0] = LanguageWrapper.FIRST_SENSOR;
        resources[17][1] = "Первый датчик";
        resources[18][0] = LanguageWrapper.SECOND_SENSOR;
        resources[18][1] = "Второй датчик";
        resources[19][0] = LanguageWrapper.THIRD_SENSOR;
        resources[19][1] = "Третий датчик";
        resources[20][0] = LanguageWrapper.FOURTH_SENSOR;
        resources[20][1] = "четвертый датчик";
        resources[21][0] = LanguageWrapper.FIFTH_SENSOR;
        resources[21][1] = "пятый датчик";

        // settings activity
        resources[22][0] = LanguageWrapper.LANGUAGE;
        resources[22][1] = "Язык";

        return resources;
    }
}
