using FlyCapture2SimpleGUI_WPF;
using FlyCapture2Managed;
using FlyCapture2Managed.Gui;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Shapes;
using System.Windows.Threading;

namespace FlyCapture2SimpleGUI_WPF
{
    /// <summary>
    /// Interaction logic for FullImageWindow.xaml
    /// </summary>
    public partial class FullImageWindow : Window
    {
        public struct WorkerHelper
        {
            public ManagedImage raw;
            public ManagedImage converted;
            public ManagedCameraBase cam;
            public BitmapSource source;
        }

        ManagedBusManager m_busmgr;
        ManagedCameraBase m_cam;
        CameraControlDialog m_ctldlg;
        CameraSelectionDialog m_selDlg;
        ManagedImage m_image;
        ManagedImage m_converted;
        BitmapImage m_bitmap;

        BackgroundWorker m_worker;
        bool m_continue = false;
        AutoResetEvent m_Done;

        public FullImageWindow()
        {
            InitializeComponent();
            this.Title =string.Format("FLIR Integrated Imaging Solutions. Zoom Demo. Tier {0}", (RenderCapability.Tier >> 16).ToString());

            m_busmgr = new ManagedBusManager();
            m_ctldlg = new CameraControlDialog();
            m_selDlg = new CameraSelectionDialog();
            m_image = new ManagedImage();
            m_converted = new ManagedImage();

            m_bitmap = new BitmapImage();
            m_worker = new BackgroundWorker();
            m_worker.WorkerReportsProgress = true;
            m_worker.DoWork += new DoWorkEventHandler(m_worker_DoWork);
            m_worker.ProgressChanged += new ProgressChangedEventHandler(m_worker_ProgressChanged);
            m_Done = new AutoResetEvent(false);

            RenderOptions.SetBitmapScalingMode(myImage, BitmapScalingMode.LowQuality);
            RenderOptions.SetEdgeMode(myImage, EdgeMode.Aliased);

            if (m_selDlg.ShowModal())
            {
                ManagedPGRGuid[] guids = m_selDlg.GetSelectedCameraGuids();

                // Determine camera interface
                var interfaceType = m_busmgr.GetInterfaceTypeFromGuid(guids[0]);

                if (interfaceType == InterfaceType.GigE)
                {
                    m_cam = new ManagedGigECamera();
                }
                else
                {
                    m_cam = new ManagedCamera();
                }

                // Connect to camera object
                m_cam.Connect(guids[0]);
                
                // Connect control dialog
                m_ctldlg.Connect(m_cam);
                
                // Start capturing
                m_cam.StartCapture();

                btn_nearfast.IsChecked = true;

                WorkerHelper helper = new WorkerHelper();
                helper.converted = m_converted;
                helper.raw = m_image;
                helper.cam = m_cam;
                m_continue = true;
                m_worker.RunWorkerAsync(helper);
            }
            else
            {
                Application.Current.Shutdown();
            }
        }

        private void m_worker_DoWork(object sender, DoWorkEventArgs e)
        {
            while (m_continue)
            {
                try
                {
                    BackgroundWorker worker = (BackgroundWorker)sender;
                    WorkerHelper helper = (WorkerHelper)e.Argument;

                    helper.cam.RetrieveBuffer(helper.raw);
                    helper.raw.ConvertToBitmapSource(helper.converted);
                    helper.source = helper.converted.bitmapsource;
                    helper.source.Freeze();
                    worker.ReportProgress(0, helper.source);
                }
                catch (Exception ex)
                {
                    Debug.WriteLine(ex.Message);
                }
                finally
                {
                    GC.Collect();
                }
            }
        }

        private void m_worker_ProgressChanged(object sender, ProgressChangedEventArgs e)
        {
            BitmapSource image = (BitmapSource)e.UserState;
            this.Dispatcher.Invoke(DispatcherPriority.Render,
            (ThreadStart)delegate()
            {
                myImage.Source = image;
            }
            );
        }

        private void Window_Closing(object sender, EventArgs e)
        {
            m_continue = false;
            try
            {
                m_Done.WaitOne(100);
                m_cam.StopCapture();
                m_cam.Disconnect();
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
            }
            finally
            {
                Application.Current.Shutdown();
            }
        }


        private void btn_Camctldlg_Click(object sender, RoutedEventArgs e)
        {
            if (m_ctldlg.IsVisible())
            {
                m_ctldlg.Hide();
            }
            else
            {
                m_ctldlg.Show();
            }
        }

        private void btn_Exit_Click(object sender, RoutedEventArgs e)
        {
            m_continue = false;
            try
            {
                m_Done.WaitOne(100);
                m_cam.StopCapture();
                m_cam.Disconnect();
            }
            catch (Exception ex)
            {
                Debug.WriteLine(ex.Message);
            }
            finally
            {
                Application.Current.Shutdown();
            }
        }

        private void btn_About_Click(object sender, RoutedEventArgs e)
        {
            MessageBox.Show(string.Format("FlyCapture2SimpleGUI_WPF\nWritten by: Ran Guo"));
        }

        private void UncheckAll()
        {
            foreach (MenuItem item in colorProcessingMethods.Items)
            {
                item.IsChecked = false;
            }
        }

        private void btn_None_Click(object sender, RoutedEventArgs e)
        {
            UncheckAll();
            btn_None.IsChecked = true;
            ManagedImage.defaultColorProcessingAlgorithm = ColorProcessingAlgorithm.NoColorProcessing;
        }

        private void btn_nearfast_Click(object sender, RoutedEventArgs e)
        {
            UncheckAll();
            btn_nearfast.IsChecked = true;
            ManagedImage.defaultColorProcessingAlgorithm = ColorProcessingAlgorithm.NearestNeighbor;
        }

        private void btn_edgesensing_Click(object sender, RoutedEventArgs e)
        {
            UncheckAll();
            btn_edgesensing.IsChecked = true;
            ManagedImage.defaultColorProcessingAlgorithm = ColorProcessingAlgorithm.EdgeSensing;
        }

        private void btn_HQLinear_Click(object sender, RoutedEventArgs e)
        {
            UncheckAll();
            btn_HQLinear.IsChecked = true;
            ManagedImage.defaultColorProcessingAlgorithm = ColorProcessingAlgorithm.HQLinear;
        }

        private void btn_Directional_Click(object sender, RoutedEventArgs e)
        {
            UncheckAll();
            btn_Directional.IsChecked = true;
            ManagedImage.defaultColorProcessingAlgorithm = ColorProcessingAlgorithm.Directional;
        }

        private void btn_WeightedDirectional_Click(object sender, RoutedEventArgs e)
        {
            UncheckAll();
            btn_WeightedDirectional.IsChecked = true;
            ManagedImage.defaultColorProcessingAlgorithm = ColorProcessingAlgorithm.WeightedDirectional;
        }

        private void btn_Rigorous_Click(object sender, RoutedEventArgs e)
        {
            UncheckAll();
            btn_Rigorous.IsChecked = true;
            ManagedImage.defaultColorProcessingAlgorithm = ColorProcessingAlgorithm.Rigorous;
        }

        private void btn_IPP_Click(object sender, RoutedEventArgs e)
        {
            UncheckAll();
            btn_IPP.IsChecked = true;
            ManagedImage.defaultColorProcessingAlgorithm = ColorProcessingAlgorithm.IPP;
        }
    }
}
