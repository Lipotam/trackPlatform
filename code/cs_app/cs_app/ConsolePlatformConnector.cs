using System;
using TrackPlatform.Api;
using TrackPlatform.Other;

namespace TrackPlatform.Example
{
    public static class ConsolePlatformConnector
    {
        public static Manager Connect()
        {
            Console.WriteLine("Connect by:");
            Console.WriteLine("\t1) USB");
            Console.WriteLine("\t2) Bluetooth");
            Console.WriteLine("\t3) WiFi");
            int answer = Console.ReadKey().KeyChar;
            Console.WriteLine();

            switch (answer)
            {
                case '1':
                case '2':
                    return ConnectBySerial();
                case '3':
                    return ConnectByTcpIp();
                default: 
                    Console.WriteLine("No connector at number " + answer);
                    return null;
            }
        }

        public static Manager ConnectBySerial()
        {
            string rtx = "COM13";
            int baudrate = 9600;

            Console.WriteLine("port");
            rtx = Console.ReadLine();
            Console.WriteLine("baudrate");
            baudrate = int.Parse(Console.ReadLine() ?? throw new InvalidOperationException());

            Console.WriteLine($"rx = {rtx}\ntx = {rtx}\nbaudrate = {baudrate}");

            CommunicationInfoStruct info = new CommunicationInfoStruct();

            info.SerialInfo.RxPort = rtx;
            info.SerialInfo.TxPort = rtx;
            info.SerialInfo.Baudrate = baudrate;
            return new Manager(ConnectionModes.Bluetooth, info);
        }

        public static Manager ConnectByTcpIp()
        {
            string ip = "192.168.4.1";
            int port = 333;

            Console.WriteLine("server ip");
            ip = Console.ReadLine();
            Console.WriteLine("port");
            port = int.Parse(Console.ReadLine() ?? throw new InvalidOperationException());

            Console.WriteLine($"ip = {ip}\nport = {port}");

            CommunicationInfoStruct info = new CommunicationInfoStruct();

            info.TcpInfo.Ip = ip;
            info.TcpInfo.Port = port;
            return new Manager(ConnectionModes.WiFi, info);
        }

    }
}