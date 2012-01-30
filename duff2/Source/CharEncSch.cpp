#include "stdafx.h"

#include "CharEncSch.h"






CCharacterEncodingScheme CharEncSchemes[4] = 
{
	CCharacterEncodingScheme( _T("ANSI")                             , NULL               , 0, 1 ),
	CCharacterEncodingScheme( _T("UTF-8")                            , _T("\xEF\xBB\xBF") , 3, 1 ),
	CCharacterEncodingScheme( _T("Unicode Little Endian (UTF-16LE)") , _T("\xFF\xFE")     , 2, 2 ),
	CCharacterEncodingScheme( _T("Unicode Big Endian (UTF-16BE)")    , _T("\xFE\xFE")     , 2, 2 )
};
