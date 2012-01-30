#ifndef CHARACTER_ENCODING_SCHEMES_H_
#define CHARACTER_ENCODING_SCHEMES_H_


#include <afxtempl.h>

struct CCharacterEncodingScheme
{
	CCharacterEncodingScheme();
 CCharacterEncodingScheme(TCHAR*, TCHAR*, BYTE, BYTE);
	TCHAR *Name;
	TCHAR *Header;
	BYTE   HeaderLength;
	BYTE   CharacterLength;

 static CArray<CCharacterEncodingScheme *,CCharacterEncodingScheme *> m_pSchemes;
};

inline CCharacterEncodingScheme::CCharacterEncodingScheme()
{
	m_pSchemes.Add(this);
}


inline CCharacterEncodingScheme::CCharacterEncodingScheme(TCHAR *name, TCHAR *header, BYTE headerlength, BYTE characterlength)
{
 Name = name;
	Header = header;
	HeaderLength = headerlength;
	CharacterLength = characterlength;
}

/*
 int sCharacterEncodingScheme::GetType(BYTE* pByte)
{
 for (int i = 1; i < Count; i++)
	{
  if ( memcpy(pByte,CharEncSchemes[i].Header, CharEncSchemes[i].HeaderLength) == 0)
			return i;

	}
	return -1;
}

UINT sCharacterEncodingScheme::Count = 0;

 */
	
 
 



#endif