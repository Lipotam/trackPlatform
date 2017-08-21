#ifndef _COMMUNICATION_INFO_STRUCT_H_
#define _COMMUNICATION_INFO_STRUCT_H_
#include <string>
#include <cstdint>

/**
 * @brief Information to communicator. 
 * @attention You must fill info about required communication before send it to class constructor
 */
struct CommunicationInfoStruct
{
	struct
	{
		std::string rxPort;
		std::string txPort;
		uint32_t baudrate;
	} SerialInfo;
	struct
	{
		std::string ip;
		uint16_t port;
	} TCPIPInfo;
};

#endif /* _COMMUNICATION_INFO_STRUCT_H_ */
