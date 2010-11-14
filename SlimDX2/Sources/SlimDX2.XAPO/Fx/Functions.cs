// Copyright (c) 2007-2010 SlimDX Group
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

//------------------------------------------------------------------------------
// <auto-generated>
//     Functions for SlimDX2.XAPO.Fx namespace.
//     This code was generated by a tool.
//     Date : 11/14/2010 00:36:12
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------
using System;
using System.Runtime.InteropServices;
using System.Security;

namespace SlimDX2.XAPO.Fx {


	/// <summary>
    /// XAPOFx Functions.
    /// </summary>
    static partial class XAPOFx {   
        
        /// <summary>Constant None.</summary>
        internal static System.Guid CLSID_FXEQ = new System.Guid("a90bc001-e897-e897-7439-435500000000");
        
        /// <summary>Constant None.</summary>
        internal static System.Guid CLSID_FXMasteringLimiter = new System.Guid("a90bc001-e897-e897-7439-435500000001");
        
        /// <summary>Constant None.</summary>
        internal static System.Guid CLSID_FXReverb = new System.Guid("a90bc001-e897-e897-7439-435500000002");
        
        /// <summary>Constant None.</summary>
        internal static System.Guid CLSID_FXEcho = new System.Guid("a90bc001-e897-e897-7439-435500000003");
        
        /// <summary>	
        /// No documentation.	
        /// </summary>	
        /// <param name="clsid">No documentation.</param>
        /// <param name="effectRef">No documentation.</param>
        /// <returns>No documentation.</returns>
        /// <unmanaged>HRESULT CreateFX([None] REFCLSID clsid,[Out] IUnknown** pEffect)</unmanaged>
		public static SlimDX2.Result CreateFX(Guid clsid, out SlimDX2.ComObject effectRef) {
            unsafe {
                IntPtr effectRef_ = IntPtr.Zero;
                SlimDX2.Result __result__;
                __result__= (SlimDX2.Result)CreateFX_(ref  clsid, out effectRef_);
                effectRef = (effectRef_ == IntPtr.Zero)?null:new SlimDX2.ComObject(effectRef_);
                __result__.CheckError();
                return __result__;
            }
        }
		
		/// <summary>Native Interop Function</summary>
        /// <unmanaged>HRESULT CreateFX([None] REFCLSID clsid,[Out] IUnknown** pEffect)</unmanaged>
		[DllImport("XAPOFX1_5.dll", EntryPoint = "CreateFX", CallingConvention = CallingConvention.StdCall, PreserveSig = true), SuppressUnmanagedCodeSecurityAttribute]
		private extern static SlimDX2.Result CreateFX_(ref Guid clsid, out IntPtr effectRef);		
    }
}