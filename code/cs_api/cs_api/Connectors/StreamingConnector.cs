using System;
using System.Collections.Generic;
using System.IO;
using TrackPlatform.Basic;
using TrackPlatform.Tools;

namespace TrackPlatform.Connectors
{
    public abstract class StreamingConnector : BasicConnector
    {
        private const int MessageMaxSize = 65535;

        private readonly List<byte> _buffer = new List<byte>();
        private readonly byte[] _readBuffer = new byte[MessageMaxSize];

        /// <summary>
        /// Need to manually manage from derived class
        /// </summary>
        protected abstract Stream ReadStream { get; }
        protected abstract Stream WriteStream { get; }

        protected abstract int ReadAvailable { get; }

        protected sealed override void Write(byte[] s)
        {
            WriteStream.Write(s, 0, s.Length);
        }

        protected sealed override byte[] Read()
        {
            if (_buffer.Count == 0)
            {
                int readByte = ReadStream.ReadByte();
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
                int bytesNeedToRead = Math.Max(substringLen - sizeof(byte), ReadAvailable);

                //TODO: check for max buffer length

                int bytesWereRead = ReadStream.Read(_readBuffer, 0, bytesNeedToRead);

                if (bytesNeedToRead > bytesWereRead)
                {
                    throw new TimeoutException();
                }

                _buffer.AddRange(_readBuffer.SubArray(0, bytesWereRead));
            }

            byte[] answer = _buffer.GetRange(0, substringLen).ToArray();
            _buffer.RemoveRange(0, substringLen);

            return answer;
        }
    }
}