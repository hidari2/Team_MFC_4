
#pragma once


// CMonsterTool ��ȭ �����Դϴ�.

class CMonsterTool : public CDialogEx
{
	DECLARE_DYNAMIC(CMonsterTool)

public:
	CMonsterTool(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CMonsterTool();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MONSTERTOOL };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBringImage();
	afx_msg void OnListBox();

public:
	// control
	CListBox m_ListBox;

	//CImage : jpeg, gif, bmp, png ������ ������	
	CStatic m_Picture;

	// value
	map<CString, CImage*>			m_MonsterPngImg;
	afx_msg void OnSave();
};
