#include <afx.h>

#include <Windows.h>

// Simple little namespace for text-only clipboard access
namespace NTextClipboard
{

 // Returns true is the data in the clipboard is text, otherwise returns false 
 bool IsText() 
 {
 	if (OpenClipboard (NULL))
 	{
 		UINT Format = 0;
 		while ((Format = ::EnumClipboardFormats (Format)) != 0)
 				if (Format == CF_TEXT)
 						break;
 					else;
 			if (!::CloseClipboard ()) return false;
 			return (Format == CF_TEXT);
		}
	 	else
			return false;
 }

 // Retrieves the text in the clipboard
 // If the clipboard is empty or the data in the clipboard is not text, sets the string to a blank string
 // returns true if the data in the clipboard was text and it was successfully copied, otherwise false
 bool GetClipboardText(CString & Str) 
 {
 	if (OpenClipboard (NULL))
 	{
 		HGLOBAL hMem = GetClipboardData(CF_TEXT);
			if (!hMem) return false;
 	 char * Ptr = (char *) GlobalLock (hMem);
 		Str = Ptr;
			if ( !GlobalUnlock (hMem) ) return false;
 		if (! ::CloseClipboard () ) return false;
			return true;

 	}
 		else
 			return false;
 }

 

 // Empties the clipboard. Returns true if successful, otherwise false
 bool Empty()
	{
		return !!::EmptyClipboard();
	}

 // Sets the clipboard text to the specified string
 // returns true if successful, false otherwise
 bool SetClipboardText(const CString & Str) 
 {
 	if (OpenClipboard (NULL))
 	{
 		//char Buffer [] = "Test String One";
 		Empty();
 		HGLOBAL hMem = ::GlobalAlloc (GMEM_SHARE, (Str.GetLength() + 1) * sizeof(TCHAR));
 		if (!hMem) return false;
 		LPTSTR Ptr = (LPTSTR) GlobalLock (hMem);
		_tcscpy(Ptr, Str);
 		if ( !GlobalUnlock (hMem) ) return false;
		::SetClipboardData ((sizeof(TCHAR) > 1 ? CF_UNICODETEXT : CF_TEXT), hMem);
 		if (!::CloseClipboard ()) return false;
			return true;
 	}
 		else
 			return false;
 }

};
