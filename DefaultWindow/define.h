#pragma once

#define WINCX 600
#define WINCY 800

#define PURE = 0
#define PI   3.141592f

#define OBJ_NOEVENT 0
#define OBJ_NODRAW 0
#define OBJ_DEAD 1

#define VK_W 0x57
#define VK_A 0x41
#define VK_S 0x53
#define VK_D 0x44

#define MAX_HP 5

extern HWND g_hWnd;
extern HDC g_hDC;

enum OBJ_ID { OBJ_BOOMEFFECT, OBJ_PLAYER, OBJ_MONSTER, OBJ_P_BULLET, OBJ_M_BULLET, OBJ_ITEM, OBJ_PET, OBJ_END };
enum ITEM_ID { ITEM_BOOM, ITEM_ATTACK, ITEM_PET1, ITEM_PET2, ITEM_PET3, ITEM_END };
enum PET_TYPE { ROT_PET, CURVE_PET, TRACK_PET, PET_END };

typedef struct tagInfo
{
	float fX, fY;    // �߽����� ����ϱ� ���� ��ǥ
	float fCX, fCY;  // ����, ���� ����

}INFO;

template<typename T>
void Safe_Delete(T& p)
{
	if (p != nullptr)
	{
		delete p;
		p = nullptr;
	}
}