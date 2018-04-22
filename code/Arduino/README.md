# Arduino Mega 2560

В данном разделе расположены прошивки для Arduino Mega 2560 модуля.

## Зависимости

Все зависимости требуется устанавливать как библиотеки для `Arduino IDE`

* Модуль для расчета CRC `FastCRC` ([ссылка для скачивания](https://github.com/FrankBoesing/FastCRC))
* Модуль для поддержки диспея `Adafruit SSD1306` ([ссылка для скачивания](https://github.com/adafruit/Adafruit_SSD1306))
* Базовый модуль для поддержки диспея (требуется для `Adafruit SSD1306`) `Adafruit GFX Library` ([ссылка для скачивания](https://github.com/adafruit/Adafruit-GFX-Library))
* Правка исходных кодов Arduino IDE в соответствии с [этой](https://playground.arduino.cc/Main/Printf) статьей (требуется при включенных отладочных сообщениях)

## Сборка

Утилиты для сборки:

* Arduino IDE
* Microsoft Visual Studio with C++ compiler
* Visual Micro plug-in ([можно скачать отсюда](http://www.visualmicro.com/page/Arduino-Visual-Studio-Downloads.aspx))

Для сборки откройте файл `trackPlatform.sln` в установленной выше Microsoft Visual Studio. Далее следуйте стандартной процедуре сборки проекта в Visual Studio.

P.S. **Внимание!!!** Для корректной работы прошивки в версии сборки ВСЕГДА указывать `Release`, даже с включенными при компиляции отладочными сообщениями.

## Прошивка

В Visual Studio в панеле VisualMicro выберите требуемый (к которому подключена Arduino для прошивки) последовательный порт, и нажмите на иконку запуска (`Build and run`).

