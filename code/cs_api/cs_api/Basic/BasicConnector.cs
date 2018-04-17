using System;
using System.Linq;
using System.Text;
using System.Threading;
using TrackPlatform.CommandsSpecification;
using TrackPlatform.Exceptions;
using TrackPlatform.Other;
using TrackPlatform.Tools;

namespace TrackPlatform.Basic
{
    public abstract class BasicConnector : IDisposable
    {
        protected const int ReadWriteTimeoutInMs = 1500;

        private bool _isConnectedToArduino = false;
        private readonly Timer _autoConnector;

        protected const uint TimesToAutoreconnect = 3;
        protected const int TimeoutToNextConnectInMs = 500;
        protected const uint TimeoutToAutoreconnectInMs = 4500;
        protected readonly byte[] CorrectAnswer = Encoding.ASCII.GetBytes("OK");
        protected readonly byte[] ErrorAnswer = Encoding.ASCII.GetBytes("ERROR");
        protected const uint CrcLength = sizeof(ushort);
        protected const uint LenLength = sizeof(byte);

        protected readonly Mutex ReadWriteAtomicMutex = new Mutex();

        protected abstract void Write(byte[] s);
        protected abstract byte[] Read();
        protected virtual byte[] ReadOneAnswer()
        {
            if (!IsConnected())
            {
                throw new NoConnectionException();
            }

            byte[] answer = Read();
            byte len = answer[0];
            if (answer.Length != (len + LenLength + CrcLength))
            {
                Logger.Log("Bad message length");
                throw new CorruptedAnswerException();
            }

            if (Crc16.Modbus(answer) != 0)
            {
                Logger.Log("Bad crc value");
                throw new CorruptedAnswerException();
            }

            answer = answer.SubArray((int) LenLength, len);

            return answer;
        }
        
        #region Connection management commands

        /// <summary>
        /// Send start connection command
        /// </summary>
        /// <remarks>
        /// Must be called in constructor after configuring and opening connection
        /// </remarks>
        protected void SendStartCommand()
        {
            byte[] command =
            {
                (byte)ControllerEnum.CommunicationController,
                (byte)CommunicationCommands.Start,
                (byte)ApiVersion.ApiWithCrc,
            };
            _isConnectedToArduino = true;
            if (!IsConnected())
            {
                Connect();
            }
            SendOneCommand(command);
            _autoConnector.Change(TimeoutToAutoreconnectInMs, TimeoutToAutoreconnectInMs);
        }

        /// <summary>
        /// Send stop connection command
        /// </summary>
        /// <remarks>
        /// Must be called in destructor before closing and deleting connection
        /// </remarks>
        protected void SendStopCommand()
        {
            if (!IsConnected())
            {
                throw new NoConnectionException();
            }
            _autoConnector.Change(Timeout.Infinite, Timeout.Infinite);
            byte[] command =
            {
                (byte)ControllerEnum.CommunicationController,
                (byte)CommunicationCommands.Stop,
            };
            SendOneCommand(command);
            _isConnectedToArduino = false;
        }

        /// <summary>
        /// Send renew connection command
        /// </summary>
        /// <remarks>
        /// Must be called periodically
        /// </remarks>
        protected void SendRenewConnectionCommand()
        {
            if (!IsConnected())
            {
                throw new NoConnectionException();
            }

            byte[] command =
            {
                (byte)ControllerEnum.CommunicationController,
                (byte)CommunicationCommands.RefreshConnection,
            };
            SendOneCommand(command);
        }

        #endregion

        protected virtual byte[] GeneratePackage(byte[] command)
        {
            byte[] package = command.Add((byte) command.Length, 0);
            ushort crc = Crc16.Modbus(package);
            return package.Concat(BitConverter.GetBytes(crc));
        }

        protected virtual byte[] SendOneCommand_unsafe(byte[] s, bool isWithAnswer)
        {
            if (!IsConnected())
            {
                throw new NoConnectionException();
            }
            byte[] package = GeneratePackage(s);
            Logger.Log("Send: " + package);
            for (var i = 0; i < TimesToAutoreconnect; ++i)
            {
                if (i != 0)
                {
                    Thread.Sleep(TimeoutToNextConnectInMs);
                }

                Logger.Log("Trying to send command. Attempt " + Convert.ToString(i + 1));
                Write(package);
                try
                {
                    byte[] managedAnswer = ReadOneAnswer();
                    if (managedAnswer.SequenceEqual(ErrorAnswer))
                    {
                        Logger.Log("Error was getted (part 1)");
                        continue;
                    }
                    if (!managedAnswer.SequenceEqual(CorrectAnswer))
                    {
                        Logger.Log("Command not parsed");
                        continue;
                    }

                    byte[] answer = new byte[0];

                    if (isWithAnswer)
                    {
                        answer = ReadOneAnswer();
                        Logger.Log("Read answer: " + answer);
                    }

                    managedAnswer = ReadOneAnswer();
                    if (managedAnswer.SequenceEqual(ErrorAnswer))
                    {
                        Logger.Log("Error was getted (part 2)");
                        continue;
                    }
                    if (!managedAnswer.SequenceEqual(CorrectAnswer))
                    {
                        Logger.Log("Command not executed");
                        continue;
                    }

                    Logger.Log("Sending successfully");
                    return answer;
                }
                catch (CorruptedAnswerException)
                {
                    //All is good, module not answered, try again
                    Logger.Log("Answer is corrupted");
                }
                catch (TimeoutException)
                {
                    //All is good, module not answered, try again
                    Logger.Log("Timeout exception");
                }
            }

            _isConnectedToArduino = false;
            Logger.Log("Cannot connect to arduino");
            throw new CannotConnectToArduinoException();
        }

        public BasicConnector()
        {
            _autoConnector = new Timer(state => SendRenewConnectionCommand(), null, Timeout.Infinite, Timeout.Infinite);
        }
        
        /// <summary>
        /// Send one command and read answer to it, if requires
        /// </summary>
        /// <param name="s">Command to send</param>
        /// <param name="isWithAnswer">Is need to read answer after command sending</param>
        /// <returns>Answer from command</returns>
        public byte[] SendOneCommand(byte[] s, bool isWithAnswer = false)
        {
            ReadWriteAtomicMutex.WaitOne();

            try
            {
                byte[] answer = SendOneCommand_unsafe(s, isWithAnswer);
                ReadWriteAtomicMutex.ReleaseMutex();
                return answer;
            }
            catch
            {
                ReadWriteAtomicMutex.ReleaseMutex();
                throw;
            }
        }
        public virtual bool IsConnected()
        {
            return _isConnectedToArduino;
        }
        
        /// <summary>
        /// Manual connect if not already connected
        /// </summary>
        public abstract void Connect();

        /// <summary>
        /// Manual disconnect
        /// </summary>
        public abstract void Disconnect();

        public virtual void Dispose()
        {
            if (IsConnected())
            {
                SendStopCommand();
            }

            Disconnect();

            ReadWriteAtomicMutex.Close();
        }
    }
}
