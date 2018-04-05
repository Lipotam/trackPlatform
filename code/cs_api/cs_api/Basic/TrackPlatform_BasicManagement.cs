using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;
using TrackPlatform.Tools;

public class TrackPlatform_BasicManagement
{
    public TrackPlatform_BasicConnector connector { get; private set; }

    protected const byte minSpeed = 0;
    protected const byte maxSpeed = 255;
    protected const byte minServoAngle = 0;
    protected const byte maxServoAngle = 180;
    protected const byte delimiter = (byte)';';
    protected const double minInputSpeed = -1;
    protected const double maxInputSpeed = 1;

    protected int CalcSpeed(double speed)
    {
        return (int) (speed * (maxSpeed - minSpeed) + minSpeed);
    }

    protected byte[] sendCommand(ControllerEnum targetController, byte[] additionalInfo, bool isWaitAnswer = false)
    {
        byte[] buff = additionalInfo.Add((byte)targetController, 0);
        return connector.sendOneCommand(buff, isWaitAnswer);
    }

    /**
	 * \brief Send movement command to with connector
	 * \param command Command to send with speed
	 * \param speed Speed from @minSpeed to @maxSpeed interval
	 * \return true, if all is good, else false
	 */
    protected bool sendMovement(MoveEnum command, double speed)
    {
        if (speed < minInputSpeed || speed > maxInputSpeed)
        {
            return false;
        }

        byte[] buff = CalcSpeed(speed).NumToArray().Add((byte)command, 0);
        sendCommand(ControllerEnum.movementControllerID, buff);

        return true;
    }

    public TrackPlatform_BasicManagement(TrackPlatform_BasicConnector connector)
    {
        this.connector = connector;
    }

    #region Movement controller

    public void moveForward()
    {
        moveForward(maxInputSpeed);
    }
    //speed must be in [0,1] range
    public bool moveForward(double speed)
    {
        return sendMovement(MoveEnum.forward_speed, speed);
    }
    public void moveForward(int timeInMSec)
    {
        moveForward(maxInputSpeed);
        Thread.Sleep(timeInMSec);
        moveStopAll();
    }

    public void moveBackward()
    {
        moveForward(-maxInputSpeed);
    }
    //speed must be in [0,1] range
    public bool moveBackward(double speed)
    {
        return moveForward(-speed);
    }

    public bool rotateClockwise(double speed = maxInputSpeed)
    {
        return sendMovement(MoveEnum.clockwise, speed);
    }
    public bool rotateAntiClockwise(double speed = maxInputSpeed)
    {
        return rotateClockwise(-speed);
    }

    public void moveStopAll()
    {
        sendCommand(ControllerEnum.movementControllerID, new[] { (byte)MoveEnum.stop });
    }

    //speed must be in [-1, 1] range
    public bool setTrackForwardSpeed(TrackIndex trackId, double speed)
    {
        if (speed < minInputSpeed || speed > maxInputSpeed)
        {
            return false;
        }

        byte[] buff =
        {
            (byte) MoveEnum.track_set_speed,
            (byte) (trackId + '0'),
            delimiter,
        };

        buff = buff.Concat(CalcSpeed(speed).NumToArray());
        sendCommand(ControllerEnum.movementControllerID, buff);

        return true;
    }
    //speed must be in [-1, 1] range
    public bool setAllTrackForwardSpeed(double leftSpeed, double rightSpeed)
    {
        if (leftSpeed < minInputSpeed || leftSpeed > maxInputSpeed || rightSpeed < minInputSpeed || rightSpeed > maxInputSpeed)
        {
            return false;
        }

        byte[] buff =
        {
            (byte) MoveEnum.track_all_set_speed,
        };

        buff = buff.Concat(CalcSpeed(leftSpeed).NumToArray()).Concat(delimiter);
        buff = buff.Concat(CalcSpeed(rightSpeed).NumToArray());

        sendCommand(ControllerEnum.movementControllerID, buff);

        return true;
    }

    #endregion

    #region Sensors controller

