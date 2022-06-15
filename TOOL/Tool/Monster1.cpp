#include "stdafx.h"
#include "Monster1.h"
#include "TextureMgr.h"
#include "Device.h"
#include "ToolView.h"

CMonster1::CMonster1()
{
	m_vecMonster.reserve(30);
}


CMonster1::~CMonster1()
{
	Release();
}

void CMonster1::Initialize(D3DXVECTOR3 _pos)
{
	if (FAILED(CTextureMgr::Get_Instance()->InsertTexture(L"../Texture/Stage/Monster/Monster2/Dir_B/%d.png", TEX_MULTI, L"Monster2", L"Dir_B", 1)))
	{
		AfxMessageBox(L"Tile Image Insert failed");
		return;
	}
	
	MonsterDATA* pMonster = new	MonsterDATA;

	pMonster->vPos = { _pos.x, _pos.y-35 , 0.f };
	pMonster->vSize = { (float)130, (float)180, 0.f };
	pMonster->iAttack = 1;
	pMonster->iHp = 5;

	m_vecMonster.push_back(pMonster);

}

void CMonster1::Update(void)
{
}

void CMonster1::Render(void)
{
	D3DXMATRIX		matWorld, matScale, matTrans;
	RECT	rc{};

	::GetClientRect(m_pMainView->m_hWnd, &rc);

	float	fX = WINCX / float(rc.right - rc.left);
	float	fY = WINCY / float(rc.bottom - rc.top);

	for (auto& iter : m_vecMonster)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 1.f, 1.f, 1.f);
		D3DXMatrixTranslation(&matTrans, iter->vPos.x - m_pMainView->GetScrollPos(0),
			iter->vPos.y - m_pMainView->GetScrollPos(1),
			iter->vPos.z);

		matWorld = matScale *  matTrans;

		Set_Ratio(&matWorld, fX, fY);

		const TEXINFO*		pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"Monster2", L"Dir_B", 0);

		if (nullptr == pTexInfo)
			return;

		float		fX = pTexInfo->tImgInfo.Width / 2.f;
		float		fY = pTexInfo->tImgInfo.Height / 2.f;

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(fX, fY, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));

	}


}

void CMonster1::Release(void)
{
	for_each(m_vecMonster.begin(), m_vecMonster.end(), CDeleteObj());
	m_vecMonster.clear();
	m_vecMonster.shrink_to_fit();
}

void CMonster1::Set_Ratio(D3DXMATRIX* pOut, const float& _fX, const float& _fY, const float& fZ)
{
	pOut->_11 *= _fX;
	pOut->_21 *= _fX;
	pOut->_31 *= _fX;
	pOut->_41 *= _fX;

	pOut->_12 *= _fY;
	pOut->_22 *= _fY;
	pOut->_32 *= _fY;
	pOut->_42 *= _fY;


}
