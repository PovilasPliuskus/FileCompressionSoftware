using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Win32;
using System.IO;
using System.Runtime.CompilerServices;

namespace FileCompressionSoftware
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
        }

        private void Border_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.FilterIndex = 1;

            if (openFileDialog.ShowDialog() == true)
            {
                // selectedFile - the absolute address of the file
                string selectedFile = openFileDialog.FileName;
                string fileName = System.IO.Path.GetFileName(selectedFile);
                DADTextBlock.Text = "Selected file: " + fileName;
                DADTextBlock.Foreground = Brushes.Black;
                DADTextBlock.VerticalAlignment = VerticalAlignment.Top;
                DADTextBlock.HorizontalAlignment= HorizontalAlignment.Left;
                CompressButton.IsEnabled = true;
                EncryptButton.IsEnabled = true;
            }
        }

        // This attribute specifies the method that will be called when a file is dropped onto the container
        private void Border_Drop(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                string[] files = (string[])e.Data.GetData(DataFormats.FileDrop);

                // For simplicity, we only handle the first file
                string selectedFile = files[0];
                string fileName = System.IO.Path.GetFileName(selectedFile);
                DADTextBlock.Text = "Selected file: " + fileName;
                DADTextBlock.Foreground = Brushes.Black;
                DADTextBlock.VerticalAlignment = VerticalAlignment.Top;
                DADTextBlock.HorizontalAlignment = HorizontalAlignment.Left;
                CompressButton.IsEnabled = true;
                EncryptButton.IsEnabled = true;
            }
        }

        // This attribute specifies the method that will be called when a file is dragged over the container
        private void Border_DragEnter(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                e.Effects = DragDropEffects.Copy;
            }
            else
            {
                e.Effects = DragDropEffects.None;
            }

            e.Handled = true;
        }

        // This attribute specifies the method that will be called repeatedly while a file is being dragged over the container
        private void Border_DragOver(object sender, DragEventArgs e)
        {
            if (e.Data.GetDataPresent(DataFormats.FileDrop))
            {
                e.Effects = DragDropEffects.Copy;
            }
            else
            {
                e.Effects = DragDropEffects.None;
            }

            e.Handled = true;
        }

        private void CompressButton_Click(object sender, RoutedEventArgs e)
        {
            Compress compress = new Compress();
            compress.ShowDialog();
        }
    }

}
