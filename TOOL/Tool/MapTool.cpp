// MapTool.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "afxdialogex.h"

#include "FileInfo.h"
#include "MainFrm.h"
#include "ToolView.h"


// CMapTool 대화 상자입니다.

IMPLEMENT_DYNAMIC(CMapTool, CDialog)

CMapTool::CMapTool(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_MAPTOOL, pParent), m_iDrawID(123)
{

}

CMapTool::~CMapTool()
{
	for_each(m_MapPngImg.begin(), m_MapPngImg.end(), [](auto& Pair) 
	{
		Pair.second->Destroy();
		Safe_Delete<CImage*>(Pair.second);
	});

	m_MapPngImg.clear();
}

void CMapTool::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListBox);
	DDX_Control(pDX, IDC_PICTURE, m_Picture);
	DDX_Control(pDX, IDC_COMBO1, TileCombo);

}


BEGIN_MESSAGE_MAP(CMapTool, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST1, &CMapTool::OnListBox)
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CMapTool::OnSaveData)
	ON_BN_CLICKED(IDC_BUTTON2, &CMapTool::OnBringImage)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CMapTool::OnCbnSelchangeCombo1)
END_MESSAGE_MAP()


// CMapTool 메시지 처리기입니다.


void CMapTool::OnListBox()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());

	CToolView*		pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));

	pView->create_monster = false;
	pView->create_tile = true;

	CString		strSelectName;

	int iSelect = m_ListBox.GetCurSel();

	m_ListBox.GetText(iSelect, strSelectName);

	auto	iter = m_MapPngImg.find(strSelectName);

	if (iter == m_MapPngImg.end())
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

	// _tstoi : 문자를 정수형으로 변환하는 함수
	m_iDrawID = _tstoi(strSelectName);
	
	UpdateData(FALSE);
}


void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	UpdateData(TRUE);

	CDialog::OnDropFiles(hDropInfo);


	TCHAR		szFilePath[MAX_PATH] = L"";
	TCHAR		szFileName[MAX_STR] = L"";

	// DragQueryFile : 드롭된 파일의 정보를 얻어오는 함수(0번 인텍스에 해당하는 파일의 전체 경로를 얻어온다)
	// 두번째 인자가 0xffffffff(-1)로 지정하면 드롭된 파일의 개수를 반환

	int			iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

	for(int i = 0; i < iFileCnt; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);

		CString	strRelative = CFileInfo::ConvertRelativePath(szFilePath);

		//PathFindFileName : 경로 중 파일 이름만 남기고 모두 제거하는 함수
		CString	strFileName = PathFindFileName(strRelative);

		lstrcpy(szFileName, strFileName.GetString());

		// 파일의 확장자 명을 제거하는 함수
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto	iter = m_MapPngImg.find(strFileName);

		if (iter == m_MapPngImg.end())
		{
			CImage*		pPngImg = new CImage;

			pPngImg->Load(strRelative);	// 해당 경로의 이미지 로드

			m_MapPngImg.insert({ strFileName, pPngImg });
			m_ListBox.AddString(szFileName);
		}
	}
	
	Horizontal_Scroll();

	UpdateData(FALSE);
}

void CMapTool::Horizontal_Scroll(void)
{

	CString		strName;
	CSize		size;

	int		iWidth = 0;

	// 리스트 박스 또한 DC기반 출력이기 때문에 화면 DC를 얻어올 수 있다.
	CDC*		pDC = m_ListBox.GetDC();

	// GetCount : 리스트 박스에 있는 목록의 개수 반환
	for (int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		m_ListBox.GetText(i, strName);

		// 현재 문자열의 길이를 픽셀 단위로 변환
		size = pDC->GetTextExtent(strName);

		if (size.cx > iWidth)
			iWidth = size.cx;
	}

	m_ListBox.ReleaseDC(pDC);

	// GetHorizontalExtent : 리스트 박스가 가로로 스크롤 할 수 있는 최대 범위를 얻어오는 함수
	if (iWidth > m_ListBox.GetHorizontalExtent())
		m_ListBox.SetHorizontalExtent(iWidth);

}


