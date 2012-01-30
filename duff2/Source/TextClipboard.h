#ifndef TEXTCLIPBOARD_NAMESPACE_H
#define TEXTCLIPBOARD_NAMESPACE_H

// Simple little namespace for text-only clipboard access
namespace NTextClipboard
{

 // Returns true is the data in the clipboard is text, otherwise returns false 
 bool IsText();

 // Retrieves the text in the clipboard
 // If the clipboard is empty or the data in the clipboard is not text, sets the string to a blank string
 // returns true if the data in the clipboard was text and it was successfully copied, otherwise false
 bool GetClipboardText(CString & Str);
 

 // Empties the clipboard. Returns true if successful, otherwise false
 bool Empty();

 // Sets the clipboard text to the specified string
 // returns true if successful, false otherwise
 bool SetClipboardText(const CString & Str);
};


#endif
