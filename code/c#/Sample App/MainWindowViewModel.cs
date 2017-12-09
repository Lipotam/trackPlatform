using System.ComponentModel;

namespace Sample_App
{
    public class MainWindowViewModel : INotifyPropertyChanged
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

        private const int DinstanseNum = 5;
        private const int LineNum = 5;

        public uint[] Distanse { get; } = new uint[DinstanseNum];
        /// <summary>
        /// Contains true if Line is white, else false
        /// </summary>
        public bool[] Line { get; } = new bool[LineNum];
    }
}