#include "DXUT.h"
#include "cPlayerCannon.h"

#include "cTileMap.h"
#include "cTileExplode.h"
#include "cPlayerSoldier.h"

cPlayerCannon::cPlayerCannon()
{
}


cPlayerCannon::~cPlayerCannon()
{
}

void cPlayerCannon::Init()
{
}

void cPlayerCannon::Update()
{
	CannonShoot(D3DXVECTOR2(0, 0));
}

void cPlayerCannon::Render()
{
}

void cPlayerCannon::Release()
{
}

void cPlayerCannon::CannonShoot(D3DXVECTOR2 startPos)
{
	if (GETKEY_DOWN(VK_LBUTTON)) {
		if (SCENEMANAGER->GetNowScene() == "ingame" && GAMEMANAGER->GetWiner() == 2) {
			if (GAMEMANAGER->GetTurnOwner() == FALSE) {
				Shot();
			}
		}
	}
}

bool cPlayerCannon::Shot()
{
	for (auto iter : (*OBJECTMANAGER->GetObjectList(OBJ_TILEMAPS))) {

		if (INPUTMANAGER->GetMouseOnTilePos() == iter->GetPos()) {

			if (dynamic_cast<cTile*>(iter)->GetIsDestroy() == false) {

				dynamic_cast<cTile*>(iter)->SetDestroy(true);
				OBJECTMANAGER->AddObject(new cTileExplode(dynamic_cast<cTile*>(iter)->GetPos().x,
					dynamic_cast<cTile*>(iter)->GetPos().y), OBJ_EFFECT);

				if (dynamic_cast<cTile*>(iter)->GetOnUnit() == true) {
					TIMER_STRING("Hit!", 800, dynamic_cast<cTile*>(iter)->GetPos(),50);
					GAMEMANAGER->SetPlayerScore(GAMEMANAGER->GetPlayerScore() + GAMEMANAGER->GetPlusScore() + 100);
					GAMEMANAGER->SetPlusScore(GAMEMANAGER->GetPlusScore() + 25);
					GAMEMANAGER->SetTurnOwner(FALSE);
				}
				else {
					GAMEMANAGER->SetPlusScore(0);
					GAMEMANAGER->SetTurnOwner(TRUE);
				}
				return true;
			}
			else return false;
		}

	}

}
