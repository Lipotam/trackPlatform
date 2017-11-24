#pragma once
#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>

struct Data {
	std::function<void()> callback;
	std::atomic_bool* pIsRepeat;
	uint32_t frequency;
};

class AutoConnector {
private:
	std::thread* pConnectingThread;
	std::function<void()> callback;
	std::atomic_bool isRepeat;
	uint32_t frequency;

public:
	/**
	 * @param c Callback to run by timer
	 * @param f Time to wait before next callback call in milliseconds
	 */
	AutoConnector(std::function<void()> c, uint32_t f);
	~AutoConnector();
	void start();
	void stop();
	bool isConnecting();
};