using Microsoft.Win32;
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
using System.Windows.Shapes;
using System.IO;
using System.Diagnostics;
using System.Reflection;

namespace FileCompressionSoftware
{
    /// <summary>
    /// Interaction logic for Compress.xaml
    /// </summary>
    public partial class Compress : Window
    {
        public Compress(string selectedFileURL)
        {
            InitializeComponent();
            SelectedDocumentTextBox.Text = selectedFileURL;
            FillFileInformation();
        }

        public void FillFileInformation()
        {
            // file name
            FileName.Text = System.IO.Path.GetFileName(SelectedDocumentTextBox.Text);
            // file size
            FileInfo fileInfo = new FileInfo(SelectedDocumentTextBox.Text);
            FileSize.Text = System.Math.Ceiling(fileInfo.Length / 1024.0).ToString() + " KB";
            // convertion date
            DateTime now = DateTime.Now;
            ModificationDate.Text = now.ToString("yyyy-MM-dd HH:mm:ss");
        }

        private void SelectedDocumentButton_Click(object sender, RoutedEventArgs e)
        {
            OpenFileDialog openFileDialog= new OpenFileDialog();
            openFileDialog.FilterIndex = 1;

            if (openFileDialog.ShowDialog() == true)
            {
                SelectedDocumentTextBox.Text = openFileDialog.FileName;
                FillFileInformation();
            }
        }

        private void CompressedDocumentButton_Click(object sender, RoutedEventArgs e)
        {
            SaveFileDialog saveFileDialog= new SaveFileDialog();

            if (HuffmanRadioButton.IsChecked == true)
            {
                saveFileDialog.Filter = "Huffman Coded File(*.hfm)|*.hfm";
            }
            else
            {
                saveFileDialog.Filter = "LZ Coded File(*.lz)|*.lz";
            }

            if (saveFileDialog.ShowDialog() == true)
            {
                CompressedDocumentTextBox.Text = saveFileDialog.FileName;
            }
        }

        private async void CompressionButton_Click(object sender, RoutedEventArgs e)
        {
<<<<<<< HEAD
            if (CheckIfValidInput() == false)
            {
                return;
            }
            if (HuffmanRadioButton.IsChecked == true)
            {
                StatusTextBlock.Text = "Compressing";
                StatusTextBlock.Background = Brushes.Yellow;

                string HuffmanAlgorithm = @"..\\..\\..\\HuffmanAlgorithm\\main.exe";
                string inputFile = SelectedDocumentTextBox.Text;
                string outputFile = CompressedDocumentTextBox.Text;

                int estimatedTimeInSeconds = 30;

                await Task.Run(() =>
                {
                    ProcessStartInfo startInfo = new ProcessStartInfo(HuffmanAlgorithm, $"{inputFile} {outputFile}")
                    {
                        CreateNoWindow = true
                    };
                    Process process = Process.Start(startInfo);

                    while (!process.WaitForExit(100))
                    {

                        Dispatcher.Invoke(() =>
                        {
                            double progress = 0;
                            if (estimatedTimeInSeconds > 0)
                            {
                                progress = ((double)process.TotalProcessorTime.Ticks / (double)TimeSpan.TicksPerSecond) / (double)estimatedTimeInSeconds;
                            }
                            CompressionProgressBar.Value = progress * 100;
                        });
                    }

                    if (process.ExitCode == 0)
                    {
                        Dispatcher.Invoke(() =>
                        {
                            StatusTextBlock.Text = "Successfully Compressed";
                            StatusTextBlock.Background = Brushes.Green;
                            CompressionProgressBar.Value = 100;
                        });
                    }
                    else
                    {
                        Dispatcher.Invoke(() =>
                        {
                            StatusTextBlock.Text = "Compression Failed";
                            StatusTextBlock.Background = Brushes.Red;
                            CompressionProgressBar.Value = 0;
                        });
                    }
                });
            }
            else if (LZRadioButton.IsChecked == true)
            {
                StatusTextBlock.Text = "Compressing";
                StatusTextBlock.Background = Brushes.Yellow;

                string LZAlgorithm = @"..\\..\\..\\LZAlgorithm\\LZAlgorithm.exe";
                string inputFile = SelectedDocumentTextBox.Text;
                string outputFile = CompressedDocumentTextBox.Text;

                int estimatedTimeInSeconds = 60;

                await Task.Run(() =>
                {
                    ProcessStartInfo startInfo = new ProcessStartInfo(LZAlgorithm, $"{inputFile} {outputFile}")
                    {
                        CreateNoWindow = true
                    };
                    Process process = Process.Start(startInfo);

                    while (!process.WaitForExit(100))
                    {

                        Dispatcher.Invoke(() =>
                        {
                            double progress = 0;
                            if (estimatedTimeInSeconds > 0)
                            {
                                progress = ((double)process.TotalProcessorTime.Ticks / (double)TimeSpan.TicksPerSecond) / (double)estimatedTimeInSeconds;
                            }
                            CompressionProgressBar.Value = progress * 100;
                        });
                    }

                    if (process.ExitCode == 0)
                    {
                        Dispatcher.Invoke(() =>
                        {
                            StatusTextBlock.Text = "Successfully Compressed";
                            StatusTextBlock.Background = Brushes.Green;
                            CompressionProgressBar.Value = 100;
                        });
                    }
                    else
                    {
                        Dispatcher.Invoke(() =>
                        {
                            StatusTextBlock.Text = "Compression Failed";
                            StatusTextBlock.Background = Brushes.Red;
                            CompressionProgressBar.Value = 0;
                        });
                    }
                });
            }
        }

        public bool CheckIfValidInput()
        {
            if (SelectedDocumentTextBox.Text == "")
            {
                MessageBox.Show("No document selected for compression");
                return false;
            }
            if (CompressedDocumentTextBox.Text == "")
            {
                MessageBox.Show("Please select compressed document location");
                return false;
            }
            if (!File.Exists(SelectedDocumentTextBox.Text))
            {
                MessageBox.Show("Could not locate the selected document for compression");
                return false;
            }
            return true;
        }

        private void HuffmanRadioButton_Checked(object sender, RoutedEventArgs e)
        {
            if (CompressedDocumentTextBox.Text != "")
            {
                string tempString = CompressedDocumentTextBox.Text;
                string currentExtension = System.IO.Path.GetExtension(CompressedDocumentTextBox.Text);
                CompressedDocumentTextBox.Text = tempString.Substring(0, tempString.Length - currentExtension.Length) + ".hfm";
            }
        }

        private void LZRadioButton_Checked(object sender, RoutedEventArgs e)
        {
            if (CompressedDocumentTextBox.Text != "")
            {
                string tempString = CompressedDocumentTextBox.Text;
                string currentExtension = System.IO.Path.GetExtension(CompressedDocumentTextBox.Text);
                CompressedDocumentTextBox.Text = tempString.Substring(0, tempString.Length - currentExtension.Length) + ".lz";
            }
=======
            // \\ - zemyn
            // ..\\ - virsu

            string HuffmanAlgorithm = @"..\\..\\..\\HuffmanAlgorithm\\main.exe";
            string inputFile = SelectedDocumentTextBox.Text;
            string outputFile = CompressedDocumentTextBox.Text;
            
            ProcessStartInfo startInfo= new ProcessStartInfo(HuffmanAlgorithm, $"{inputFile} {outputFile}");
            startInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Maximized;
            Process.Start(startInfo);
>>>>>>> a54f32e1f94fc52b969120096d71b273ec58adee
        }
    }
}