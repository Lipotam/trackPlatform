package com.example.kimentii.application20.language_resources;

import com.example.kimentii.application20.wrappers.LanguageWrapper;

import java.util.ListResourceBundle;

public class RussianLanguage extends ListResourceBundle {
    @Override
    protected Object[][] getContents() {
        Object[][] resources = new Object[24][2];
        int i = 0;
        resources[i][0] = LanguageWrapper.NO_CONNECTION;
        resources[i++][1] = "нет подключения";
        resources[i][0] = LanguageWrapper.CONNECTED;
        resources[i++][1] = "подключен";

        // main menu activity
        resources[i][0] = LanguageWrapper.MOTION_BUTTON;
        resources[i++][1] = "движение";
        resources[i][0] = LanguageWrapper.SERVO_BUTTON;
        resources[i++][1] = "сервоприводы";
        resources[i][0] = LanguageWrapper.SENSORS_BUTTON;
        resources[i++][1] = "сенсоры";
        resources[i][0] = LanguageWrapper.SETTINGS_BUTTON;
        resources[i++][1] = "настройки";
        resources[i][0] = LanguageWrapper.EXIT_BUTTON;
        resources[i++][1] = "выход";

        // motion activity
        resources[i][0] = LanguageWrapper.FORWARD_BUTTON;
        resources[i++][1] = "вперед";
        resources[i][0] = LanguageWrapper.RIGHT_BUTTON;
        resources[i++][1] = "вправо";
        resources[i][0] = LanguageWrapper.LEFT_BUTTON;
        resources[i++][1] = "влево";
        resources[i][0] = LanguageWrapper.BACK_BUTTON;
        resources[i++][1] = "назад";
        resources[i][0] = LanguageWrapper.STOP_BUTTON;
        resources[i++][1] = "стоп";

        // servo activity
        resources[i][0] = LanguageWrapper.UP_SERVO_BUTTON;
        resources[i++][1] = "вверх";
        resources[i][0] = LanguageWrapper.RIGHT_SERVO_BUTTON;
        resources[i++][1] = "вправо";
        resources[i][0] = LanguageWrapper.LEFT_SERVO_BUTTON;
        resources[i++][1] = "влево";
        resources[i][0] = LanguageWrapper.DOWN_SERVO_BUTTON;
        resources[i++][1] = "вниз";

        // sensors activity
        resources[i][0] = LanguageWrapper.DISTANCE_SENSORS;
        resources[i++][1] = "Датчики расстояния";
        resources[i][0] = LanguageWrapper.LINE_SENSORS;
        resources[i++][1] = "Дитчики линии";
        resources[i][0] = LanguageWrapper.FIRST_SENSOR;
        resources[i++][1] = "Первый датчик";
        resources[i][0] = LanguageWrapper.SECOND_SENSOR;
        resources[i++][1] = "Второй датчик";
        resources[i][0] = LanguageWrapper.THIRD_SENSOR;
        resources[i++][1] = "Третий датчик";
        resources[i][0] = LanguageWrapper.FOURTH_SENSOR;
        resources[i++][1] = "Четвертый датчик";
        resources[i][0] = LanguageWrapper.FIFTH_SENSOR;
        resources[i++][1] = "Пятый датчик";

        // settings activity
        resources[i][0] = LanguageWrapper.LANGUAGE;
        resources[i++][1] = "Язык";

        return resources;
    }
}
