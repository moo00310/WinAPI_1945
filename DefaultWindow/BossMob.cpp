#include "pch.h"
#include "BossMob.h"
CBossMob::CBossMob() : m_iDistance(50), m_tCircle(INFO{}), m_iTime(1), m_iVel(5),
m_iHp(500), m_iAddX(1), m_iAddY(1), m_iStack(0), m_fXOne(0), m_fYOne(0), m_iAtkAction(0),
m_fRotate(0), m_iMoving(0), m_bMoving(true), m_bRotate(true), m_bScale(true)
{
}

CBossMob::~CBossMob()
{
	Release();
}

void CBossMob::Initialize()
{
	m_tInfo = { 100.f, 50.f, 100.f, 100.f };
	m_fSpeed = 3.f;
	m_eBullet_Type = BUL_MON4;
	m_bulletCoolDown = 50;
}

int CBossMob::Update()
{
	if (m_bDead == true)
		return OBJ_DEAD;
	__super::Update_Rect();

	ULONGLONG currentTime = GetTickCount64(); // 현재 시간

	switch (m_eState)
	{
	case Appear:
	{
		if (currentTime - m_dwStateStartTime < 2000)
		{
			float elapsedTime = float(currentTime - m_dwStateStartTime);
			float totalTime = 2000.0f;
			float speedFactor = 1.0f - (elapsedTime / totalTime);

			float speed = 3.0f * speedFactor;
			AddPos(0.0f, speed);
		}
		else
		{
			++m_iStack;
			m_eState = STATE_IDLE;
			m_dwStateStartTime = currentTime;
			m_iAtkAction = rand() % 3;
		}
		break;
	}

	case STATE_01:
	{
		if (currentTime - m_dwStateStartTime < 2000) {
			float elapsedTime = float(currentTime - m_dwStateStartTime);
			float totalTime = 2000.0f;
			float speedFactor = 1.0f - (elapsedTime / totalTime);

			float speedX = -2.0f * speedFactor;
			float speedY = -1.0f * speedFactor;

			AddPos(speedX, speedY);

			m_fXOne = Get_Info().fX;
			m_fYOne = Get_Info().fY;
		}
		else
		{
			++m_iStack;
			m_eState = STATE_IDLE;
			m_dwStateStartTime = currentTime;
			m_iAtkAction = rand() % 3;
		}
		break;
	}

	case STATE_02:
	{
		if (currentTime - m_dwStateStartTime < 4000) {
			float elapsedTime = float(currentTime - m_dwStateStartTime);
			float totalTime = 4000.0f;
			float speedFactor = 1.0f - (elapsedTime / totalTime);

			float speedX = 2.0f * speedFactor;
			float speedY = 0.0f * speedFactor;

			AddPos(speedX, speedY);
		}
		else
		{
			++m_iStack;
			m_eState = STATE_IDLE;
			m_dwStateStartTime = currentTime;
			m_iAtkAction = rand() % 3;
		}
		break;
	}

	case STATE_03:
	{
		if (currentTime - m_dwStateStartTime < 2000) {
			float elapsedTime = float(currentTime - m_dwStateStartTime);
			float totalTime = 2000.0f;
			float speedFactor = 1.0f - (elapsedTime / totalTime);

			float speedX = -2.0f * speedFactor;
			float speedY = 1.0f * speedFactor;

			AddPos(speedX, speedY);
		}
		else
		{
			++m_iStack;
			m_eState = STATE_IDLE;
			m_dwStateStartTime = currentTime; // 상태 시작 시간 갱신
			m_iAtkAction = rand() % 3;
		}
		break;
	}


	case STATE_IDLE:
	{
		if (currentTime - m_dwStateStartTime < 2000)
		{
			ULONGLONG elapsedTime = currentTime - m_dwStateStartTime;

			switch (m_iAtkAction)
			{
			case 0:
				//행동
				Rotate_pattern();
				Atk_Pattern1();
				break;
			case 1:
				Scale_pattern();
				Atk_Pattern2();
				break;
			case 2:
				Moving_pattern();
				if (Bullet_CoolDown(m_bulletCoolDown))
					Create_Bullet();
				break;
			default:
				break;
			}
		}
		else
		{
			m_bScale = true;
			m_bRotate = false;
			int a = m_iStack;
			if (1 == (m_iStack % 3))
				m_eState = STATE_01;
			if (2 == (m_iStack % 3))
				m_eState = STATE_02;
			if (0 == (m_iStack % 3))
				m_eState = STATE_03;
			m_dwStateStartTime = currentTime;
		}
		break;
	}
	}
	return OBJ_NOEVENT;
};

