#ifndef UTIL_H_12_Mar_2002__12_12_05
#define UTIL_H_12_Mar_2002__12_12_05

//#include <afx.h>


inline CString StringFromResource(UINT ID)
{
	CString S;
	S.LoadString(ID);
	return S;
}


const LPTSTR  GetErrorStr( DWORD ID = GetLastError() );

inline const LPTSTR  GetErrorStr( DWORD ID)
{
	LPVOID lpMsgBuf;
 FormatMessage( 
    FORMAT_MESSAGE_ALLOCATE_BUFFER | 
    FORMAT_MESSAGE_FROM_SYSTEM | 
    FORMAT_MESSAGE_IGNORE_INSERTS,
    NULL,
    ID,
    0, // Default language
    (LPTSTR) &lpMsgBuf,
    0,
    NULL 
);

return (const LPTSTR )lpMsgBuf;
}


inline bool isinteger(const CString & Str)
{
 bool IsInt = true;
 int i = 0;
	while ( IsInt && i < Str.GetLength() )
	{
  if ( ! _istdigit(Str.GetAt(i)) ) IsInt = false;
		i++;
	}
	return IsInt;
}



#include <sys/timeb.h>

// Generates random integer between MinVal and MaxVal
// It will re-seed the rand function if 'Seed' parameter is true
inline unsigned int RandomInt(unsigned int MinVal, unsigned int MaxVal, bool Seed = false)
{
	struct _timeb tstruct;
 _ftime(&tstruct);

	if (MaxVal < MinVal) return 0;
	if ( Seed ) srand( unsigned int(time(NULL) + tstruct.millitm) ); 

	return ( ( rand() % (MaxVal-MinVal+1) )  + MinVal );
}




// get approximation of a ulonglong division
inline double ulonglongdivide(ULONGLONG dividend, ULONGLONG divisor)
{
	// make sure the numbers will fit into a UINT
 while ( divisor > (ULONGLONG)UINT_MAX ) 
	{
		dividend = dividend / 2;
		divisor = divisor / 2;
	}

	// return the ratio
	return (double)(UINT)dividend / (double)(UINT)divisor;
}


static TCHAR sDecimalSeparator = _T('.'); // dot by default
static TCHAR sThousantSeparator = _T(','); // comma by default


// call this to format an 64-bit unsigned number to a string
inline LPTSTR  __stdcall ulonglong2str( LPTSTR szBuffer, ULONGLONG lValue /*, int iShowSign = 0*/ )
{
  TCHAR *p;               // pointer to traverse string
  TCHAR *firstdig;        // pointer to first digit
  TCHAR temp;             // temp char
  ULONG digval;       // value of digit
  ULONGLONG val;

  p = szBuffer;

 // if (lValue < 0 ) {
 //    // negative, so output '-' and negate
 //    if (iShowSign < 2)
 //      	*p++ = '-';
 //    val = (unsigned long)(-(long)lValue); // make it positive!!
 // } else
 // {
 //    if  ( iShowSign == 1 )
 //      *p++ = '+';
     val = lValue;
 // }

  firstdig = p;     // save pointer to first digit

  int iDecimalPos = 0;

  do {
     iDecimalPos ++;
     if (iDecimalPos != 4)
     {
       digval = (ULONG) (val % 10);
       val /= 10;                    // get next digit
       *p = (TCHAR) (digval + _T('0') ); // and store the digit
							p += sizeof(TCHAR);
     } else
     {
       *p = sThousantSeparator;
							p += sizeof(TCHAR);
       iDecimalPos = 0;
     }
  } while (val > 0);

  //  We now have the digit of the number in the buffer, 
  // but in reverse order.  Thus we reverse them now.

  // Check if we have to add signs
//  if ( iShowSign == 2 )
//  {
//     if ( lValue < 0 )
//       *p++ = '-';
//     else
//       *p++ = '+';
//     *p-- = '\0'; // terminate string; p points to last digit
//     *p--; // go back one more step to leave the sign sign intact!
//  } else
//  {
     *p = _T('\0'); // terminate string; p points to last digit
					p -= sizeof(TCHAR);
//  }

  do {
      temp = *p;
      *p = *firstdig;
      *firstdig = temp;   // swap *p and *firstdig
      p -= sizeof(TCHAR);
      ++firstdig;
  } while (firstdig < p); // repeat until halfway

  return szBuffer;
}







// find a substring in a string without regard to case
inline TCHAR* _tcsistr(const TCHAR *string, const TCHAR *substring)
{
	unsigned int stringlen    = _tcsclen (string);
	unsigned int substringlen = _tcsclen (substring);
 int notfound = 1;
 unsigned int i;

	if ( stringlen >= substringlen )
	{
  i = 0;
  while ( (i <= stringlen - substringlen) && notfound )
		{
			notfound = _tcsnicmp( substring, string+ (sizeof(TCHAR) * i++), substringlen );
		}
		return notfound ? NULL : (TCHAR*)string+ (sizeof(TCHAR) * i-1);
	}
	else
	{
		return NULL;
	}
}










#pragma warning (disable:4201) // Disable 'warning C4201: nonstandard extension used : nameless struct/union'

#include <mmsystem.h>
inline void PlaySoundFile(const CString &FN)
{
	if ( FN != "") PlaySound( FN , NULL ,SND_FILENAME | SND_ASYNC | SND_NODEFAULT );
}

inline void PlaySoundFileSync(const CString &FN)
{
 if ( FN != "") PlaySound( FN , NULL ,SND_FILENAME | SND_SYNC  | SND_NODEFAULT );
}













#endif