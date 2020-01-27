using System;
using System.Runtime.InteropServices;
using System.Text;

using FlyCapture2Managed;

namespace FlyCap2CameraControl
{
    /** 
     * Simple class to check if the camera is a Ladybug camera. In cases where
     * there are both single lens and Ladybug cameras present, then a combined
     * call to check for the DLL *AND* the camera type is required!
     * 
     */
    internal class LadybugChecker
    {
        public static bool IsLadybug(CameraInfo camInfo)
        {
            return IsLadybug2(camInfo) || IsLadybug3(camInfo) || IsLadybug5(camInfo);
        }

        public static bool IsLadybug2(CameraInfo camInfo)
        {
            return camInfo.modelName.Contains("Compressor");
        }

        public static bool IsLadybug3(CameraInfo camInfo)
        {
            return camInfo.modelName.Contains("Ladybug3");
        }

        public static bool IsLadybug5(CameraInfo camInfo)
        {
            return camInfo.modelName.Contains("Ladybug5");
        }

        [DllImport("kernel32.dll", CharSet = CharSet.Auto)]
        public static extern IntPtr GetModuleHandle(string lpModuleName);

        public static bool IsLadybugDLLPresent()
        {
            string[] modules = new string[] { "LadybugGUI.dll", "LadybugGUId.dll" };
            int numModules = modules.Length;
            IntPtr module = IntPtr.Zero;

            for (int i = 0; i < modules.Length; i++)
            {
                module = GetModuleHandle(modules[i]);
                if (module != IntPtr.Zero)
                {
                    break;
                }
            }

            if (module == IntPtr.Zero)
            {
                return false;
            }
            else
            {
                module = IntPtr.Zero;
                return true;
            }
        }
    }
}
