#pragma once
#include "ConnectingDevice.h"

class WiFi : public ConnectingDevice
{
	/**
	 * @brief Block for double initialization
	 */
	static bool isInited;

public:
	explicit WiFi(unsigned long speed);
	~WiFi();
	
	/**
	* @brief Проверка версии прошивки
	* @return Возвращает значение типа String
	*/
	virtual String VersionCheck();
	
	/**
	* @brief Выводит список доступных модулю в данный момент сетей для подключения
	* @Возвращает значение типа String
	*/
	virtual String NetsList();
	
	/**
	* @brief Получение текущих IP и MAC
	* @Возвращает значение типа String
	*/
	virtual String CheckIPandMAC();

	/**
	* @Изменяет рабочую скорость модуля
	* @param speed Скорость работы модуля
	да. Только писать то, что оно возвращает стринг, по-моему бессмысденно. Ты должен расписать, что там за статусы могут быть или где их искать
	*/
	virtual void ChangeSpeed(unsigned long speed);
	
	/**
	* Перезапускает модуль
	* Возвращает строку со статусом типа String
	*/
	virtual bool Reset();

	/**
	* Перезапускает модуль
	* Принимает новую скорость работы модуля
	* Возвращает строку со статусом типа String
	*/
	virtual bool Reset(unsigned long speed);
	
	/**
	* Делает первичную проверку модуля
	* Возвращает переменную со статусом типа bool
	*/
	virtual bool Check();
	
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
	virtual void CreateCurrentHost(String name, String password, int port);
	
	/**
	* Устанавливает параметры хоста с записью в кэш
	* Принимает имя точки доступа типа String, пароль типа String и номер порта типа int для вызова функции UseTCP
	*/
	virtual void CreateStaticHost(String name, String password, int port);

	void send(String command) override;

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