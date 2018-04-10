using System;
using System.Collections.Generic;
using System.IO.Ports;
using TrackPlatform.Basic;

namespace TrackPlatform.Connectors
{
    public class SerialConnector : BasicConnector
    {
        private const int MessageMaxSize = 65535;
        private const int TimeoutInMs = 1500;

        private readonly SerialPort _readPort;
        private readonly SerialPort _writePort;

        private readonly List<byte> _buffer = new List<byte>();
        private readonly byte[] _readBuffer = new byte[MessageMaxSize];

        protected override void Write(byte[] s)
        {
            _writePort.Write(s, 0, s.Length);
        }

        protected override byte[] Read()
        {
            if (_buffer.Count == 0)
            {
                int readByte = _readPort.ReadByte();
                if (readByte < 0)
                {
                    throw new TimeoutException();
                }
                _buffer.Add((byte) readByte);
            }

            byte len = _buffer[0];
            int substringLen = (int) (sizeof(byte) + len + CrcLength);
            if ((substringLen) > _buffer.Count)
            {
                int bytesNeedToRead = Math.Max(substringLen - sizeof(byte), _readPort.BytesToRead);

                int bytesWereRead = _readPort.Read(_readBuffer, 0, bytesNeedToRead);

                if (bytesNeedToRead > bytesWereRead)
                {
                    throw new TimeoutException();
                }
            }

            byte[] answer = _buffer.GetRange(0, substringLen).ToArray();
            _buffer.RemoveRange(0, substringLen);

            return answer;
        }

        public SerialConnector(string rx, string tx, int baudRate)
        {
            _readPort = new SerialPort(rx, baudRate);
            _writePort = (rx == tx) ? _readPort : new SerialPort(tx, baudRate);

            _readPort.ReadTimeout = TimeoutInMs;
            _writePort.WriteTimeout = TimeoutInMs;

            //board reloading when connect block
            _writePort.DtrEnable = false;

            SendStartCommand();
        }
        public override void Dispose()
        {
            SendStopCommand();

            Disconnect();
            if (_readPort != _writePort)
            {
                _writePort?.Dispose();
            }

            _readPort?.Dispose();
            base.Dispose();
        }
        public override bool IsConnected()
        {
            return (base.IsConnected() && _readPort.IsOpen && _writePort.IsOpen);
        }
        public override void Connect()
        {
            if (_readPort != null && !_readPort.IsOpen)
            {
                _readPort.Open();
            }
            if (_writePort != null && !_writePort.IsOpen)
            {
                _writePort.Open();
            }
        }
        public override void Disconnect()
        {
            if (_readPort != null && _readPort.IsOpen)
            {
                _readPort.Close();
            }
            if (_writePort != null && _writePort.IsOpen)
            {
                _writePort.Close();
            }
        }
    }
}
