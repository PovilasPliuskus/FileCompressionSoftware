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
using System.Diagnostics;
using System.Security.Cryptography.Xml;

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

        // selectedFileURL - the absolute address of the file
        string selectedFileURL;

        private void Border_MouseLeftButtonDown(object sender, MouseButtonEventArgs e)
        {
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.FilterIndex = 1;

            if (openFileDialog.ShowDialog() == true)
            {
                selectedFileURL = openFileDialog.FileName;
                string fileName = System.IO.Path.GetFileName(selectedFileURL);
                DADTextBlock.Text = "Selected file: " + fileName;
                DADTextBlock.Foreground = Brushes.Black;
                DADTextBlock.VerticalAlignment = VerticalAlignment.Top;
                DADTextBlock.HorizontalAlignment= HorizontalAlignment.Left;
                CompressButton.IsEnabled = true;
                EncryptButton.IsEnabled = true;
                DecompressButton.IsEnabled = true;
                DecryptButton.IsEnabled = true;
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
                DecryptButton.IsEnabled = true;
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
            Compress compress = new Compress(selectedFileURL);
            compress.ShowDialog();
        }

        private void EncryptButton_Click(object sender, RoutedEventArgs e)
        {
            string arguments = $"/e {selectedFileURL}"; 

            ProcessStartInfo startInfo = new ProcessStartInfo(@"C:\Windows\System32\cipher.exe", $"{arguments}");
            startInfo.UseShellExecute = false;
            startInfo.RedirectStandardOutput = true;

            Process process = Process.Start(startInfo);

            // Check if there was an error while encrypting
            process.WaitForExit();
            if(process.ExitCode == 0)
            {

            }
        }

        private void DectryptButton_Click(object sender, RoutedEventArgs e)
        {
            string arguments = $"/d {selectedFileURL}";

            ProcessStartInfo startInfo = new ProcessStartInfo(@"C:\Windows\System32\cipher.exe", $"{arguments}");
            startInfo.UseShellExecute = false;
            startInfo.RedirectStandardOutput = true;

            Process process = Process.Start(startInfo);

            // Check if there was an error while decrypting
            process.WaitForExit();
            if (process.ExitCode == 0)
            {

            }
        }

        private void DecompressButton_Click(object sender, RoutedEventArgs e)
        {
            Decompress decompress = new Decompress(selectedFileURL);
            decompress.ShowDialog();
        }
    }

}
