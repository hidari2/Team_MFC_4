#include "stdafx.h"
#include "Back.h"
#include "TextureMgr.h"
#include "Device.h"
#include "ToolView.h"


Back::Back()
{
}


Back::~Back()
{
}
void Back::Initialize(void)
{
	if (FAILED(CTextureMgr::Get_Instance()->InsertTexture(L"../Texture/Stage/BackGround/BackGround/Default/BackGround%d.png", TEX_MULTI, L"BackGround", L"Back", 4)))
	{
		AfxMessageBox(L"Tile Image Insert failed");
		return;
	}
	

			BACK* pBack = new BACK;

			float		fX = WINCX / 2.f;
			float		fY = WINCY / 2.f;

			pBack->vPos = { fX, fY, 0.f };
			pBack->vSize = { (float)BACKX, (float)BACKY, 0.f };
			pBack->byDrawID = 0;
			pBack->byOption = 0;
			m_vecBack.push_back(pBack);
	}
void	Back::Update(void)
{

}
void	Back::Render(int _Groundid)
{

	D3DXMATRIX		matWorld, matScale, matTrans;

	RECT	rc{};

	::GetClientRect(m_pMainView->m_hWnd, &rc);

	float	fX = WINCX / float(rc.right - rc.left);
	float	fY = WINCY / float(rc.bottom - rc.top);
	for (auto& iter : m_vecBack)
	{
		D3DXMatrixIdentity(&matWorld);
		D3DXMatrixScaling(&matScale, 0.3f, 0.4f, 1.f);
		D3DXMatrixTranslation(&matTrans,iter-> vPos.x - m_pMainView->GetScrollPos(0),
			iter->vPos.y - m_pMainView->GetScrollPos(1),
			iter->vPos.z);
		matWorld = matScale*matTrans;
		//Set_Ratio(&matWorld, 0.5, 0.5);

		const TEXINFO*		pTexInfo = CTextureMgr::Get_Instance()->Get_Texture(L"BackGround", L"Back", _Groundid);

		if (nullptr == pTexInfo)
			return;

		float		fX2 = pTexInfo->tImgInfo.Width / 2.f;
		float		fY2 = pTexInfo->tImgInfo.Height / 2.f;

		CDevice::Get_Instance()->Get_Sprite()->SetTransform(&matWorld);

		CDevice::Get_Instance()->Get_Sprite()->Draw(pTexInfo->pTexture,
			nullptr,
			&D3DXVECTOR3(fX2, fY2, 0.f),
			nullptr,
			D3DCOLOR_ARGB(255, 255, 255, 255));
	}
	}

void	Back::Mini_Render(void)
{

}
void	Back::Release(void)
{

}
void Back::Set_Ratio(D3DXMATRIX* pOut, const float& _fX, const float& _fY, const float& fZ)
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
