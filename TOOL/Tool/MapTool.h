#pragma once
#include "afxwin.h"


// CMapTool ��ȭ �����Դϴ�.

class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMapTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnListBox();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnSaveData();
	afx_msg void OnBringImage();

public:
	void		Horizontal_Scroll(void);

public:
	// control
	CComboBox TileCombo;

	CListBox m_ListBox;

	//CImage : jpeg, gif, bmp, png ������ ������	
	CStatic m_Picture;
	
	// value
	int		m_iDrawID;
	map<CString, CImage*>			m_MapPngImg;
	afx_msg void OnCbnSelchangeCombo1();
	virtual BOOL OnInitDialog();
};
