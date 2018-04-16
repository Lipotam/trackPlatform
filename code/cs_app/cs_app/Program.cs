using System;
using TrackPlatform.Api;

namespace TrackPlatform.Example
{
    class Program
    {
        static void Main(string[] args)
        {
            try
            {
                UnsafeMain();
            }
            catch (Exception)
            {
                Console.WriteLine("Exception was catched");
            }
        }

        private static void UnsafeMain()
        {
            using(Manager trackPlatform = ConsolePlatformConnector.Connect())
	        {
		        if (trackPlatform == null)
		        {
                    Console.WriteLine("Cannot create Manager class");
			        return;
		        }

		        Console.WriteLine("Connected");

		        bool isExit = false;
		        while (!isExit)
		        {
			        Console.Write("Input command, please (0 to help): ");
			        ConsoleKeyInfo key = Console.ReadKey();
                    
			        Console.WriteLine();

			        switch (key.KeyChar)
			        {
			        case '0':
				        Console.WriteLine("0: help");
				        Console.WriteLine("q: quit");
				        Console.WriteLine("w: move forward");
				        Console.WriteLine("s: move back");
				        Console.WriteLine("a: turn left (anticlockwise)");
				        Console.WriteLine("d: turn right (clockwise)");
				        Console.WriteLine(" : stop");
				        Console.WriteLine("r: get all line values");
				        Console.WriteLine("e: get fixed line value");
				        Console.WriteLine("t: get all distance values");
				        Console.WriteLine("y: get fixed distance value");
				        Console.WriteLine("g: set horisontal servo angle in degree");
				        Console.WriteLine("h: set vertical servo angle in degree");
				        break;
			        case 'q':
				        isExit = true;
				        break;
			        case 'w':
				        trackPlatform.MoveForward();
				        break;
			        case 's':
				        trackPlatform.MoveBackward();
				        break;
			        case 'a':
				        trackPlatform.RotateAntiClockwise();
				        break;
			        case 'd':
				        trackPlatform.RotateClockwise();
				        break;
			        case ' ':
				        trackPlatform.MoveStopAll();
				        break;
			        case 'r':
			        {
				        int[] arr = trackPlatform.SensorLineGetAllValues();
				        foreach (int a in arr)
				        {
					        Console.WriteLine(a);
				        }
				        break;
			        }
			        case 'e':
			        {
				        Console.Write("Input num: ");
				        int a = int.Parse(Console.ReadLine() ?? "1");
				        Console.WriteLine("Value: " + trackPlatform.SensorLineGetValue(a));
				        break;
			        }
			        case 't':
			        {
				        int[] arr = trackPlatform.SensorDistanceGetAllValues();
				        foreach (int a in arr)
				        {
					        Console.WriteLine(a);
				        }
				        break;
			        }
			        case 'y':
			        {
			            Console.Write("Input num: ");
			            int a = int.Parse(Console.ReadLine() ?? "1");
			            Console.WriteLine("Value: " + trackPlatform.SensorDistanceGetValue(a));
			            break;
			        }
			        case 'g':
			        {
			            Console.Write("Input num: ");
			            int a = int.Parse(Console.ReadLine() ?? "1");
			            trackPlatform.ServoSetHorizontalAngle(a);
			            break;
			        }
			        case 'h':
			        {
			            Console.Write("Input num: ");
			            int a = int.Parse(Console.ReadLine() ?? "1");
			            trackPlatform.ServoSetVerticalAngle(a);
			            break;
			        }
			        }
		        }
            }
        }
    }
}
