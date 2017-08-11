#pragma once
#include "ConnectingDevice.h"

class WiFi : public ConnectingDevice
{
public:
	WiFi(int rx, int tx, int speed);
	~WiFi();
	
	/**
	* Проверка версии прошивки
	* Возвращает значение типа String
	*/
	virtual String VersionCheck();
	
	/**
	* Выводит список доступных модулю в данный момент сетей для подключения
	* Возвращает значение типа String
	*/
	virtual String NetsList();
	
	/**
	* Получение текущих IP и MAC
	* Возвращает значение типа String
	*/
	virtual String CheckIPandMAC();

	/**
	* Изменяет рабочую скорость модуля
	* Принимает новую скорость работы модуля
	*/
	virtual void ChangeSpeed(int speed);
	
	/**
	* Перезапускает модуль
	* Принимает новую скорость работы модуля
	*/
	virtual void Reset(int speed);
	
	/**
	* Делает первичную проверку модуля
	*/
	virtual void Check();
	
	/**
	* Переводит модуль в режим клиента
	*/
	virtual void Close();
	
	/**
	* Переводит модуль в режим хоста без TCP
	*/
	virtual void Open();
	
	/**
	* Включает TCP
	* Принимает номер порта типа int
	*/
	virtual void UseTCP(int port);
	
	/**
	* Устанавливает параметры хоста без записи в кэш
	* Принимает имя точки доступа типа String, пароль типа String и номер порта типа int для вызова функции UseTCP
	*/
	virtual void CurrentLog(String name, String password, int port);
	
	/**
	* Устанавливает параметры хоста с записью в кэш
	* Принимает имя точки доступа типа String, пароль типа String и номер порта типа int для вызова функции UseTCP
	*/
	virtual void StaticLog(String name, String password, int port);

private:
	
	/**
	* Индикатор готовности модуля к работе
	*/
	bool ready = false;

	/**
	* Индикатор состояния модуля клиент/хост
	*/
	bool opened = false;
};