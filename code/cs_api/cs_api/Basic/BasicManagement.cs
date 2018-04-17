using System.Threading;
using TrackPlatform.CommandsSpecification;
using TrackPlatform.Tools;

namespace TrackPlatform.Basic
{
    public class BasicManagement
    {
        public BasicConnector Connector { get; private set; }

        protected const byte MinSpeed = 0;
        protected const byte MaxSpeed = 255;
        protected const byte MinServoAngle = 0;
        protected const byte MaxServoAngle = 180;
        protected const byte Delimiter = (byte)';';
        protected const double MinInputSpeed = -1;
        protected const double MaxInputSpeed = 1;

        protected int CalcSpeed(double speed)
        {
            return (int) (speed * (MaxSpeed - MinSpeed) + MinSpeed);
        }

        protected byte[] SendCommand(ControllerEnum targetController, byte[] additionalInfo, bool isWaitAnswer = false)
        {
            byte[] buff = additionalInfo.Add((byte)targetController, 0);
            return Connector.SendOneCommand(buff, isWaitAnswer);
        }
        
        /// <summary>
        /// Send movement command to with connector
        /// </summary>
        /// <param name="command">Command to send with speed</param>
        /// <param name="speed">Speed from <c>MinInputSpeed</c> to <c>MaxInputSpeed</c> interval</param>
        /// <returns>true, if all is good, else false</returns>
        protected bool SendMovement(MoveEnum command, double speed)
        {
            if (speed < MinInputSpeed || speed > MaxInputSpeed)
            {
                return false;
            }

            byte[] buff = CalcSpeed(speed).NumToArray().Add((byte)command, 0);
            SendCommand(ControllerEnum.MovementController, buff);

            return true;
        }

        public BasicManagement(BasicConnector connector)
        {
            Connector = connector;
        }

        #region Movement controller

        public void MoveForward()
        {
            MoveForward(MaxInputSpeed);
        }
        
        //speed must be in [-1,1] range
        public bool MoveForward(double speed)
        {
            return SendMovement(MoveEnum.ForwardSpeed, speed);
        }
        public void MoveForward(int timeInMSec)
        {
            MoveForward(MaxInputSpeed);
            Thread.Sleep(timeInMSec);
            MoveStopAll();
        }

        public void MoveBackward()
        {
            MoveForward(-MaxInputSpeed);
        }
        //speed must be in [0,1] range
        public bool MoveBackward(double speed)
        {
            return MoveForward(-speed);
        }

        public bool RotateClockwise(double speed = MaxInputSpeed)
        {
            return SendMovement(MoveEnum.Clockwise, speed);
        }
        public bool RotateAntiClockwise(double speed = MaxInputSpeed)
        {
            return RotateClockwise(-speed);
        }

        public void MoveStopAll()
        {
            SendCommand(ControllerEnum.MovementController, new[] { (byte)MoveEnum.Stop });
        }

        //speed must be in [-1, 1] range
        public bool SetTrackForwardSpeed(TrackIndex trackId, double speed)
        {
            if (speed < MinInputSpeed || speed > MaxInputSpeed)
            {
                return false;
            }

            byte[] buff =
            {
                (byte) MoveEnum.TrackSetSpeed,
                (byte) (trackId + '0'),
                Delimiter,
            };

            buff = buff.Concat(CalcSpeed(speed).NumToArray());
            SendCommand(ControllerEnum.MovementController, buff);

            return true;
        }
        //speed must be in [-1, 1] range
        public bool SetAllTrackForwardSpeed(double leftSpeed, double rightSpeed)
        {
            if (leftSpeed < MinInputSpeed || leftSpeed > MaxInputSpeed || rightSpeed < MinInputSpeed || rightSpeed > MaxInputSpeed)
            {
                return false;
            }

            byte[] buff =
            {
                (byte) MoveEnum.TrackAllSetSpeed,
            };

            buff = buff.Concat(CalcSpeed(leftSpeed).NumToArray()).Concat(Delimiter);
            buff = buff.Concat(CalcSpeed(rightSpeed).NumToArray());

            SendCommand(ControllerEnum.MovementController, buff);

            return true;
        }

        #endregion

        #region Sensors controller

        public int SensorDistanceGetValue(int num)
        {
            return SensorGetValue(SensorsEnum.DistanceSensor, num);
        }
        public int[] SensorDistanceGetAllValues()
        {
            return SensorGetAllValues(SensorsEnum.DistanceSensorAll);
        }
        public int SensorLineGetValue(int num)
        {
            return SensorGetValue(SensorsEnum.LineSensor, num);
        }
        public int[] SensorLineGetAllValues()
        {
            return SensorGetAllValues(SensorsEnum.LineSensorAll);
        }
        public int SensorDistanceGetRawValue(int num)
        {
            return SensorGetValue(SensorsEnum.RawDistanceSensor, num);
        }
        public int[] SensorDistanceGetAllRawValues()
        {
            return SensorGetAllValues(SensorsEnum.RawDistanceSensorAll);
        }
        public int SensorLineGetRawValue(int num)
        {
            return SensorGetValue(SensorsEnum.RawLineSensor, num);
        }
        public int[] SensorLineGetAllRawValues()
        {
            return SensorGetAllValues(SensorsEnum.RawLineSensorAll);
        }

        private int SensorGetValue(SensorsEnum sensorCommand, int num)
        {
            byte[] buff = num.NumToArray().Add((byte) sensorCommand, 0);
            byte[] answer = SendCommand(ControllerEnum.SensorsController, buff, true);
            return answer.ArrayToNum();
        }

        private int[] SensorGetAllValues(SensorsEnum sensorCommand)
        {
            byte[] buff =
            {
                (byte) sensorCommand
            };
            byte[] answer = SendCommand(ControllerEnum.SensorsController, buff, true);
            return answer.ArrayToArrayNums(Delimiter);
        }

        #endregion

        #region Servo controller

        public void ServoSetHorizontalAngle(int angle)
        {
            ServoSetAngle(ServoIndex.XyPlane, angle);
        }
        public void ServoSetVerticalAngle(int angle)
        {
            ServoSetAngle(ServoIndex.XzPlane, angle);
        }
        public void ServoSetHorizontalVerticalAngle(int horizontalAngle, int verticalAngle)
        {
            ServoSetAngle(ServoIndex.XyPlane, horizontalAngle);
            ServoSetAngle(ServoIndex.XzPlane, verticalAngle);
        }
        public int[] ServoGetAngles()
        {
            return new[]
            {
                ServoGetAngle(ServoIndex.XyPlane), 
                ServoGetAngle(ServoIndex.XzPlane),
            };
        }

        //angle must be in [0, 180] range
        public bool ServoSetAngle(ServoIndex axisIndex, int angle)
        {
            if (angle < MinServoAngle || angle > MaxServoAngle)
            {
                return false;
            }

            byte[] buff = new []
                {
                    (byte) ServoCommands.SetAngle,
                }
                .Concat(((byte) axisIndex).NumToArray())
                .Concat(Delimiter)
                .Concat(angle.NumToArray());
            SendCommand(ControllerEnum.ServoController, buff);
            return true;
        }
        public int ServoGetAngle(ServoIndex axisIndex)
        {
            byte[] buff = new[]
                {
                    (byte) ServoCommands.GetAngle,
                }
                .Concat(((byte) axisIndex).NumToArray());
            byte[] answer = SendCommand(ControllerEnum.ServoController, buff, true);
            return answer.ArrayToNum();
        }

        #endregion
    }
}
