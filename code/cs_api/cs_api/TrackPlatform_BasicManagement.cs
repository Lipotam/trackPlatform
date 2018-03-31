using System;
using System.Collections.Generic;

public class TrackPlatform_BasicManagement : System.IDisposable
{
	private TrackPlatform_BasicConnector connector;

	protected const uint8_t minSpeed = 0;
	protected const uint8_t maxSpeed = 255;
	protected const uint8_t minServoAngle = 0;
	protected const uint8_t maxServoAngle = 180;
	protected const sbyte delimiter = (sbyte)';';
	protected readonly double minInputSpeed = -1;
	protected readonly double maxInputSpeed = 1;

	protected string sendCommand(ControllerEnum targetController, string additionalInfo, bool isWaitAnswer = false)
	{
		return connector.sendOneCommand((sbyte)targetController + additionalInfo, isWaitAnswer);
	}

	protected static List<uint32_t> parseStringToArray(string s)
	{
		List<uint32_t> distancies = new List<uint32_t>();
		size_t stringOldLen = 0;
		size_t posToNextValue = 0;
		try
		{
			do
			{

				distancies.Add(std::stoul(s, posToNextValue));
				stringOldLen = s.Length;
				s = s.Substring(posToNextValue + sizeof (sbyte));

			} while ((s != "") && (stringOldLen > s.Length));
		}
		catch
		{
			return distancies;
		}

		if (stringOldLen <= s.Length)
		{
			distancies.RemoveAt(distancies.Count - 1);
		}
		return distancies;
	}

//C++ TO C# CONVERTER WARNING: 'const' methods are not available in C#:
//ORIGINAL LINE: TrackPlatform_BasicConnector* getConnector() const
	protected TrackPlatform_BasicConnector getConnector()
	{
		return connector;
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

		string toSend = new string(1, command);
		toSend += Convert.ToString((uint16_t)(speed * (maxSpeed - minSpeed) + minSpeed));
		sendCommand(ControllerEnum.movementControllerID, toSend);

		return true;
	}

	public TrackPlatform_BasicManagement(TrackPlatform_BasicConnector connector)
	{
		this.connector = connector;
	}
	public virtual void Dispose()
	{
	}

	/* movement controller */
	public void moveForward()
	{
		moveForward(maxInputSpeed);
	}
	//speed must be in [0,1] range
	public bool moveForward(double speed)
	{
		return sendMovement(MoveEnum.forward_speed, speed);
	}
	public void moveForward(uint32_t timeInMSec)
	{
		moveForward(maxInputSpeed);
		std::this_thread.sleep_for(std::chrono.milliseconds(timeInMSec));
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
		string toSend = new string(1, MoveEnum.stop);
		sendCommand(ControllerEnum.movementControllerID, toSend);
	}

	//speed must be in [-1, 1] range
	public bool setTrackForwardSpeed(TrackIndex trackId, double speed)
	{
		if (speed < -1 || speed > 1)
		{
			return false;
		}

		string toSend = new string(1, MoveEnum.track_set_speed);
//C++ TO C# CONVERTER TODO TASK: There is no equivalent to 'reinterpret_cast' in C#:
		toSend += Convert.ToString(*reinterpret_cast<const uint8_t>(trackId));
		toSend += (char)delimiter;
		toSend += Convert.ToString((int16_t)(speed * (maxSpeed - minSpeed) + minSpeed));
		sendCommand(ControllerEnum.movementControllerID, toSend);

		return true;
	}
	//speed must be in [-1, 1] range
	public bool setAllTrackForwardSpeed(double leftSpeed, double rightSpeed)
	{
		if (leftSpeed < -1 || leftSpeed > 1 || rightSpeed < -1 || rightSpeed > 1)
		{
			return false;
		}

		string toSend = new string(1, MoveEnum.track_all_set_speed);
		toSend += Convert.ToString((int16_t)(leftSpeed * (maxSpeed - minSpeed) + minSpeed));
		toSend += (char)delimiter;
		toSend += Convert.ToString((int16_t)(rightSpeed * (maxSpeed - minSpeed) + minSpeed));
		sendCommand(ControllerEnum.movementControllerID, toSend);

		return true;
	}

	/* sensors controller */
	public uint32_t sensorDistanceGetValue(uint8_t num)
	{
		string toSend = new string(1, SensorsEnum.distance_sensor);
		toSend += Convert.ToString(num);
		string answer = sendCommand(ControllerEnum.sensorsControllerID, toSend, true);
		return Convert.ToInt32(answer);
	}
	public List<uint32_t> sensorDistanceGetAllValues()
	{
		string toSend = new string(1, SensorsEnum.distance_sensor_all);
		string answer = sendCommand(ControllerEnum.sensorsControllerID, toSend, true);
		return parseStringToArray(answer);
	}
	public uint32_t sensorLineGetValue(uint8_t num)
	{
		string toSend = new string(1, SensorsEnum.line_sensor);
		toSend += Convert.ToString(num);
		string answer = sendCommand(ControllerEnum.sensorsControllerID, toSend, true);
		return Convert.ToInt32(answer);
	}
	public List<uint32_t> sensorLineGetAllValues()
	{
		string toSend = new string(1, SensorsEnum.line_sensor_all);
		string answer = sendCommand(ControllerEnum.sensorsControllerID, toSend, true);
		return parseStringToArray(answer);
	}
	public uint32_t sensorDistanceGetRawValue(uint8_t num)
	{
		string toSend = new string(1, SensorsEnum.raw_distance_sensor);
		toSend += Convert.ToString(num);
		string answer = sendCommand(ControllerEnum.sensorsControllerID, toSend, true);
		return Convert.ToInt32(answer);
	}
	public List<uint32_t> sensorDistanceGetAllRawValues()
	{
		string toSend = new string(1, SensorsEnum.raw_distance_sensor_all);
		string answer = sendCommand(ControllerEnum.sensorsControllerID, toSend, true);
		return parseStringToArray(answer);
	}
	public uint32_t sensorLineGetRawValue(uint8_t num)
	{
		string toSend = new string(1, SensorsEnum.raw_line_sensor);
		toSend += Convert.ToString(num);
		string answer = sendCommand(ControllerEnum.sensorsControllerID, toSend, true);
		return Convert.ToInt32(answer);
	}
	public List<uint32_t> sensorLineGetAllRawValues()
	{
		string toSend = new string(1, SensorsEnum.raw_line_sensor_all);
		string answer = sendCommand(ControllerEnum.sensorsControllerID, toSend, true);
		return parseStringToArray(answer);
	}

	/* servo controller */
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
		toSend += Convert.ToString(*reinterpret_cast<const uint8_t>(axisIndex));
		toSend += (char)delimiter;
		toSend += Convert.ToString(angle);
		sendCommand(ControllerEnum.servoControllerID, toSend);
		return true;
	}
	public uint16_t servoGetAngle(ServoIndex axisIndex)
	{
		string toSend = new string(1, ServoCommands.get_angle);
//C++ TO C# CONVERTER TODO TASK: There is no equivalent to 'reinterpret_cast' in C#:
		toSend += Convert.ToString(*reinterpret_cast<const uint8_t>(axisIndex));
		string answer = sendCommand(ControllerEnum.servoControllerID, toSend, true);
		return Convert.ToInt32(answer);
	}
}
