#pragma once
#include <SoftwareSerial.h>

#include "ConnectingDevice.h"

class DebugSerial : public ConnectingDevice
{
	static SoftwareSerial* serial;

	static SoftwareSerial* generateDbgSerial();
public:
	DebugSerial();

	static Stream* getSerial();

    /**
     * @brief println(String) duplicate
     *
     * @param data String to send
     */
	void send(String data) override;
    /**
     * @brief Prints data string to debug console
     *
     * @param data String to print
     */
	void print(String data);
    /**
     * @brief Prints data to debug console and adds newline symbol in the end
     *
     * @param data String to print
     */
	void println(String data);
    /**
     * @brief Prints data in hex view (with space delimiters) to debug console
     *
     * @param data String to print
     */
	void printHex(String data);
    /**
     * @brief Prints data in hex view (with space delimiters) to debug console and prints newline symbol at the end
     *
     * @param data String to print
     */
	void printlnHex(String data);
};
