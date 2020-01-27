// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently,
// but are changed infrequently

#pragma once

#define _CRT_SECURE_NO_WARNINGS

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#endif

// Modify the following defines if you have to target a platform prior to the ones specified below.
// Refer to MSDN for the latest info on corresponding values for different platforms.
#ifndef WINVER				// Allow use of features specific to Windows XP or later.
#define WINVER 0x0501		// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINNT		// Allow use of features specific to Windows XP or later.
#define _WIN32_WINNT 0x0501	// Change this to the appropriate value to target other versions of Windows.
#endif

#ifndef _WIN32_WINDOWS		// Allow use of features specific to Windows 98 or later.
#define _WIN32_WINDOWS 0x0410 // Change this to the appropriate value to target Windows Me or later.
#endif

#ifndef _WIN32_IE			// Allow use of features specific to IE 6.0 or later.
#define _WIN32_IE 0x0600	// Change this to the appropriate value to target other versions of IE.
#endif

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS	// some CString constructors will be explicit

// turns off MFC's hiding of some common and often safely ignored warning messages
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions


#include <afxdisp.h>        // MFC Automation classes



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


// FlyCapture includes
#include "FlyCapture2.h"
#include "FlyCapture2Gui.h"

#ifdef DIRECT2D_SUPPORT

#include <d2d1.h>

/******************************************************************
 *                                                                 *
 *  Macros                                                         *
 *                                                                 *
 ******************************************************************/

template<class Interface>
	inline void
SafeRelease(Interface **ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}

#endif
// Multithreaded access include
#include "afxmt.h"



#include <queue>
#include <afxdlgs.h>

//Histogram Definition
namespace Histogram
{
	/**
	 * Mode of the histogram window.
	 */
	enum DrawMode
	{
		MODE_HISTOGRAM, /**< Histogram mode. */
		MODE_ROWCOL /**< Row column plot mode. */
	};
	/**
	 * Histogram  Data Grid Columns
	 */
	enum DataGridColumns
	{
		CHANNEL = 0,
		RANGE,
		MEAN,
		MIN,
		MAX,
		NUM_OF_COLUMNS
	};

	/**
	 * Row column mode.
	 */
	enum RowColMode
	{
		ROWCOL_COLUMN, /**< Column mode. */
		ROWCOL_ROW, /**< Row mode. */
	};

	/**
	 * Row column channels to display.
	 */
	enum RowColDisplay
	{
		ROWCOL_GREY, /**< Display grey channel. */
		ROWCOL_RED, /**< Display red channel. */
		ROWCOL_GREEN, /**< Display green channel. */
		ROWCOL_BLUE, /**< Display blue channel. */
	};

	/**
	 * Row column functions to calculate for.
	 */
	enum RowColFunction
	{
		ROWCOL_MAX, /**< Maximum channel value. */
		ROWCOL_MEAN, /**< Mean channel value. */
		ROWCOL_MIN, /**< Minimum channel value. */
	};
	/**
	 * Histogram Binning Types
	 */
	enum BinningType
	{
		BINNING_8_16_BITS = 0,
		BINNING_10_BITS,
		BINNING_12_BITS,
		NUM_OF_BINNING_TYPES
	};

	/**
	 * Row column channels status.
	 */
	struct RowColDisplayOptions
	{
		bool showGrey;
		bool showRed;
		bool showGreen;
		bool showBlue;
	};

	/**
	 * Row column function status.
	 */
	struct RowColFunctionOptions
	{
		bool showMax;
		bool showMean;
		bool showMin;
	};

	/** The row column options, i.e. row or column, show grey or not */
	struct RowColAllOptions
	{
		RowColMode mode;
		RowColDisplayOptions displayOptions;
		RowColFunctionOptions functionOptions;
	};

	/**
	 *  Statistic data for single channel.
	 */
	struct RowColChannelStats
	{
		std::vector<unsigned int> vecMax;
		std::vector<unsigned int> vecMean;
		std::vector<unsigned int> vecMin;
	};

	/**
	 * Statistic data for row column plot mode.
	 */
	struct RowColStats
	{
		int numPixelValues;
		int imageDimension;

		RowColChannelStats grey;
		RowColChannelStats red;
		RowColChannelStats green;
		RowColChannelStats blue;

		RowColAllOptions options;
	};
}
static bool ConvertToBoolean(BOOL value)
{
	return (value == TRUE);
}
