using System;
using System.Collections.Generic;
using System.Windows.Forms;
using FlyCapture2Managed;

namespace FlyCap2CameraControl
{
    static class Program
    {

        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        [STAThread]
        static void Main()
        {
            ManagedBusManager busMgr = new ManagedBusManager();
            // Pop up the camera selection dialog
            FlyCapture2Managed.Gui.CameraSelectionDialog camSlnDlg = new FlyCapture2Managed.Gui.CameraSelectionDialog();
            if (camSlnDlg.ShowModal() == false)
            {
                MessageBox.Show("No cameras selected.", "Flycapture2", MessageBoxButtons.OK, MessageBoxIcon.Information);
                return;
            }

            ManagedPGRGuid[] selectedGuids = camSlnDlg.GetSelectedCameraGuids();

            // Only start the first selected camera
            ManagedPGRGuid guid = selectedGuids[0];
            InterfaceType ifType;
            ManagedCameraBase camera;
            try
            {
                ifType = busMgr.GetInterfaceTypeFromGuid(guid);//unable to handle this error

            }
            catch (FC2Exception ex)
            {
                string error = string.Format("Failed to get interface for camera. {0}", ex.Message);
                Console.WriteLine(error);
                MessageBox.Show(error, "Flycapture 2", MessageBoxButtons.OK, MessageBoxIcon.Error);
                return;
            }
            if (ifType == InterfaceType.GigE)
            {
                camera = new ManagedGigECamera();
            }
            else
            {
                camera = new ManagedCamera();
            }
            camera.Connect(guid);

            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            CameraControlMainFrame mainWindow = new CameraControlMainFrame();
            mainWindow.Connect(camera);
            mainWindow.ShowWindow();
            
        }
    }
}