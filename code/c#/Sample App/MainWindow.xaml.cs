using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Sample_App
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        private readonly MainWindowViewModel _vm;

        public MainWindow()
        {
            InitializeComponent();
            _vm = DataContext as MainWindowViewModel;

            //Dispose resources
            Dispatcher.ShutdownStarted += (sender, args) =>
            {
                _vm.Dispose();
            };
        }

        private void OnConnectClicked(object sender, RoutedEventArgs e)
        {
            if (!_vm.ToggleConnection())
            {
                MessageBox.Show("Cannot connect or disconnect from device");
            }
        }
    }
}
