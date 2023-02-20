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
    }
}
