// FileAttributesFilter.cpp: implementation of the CFileAttributesFilter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "duff.h"
#include "FilterFileAttributes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
#include "DuplicateFileFind.h"

extern CDuplicateFileFind g_DupeFileFind;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFileAttributesFilter::CFileAttributesFilter()
{
 m_pForm = &m_FileAttributesFilterForm;
	m_uiFormID = IDD_FILE_ATTRIBUTES_FILTER_FORM;
	m_sName = "Attributes";
	m_sDescription = "Process only files with or without certain file attributes";

}

CFileAttributesFilter::~CFileAttributesFilter()
{

}

int CFileAttributesFilter::FilterDuplicateList( CList<CFileInfo*,CFileInfo*> & FileList)
{
// int i;
 int Count = 0;
	int Iteration = 0;
	POSITION xPos;

	// update status and log
 g_DupeFileFind.m_DuffStatus.Lock();
 g_DupeFileFind.m_DuffStatus.CurrentTaskInfo = m_sName;
 g_DupeFileFind.m_DuffStatus.SubProgress2.Min = 0;
 g_DupeFileFind.m_DuffStatus.SubProgress2.Max = FileList.GetCount();
	g_DupeFileFind.m_DuffStatus.Unlock();
 //

	if ( m_IncludeReadOnly   != BST_INDETERMINATE ||
      m_IncludeHidden     != BST_INDETERMINATE ||
						m_IncludeSystem     != BST_INDETERMINATE ||
      m_IncludeCompressed != BST_INDETERMINATE ||
      m_IncludeArchived   != BST_INDETERMINATE ||
						m_IncludeEncrypted  != BST_INDETERMINATE ||    
						m_IncludeTemporary  != BST_INDETERMINATE    )
	{

		xPos = FileList.GetHeadPosition();

		//for (i = 0; i < FileList.GetCount(); i++)
		while (xPos)
		{

			// remove files that do not conform to file attribute specifications
			if (
				   ( (m_IncludeReadOnly   != BST_INDETERMINATE) && ( (m_IncludeReadOnly   == BST_UNCHECKED) == ( (FileList.GetAt(xPos)->Attributes & FILE_ATTRIBUTE_READONLY   ) != 0) ) ) || 
							(	(m_IncludeHidden     != BST_INDETERMINATE) && ( (m_IncludeHidden     == BST_UNCHECKED) == ( (FileList.GetAt(xPos)->Attributes & FILE_ATTRIBUTE_HIDDEN     ) != 0) ) ) || 
							(	(m_IncludeSystem     != BST_INDETERMINATE) && ( (m_IncludeSystem     == BST_UNCHECKED) == ( (FileList.GetAt(xPos)->Attributes & FILE_ATTRIBUTE_SYSTEM     ) != 0) ) ) || 
							(	(m_IncludeCompressed != BST_INDETERMINATE) && ( (m_IncludeCompressed == BST_UNCHECKED) == ( (FileList.GetAt(xPos)->Attributes & FILE_ATTRIBUTE_COMPRESSED ) != 0) ) ) || 
							(	(m_IncludeArchived   != BST_INDETERMINATE) && ( (m_IncludeArchived   == BST_UNCHECKED) == ( (FileList.GetAt(xPos)->Attributes & FILE_ATTRIBUTE_ARCHIVE    ) != 0) ) ) ||
							(	(m_IncludeEncrypted  != BST_INDETERMINATE) && ( (m_IncludeEncrypted  == BST_UNCHECKED) == ( (FileList.GetAt(xPos)->Attributes & FILE_ATTRIBUTE_ENCRYPTED  ) != 0) ) ) ||
							(	(m_IncludeTemporary  != BST_INDETERMINATE) && ( (m_IncludeTemporary  == BST_UNCHECKED) == ( (FileList.GetAt(xPos)->Attributes & FILE_ATTRIBUTE_TEMPORARY  ) != 0) ) ) 
						) 
			{
				//FileList.ElementAt(i)->Unaccessible = true;
				POSITION Pos2 = xPos;
				FileList.GetNext(Pos2);
				delete FileList.GetAt(xPos);
				FileList.RemoveAt(xPos);
				//i--;
				xPos = Pos2;
				Count++;	
			}
			else
			{
				FileList.GetNext(xPos);
			}

			Iteration++;

			// update status and log
			if (g_DupeFileFind.m_DuffStatus.LockIfUnlocked() )
			{
				g_DupeFileFind.m_DuffStatus.SubProgress2.Pos = Iteration;
				g_DupeFileFind.m_DuffStatus.Unlock();
			}
			//

			//FileList.GetNext(xPos);
		}

	}
 return Count;
}


