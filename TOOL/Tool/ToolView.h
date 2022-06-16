
// ToolView.h : CToolView 클래스의 인터페이스
//

#pragma once

#include "Device.h"
#include "Terrain.h"
#include "Bossmonster.h"
#include "Monster1.h"
#include "Monster2.h"
#include "Back.h"


class CToolDoc;
class CToolView : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CToolView();
	DECLARE_DYNCREATE(CToolView)

// 특성입니다.
public:
	CToolDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CToolView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

public:
	bool create_tile;
	bool create_monster;
	int  Monsterid;
	int  Groundid;

	CTerrain*			Get_Terrain(void) {	return m_pTerrain;	}
	Back*			Get_Back(void) { return m_pBack; }
	CBossmonster*		Get_Bossmonster(void) { return m_pBossmonster; }

protected:
	CDevice*			m_pDevice;
	CTerrain*			m_pTerrain;
	Back*				m_pBack;
	

	CBossmonster*		m_pBossmonster;
	CMonster1*		    m_pMonster1;
	CMonster2*		    m_pMonster2;

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // ToolView.cpp의 디버그 버전
inline CToolDoc* CToolView::GetDocument() const
   { return reinterpret_cast<CToolDoc*>(m_pDocument); }
#endif

