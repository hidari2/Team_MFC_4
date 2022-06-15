// MapTool.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MapTool.h"
#include "afxdialogex.h"

#include "FileInfo.h"
#include "MainFrm.h"
#include "ToolView.h"


// CMapTool ��ȭ �����Դϴ�.

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


// CMapTool �޽��� ó�����Դϴ�.


void CMapTool::OnListBox()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
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
		// isdigit : �Ű� ������ �Ѱܹ��� ���� ���ڰ� ���� ������ �������� �ƴϸ� ���� ������ �������� �Ǻ��ϴ� �Լ�
		//		     ����, ���� ������ ���ڶ�� �Ǹ�Ǹ� 0�� �ƴ� ���� ��ȯ�Ѵ�.
		if (0 != isdigit(strSelectName[i]))
			break;
	}


	//Delete(index, count) : �ε��� ��ġ�κ��� ī��Ʈ��ŭ ���ڸ� �����ϴ� �Լ�
	strSelectName.Delete(0, i);

	// _tstoi : ���ڸ� ���������� ��ȯ�ϴ� �Լ�
	m_iDrawID = _tstoi(strSelectName);
	
	UpdateData(FALSE);
}


void CMapTool::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	UpdateData(TRUE);

	CDialog::OnDropFiles(hDropInfo);


	TCHAR		szFilePath[MAX_PATH] = L"";
	TCHAR		szFileName[MAX_STR] = L"";

	// DragQueryFile : ��ӵ� ������ ������ ������ �Լ�(0�� ���ؽ��� �ش��ϴ� ������ ��ü ��θ� ���´�)
	// �ι�° ���ڰ� 0xffffffff(-1)�� �����ϸ� ��ӵ� ������ ������ ��ȯ

	int			iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

	for(int i = 0; i < iFileCnt; ++i)
	{
		DragQueryFile(hDropInfo, i, szFilePath, MAX_PATH);

		CString	strRelative = CFileInfo::ConvertRelativePath(szFilePath);

		//PathFindFileName : ��� �� ���� �̸��� ����� ��� �����ϴ� �Լ�
		CString	strFileName = PathFindFileName(strRelative);

		lstrcpy(szFileName, strFileName.GetString());

		// ������ Ȯ���� ���� �����ϴ� �Լ�
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto	iter = m_MapPngImg.find(strFileName);

		if (iter == m_MapPngImg.end())
		{
			CImage*		pPngImg = new CImage;

			pPngImg->Load(strRelative);	// �ش� ����� �̹��� �ε�

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

	// ����Ʈ �ڽ� ���� DC��� ����̱� ������ ȭ�� DC�� ���� �� �ִ�.
	CDC*		pDC = m_ListBox.GetDC();

	// GetCount : ����Ʈ �ڽ��� �ִ� ����� ���� ��ȯ
	for (int i = 0; i < m_ListBox.GetCount(); ++i)
	{
		m_ListBox.GetText(i, strName);

		// ���� ���ڿ��� ���̸� �ȼ� ������ ��ȯ
		size = pDC->GetTextExtent(strName);

		if (size.cx > iWidth)
			iWidth = size.cx;
	}

	m_ListBox.ReleaseDC(pDC);

	// GetHorizontalExtent : ����Ʈ �ڽ��� ���η� ��ũ�� �� �� �ִ� �ִ� ������ ������ �Լ�
	if (iWidth > m_ListBox.GetHorizontalExtent())
		m_ListBox.SetHorizontalExtent(iWidth);

}


void CMapTool::OnSaveData()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CFileDialog		Dlg(FALSE,
		L"dat",
		L"*.dat",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"Data Files(*.dat)|*.dat||",
		this);

	TCHAR	szPath[MAX_PATH] = L"";

	// ���� ������Ʈ ��θ� ������ �Լ�
	GetCurrentDirectory(MAX_PATH, szPath);


	// ��ü ��ο��� ���� �̸��� �߶��ִ� �Լ�, ���� ��� �� ���ϸ��� ���ٸ� ���� ������ �������� �߶󳽴�.
	PathRemoveFileSpec(szPath);

	// data �������� �߶� ��ο� �ռ�
	lstrcat(szPath, L"\\Data");

	// ��ȭ���ڸ� ������ �� ���̴� �⺻ ��η� ����
	Dlg.m_ofn.lpstrInitialDir = szPath;


	if (IDOK == Dlg.DoModal())
	{
		// GetPathName : ���õ� ��θ� ��ȯ
		CString		str = Dlg.GetPathName();

		// GetString ���� ���ڿ��� ��ȯ�ϴ� �Լ�
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
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	UpdateData(TRUE);


	TCHAR		szFilePath[MAX_PATH] = L"C:/Users\qoxmf\Desktop/������ 2��/Texture/StageTerrain\Tile";
	TCHAR		szFileName[MAX_STR] = L"";

	// DragQueryFile : ��ӵ� ������ ������ ������ �Լ�(0�� ���ؽ��� �ش��ϴ� ������ ��ü ��θ� ���´�)
	// �ι�° ���ڰ� 0xffffffff(-1)�� �����ϸ� ��ӵ� ������ ������ ��ȯ

	//int			iFileCnt = DragQueryFile(hDropInfo, 0xffffffff, nullptr, 0);

	int			iFileCnt = 124;

	for (int i = 0; i < iFileCnt; ++i)
	{


		CString	strRelative;

		strRelative.Format(_T("../Texture/Stage/Terrain/Tile/Tile%d.png"), i);

		//PathFindFileName : ��� �� ���� �̸��� ����� ��� �����ϴ� �Լ�
		CString	strFileName = PathFindFileName(strRelative);

		lstrcpy(szFileName, strFileName.GetString());

		// ������ Ȯ���� ���� �����ϴ� �Լ�
		PathRemoveExtension(szFileName);

		strFileName = szFileName;

		auto	iter = m_MapPngImg.find(strFileName);

		if (iter == m_MapPngImg.end())
		{
			CImage*		pPngImg = new CImage;

			pPngImg->Load(strRelative);	// �ش� ����� �̹��� �ε�

			m_MapPngImg.insert({ strFileName, pPngImg });
			m_ListBox.AddString(szFileName);
		}
	}

	Horizontal_Scroll();

	UpdateData(FALSE);


}


void CMapTool::OnCbnSelchangeCombo1()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	UpdateData(TRUE);


	TCHAR		szFilePath[MAX_PATH] = L"";
	TCHAR		szFileName[MAX_STR] = L"";

	// DragQueryFile : ��ӵ� ������ ������ ������ �Լ�(0�� ���ؽ��� �ش��ϴ� ������ ��ü ��θ� ���´�)
	// �ι�° ���ڰ� 0xffffffff(-1)�� �����ϸ� ��ӵ� ������ ������ ��ȯ

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
			//PathFindFileName : ��� �� ���� �̸��� ����� ��� �����ϴ� �Լ�
			CString	strFileName = PathFindFileName(strRelative);
			lstrcpy(szFileName, strFileName.GetString());
			// ������ Ȯ���� ���� �����ϴ� �Լ�
			PathRemoveExtension(szFileName);
			strFileName = szFileName;
			auto	iter = m_MapPngImg.find(strFileName);


				CImage*		pPngImg = new CImage;
				pPngImg->Load(strRelative);	// �ش� ����� �̹��� �ε�
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
			// ������ Ȯ���� ���� �����ϴ� �Լ�
			PathRemoveExtension(szFileName);
			strFileName = szFileName;
			auto	iter = m_MapPngImg.find(strFileName);

				CImage*		pPngImg = new CImage;
				pPngImg->Load(strRelative);	// �ش� ����� �̹��� �ε�
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
			//PathFindFileName : ��� �� ���� �̸��� ����� ��� �����ϴ� �Լ�
			CString	strFileName = PathFindFileName(strRelative);
			lstrcpy(szFileName, strFileName.GetString());
			// ������ Ȯ���� ���� �����ϴ� �Լ�
			PathRemoveExtension(szFileName);
			strFileName = szFileName;
			auto	iter = m_MapPngImg.find(strFileName);

				CImage*		pPngImg = new CImage;
				pPngImg->Load(strRelative);	// �ش� ����� �̹��� �ε�
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
			//PathFindFileName : ��� �� ���� �̸��� ����� ��� �����ϴ� �Լ�
			CString	strFileName = PathFindFileName(strRelative);
			lstrcpy(szFileName, strFileName.GetString());
			// ������ Ȯ���� ���� �����ϴ� �Լ�
			PathRemoveExtension(szFileName);
			strFileName = szFileName;
			auto	iter = m_MapPngImg.find(strFileName);

				CImage*		pPngImg = new CImage;
				pPngImg->Load(strRelative);	// �ش� ����� �̹��� �ε�
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

	// TODO:  ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	SetWindowPos(NULL, 1200, 0, 0, 0, SWP_NOSIZE);

	TileCombo.AddString(TEXT("01.�ʿ�Ÿ��"));
	TileCombo.AddString(TEXT("02.����Ÿ��"));
	TileCombo.AddString(TEXT("03.��Ÿ��"));
	TileCombo.AddString(TEXT("04.����Ÿ��"));
	TileCombo.AddString(TEXT("[Ÿ����������]"));
	TileCombo.SetCurSel(4);
	return FALSE;  // return TRUE unless you set the focus to a control
				   // ����: OCX �Ӽ� �������� FALSE�� ��ȯ�ؾ� �մϴ�.
}
