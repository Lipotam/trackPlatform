using System;
using System.Runtime.InteropServices;

namespace Sample_App
{
    public class ApiManager : IDisposable
    {
        private const string DllName = "cxx.unmanaged.dll";
        
        [UnmanagedFunctionPointer(CallingConvention.Cdecl)]
        public delegate void SensorCallback(int sensorIndex, uint value);

        [DllImport(DllName, EntryPoint = "connect", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Connect(string comAddress, uint speed);
        [DllImport(DllName, EntryPoint = "disconnect", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Disconnect(IntPtr manager);
        [DllImport(DllName, EntryPoint = "set_sensor_callbacks", CallingConvention = CallingConvention.Cdecl)]
        private static extern void SetSensorCallbacks([MarshalAs(UnmanagedType.FunctionPtr)] SensorCallback distanceSensorCallback, [MarshalAs(UnmanagedType.FunctionPtr)] SensorCallback lineSensorCallback);

        private readonly SensorCallback _distanceCallback;
        private readonly SensorCallback _lineCallback;
        private IntPtr _unmanagedPtr = IntPtr.Zero;

        public ApiManager(SensorCallback distanceCallback, SensorCallback lineCallback)
        {
            _distanceCallback = distanceCallback;
            _lineCallback = lineCallback;
        }

        /// <summary>
        /// Connect to target device
        /// </summary>
        /// <param name="comAddress">Address of COM port to connect</param>
        /// <param name="speed">COM port speed</param>
        /// <returns>true, if connectio was successful, else false</returns>
        public bool ConnectToDevice(string comAddress, uint speed)
        {
            if (_unmanagedPtr != IntPtr.Zero)
            {
                return false;
            }

            _unmanagedPtr = Connect(comAddress, speed);
            if (_unmanagedPtr == IntPtr.Zero)
            {
                return false;
            }

            SetSensorCallbacks(_distanceCallback, _lineCallback);
            return true;
        }

        /// <summary>
        /// Disconnect from target device
        /// </summary>
        public void Disconnect()
        {
            if (_unmanagedPtr == IntPtr.Zero) return;

            Disconnect(_unmanagedPtr);
            _unmanagedPtr = IntPtr.Zero;
        }

        private void ReleaseUnmanagedResources()
        {
            Disconnect();
        }

        public void Dispose()
        {
            ReleaseUnmanagedResources();
            GC.SuppressFinalize(this);
        }

        ~ApiManager()
        {
            ReleaseUnmanagedResources();
        }
    }
}