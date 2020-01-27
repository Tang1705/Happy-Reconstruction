#include "stdafx.h"
#include "RecordingDialogCommon.h"

namespace FlyCap2RecordingDialog
{
	BOOL ConvertToInt(CString* text, unsigned int* integer)
	{
		errno = 0;
		*integer = _ttoi(text->GetBuffer());
		return ((errno == 0) || (*integer != 0));
	}
}