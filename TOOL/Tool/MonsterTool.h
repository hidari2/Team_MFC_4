
#pragma once


// CMonsterTool 대화 상자입니다.

class CMonsterTool : public CDialogEx
{
	DECLARE_DYNAMIC(CMonsterTool)

public:
	CMonsterTool(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CMonsterTool();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONSTERTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBringImage();
	afx_msg void OnListBox();

public:
	// control
	CListBox m_ListBox;

	//CImage : jpeg, gif, bmp, png 형식을 지원하	
	CStatic m_Picture;

	// value
	map<CString, CImage*>			m_MonsterPngImg;
	afx_msg void OnSave();
};
