// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

using System;
using System.Net;
using System.Runtime.InteropServices;

namespace Client_GUI.NativeClient
{
    internal static class NativeMethods
    {
        [DllImport("Client DLL.dll", BestFitMapping = false, ThrowOnUnmappableChar = true)]
        internal static extern IntPtr CtorApplication(String ip, String port);

        [DllImport("Client DLL.dll")]
        internal static extern void DtorApplication(IntPtr pNative);

        [DllImport("Client DLL.dll", BestFitMapping = false, ThrowOnUnmappableChar = true)]
        internal static extern void SendCommand(IntPtr pNative, String command);

        [DllImport("Client DLL.dll")]
        internal static extern void Close(IntPtr pNative);
    }

    public class Client : IDisposable 
    {
        #region Fileds

        private IntPtr m_pNativeClient = IntPtr.Zero;

        #endregion

        #region Methods

        public void SendCommand(String command)
        {
            NativeMethods.SendCommand(this.m_pNativeClient, command);
        }

        public void Close()
        {
            NativeMethods.Close(this.m_pNativeClient);
        }

        public void Dispose()
        {
            this.Dispose(true);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (this.m_pNativeClient != IntPtr.Zero)
            {
                NativeMethods.Close(this.m_pNativeClient);
                NativeMethods.DtorApplication(this.m_pNativeClient);

                this.m_pNativeClient = IntPtr.Zero;
            }

            if (disposing)
                GC.SuppressFinalize(this);
        }

        #endregion

        #region Constructors

        public Client(IPEndPoint ipEndPoint)
        {
            this.m_pNativeClient = NativeMethods.CtorApplication(ipEndPoint.Address.ToString(), ipEndPoint.Port.ToString());
        }

        #endregion

        #region Finalizers

        ~Client()
        {
            this.Dispose(false);
        }

        #endregion
    }
}

