#pragma once
#include "Include.h"
class CToolView;
class Back
{
public:
	Back();
	~Back();

public:
	void		Initialize(void);
	void		Update(void);
	void		Render(int _Groundid);
	void		Mini_Render(void);
	void		Release(void);

public:
	

	void		Set_MainView(CToolView* pMainView) { m_pMainView = pMainView; }

	// d2d이기 때문에 z값을 매개 변수로 받을 필요가 없다
	void		Set_Ratio(D3DXMATRIX* pOut, const float& _fX, const float& _fY, const float& fZ = 0.f);

	int m_drawid = 0;

	vector<BACK*>			m_vecBack;
	CToolView*				m_pMainView = nullptr;
private:

};

