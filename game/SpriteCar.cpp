#include "stdafx.h"
#include "SpriteCar.h"

CSpriteCar::CSpriteCar(Sint16 x, Sint16 y, Uint32 time)
	: CSprite(x, y, 100, 100, "car.gif", time)
{
	turn = 0;
	gear = 0;
	brakes = false;
}

CSpriteCar::~CSpriteCar()
{
}

void CSpriteCar::OnUpdate(Uint32 time, Uint32 deltaTime)
{
	// first thing done for you: retrieve the current speed
	float v = GetSpeed();

	float d = GetDirection();
	float r = GetRotation();

	float maxAcc = 0.250;
	float reverseAcc = -0.150;
	float rollingresist = 0.02;
	float airresist;

	// TODO: Everything else to calculate the new car's speed!
	//v = v * deltaTime;

	double acc;

	if (gear > 0)
	{
		acc = maxAcc;
	}
	else if (gear < 0)
	{
		acc = reverseAcc;
	}
	else if (gear == 0)
	{
		acc = 0;
	}

	if (v > 0)
	{
		acc -= v * v * 0.000005;
		v = v - acc - rollingresist;
	}
	else if (v > -1 && v < 0)
	{
		v = 0;
	}
	else if (v < -1)
	{
		acc += v * v * 0.000005;
		v = v + acc + rollingresist;
	}

	if (brakes == true)
	{
		if (v > 0)
		{
			v -= acc - rollingresist - 1;
		}
		else if (v > -1 && v < 0)
		{
			v = 0;
		}
		else if (v < -1)
		{
			v += acc + rollingresist + 1;
		}
	}

	// At the end, don't forget to set the new speed back to your car!
	//SetSpeed(v);
	
	// TURN
	// TODO: modify Direction & Rotation

	//Accelerate right
	if (v > 1 && turn > 0)
	{
		d = d + 1;
		r = r + 1;
	}
	//Reverse left
	else if (v < 1 && turn > 0)
	{
		d = d - 1;
		r = d - 1;
	}

	//Accelerate left
	if (v > 1 && turn < 0)
	{
		d = d - 1;
		r = r - 1;
	}

	//Reverse Right
	else if (v < 1 && turn < 0)
	{
		d = d + 1;
		r = d + 1;
	}

	v += acc * deltaTime;

	SetSpeed(v);
	SetDirection(d);
	SetRotation(r);

	CSprite::OnUpdate(time, deltaTime);
}
