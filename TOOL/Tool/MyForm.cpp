// MyForm.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyForm.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM), m_MySheet(L"의미없음")
{

}

CMyForm::~CMyForm()
{
}

void CMyForm::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMyForm, CFormView)


	ON_BN_CLICKED(IDC_BUTTON1, &CMyForm::OnUnitTool)
	ON_BN_CLICKED(IDC_BUTTON7, &CMyForm::OnMapTool)
	ON_BN_CLICKED(IDC_BUTTON8, &CMyForm::OnProperty)
	ON_BN_CLICKED(IDC_BUTTON9, &CMyForm::OnPathFind)
	ON_BN_CLICKED(IDC_BUTTON10, &CMyForm::OnMonstertool)
END_MESSAGE_MAP()


// CMyForm 진단입니다.

#ifdef _DEBUG
void CMyForm::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void CMyForm::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMyForm 메시지 처리기입니다.


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	// CreatePointFont(폰트 크기, 서체)
	m_Font.CreatePointFont(130, L"궁서");

	// GetDlgItem : 다이얼로그에 배치된 리소스를 ID 값에 따라 얻어오는 함수
	GetDlgItem(IDC_BUTTON1)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON7)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON8)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON9)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON10)->SetFont(&m_Font);

	if (nullptr == m_MySheet.GetSafeHwnd())
		m_MySheet.Create(0, WS_OVERLAPPEDWINDOW);

	// 프로퍼티시트 객체의 멤버함수 Create는 뷰 클래스들과는 달리 함수 내부에 WS_VISIBLE 속성이 기본 탑재되어 있다.
	// 그래서 버튼을 누르지 않음에도 실행과 동시에 시트와 페이지 화면이 보이게 된다.

}

void CMyForm::OnUnitTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	// GetSafeHwnd : 현재 다이얼로그의 윈도우 핸들을 반환
	// 핸들이 nullptr이면 아직 생성되어 있지 않음을 의미

	if(nullptr == m_UnitTool.GetSafeHwnd())
		m_UnitTool.Create(IDD_UNITTOOL);	// 해당 ID에 맞는 다이얼로그 생성

	m_UnitTool.ShowWindow(SW_SHOW);		// 창 모양으로 출력
}


void CMyForm::OnMapTool()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	if (nullptr == m_MapTool.GetSafeHwnd())
		m_MapTool.Create(IDD_MAPTOOL);	// 해당 ID에 맞는 다이얼로그 생성

	m_MapTool.ShowWindow(SW_SHOW);
}

void CMyForm::OnMonstertool()
{
	if (nullptr == m_MonsterTool.GetSafeHwnd())
		m_MonsterTool.Create(IDD_MONSTERTOOL);	// 해당 ID에 맞는 다이얼로그 생성

	m_MonsterTool.ShowWindow(SW_SHOW);
}

void CMyForm::OnProperty()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	m_MySheet.ShowWindow(SW_SHOW);		// 창 모양으로 출력
}


void CMyForm::OnPathFind()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (nullptr == m_PathFind.GetSafeHwnd())
		m_PathFind.Create(IDD_PATHFIND);	// 해당 ID에 맞는 다이얼로그 생성

	m_PathFind.ShowWindow(SW_SHOW);
}


