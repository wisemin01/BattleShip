#include "DXUT.h"

// Á¡ ÁÂÇ¥, ÁÂÇ¥ , Å©±â
BOOL CoillsionCheck_Mouse_Tile(const D3DXVECTOR3 & vPoint, const D3DXVECTOR3 & vPos, const D3DXVECTOR3 & vSize)
{
	D3DXVECTOR2 vMyPoint[4];

	vMyPoint[0] = D3DXVECTOR2(vPos.x - (vSize.x / 2.f), vPos.y);
	vMyPoint[1] = D3DXVECTOR2(vPos.x, vPos.y + (vSize.y / 2.f));
	vMyPoint[2] = D3DXVECTOR2(vPos.x + (vSize.x / 2.f), vPos.y);
	vMyPoint[3] = D3DXVECTOR2(vPos.x, vPos.y - (vSize.y / 2.f));

	float fGrad = (vSize.y / 2.f) / (vSize.x / 2.f);

	float fB[4] =
	{
		vMyPoint[0].y - fGrad * vMyPoint[0].x,
		vMyPoint[1].y + fGrad * vMyPoint[1].x,
		vMyPoint[2].y - fGrad * vMyPoint[2].x,
		vMyPoint[3].y + fGrad * vMyPoint[3].x
	};

	if (vPoint.y - fGrad * vPoint.x - fB[0] <= 0 &&
		vPoint.y + fGrad * vPoint.x - fB[1] <= 0 &&
		vPoint.y - fGrad * vPoint.x - fB[2] > 0 &&
		vPoint.y + fGrad * vPoint.x - fB[3] > 0)
	{
		return true;
	}

	return false;
}

BOOL nIntersectRect(RECT rc1, RECT rc2)
{
	if (rc2.right >= rc1.left
		&& rc2.left <= rc1.right
		&& rc2.bottom >= rc1.top
		&& rc2.top <= rc1.bottom) {
		return TRUE;
	}
	else return FALSE;
}

BOOL nIntersectRectToPoint(RECT rc, D3DXVECTOR2 point)
{
	if (rc.left <= point.x &&
		rc.right >= point.x &&
		rc.top <= point.y &&
		rc.bottom >= point.y) {
		return true;
	}
	else return false;
}

int RandomNumber(int min, int max)
{
	random_device rn;
	mt19937_64 rnd(rn());

	uniform_int_distribution<int> range(min, max);

	return range(rnd);
}
