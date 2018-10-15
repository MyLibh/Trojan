using System;
using System.Net;
using System.Runtime.InteropServices;

namespace Client_GUI.NativeClient
{ 
    public class NativeMethods : IDisposable
    {
        #region P/Invokes

        [DllImport("Client DLL.dll", BestFitMapping = false, ThrowOnUnmappableChar = true)]
        static private extern IntPtr CtorApplication(string ip, string port);
        
        [DllImport("Client DLL.dll")]
        static private extern void DtorApplication(IntPtr pNative);

        [DllImport("Client DLL.dll", BestFitMapping = false, ThrowOnUnmappableChar = true)]
        static private extern void SendCommand(IntPtr pNative, string command);

        [DllImport("Client DLL.dll")]
        static private extern void Close(IntPtr pNative);

        #endregion

        private IntPtr m_pNativeClient = IntPtr.Zero;
        
        public NativeMethods(IPEndPoint endPoint)
        {
            this.m_pNativeClient = CtorApplication(endPoint.Address.ToString(), endPoint.Port.ToString());
            if (this.m_pNativeClient == IntPtr.Zero)
                Console.Write("Bad Alloc");
        }

        public void Dispose()
        {
            Dispose(true);
        }

        protected virtual void Dispose(bool disposing)
        {
            if(this.m_pNativeClient != IntPtr.Zero)
            {
                Close(this.m_pNativeClient);
                DtorApplication(this.m_pNativeClient);

                this.m_pNativeClient = IntPtr.Zero;
            }

            if (disposing)
                GC.SuppressFinalize(this);
        }

        ~NativeMethods()
        {
            Dispose(false);
        }

        #region Wrapper methods

        public void SendCommand(string command)
        {
            SendCommand(this.m_pNativeClient, command);
        }

        public void Close()
        {
            Close(m_pNativeClient);
        }

        #endregion
    }
}

