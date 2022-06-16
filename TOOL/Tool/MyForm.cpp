// MyForm.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Tool.h"
#include "MyForm.h"


// CMyForm

IMPLEMENT_DYNCREATE(CMyForm, CFormView)

CMyForm::CMyForm()
	: CFormView(IDD_MYFORM), m_MySheet(L"�ǹ̾���")
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


// CMyForm �����Դϴ�.

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


// CMyForm �޽��� ó�����Դϴ�.


void CMyForm::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	// CreatePointFont(��Ʈ ũ��, ��ü)
	m_Font.CreatePointFont(130, L"�ü�");

	// GetDlgItem : ���̾�α׿� ��ġ�� ���ҽ��� ID ���� ���� ������ �Լ�
	GetDlgItem(IDC_BUTTON1)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON7)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON8)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON9)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON10)->SetFont(&m_Font);

	if (nullptr == m_MySheet.GetSafeHwnd())
		m_MySheet.Create(0, WS_OVERLAPPEDWINDOW);

	// ������Ƽ��Ʈ ��ü�� ����Լ� Create�� �� Ŭ��������� �޸� �Լ� ���ο� WS_VISIBLE �Ӽ��� �⺻ ž��Ǿ� �ִ�.
	// �׷��� ��ư�� ������ �������� ����� ���ÿ� ��Ʈ�� ������ ȭ���� ���̰� �ȴ�.

}

void CMyForm::OnUnitTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	// GetSafeHwnd : ���� ���̾�α��� ������ �ڵ��� ��ȯ
	// �ڵ��� nullptr�̸� ���� �����Ǿ� ���� ������ �ǹ�

	if(nullptr == m_UnitTool.GetSafeHwnd())
		m_UnitTool.Create(IDD_UNITTOOL);	// �ش� ID�� �´� ���̾�α� ����

	m_UnitTool.ShowWindow(SW_SHOW);		// â ������� ���
}


void CMyForm::OnMapTool()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	if (nullptr == m_MapTool.GetSafeHwnd())
		m_MapTool.Create(IDD_MAPTOOL);	// �ش� ID�� �´� ���̾�α� ����

	m_MapTool.ShowWindow(SW_SHOW);
}

void CMyForm::OnMonstertool()
{
	if (nullptr == m_MonsterTool.GetSafeHwnd())
		m_MonsterTool.Create(IDD_MONSTERTOOL);	// �ش� ID�� �´� ���̾�α� ����

	m_MonsterTool.ShowWindow(SW_SHOW);
}

void CMyForm::OnProperty()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.

	m_MySheet.ShowWindow(SW_SHOW);		// â ������� ���
}


void CMyForm::OnPathFind()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	if (nullptr == m_PathFind.GetSafeHwnd())
		m_PathFind.Create(IDD_PATHFIND);	// �ش� ID�� �´� ���̾�α� ����

	m_PathFind.ShowWindow(SW_SHOW);
}


