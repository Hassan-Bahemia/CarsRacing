#include "stdafx.h"
#include "MyGame.h"

CMyGame::CMyGame(void) :
racetrack(4500, 300, "Racetrack.bmp", 0)
{
	m_pCar = NULL;
}

CMyGame::~CMyGame(void)
{
	// TODO: add destruction code here
}

/////////////////////////////////////////////////////
// Per-Frame Callback Funtions (must be implemented!)

void CMyGame::OnUpdate()
{
	if (m_pCar) m_pCar->Update(GetTime());
	if (m_pCar2) m_pCar2->Update(GetTime());

	//car 1
	if (m_pCar->GetLeft() <= 0)
	{
		m_pCar->SetSpeed(0);
	}
	if (m_pCar->GetTop() <= 145)
	{
		m_pCar->SetSpeed(0);
	}
	if (m_pCar->GetBottom() >= 425)
	{
		m_pCar->SetSpeed(0);
	}

	//car 2
	if (m_pCar2->GetLeft() <= 0)
	{
		m_pCar2->SetSpeed(0);
	}

	if (m_pCar2->GetTop() <= 145)
	{
		m_pCar2->SetSpeed(0);
	}


	if (m_pCar2->GetBottom() >= 425)
	{
		m_pCar2->SetSpeed(0);
	}

	if (m_pCar->HitTest(m_pCar2))
	{
		m_pCar->SetSpeed(0);
	}

	if (m_pCar2->HitTest(m_pCar))
	{
		m_pCar2->SetSpeed(0);
	}


}

void CMyGame::OnDraw(CGraphics* g)
{
	int leftScreenLimit = 300;
	int rightScreenLimit = 8500;

	// we scroll the whole game world according to the player position
	if (m_pCar->GetX() >= leftScreenLimit && m_pCar->GetX() <= rightScreenLimit)
	{
		g->SetScrollPos(leftScreenLimit - m_pCar->GetX(), 0);
	}
	// we stop scrolling with the player once we have reached the right limit
	if (m_pCar->GetX() > rightScreenLimit)
	{
		g->SetScrollPos(-rightScreenLimit + leftScreenLimit, 0);
	}

	if (m_pCar2->GetX() >= leftScreenLimit && m_pCar2->GetX() <= rightScreenLimit)
	{
		g->SetScrollPos(leftScreenLimit - m_pCar2->GetX(), 0);
	}
	// we stop scrolling with the player once we have reached the right limit
	if (m_pCar2->GetX() > rightScreenLimit)
	{
		g->SetScrollPos(-rightScreenLimit + leftScreenLimit, 0);
	}

	racetrack.Draw(g);

	if (m_pCar) m_pCar->Draw(g);

	if (m_pCar2) m_pCar2->Draw(g);


	int x_pCar1 = m_pCar->GetX(), y_pCar1 = m_pCar->GetY();
	if (x_pCar1 < 0) x_pCar1 = 0;
	if (x_pCar1 > GetWidth() - 50) x_pCar1 = GetWidth() - 50;
	if (y_pCar1 < 0) y_pCar1 = 0;
	if (y_pCar1 > GetHeight() - 30) y_pCar1 = GetHeight() - 30;

	int x_pCar2 = m_pCar2->GetX(), y_pCar2 = m_pCar2->GetY();
	if (x_pCar2 < 0) x_pCar2 = 0;
	if (x_pCar2 > GetWidth() - 50) x_pCar2 = GetWidth() - 50;
	if (y_pCar2 < 0) y_pCar2 = 0;
	if (y_pCar2 > GetHeight() - 30) y_pCar2 = GetHeight() - 30;

	/*
	if (m_pCar->GetX() < m_pCar2->GetX())
	{
		*g << font(32) << color(CColor::Blue()) << xy(m_pCar->GetX(), m_pCar->GetY()) << "P1";
	}

	if (m_pCar2->GetX() < m_pCar->GetX())
	{
		*g << font(32) << color(CColor::Blue()) << xy(m_pCar2->GetX(), m_pCar2->GetY()) << "P2";
	}

	*/


	g->SetScrollPos(0, 0);

	*g << font(16) << color(CColor::Blue()) << xy(5, 580) << " Player 1 Speed: " << m_pCar->GetSpeed();

	*g << font(16) << color(CColor::Blue()) << xy(600, 580) << " Player 2 Speed: " << m_pCar2->GetSpeed();

	if (m_pCar->GetX() > 9000)
	{
		*g << font(32) << color(CColor::Blue()) << xy(300, 300) << "Player 1 Wins!!!";
		m_pCar2->Delete();
		m_pCar->Delete();
	}

	if (m_pCar2->GetX() > 9000)
	{
		*g << font(32) << color(CColor::Blue()) << xy(300, 300) << "Player 2 Wins!!!";
		m_pCar->Delete();
		m_pCar2->Delete();
	}

	*g << font(32) << color(CColor::Blue()) << xy(x_pCar1, y_pCar1) << "P1";
	*g << font(32) << color(CColor::Blue()) << xy(x_pCar2, y_pCar2) << "P2";
}