void CMapTool::OnSaveData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFileDialog		Dlg(FALSE,
		L"dat",
		L"*.dat",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||",
		this);

	TCHAR	szPath[MAX_PATH] = L"";

	// 현재 프로젝트 경로를 얻어오는 함수
	GetCurrentDirectory(MAX_PATH, szPath);


	// 전체 경로에서 파일 이름만 잘라주는 함수, 만약 경로 상에 파일명이 없다면 제일 마지막 폴더명을 잘라낸다.
	PathRemoveFileSpec(szPath);

	// data 폴더명을 잘라낸 경로에 합성
	lstrcat(szPath, L"\\Data");

	// 대화상자를 열었을 때 보이는 기본 경로로 설정
	Dlg.m_ofn.lpstrInitialDir = szPath;


	if (IDOK == Dlg.DoModal())
	{
		// GetPathName : 선택된 경로를 반환
		CString		str = Dlg.GetPathName();

		// GetString 원시 문자열로 변환하는 함수
		const TCHAR* pGetPath = str.GetString();

		HANDLE		hFile = CreateFile(pGetPath, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);

		if (INVALID_HANDLE_VALUE == hFile)
			return;


		CMainFrame*		pMainFrm = dynamic_cast<CMainFrame*>(AfxGetApp()->GetMainWnd());

		CToolView*		pView = dynamic_cast<CToolView*>(pMainFrm->m_MainSplitter.GetPane(0, 1));

		CTerrain*		pTerrain = pView->Get_Terrain();

		vector<TILE*>& vecTile = pTerrain->Get_VecTile();
		
		DWORD	dwByte = 0;

		for (auto& iter : vecTile)
		{
			WriteFile(hFile, iter, sizeof(TILE), &dwByte, nullptr);
		}

		CloseHandle(hFile);
	}

}


void CMapTool::OnBringImage()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UpdateData(TRUE);


	TCHAR		szFilePath[MAX_PATH] = L"C:/Users\qoxmf\Desktop/툴제작 2일/Texture/StageTerrain\Tile";
	TCHAR		szFileName[MAX_STR] = L"";

	// DragQueryFile : 드롭된 파일의 정보를 얻어오는 함수(0번 인텍스에 해당하는 파일의 전체 경로를 얻어온다)
	// 두번째 인자가 0xffffffff(-1)로 지정하면 드롭된 파일의 개수를 반환

	//int			iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

	int			iFileCnt = 124;

	for (int i = 0; i < iFileCnt; ++i)
	{


		CString	strRelative;

		strRelative.Format(_T("../Texture/Stage/Terrain/Tile/Tile%d.png"), i);

		//PathFindFileName : 경로 중 파일 이름만 남기고 모두 제거하는 함수
		CString	strFileName = PathFindFileName(strRelative);

		lstrcpy(szFileName, strFileName.GetString());

		// 파일의 확장자 명을 제거하는 함수
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto	iter = m_MapPngImg.find(strFileName);

		if (iter == m_MapPngImg.end())
		{
			CImage*		pPngImg = new CImage;

			pPngImg->Load(strRelative);	// 해당 경로의 이미지 로드

			m_MapPngImg.insert({ strFileName, pPngImg });
			m_ListBox.AddString(szFileName);
		}
	}

	Horizontal_Scroll();

	UpdateData(FALSE);


}


