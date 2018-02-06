#pragma once
#include <SoftwareSerial.h>
#include <HardwareSerial.h>

#include "IConnector.h"

/**
 *	@brief Define, if debug is require
 */
#define DEBUG_ON

#ifdef DEBUG_ON

#define DEBUG_PRINT(...)				DebugSerial().print(__VA_ARGS__)
#define DEBUG_PRINTLN(...)				DebugSerial().println(__VA_ARGS__)
#define DEBUG_PRINTHEX(...)				DebugSerial().printHex(__VA_ARGS__)
#define DEBUG_PRINTLNHEX(...)			DebugSerial().printlnHex(__VA_ARGS__)
#define DEBUG_PRINTF(...)				DebugSerial().printf(__VA_ARGS__)

#else

#define DEBUG_PRINT(...)
#define DEBUG_PRINTLN(...)
#define DEBUG_PRINTHEX(...)
#define DEBUG_PRINTLNHEX(...)
#define DEBUG_PRINTF(...)

#endif

#ifdef DEBUG_ON
class DebugSerial : public IConnector
{
	static HardwareSerial* serial_;
	static const int printfBuffSize = 120;

	/**
	* @brief Block for double initialization
	*/
	static bool isInited;

public:
	DebugSerial();

	static Stream* get_serial();

    /**
     * @brief println(String) duplicate
     *
     * @param answer_ptr String to send
     */
	void write_answer(const uint8_t* answer_ptr, int length) override;
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
	void printHex(uint8_t* data, size_t size);
    /**
     * @brief Prints data in hex view (with space delimiters) to debug console and prints newline symbol at the end
     *
     * @param data String to print
     */
	void printlnHex(String data);

	void printlnHex(uint8_t* data, size_t size);
	/**
	 * @brief Prints data as simple printf function
	 * @warning No float/double support
	 * @warning Max buffer length (with printed values) must be less that @printBuffSize class member
	 */
	void printf(const char *format, ...);
};

#endif
