#include "Player.h"
#include <stdlib.h>

Player::Player()
{

}

Player::~Player()
{
	delete _playerGeometry;
	delete[] _missiles;
	free(_missileXLocations);
	free(_missileYLocations);
}

void Player::Inintialize(Graphics *graphics)
{
	//intialize player cube object
	_playerGeometry = new Cube();
	_playerGeometry->Initialize(graphics);

	//initialize missiles
	_numMissiles = 10;
	_missiles = new Missile[_numMissiles]();
	for (int index = 0; index < _numMissiles; index++)
	{
		_missiles[index].Inintialize(graphics, false);
	}
	_missileXLocations = (float*)malloc(sizeof(float)*(_numMissiles + 1));
	_missileYLocations = (float*)malloc(sizeof(float)*(_numMissiles + 1));
}

void Player::Update(float dt)
{
	_playerGeometry->Update(dt);
	for (int index = 0; index < _numMissiles; index++)
	{
		_missiles[index].Update(dt, true);
	}
}

void Player::Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt)
{
	_playerGeometry->Draw(graphics, relativeTo, dt);
	for (int index = 0; index < _numMissiles; index++)
	{
		_missiles[index].Draw(graphics, relativeTo, dt);
	}
}

void Player::FireMissile(float dt)
{
	static float timeElapsed = 0;
	for (int index = 0; index < _numMissiles; index++)
	{
		if (_missiles[index].GetIsAliveFlag() == false)
		{
			timeElapsed += dt;
			if (timeElapsed > 1)
			{
				_missiles[index].GetTransform().position.y = GetTransform().position.y;
				_missiles[index].GetTransform().position.x = GetTransform().position.x;
				_missiles[index].SetIsAliveFlag(true);
				timeElapsed = 0;
			}
		}
	}
}

void Player::ResetMissiles()
{
	for (int index = 0; index < _numMissiles; index++)
	{
		_missiles[index].SetIsAliveFlag(false);
	}
}

float* Player::GetMissileXLocations()
{
	int i = 0;
	for (int index = 0; index < _numMissiles; index++)
	{
		if (_missiles[index].GetIsAliveFlag())
		{
			_missileXLocations[i] = _missiles[index].GetTransform().position.x;
			i++;
		}
	}
	_missileXLocations[i] = -100000;
	return _missileXLocations;
}

float* Player::GetMissileYLocations()
{
	int i = 0;
	for (int index = 0; index < _numMissiles; index++)
	{
		if (_missiles[index].GetIsAliveFlag())
		{
			_missileYLocations[i] = _missiles[index].GetTransform().position.y;
			i++;
		}
	}
	_missileYLocations[i] = -100000;
	return _missileYLocations;
}


Transform& Player::GetTransform()
{
	return _playerGeometry->GetTransform();
}
