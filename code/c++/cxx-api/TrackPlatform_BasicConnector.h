#ifndef _TRACKPLATFORM_BASICCONNECTOR_H_
#define _TRACKPLATFORM_BASICCONNECTOR_H_

#include <string>

class TrackPlatform_BasicConnector
{
	bool isConnectedToArduino = false;

protected:
	static const char stopSymbol = '|';
	static const uint8_t timesToAutoreconnect = 3;
	static const uint32_t timeoutToNextConnectInMs = 500;
	static const std::string correctAnswer;

	virtual void write(const std::string& s) = 0;
	virtual std::string read() = 0;

	/**
	 * @brief Send start connection command
	 * @warning Must be called in constructor after configuring and opening connection
	 */
    void sendStartCommand();
	/**
	* @brief Send stop connection command
	* @warning Must be called in destructor befor closing and deleting connection
	*/
    void sendStopCommand();

public:
	TrackPlatform_BasicConnector();
	virtual ~TrackPlatform_BasicConnector();

	/**
	 * @brief Read only one answer
	 * @warning By default returns one portion of data from rx, must be overriden if require
	 */
	virtual std::string readOneAnswer();
	virtual void sendOneCommand(const std::string& s);
	virtual bool isConnected();
	/**
	 * @brief Manual connect if not already connected
	 */
	virtual void connect() = 0;
	/**
	 * @brief Manual disconnect
	 */
	virtual void disconnect() = 0;
};

#endif /* _TRACKPLATFORM_BASICCONNECTOR_H_ */
