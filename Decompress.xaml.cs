using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
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
    /// Interaction logic for Decompress.xaml
    /// </summary>
    public partial class Decompress : Window
    {
        public Decompress(string selectedFileURL)
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
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.FilterIndex = 1;

            if (openFileDialog.ShowDialog() == true)
            {
                SelectedDocumentTextBox.Text = openFileDialog.FileName;
            }
        }

        private void DecompressedDocumentButton_Click(object sender, RoutedEventArgs e)
        {
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            DecompressedDocumentTextBox.Text = saveFileDialog.FileName;

            if (saveFileDialog.ShowDialog() == true)
            {
                DecompressedDocumentTextBox.Text = saveFileDialog.FileName;
            }
        }
        public bool CheckIfValidInput()
        {
            if (SelectedDocumentTextBox.Text == "")
            {
                MessageBox.Show("No document selected for decompression");
                return false;
            }
            if (DecompressedDocumentTextBox.Text == "")
            {
                MessageBox.Show("Please select decompressed document location");
                return false;
            }
            if (!File.Exists(SelectedDocumentTextBox.Text))
            {
                MessageBox.Show("Could not locate the selected document for decompression");
                return false;
            }
            return true;
        }


        private async void DecompressionButton_Click(object sender, RoutedEventArgs e)
        {
            if (CheckIfValidInput() == false)
            {
                return;
            }

            if (SelectedDocumentTextBox.Text != null)
            {
                string filePath = SelectedDocumentTextBox.Text;
                string extension = System.IO.Path.GetExtension(filePath);

                if (extension == ".hfm")
                {
                    StatusTextBlock.Text = "Decompressing";
                    StatusTextBlock.Background = Brushes.Yellow;

                    string HuffmanAlgorithm = @"..\\..\\..\\HuffmanAlgorithm\\hfmDecompress.exe";
                    string inputFile = SelectedDocumentTextBox.Text;
                    string outputFile = DecompressedDocumentTextBox.Text;

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
                                StatusTextBlock.Text = "Successfully Decompressed";
                                StatusTextBlock.Background = Brushes.Green;
                                CompressionProgressBar.Value = 100;
                            });
                        }
                        else
                        {
                            Dispatcher.Invoke(() =>
                            {
                                StatusTextBlock.Text = "Decompression Failed";
                                StatusTextBlock.Background = Brushes.Red;
                                CompressionProgressBar.Value = 0;
                            });
                        }
                    });
                }
                else if (extension == ".lz")
                {
                    StatusTextBlock.Text = "Decompressing";
                    StatusTextBlock.Background = Brushes.Yellow;

                    string LZAlgorithm = @"..\\..\\..\\LZAlgorithm\\LZDecompress.exe";
                    string inputFile = SelectedDocumentTextBox.Text;
                    string outputFile = DecompressedDocumentTextBox.Text;

                    int estimatedTimeInSeconds = 30;

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
                                StatusTextBlock.Text = "Successfully Decompressed";
                                StatusTextBlock.Background = Brushes.Green;
                                CompressionProgressBar.Value = 100;
                            });
                        }
                        else
                        {
                            Dispatcher.Invoke(() =>
                            {
                                StatusTextBlock.Text = "Decompression Failed";
                                StatusTextBlock.Background = Brushes.Red;
                                CompressionProgressBar.Value = 0;
                            });
                        }
                    });
                }
                else
                {
                    MessageBox.Show("Please enter a file with extensions .hfm or .lz");
                }
            }
        }
    }
}
