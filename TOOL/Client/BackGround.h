#pragma once
#include "Include.h"

class CToolView;
class  CBackGround
{
public:
	CBackGround();
	~CBackGround();

public:
	void		Initialize(void);
	void		Update(void);
	void		Render(void);
	void		Release(void);
public:
	void		Set_MainView(CToolView* pMainView) { m_pMainView = pMainView; }
	void		Set_Ratio(D3DXMATRIX* pOut, const float& _fX, const float& _fY, const float& fZ = 0.f);
	// d2d�̱� ������ z���� �Ű� ������ ���� �ʿ䰡 ����

private:
	CToolView*				m_pMainView = nullptr;

};