/////////////////////////////////////////////////////
// Game Life Cycle

// one time initialisation
void CMyGame::OnInitialize()
{
}

// called at the start of a new game - display menu here
void CMyGame::OnDisplayMenu()
{
	if (m_pCar) delete m_pCar;
	if (m_pCar2) delete m_pCar2;
	m_pCar = new CSpriteCar(100, 375, GetTime());
	m_pCar2 = new CSpriteCar(100, 150, GetTime());
	StartGame();
}

// called when Game Mode entered
void CMyGame::OnStartGame()
{
}

// called when Game is Over
void CMyGame::OnGameOver()
{
}

// one time termination code
void CMyGame::OnTerminate()
{
}

/////////////////////////////////////////////////////
// Keyboard Event Handlers

void CMyGame::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_F4 && (mod & (KMOD_LALT | KMOD_RALT)))
		StopGame();
	if (sym == SDLK_F2)
		NewGame();

	// Steer the car
	if (!m_pCar) return;
	if (sym == SDLK_RIGHT)
		m_pCar->Turn(1);
	if (sym == SDLK_LEFT)
		m_pCar->Turn(-1);
	if (sym == SDLK_UP)
		m_pCar->SetGear(1);
	if (sym == SDLK_DOWN)
		m_pCar->SetGear(-1);
	if (sym == SDLK_SPACE)
		m_pCar->SetBrake(true);

	if (!m_pCar2) return;
	if (sym == SDLK_d)
		m_pCar2->Turn(1);
	if (sym == SDLK_a)
		m_pCar2->Turn(-1);
	if (sym == SDLK_w)
		m_pCar2->SetGear(1);
	if (sym == SDLK_s)
		m_pCar2->SetGear(-1);
	if (sym == SDLK_LSHIFT)
		m_pCar->SetBrake(true);
}

void CMyGame::OnKeyUp(SDLKey sym, SDLMod mod, Uint16 unicode)
{
	if (sym == SDLK_RIGHT || sym == SDLK_LEFT)
		m_pCar->Turn(0);
	if (sym == SDLK_UP || sym == SDLK_DOWN)
		m_pCar->SetGear(0);
	if (sym == SDLK_SPACE)
		m_pCar->SetBrake(false);

	if (sym == SDLK_d || sym == SDLK_a)
		m_pCar2->Turn(0);
	if (sym == SDLK_w || sym == SDLK_s)
		m_pCar2->SetGear(0);
	if (sym == SDLK_LSHIFT)
		m_pCar2->SetBrake(false);
}

/////////////////////////////////////////////////////
// Mouse Events Handlers

void CMyGame::OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle)
{
}

void CMyGame::OnLButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnLButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnRButtonUp(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonDown(Uint16 x,Uint16 y)
{
}

void CMyGame::OnMButtonUp(Uint16 x,Uint16 y)
{
}
