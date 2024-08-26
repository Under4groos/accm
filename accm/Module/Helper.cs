using System.Runtime.InteropServices;

namespace accm.Module
{
    [UnmanagedFunctionPointer(CallingConvention.StdCall)]
    public delegate void _mouse_hook_pkm(UIntPtr key, int x, int y);



    public static partial class Helper
    {
#if DEBUG

        public const string dll_ = @"C:\Users\UnderKo\source\repos\accm\x64\Release\winapi_module.dll";
#else
        //public const string dll_ = "winapi_module.dll";
#endif


        [LibraryImport(dll_, SetLastError = true, StringMarshalling = StringMarshalling.Utf16, EntryPoint = "InitHook")]
        internal static partial int InitHook(IntPtr win);

        [LibraryImport(dll_, SetLastError = true, StringMarshalling = StringMarshalling.Utf16, EntryPoint = "SetHWNDWindow")]
        internal static partial void SetHWNDWindow(IntPtr win);


        [LibraryImport("user32.dll")]
        public static partial IntPtr GetForegroundWindow();

        [DllImport("user32.dll", EntryPoint = "SetWindowPos")]
        public static extern IntPtr SetWindowPos(IntPtr hWnd, int hWndInsertAfter, int x, int Y, int cx, int cy, int wFlags);




        public static void SetPositionWin(IntPtr hwnd, int x, int y, bool isShow = true)
        {

            Helper.SetWindowPos(hwnd, -1, x, y, 0, 0, 0x0001 | 0x0004 | (isShow ? 0x0040 : 0x0080));
        }


        //[DllImport(dll_, CharSet = CharSet.Auto, SetLastError = true)]
        //public static extern int Test();

        //public delegate IntPtr LowLevelMouseProc(int nCode, IntPtr wParam, IntPtr lParam);



        //[DllImport("user32.dll")]
        //public static extern int GetWindowText(IntPtr hWnd, StringBuilder text, int count);



        //[DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]

        //public static extern IntPtr SetWindowsHookEx(int idHook, LowLevelMouseProc lpfn, IntPtr hMod, uint dwThreadId);

        //[DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]

        //[return: MarshalAs(UnmanagedType.Bool)]

        //public static extern bool UnhookWindowsHookEx(IntPtr hhk);


        //[DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]

        //public static extern IntPtr CallNextHookEx(IntPtr hhk, int nCode, IntPtr wParam, IntPtr lParam);

        //[DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]

        //public static extern IntPtr GetModuleHandle(string lpModuleName);
    }

    [StructLayout(LayoutKind.Sequential)]
    public struct POINT
    {
        public int x;
        public int y;
    }
    public enum MosueButtons
    {
        WM_LBUTTONDOWN = 0x0201,
        WM_LBUTTONUP = 0x0202,
        WM_LBUTTONDBLCLK = 0x0203,
        WM_RBUTTONDOWN = 0x0204,
        WM_RBUTTONUP = 0x0205,
        WM_RBUTTONDBLCLK = 0x0206,
        WM_MBUTTONDOWN = 0x0207,
        WM_MBUTTONUP = 0x0208,
        WM_MBUTTONDBLCLK = 0x0209,
    }
    public unsafe struct Mouse_wParam
    {
        public int X;
        public int Y;
        public int wParam;

        public override string ToString()
        {
            return $"{(wParam)} => {X}/{Y}";
        }
    }



}
