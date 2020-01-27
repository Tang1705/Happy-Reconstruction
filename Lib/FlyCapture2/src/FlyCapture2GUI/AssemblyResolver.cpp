//=============================================================================
// Copyright © 2017 FLIR Integrated Imaging Solutions, Inc. All Rights Reserved.
//
// This software is the confidential and proprietary information of FLIR
// Integrated Imaging Solutions, Inc. ("Confidential Information"). You
// shall not disclose such Confidential Information and shall use it only in
// accordance with the terms of the license agreement you entered into
// with FLIR Integrated Imaging Solutions, Inc. (FLIR).
//
// FLIR MAKES NO REPRESENTATIONS OR WARRANTIES ABOUT THE SUITABILITY OF THE
// SOFTWARE, EITHER EXPRESSED OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE, OR NON-INFRINGEMENT. FLIR SHALL NOT BE LIABLE FOR ANY DAMAGES
// SUFFERED BY LICENSEE AS A RESULT OF USING, MODIFYING OR DISTRIBUTING
// THIS SOFTWARE OR ITS DERIVATIVES.
//=============================================================================

#include "AssemblyResolver.h"
#include <string>

#using <system.dll>

using namespace System::Diagnostics;

namespace AssemblyResolver
{
	AssemblyResolver::AssemblyResolver()
	{
		AppDomain^ currentDomain = AppDomain::CurrentDomain;
		currentDomain->AssemblyResolve += gcnew System::ResolveEventHandler(&AssemblyResolver::OnResolveFailed);
	}

	Assembly^ AssemblyResolver::OnResolveFailed( Object^ sender, ResolveEventArgs^ args )
	{
		Assembly^ executingAssemblies = Assembly::GetExecutingAssembly();
		array<AssemblyName^>^ referenceAssemblyNames = executingAssemblies->GetReferencedAssemblies();

		String^ inputPath = gcnew String("");
		String^ inputAssemblyName = args->Name->Substring(0, args->Name->IndexOf(","));

#ifdef _DEBUG
#if _MSC_VER == 1900
		std::string dllFileName("FlyCapture2GUId_v140.dll");
#elif _MSC_VER == 1800
		std::string dllFileName("FlyCapture2GUId_v120.dll");
#elif _MSC_VER == 1700
		std::string dllFileName("FlyCapture2GUId_v110.dll");
#elif _MSC_VER == 1600
		std::string dllFileName("FlyCapture2GUId_v100.dll");
#elif  _MSC_VER == 1500
		std::string dllFileName("FlyCapture2GUId_v90.dll");
#else
		std::string dllFileName("FlyCapture2GUId.dll");
#endif
#else
#if _MSC_VER == 1900
		std::string dllFileName("FlyCapture2GUI_v140.dll");
#elif _MSC_VER == 1800
		std::string dllFileName("FlyCapture2GUI_v120.dll");
#elif _MSC_VER == 1700
		std::string dllFileName("FlyCapture2GUI_v110.dll");
#elif _MSC_VER == 1600
		std::string dllFileName("FlyCapture2GUI_v100.dll");
#elif  _MSC_VER == 1500
		std::string dllFileName("FlyCapture2GUI_v90.dll");
#else
		std::string dllFileName("FlyCapture2GUI.dll");
#endif
#endif
		std::wstring dllReleaseFileName(dllFileName.begin(), dllFileName.end());
		String^ mgdDllFileName = gcnew String(dllReleaseFileName.c_str());

		bool foundAssembly = false;

		// Try to match the assembly that failed to resolve
		for each (AssemblyName^ fullAssemblyName in referenceAssemblyNames)
		{
			String^ parsedAssemblyName = fullAssemblyName->FullName->Substring(0, fullAssemblyName->FullName->IndexOf(","));

			if (parsedAssemblyName == inputAssemblyName)
			{
				// Construct a path for the assembly by searching for
				// FlyCapture2GUI.dll (or debug variants)

				HMODULE releaseDLL = ::LoadLibraryEx(dllReleaseFileName.c_str(), NULL, 0);
				if (releaseDLL != NULL)
				{
					const unsigned int fileNameLength = 256;
					wchar_t fileName[fileNameLength];
					if (GetModuleFileName(releaseDLL, fileName, fileNameLength) != 0)
					{
						String^ mgdFullPath = gcnew String(fileName);
						inputPath = mgdFullPath->Substring(0, mgdFullPath->IndexOf(mgdDllFileName));
					}

					::FreeLibrary(releaseDLL);
					foundAssembly = true;
					break;
				}
			}
		}

		Assembly^ assembly = nullptr;

		if (foundAssembly)
		{
			String^ fullAssemblyPath = inputPath + inputAssemblyName + ".dll";
			//Debug::WriteLine("Full assembly " + fullAssemblyPath);

			assembly = Assembly::LoadFrom(fullAssemblyPath);
		}

		return assembly;
	}
}
