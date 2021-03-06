#pragma once
#include "afxwin.h"


// CMapTool 대화 상자입니다.

class CMapTool : public CDialog
{
	DECLARE_DYNAMIC(CMapTool)

public:
	CMapTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMapTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAPTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

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

	//CImage : jpeg, gif, bmp, png 형식을 지원하	
	CStatic m_Picture;
	
	// value
	int		m_iDrawID;
	map<CString, CImage*>			m_MapPngImg;
	afx_msg void OnCbnSelchangeCombo1();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedBack1();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
};
