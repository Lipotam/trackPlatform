using System;
using System.Collections.Generic;
using System.IO;
using System.IO.Ports;
using TrackPlatform.Basic;
using TrackPlatform.Tools;

namespace TrackPlatform.Connectors
{
    public class SerialConnector : StreamingConnector
    {
        private readonly SerialPort _readPort;
        private readonly SerialPort _writePort;

        protected override Stream ReadStream => _readPort.BaseStream;
        protected override Stream WriteStream => _writePort.BaseStream;

        protected override int ReadAvailable => !IsConnected() ? 0 : _readPort.BytesToRead;

        public SerialConnector(string rx, string tx, int baudRate)
        {
            _readPort = new SerialPort(rx, baudRate);
            _writePort = (rx == tx) ? _readPort : new SerialPort(tx, baudRate);

            _readPort.ReadTimeout = ReadWriteTimeoutInMs;
            _writePort.WriteTimeout = ReadWriteTimeoutInMs;

            //board reloading when connect block
            _writePort.DtrEnable = false;

            SendStartCommand();
        }
        public override void Dispose()
        {
            base.Dispose();
            if (_readPort != _writePort)
            {
                _writePort?.Dispose();
            }

            _readPort?.Dispose();
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
