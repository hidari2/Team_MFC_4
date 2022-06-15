// MonsterTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MonsterTool.h"
#include "afxdialogex.h"

#include "FileInfo.h"
#include "MainFrm.h"
#include "ToolView.h"

// CMonsterTool ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CMonsterTool, CDialogEx)

CMonsterTool::CMonsterTool(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MONSTERTOOL, pParent)
{

}

CMonsterTool::~CMonsterTool()
{
}

void CMonsterTool::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
}


BEGIN_MESSAGE_MAP(CMonsterTool, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON2, &CMonsterTool::OnBringImage)
	ON_LBN_SELCHANGE(IDC_LIST2, &CMonsterTool::OnListBox)
	ON_BN_CLICKED(IDC_BUTTON1, &CMonsterTool::OnSave)
END_MESSAGE_MAP()


// CMonsterTool �޽��� ó�����Դϴ�.


void CMonsterTool::OnBringImage()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	UpdateData(TRUE);


	TCHAR		szFilePath[MAX_PATH] = L"C:/Users\qoxmf\Desktop/������ 2��/Texture/StageTerrain\Tile";
	TCHAR		szFileName[MAX_STR] = L"";

	

	int			iFileCnt = 3;

	for (int i = 0; i < iFileCnt; ++i)
	{

		CString	strRelative;

		switch (i)
		{
		case 0:
			strRelative.Format(_T("../Texture/Stage/Monster/Monster2/Dir_B/%d.png"), 0);
			break;
		case 1:
			strRelative.Format(_T("../Texture/Stage/Monster/Monster1/Dir_B/%d.png"), 1);
			break;
		case 2:
			strRelative.Format(_T("../Texture/Stage/Monster/Boss/Dir_B/%d.png"), 2);
			break;
		default:
			break;
		}

		//PathFindFileName : ��� �� ���� �̸��� ����� ��� �����ϴ� �Լ�
		CString	strFileName = PathFindFileName(strRelative);

		lstrcpy(szFileName, strFileName.GetString());

		// ������ Ȯ���� ���� �����ϴ� �Լ�
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto	iter = m_MonsterPngImg.find(strFileName);

		if (iter == m_MonsterPngImg.end())
		{
			CImage*		pPngImg = new CImage;

			pPngImg->Load(strRelative);	// �ش� ����� �̹��� �ε�

			m_MonsterPngImg.insert({ strFileName, pPngImg });
			m_ListBox.AddString(szFileName);
		}
	}

	//Horizontal_Scroll();

	UpdateData(FALSE);


}


void CMonsterTool::OnListBox()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	UpdateData(TRUE);


	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());

	CToolView*		pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));

	pView->create_monster = true;
	pView->create_tile = false;

	CString		strSelectName;

	int iSelect = m_ListBox.GetCurSel();

	m_ListBox.GetText(iSelect, strSelectName);

	auto	iter = m_MonsterPngImg.find(strSelectName);

	if (iter == m_MonsterPngImg.end())
		return;

	m_Picture.SetBitmap(*(iter->second));

	int i = 0;

	for (; i < strSelectName.GetLength(); ++i)
	{
		// isdigit : �Ű� ������ �Ѱܹ��� ���� ���ڰ� ���� ������ �������� �ƴϸ� ���� ������ �������� �Ǻ��ϴ� �Լ�
		//		     ����, ���� ������ ���ڶ�� �Ǹ�Ǹ� 0�� �ƴ� ���� ��ȯ�Ѵ�.
		if (0 != isdigit(strSelectName[i]))
			break;
	}


	//Delete(index, count) : �ε��� ��ġ�κ��� ī��Ʈ��ŭ ���ڸ� �����ϴ� �Լ�
	strSelectName.Delete(0, i);

	pView->Monsterid = _tstoi(strSelectName);

	UpdateData(FALSE);
}


void CMonsterTool::OnSave()
{
	
}
