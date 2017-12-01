#ifndef _TRACKPLATFORM_BASICCONNECTOR_H_
#define _TRACKPLATFORM_BASICCONNECTOR_H_

#include <string>
#include "AutoConnector.h"

class TrackPlatform_BasicConnector
{
	bool isConnectedToArduino = false;
	AutoConnector* autoConnector = nullptr;

	std::string generatePackage(const std::string& command);

protected:
	static const uint8_t timesToAutoreconnect = 3;
	static const uint32_t timeoutToNextConnectInMs = 500;
	static const uint32_t timeoutToAutoreconnectInMs = 4500;
	static const std::string correctAnswer;
	static const uint8_t crc_length = 2;

	virtual void write(const std::string& s) = 0;
	virtual std::string read() = 0;
	virtual std::string readOneAnswer();

	/**
	 * @brief Send start connection command
	 * @warning Must be called in constructor after configuring and opening connection
	 */
    void sendStartCommand();
	/**
	* @brief Send stop connection command
	* @warning Must be called in destructor before closing and deleting connection
	*/
    void sendStopCommand();
	/**
	* @brief Send renew connection command
	* @warning Must be called periodically
	*/
    void sendRenewConnectionCommand();

public:
	TrackPlatform_BasicConnector();
	virtual ~TrackPlatform_BasicConnector();

	/**
	 * @brief Send one command and read answer to it, if requires
	 * @warning By default returns one portion of data from rx, must be overriden if require
	 * @return Answer from command
	 */
	virtual std::string sendOneCommand(const std::string& s, bool isWithAnswer = false);
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
