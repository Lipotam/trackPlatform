using System;
using System.Runtime.InteropServices;

namespace Sample_App
{
    public class ApiManager
    {
        private const string DllName = "cxx.unmanaged.dll";
        
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SensorCallback(int sensorIndex, uint value);

        [DllImport(DllName, EntryPoint = "connect", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Connect(string comAddress, uint speed);
        [DllImport(DllName, EntryPoint = "disconnect", CallingConvention = CallingConvention.Cdecl)]
        private static extern void disconnect(IntPtr manager);
        [DllImport(DllName, EntryPoint = "set_sensor_callbacks", CallingConvention = CallingConvention.Cdecl)]
        private static extern void SetSensorCallbacks([MarshalAs(UnmanagedType.FunctionPtr)] SensorCallback distanceSensorCallback, [MarshalAs(UnmanagedType.FunctionPtr)] SensorCallback lineSensorCallback);

        private SensorCallback _distanceCallback;
        private SensorCallback _lineCallback;

        public ApiManager(SensorCallback distanceCallback, SensorCallback lineCallback)
        {
            _distanceCallback = distanceCallback;
            _lineCallback = lineCallback;
        }
    }
}