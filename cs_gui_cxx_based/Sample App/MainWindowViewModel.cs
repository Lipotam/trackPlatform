using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Threading;

namespace Sample_App
{
    public class MainWindowViewModel : INotifyPropertyChanged, IDisposable
    {
        #region INotifyPropertyChanged implementation

        /// <summary>
        /// Call to change property
        /// </summary>
        /// <typeparam name="T">Property type</typeparam>
        /// <param name="value">New property value</param>
        /// <param name="maskedValue">Field with old property value (masked field)</param>
        /// <param name="propertyName">Name of property</param>
        protected void ChangeProperty<T>(ref T value, ref T maskedValue, string propertyName)
        {
            bool isChanged;
            if (maskedValue == null)
            {
                isChanged = (value != null);
            }
            else
            {
                isChanged = !maskedValue.Equals(value);
            }
            maskedValue = value;
            if (isChanged)
            {
                OnPropertyChanged(propertyName);
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        protected virtual void OnPropertyChanged(string propertyName)
        {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        #endregion

        private bool _maskIsConnected = false;

        private const int DinstanseNum = 5;
        private const int LineNum = 5;
        private const int LineWhite = 0;

        public uint[] Distanse { get; } = new uint[DinstanseNum];
        /// <summary>
        /// Contains true if Line is white, else false
        /// </summary>
        public bool[] Line { get; } = new bool[LineNum];

        public string SelectedPort { get; set; }
        public uint Speed { get; } = 9600;

        public bool IsConnected
        {
            get => _maskIsConnected;
            set => ChangeProperty(ref value, ref _maskIsConnected, nameof(IsConnected));
        }

        private readonly ApiManager _api;

        public MainWindowViewModel()
        {
            ApiManager.SensorCallback lineCallback = (index, value) =>
            {
                Line[index] = (value == LineWhite);
                OnPropertyChanged(nameof(Line));
            };
            ApiManager.SensorCallback distanceCallback = (index, value) =>
            {
                Distanse[index] = value;
                OnPropertyChanged(nameof(Distanse));
            };

            _api = new ApiManager(distanceCallback, lineCallback);
        }

        /// <summary>
        /// Connect to device with selected configuration
        /// </summary>
        /// <returns>true, if successfully connected, else false</returns>
        private bool Connect()
        {
            bool res = _api.ConnectToDevice(SelectedPort, Speed);
            IsConnected = res;
            return res;
        }

        /// <summary>
        /// Disconnect from device
        /// </summary>
        private void Disconnect()
        {
            _api.Disconnect();
            IsConnected = false;
        }

        /// <summary>
        /// Toggle connection to device
        /// </summary>
        /// <returns>true if all is successful, else false</returns>
        public bool ToggleConnection()
        {
            try
            {
                if (IsConnected)
                {
                    Disconnect();
                    return true;
                }

                return Connect();
            }
            catch (Exception e)
            {
                MessageBox.Show(e.Message, "We have an error", MessageBoxButton.OK, MessageBoxImage.Error);
                IsConnected = false;
                return false;
            }
        }

        public void Dispose()
        {
            _api?.Dispose();
        }
    }
}