    public int sensorDistanceGetValue(int num)
    {
        return SensorGetValue(SensorsEnum.distance_sensor, num);
    }
    public int[] sensorDistanceGetAllValues()
    {
        return SensorGetAllValues(SensorsEnum.distance_sensor_all);
    }
    public int sensorLineGetValue(int num)
    {
        return SensorGetValue(SensorsEnum.line_sensor, num);
    }
    public int[] sensorLineGetAllValues()
    {
        return SensorGetAllValues(SensorsEnum.line_sensor_all);
    }
    public int sensorDistanceGetRawValue(int num)
    {
        return SensorGetValue(SensorsEnum.raw_distance_sensor, num);
    }
    public int[] sensorDistanceGetAllRawValues()
    {
        return SensorGetAllValues(SensorsEnum.raw_distance_sensor_all);
    }
    public int sensorLineGetRawValue(int num)
    {
        return SensorGetValue(SensorsEnum.raw_line_sensor, num);
    }
    public int[] sensorLineGetAllRawValues()
    {
        return SensorGetAllValues(SensorsEnum.raw_line_sensor_all);
    }

    private int SensorGetValue(SensorsEnum sensorCommand, int num)
    {
        byte[] buff = num.NumToArray().Add((byte) sensorCommand, 0);
        byte[] answer = sendCommand(ControllerEnum.sensorsControllerID, buff, true);
        return answer.ArrayToNum();
    }

    private int[] SensorGetAllValues(SensorsEnum sensorCommand)
    {
        byte[] buff =
        {
            (byte) sensorCommand
        };
        byte[] answer = sendCommand(ControllerEnum.sensorsControllerID, buff, true);
        return answer.ArrayToArrayNums(delimiter);
    }

    #endregion

    #region Servo controller

    public void servoSetHorizontalAngle(uint16_t angle)
    {
        //C++ TO C# CONVERTER TODO TASK: The following line was determined to contain a copy constructor call - this should be verified and a copy constructor should be created:
        //ORIGINAL LINE: servoSetAngle(xy_plane, angle);
        servoSetAngle(ServoIndex.xy_plane, new uint16_t(angle));
    }
    public void servoSetVerticalAngle(uint16_t angle)
    {
        //C++ TO C# CONVERTER TODO TASK: The following line was determined to contain a copy constructor call - this should be verified and a copy constructor should be created:
        //ORIGINAL LINE: servoSetAngle(xz_plane, angle);
        servoSetAngle(ServoIndex.xz_plane, new uint16_t(angle));
    }
    public void servoSetHorizontalVerticalAngle(uint16_t horizontalAngle, uint16_t verticalAngle)
    {
        //C++ TO C# CONVERTER TODO TASK: The following line was determined to contain a copy constructor call - this should be verified and a copy constructor should be created:
        //ORIGINAL LINE: servoSetAngle(xy_plane, horizontalAngle);
        servoSetAngle(ServoIndex.xy_plane, new uint16_t(horizontalAngle));
        //C++ TO C# CONVERTER TODO TASK: The following line was determined to contain a copy constructor call - this should be verified and a copy constructor should be created:
        //ORIGINAL LINE: servoSetAngle(xz_plane, verticalAngle);
        servoSetAngle(ServoIndex.xz_plane, new uint16_t(verticalAngle));
    }
    public List<uint32_t> servoGetAngles()
    {
        List<uint32_t> answer = new List<uint32_t>();
        answer.Add(servoGetAngle(ServoIndex.xy_plane));
        answer.Add(servoGetAngle(ServoIndex.xz_plane));
        return answer;
    }
    //angle must be in [0, 180] range
    public bool servoSetAngle(ServoIndex axisIndex, uint16_t angle)
    {
        if (angle < minServoAngle || angle > maxServoAngle)
        {
            return false;
        }

        string toSend = new string(1, ServoCommands.set_angle);
        //C++ TO C# CONVERTER TODO TASK: There is no equivalent to 'reinterpret_cast' in C#:
        toSend += Convert.ToString(*reinterpret_cast <const uint8_t> (axisIndex));
        toSend += (char)delimiter;
        toSend += Convert.ToString(angle);
        sendCommand(ControllerEnum.servoControllerID, toSend);
        return true;
    }
    public uint16_t servoGetAngle(ServoIndex axisIndex)
    {
        string toSend = new string(1, ServoCommands.get_angle);
        //C++ TO C# CONVERTER TODO TASK: There is no equivalent to 'reinterpret_cast' in C#:
        toSend += Convert.ToString(*reinterpret_cast <const uint8_t> (axisIndex));
        string answer = sendCommand(ControllerEnum.servoControllerID, toSend, true);
        return Convert.ToInt32(answer);
    }

    #endregion
}
