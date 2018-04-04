/**
 * @brief Information to communicator. 
 * @attention You must fill info about required communication before send it to class constructor
 */
public class CommunicationInfoStruct
{
//C++ TO C# CONVERTER NOTE: Classes must be named in C#, so the following class has been named AnonymousClass:
	public class AnonymousClass
	{
		public string rxPort;
		public string txPort;
		public uint32_t baudrate = new uint32_t();
	}
	public AnonymousClass SerialInfo = new AnonymousClass();
//C++ TO C# CONVERTER NOTE: Classes must be named in C#, so the following class has been named AnonymousClass2:
	public class AnonymousClass2
	{
		public string ip;
		public uint16_t port = new uint16_t();
	}
	public AnonymousClass2 TCPIPInfo = new AnonymousClass2();
}

