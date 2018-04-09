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

    public void servoSetHorizontalAngle(int angle)
    {
        servoSetAngle(ServoIndex.xy_plane, angle);
    }
    public void servoSetVerticalAngle(int angle)
    {
        servoSetAngle(ServoIndex.xz_plane, angle);
    }
    public void servoSetHorizontalVerticalAngle(int horizontalAngle, int verticalAngle)
    {
        servoSetAngle(ServoIndex.xy_plane, horizontalAngle);
        servoSetAngle(ServoIndex.xz_plane, verticalAngle);
    }
    public int[] servoGetAngles()
    {
        return new[]
        {
            servoGetAngle(ServoIndex.xy_plane), 
            servoGetAngle(ServoIndex.xz_plane),
        };
    }

    //angle must be in [0, 180] range
    public bool servoSetAngle(ServoIndex axisIndex, int angle)
    {
        if (angle < minServoAngle || angle > maxServoAngle)
        {
            return false;
        }

        byte[] buff = axisIndex.NumToArray()
            .Add((byte) ServoCommands.set_angle, 0)
            .Concat(delimiter)
            .Concat(angle.NumToArray())
            ;
        sendCommand(ControllerEnum.servoControllerID, buff);
        return true;
    }
    public int servoGetAngle(ServoIndex axisIndex)
    {
        byte[] buff = axisIndex.NumToArray().Add((byte) ServoCommands.get_angle, 0);
        byte[] answer = sendCommand(ControllerEnum.servoControllerID, buff, true);
        return answer.ArrayToNum();
    }

    #endregion
}
