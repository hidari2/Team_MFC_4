#pragma once

#include "Include.h"

class CFileInfo
{
public:
	CFileInfo();
	~CFileInfo();

public:
	static CString		ConvertRelativePath(CString strFullPath);
	
	// ������ ��� ������ �����ϴ� �Լ�
	static	void		DirInfoExtraction(const wstring& wstrPath, list<IMGPATH*>& rPathList);

	// ���� ���� ���� ���� ��ȯ�ϴ� �Լ�
	static  int			DirFileCount(const wstring& wstrPath);

};