void CMapTool::OnCbnSelchangeCombo1()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	UpdateData(TRUE);


	TCHAR		szFilePath[MAX_PATH] = L"";
	TCHAR		szFileName[MAX_STR] = L"";

	// DragQueryFile : 드롭된 파일의 정보를 얻어오는 함수(0번 인텍스에 해당하는 파일의 전체 경로를 얻어온다)
	// 두번째 인자가 0xffffffff(-1)로 지정하면 드롭된 파일의 개수를 반환

	//int			iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

	int iSel = TileCombo.GetCurSel();

	m_ListBox.ResetContent();

	if (iSel == 0)
	{
		for (int i = 0; i < 30; ++i)
		{
			//DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);
			//CString	strRelative = CFileInfo::ConvertRelativePath(szFilePath);
			CString	strRelative;
			strRelative.Format(_T("../Texture/Stage/Terrain/Tile/Tile%d.png"), i);
			//PathFindFileName : 경로 중 파일 이름만 남기고 모두 제거하는 함수
			CString	strFileName = PathFindFileName(strRelative);
			lstrcpy(szFileName, strFileName.GetString());
			// 파일의 확장자 명을 제거하는 함수
			PathRemoveExtension(szFileName);
			strFileName = szFileName;
			auto	iter = m_MapPngImg.find(strFileName);


				CImage*		pPngImg = new CImage;
				pPngImg->Load(strRelative);	// 해당 경로의 이미지 로드
				m_ListBox.AddString(szFileName);
				m_MapPngImg.insert({ strFileName, pPngImg });
		}

	}
	else if (iSel == 1)
	{
		for (int i = 30; i <64; ++i)
		{
			CString	strRelative;
			strRelative.Format(_T("../Texture/Stage/Terrain/Tile/Tile%d.png"), i);
			CString	strFileName = PathFindFileName(strRelative);
			lstrcpy(szFileName, strFileName.GetString());
			// 파일의 확장자 명을 제거하는 함수
			PathRemoveExtension(szFileName);
			strFileName = szFileName;
			auto	iter = m_MapPngImg.find(strFileName);

				CImage*		pPngImg = new CImage;
				pPngImg->Load(strRelative);	// 해당 경로의 이미지 로드
				m_MapPngImg.insert({ strFileName, pPngImg });
				m_ListBox.AddString(szFileName);

		}
	}
	else if (iSel == 2)
	{
		for (int i = 63; i <104; ++i)
		{
			CString	strRelative;
			strRelative.Format(_T("../Texture/Stage/Terrain/Tile/Tile%d.png"), i);
			//PathFindFileName : 경로 중 파일 이름만 남기고 모두 제거하는 함수
			CString	strFileName = PathFindFileName(strRelative);
			lstrcpy(szFileName, strFileName.GetString());
			// 파일의 확장자 명을 제거하는 함수
			PathRemoveExtension(szFileName);
			strFileName = szFileName;
			auto	iter = m_MapPngImg.find(strFileName);

				CImage*		pPngImg = new CImage;
				pPngImg->Load(strRelative);	// 해당 경로의 이미지 로드
				m_MapPngImg.insert({ strFileName, pPngImg });
				m_ListBox.AddString(szFileName);

		}
	}
	else if (iSel == 3)
	{
		for (int i = 104; i <123; ++i)
		{
			//DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);
			//CString	strRelative = CFileInfo::ConvertRelativePath(szFilePath);
			CString	strRelative;
			strRelative.Format(_T("../Texture/Stage/Terrain/Tile/Tile%d.png"), i);
			//PathFindFileName : 경로 중 파일 이름만 남기고 모두 제거하는 함수
			CString	strFileName = PathFindFileName(strRelative);
			lstrcpy(szFileName, strFileName.GetString());
			// 파일의 확장자 명을 제거하는 함수
			PathRemoveExtension(szFileName);
			strFileName = szFileName;
			auto	iter = m_MapPngImg.find(strFileName);

				CImage*		pPngImg = new CImage;
				pPngImg->Load(strRelative);	// 해당 경로의 이미지 로드
				m_MapPngImg.insert({ strFileName, pPngImg });
				m_ListBox.AddString(szFileName);
			
		}
	}
	else
	{

	}
	Horizontal_Scroll();
	UpdateData(FALSE);

}


BOOL CMapTool::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	SetWindowPos(NULL, 1200, 0, 0, 0, SWP_NOSIZE);

	TileCombo.AddString(TEXT("01.초원타일"));
	TileCombo.AddString(TEXT("02.목재타일"));
	TileCombo.AddString(TEXT("03.돌타일"));
	TileCombo.AddString(TEXT("04.판자타일"));
	TileCombo.AddString(TEXT("[타일종류선택]"));
	TileCombo.SetCurSel(4);
	return FALSE;  // return TRUE unless you set the focus to a control
				   // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