void CBossMob::Late_Update()
{

}

void CBossMob::Render(HDC hDC)
{
	//중심점 이동함수
	AddPos(m_iAddX, m_iAddY);

#pragma region 색상표현

	int iRed = 0;
	int iBlue = 0;

	//스케일 공격안함
	if (m_bScale)
	{
		iRed = 0;
		iBlue = 1;
		if (m_bRotate)
		{
			iRed = 255;
			iBlue = 0;
		}
	}
	//스케일 공격함
	else if (!m_bScale)
	{
		iRed = 255;
		iBlue = 0;
	}
	//로테이트 공격함
	else if (m_bRotate)
	{
		iRed = 255;
		iBlue = 0;
	}


#pragma endregion

	m_iRGB_value = m_iHp / 2;
	HPEN newPen = CreatePen(PS_SOLID, 1, RGB(0, 0, 0));
	HBRUSH newBrush = CreateSolidBrush(RGB(iRed, 250, iBlue * abs(m_iRGB_value)));
	//HBRUSH newBrush = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	HPEN oldPen = (HPEN)SelectObject(hDC, newPen);
	HBRUSH oldBrush = (HBRUSH)SelectObject(hDC, newBrush);

	//서클렌더
	if (m_bRotate)
	{
		m_fRotate += 3.55f;
		CulRotate(hDC, m_fRotate);
	}
	else
	{
		m_fRotate = 0;
		Rectangle(hDC,
			int(Get_Info().fX - Get_Info().fCX / 2),
			int(Get_Info().fY - Get_Info().fCY / 2),
			int(Get_Info().fX + Get_Info().fCX / 2),
			int(Get_Info().fY + Get_Info().fCY / 2));
	}

	SelectObject(hDC, oldPen);
	SelectObject(hDC, oldBrush);
	DeleteObject(newBrush);
	DeleteObject(newPen);

}

void CBossMob::Release()
{
}

void CBossMob::CulRotate(HDC hDC, float angleInDegrees)
{
	float cx = Get_Info().fX;
	float cy = Get_Info().fY;
	float halfWidth = Get_Info().fCX / 2;
	float halfHeight = Get_Info().fCY / 2;

	// 각 꼭짓점 계산 (사각형의 중심 기준 상대 위치)
	POINT vertices[4] = {
		{int(-halfWidth), int(-halfHeight)},
		{int(halfWidth), int(-halfHeight)},
		{int(halfWidth), int(halfHeight)},
		{int(-halfWidth), int(halfHeight)}
	};

	// 회전 변환 계산
	float angle = angleInDegrees * PI / 180.0f; // 각도를 라디안으로 변환
	POINT rotatedVertices[4];
	for (int i = 0; i < 4; i++)
	{
		rotatedVertices[i].x = int(cosf(angle) * vertices[i].x - sinf(angle) * vertices[i].y + cx);
		rotatedVertices[i].y = int(sinf(angle) * vertices[i].x + cosf(angle) * vertices[i].y + cy);
	}

	// Polygon 함수로 사각형 그리기
	Polygon(hDC, rotatedVertices, 4);
}

void CBossMob::Scale_pattern()
{
	if (m_bScale)
	{
		// 줄어드는 로직
		AddScale(-1, -1);
		if (Get_Info().fCX <= 95)
		{
			m_bScale = false;
		}
	}
	else
	{
		// 커지는 로직
		AddScale(1, 1);
		if (Get_Info().fCX >= 100) {
			m_bScale = true;
		}
	}
}
void CBossMob::Rotate_pattern()
{
	m_bRotate = true;
}
void CBossMob::Moving_pattern()
{
	if (m_bMoving)
	{
		// 줄어드는 로직
		AddPos(1, 0);
		m_iMoving += 1;
		if (10 <= m_iMoving)
		{
			m_bMoving = false;
		}
	}
	else
	{
		// 커지는 로직
		AddPos(-1, 0);
		m_iMoving -= 1;
		if (-2 >= m_iMoving) {
			m_bMoving = true;
		}
	}
}