#pragma once

#include "UnitTool.h"
#include "MapTool.h"
#include "MonsterTool.h"
#include "MySheet.h"
#include "PathFind.h"

// CMyForm �� ���Դϴ�.

class CMyForm : public CFormView
{
	DECLARE_DYNCREATE(CMyForm)

protected:
	CMyForm();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~CMyForm();

public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYFORM };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	DECLARE_MESSAGE_MAP()

public:
	CFont		m_Font;

	CUnitTool	 m_UnitTool;
	CMapTool	 m_MapTool;
	CMonsterTool m_MonsterTool;
	CMySheet	 m_MySheet;
	CPathFind	 m_PathFind;


public:
	virtual void OnInitialUpdate();

	afx_msg void OnUnitTool();
	afx_msg void OnMapTool();
	afx_msg void OnProperty();
	afx_msg void OnPathFind();
	afx_msg void OnMonstertool();
};

