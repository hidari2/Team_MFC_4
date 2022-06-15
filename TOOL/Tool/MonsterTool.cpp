// MonsterTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MonsterTool.h"
#include "afxdialogex.h"

#include "FileInfo.h"
#include "MainFrm.h"
#include "ToolView.h"

// CMonsterTool 대화 상자입니다.

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


// CMonsterTool 메시지 처리기입니다.


void CMonsterTool::OnBringImage()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UpdateData(TRUE);


	TCHAR		szFilePath[MAX_PATH] = L"C:/Users\qoxmf\Desktop/툴제작 2일/Texture/StageTerrain\Tile";
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

		//PathFindFileName : 경로 중 파일 이름만 남기고 모두 제거하는 함수
		CString	strFileName = PathFindFileName(strRelative);

		lstrcpy(szFileName, strFileName.GetString());

		// 파일의 확장자 명을 제거하는 함수
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto	iter = m_MonsterPngImg.find(strFileName);

		if (iter == m_MonsterPngImg.end())
		{
			CImage*		pPngImg = new CImage;

			pPngImg->Load(strRelative);	// 해당 경로의 이미지 로드

			m_MonsterPngImg.insert({ strFileName, pPngImg });
			m_ListBox.AddString(szFileName);
		}
	}

	//Horizontal_Scroll();

	UpdateData(FALSE);


}


void CMonsterTool::OnListBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
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
		// isdigit : 매개 변수로 넘겨받은 단일 문자가 숫자 형태의 문자인지 아니면 글자 형태의 문자인지 판별하는 함수
		//		     만약, 숫자 형태의 문자라고 판명되면 0이 아닌 값을 반환한다.
		if (0 != isdigit(strSelectName[i]))
			break;
	}


	//Delete(index, count) : 인덱스 위치로부터 카운트만큼 문자를 삭제하는 함수
	strSelectName.Delete(0, i);

	pView->Monsterid = _tstoi(strSelectName);

	UpdateData(FALSE);
}


void CMonsterTool::OnSave()
{
	
}