bool CFileAttributesFilter::UpdateData(bool /*SaveAndValidate*/)
{
	m_IncludeReadOnly   = m_FileAttributesFilterForm.m_AttributesList.GetCheck(DIR_ATTRIBUTE_READONLY);
	m_IncludeHidden     = m_FileAttributesFilterForm.m_AttributesList.GetCheck(DIR_ATTRIBUTE_HIDDEN);
	m_IncludeSystem     = m_FileAttributesFilterForm.m_AttributesList.GetCheck(DIR_ATTRIBUTE_SYSTEM);
	m_IncludeCompressed = m_FileAttributesFilterForm.m_AttributesList.GetCheck(DIR_ATTRIBUTE_COMPRESSED);
	m_IncludeArchived   = m_FileAttributesFilterForm.m_AttributesList.GetCheck(DIR_ATTRIBUTE_ARCHIVED);
	m_IncludeEncrypted  = m_FileAttributesFilterForm.m_AttributesList.GetCheck(DIR_ATTRIBUTE_ENCRYPTED);
 m_IncludeTemporary  = m_FileAttributesFilterForm.m_AttributesList.GetCheck(DIR_ATTRIBUTE_TEMPORARY);
 return true;
}

CString CFileAttributesFilter::GetSettingString() 
{
	UpdateData(true);

 CString Temp;
	bool ReadOnlySetting   = false;
	bool HiddenSetting     = false;
	bool SystemSetting     = false;
 bool ArchivedSetting   = false;
 bool CompressedSetting = false;
 bool EncryptedSetting  = false;

 switch ( m_IncludeReadOnly )
	{
		case BST_CHECKED:
   Temp += "are marked as read-only";
			ReadOnlySetting = true;
			break;
		case BST_UNCHECKED:
   Temp += "are not marked as read-only";
			ReadOnlySetting = true;
			break;
		case BST_INDETERMINATE:
   ReadOnlySetting = false;
			break;
	}


	switch ( m_IncludeHidden )
	{
		case BST_CHECKED:
			if ( ReadOnlySetting ) Temp += " and ";
   Temp += "are marked as hidden";
			HiddenSetting = true;
			break;
		case BST_UNCHECKED:
 		if ( ReadOnlySetting ) Temp += " and ";
   Temp += "are not marked as hidden";
			HiddenSetting = true;
			break;
		case BST_INDETERMINATE:
   HiddenSetting = false;
			break;
	}


	switch ( m_IncludeSystem )
	{
		case BST_CHECKED:
			if ( ReadOnlySetting || HiddenSetting ) Temp += " and ";
   Temp += "are marked as system";
			SystemSetting = true;
			break;
		case BST_UNCHECKED:
 		if ( ReadOnlySetting || HiddenSetting ) Temp += " and ";
   Temp += "are not marked as system";
			SystemSetting = true;
			break;
		case BST_INDETERMINATE:
   SystemSetting = false;
			break;
	}



	switch ( m_IncludeArchived )
	{
		case BST_CHECKED:
			if ( ReadOnlySetting || HiddenSetting || SystemSetting ) Temp += " and ";
   Temp += "are marked as archived";
			ArchivedSetting = true;
			break;
		case BST_UNCHECKED:
 		if ( ReadOnlySetting || HiddenSetting || SystemSetting ) Temp += " and ";
   Temp += "are not marked as archived";
			ArchivedSetting = true;
			break;
		case BST_INDETERMINATE:
   ArchivedSetting = false;
			break;
	}
	
	switch ( m_IncludeCompressed )
	{
		case BST_CHECKED:
			if ( ReadOnlySetting || HiddenSetting || SystemSetting || ArchivedSetting ) Temp += " and ";
   Temp += "are compressed";
			CompressedSetting = true;
			break;
		case BST_UNCHECKED:
 		if ( ReadOnlySetting || HiddenSetting || SystemSetting || ArchivedSetting ) Temp += " and ";
   Temp += "are not compressed";
			CompressedSetting = true;
			break;
		case BST_INDETERMINATE:
   CompressedSetting = false;
			break;
	}


	switch ( m_IncludeEncrypted )
	{
		case BST_CHECKED:
			if ( ReadOnlySetting || HiddenSetting || SystemSetting || ArchivedSetting || CompressedSetting) Temp += " and ";
   Temp += "are encrypted";
			EncryptedSetting = true;
			break;
		case BST_UNCHECKED:
 		if ( ReadOnlySetting || HiddenSetting || SystemSetting || ArchivedSetting || EncryptedSetting ) Temp += " and ";
   Temp += "are not encrypted";
			EncryptedSetting = true;
			break;
		case BST_INDETERMINATE:
   EncryptedSetting = false;
			break;
	}

 /*if ( ReadOnlySetting || HiddenSetting || SystemSetting || ArchivedSetting || CompressedSetting )
	{
		
	}
*/
	return Temp;
	
}
