#include "Enemy.h"
#include <stdlib.h>

Enemy::Enemy()
{

}

Enemy::~Enemy()
{
	delete _EnemyGeometry;
	delete[] _missiles;
	free(_missileXLocations);
	free(_missileYLocations);
}

void Enemy::Inintialize(Graphics *graphics)
{
	_EnemyGeometry = new Cube();
	_EnemyGeometry->Initialize(graphics);
	_EnemyGeometry->GetTransform().position.y = 9;

	_EnemyGeometry->GetTransform().position.x = (rand() % 20) - 10;

	_enemySpeed = 2;

	_EnemyGeometry->SetVertex(0, /*pos*/-0.5f, 0.5f, 0.5f,  /*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
	_EnemyGeometry->SetVertex(1, /*pos*/0.5f, 0.5f, 0.5f,   /*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
	_EnemyGeometry->SetVertex(2, /*pos*/-0.5f, -0.5f, 0.5f, /*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
	_EnemyGeometry->SetVertex(3, /*pos*/0.5f, -0.5f, 0.5f,  /*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
	_EnemyGeometry->SetVertex(4, /*pos*/-0.5f, 0.5f, -0.5f, /*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
	_EnemyGeometry->SetVertex(5, /*pos*/0.5f, 0.5f, -0.5f,  /*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
	_EnemyGeometry->SetVertex(6, /*pos*/-0.5f, -0.5f, -0.5f,/*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
	_EnemyGeometry->SetVertex(7, /*pos*/0.5f, -0.5f, -0.5f, /*color*/ 0.0f, 0.0f, 0.0f, 1.0f);

	_isAlive = true;

	_numMissiles = 1;
	_missiles = new Missile[_numMissiles]();
	for (int index = 0; index < _numMissiles; index++)
	{
		_missiles[index].Inintialize(graphics, true);
	}

	_missileXLocations = (float*)malloc(sizeof(float)*(_numMissiles + 1));
	_missileYLocations = (float*)malloc(sizeof(float)*(_numMissiles + 1));
}

void Enemy::Update(float dt, Vector3 playerPos)
{
	int enemyPosX = GetTransform().position.x;
	if (_isAlive)
	{
		if (playerPos.x > enemyPosX){
			GetTransform().position.x += _enemySpeed * dt;
		}
		else{
			GetTransform().position.x -= _enemySpeed * dt;
		}
		GetTransform().position.y -= _enemySpeed * dt;
		if (GetTransform().position.y < -10){ _isAlive = false; }

		_EnemyGeometry->Update(dt);
		FireMissile(dt);
	}
	for (int index = 0; index < _numMissiles; index++)
	{
		_missiles[index].Update(dt, false);
	}
}

void Enemy::Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt)
{
	if (_isAlive)
	{
		_EnemyGeometry->Draw(graphics, relativeTo, dt);
		for (int index = 0; index < _numMissiles; index++)
		{
			_missiles[index].Draw(graphics, relativeTo, dt);
		}
	}
}

void Enemy::FireMissile(float dt)
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

void Enemy::ResetMissiles()
{
	for (int index = 0; index < _numMissiles; index++)
	{
		_missiles[index].SetIsAliveFlag(false);
	}
}

void Enemy::SetIsAliveFlag(bool isAlive)
{
	_isAlive = isAlive;
}

bool Enemy::GetIsAliveFlag()
{
	return _isAlive;
}

float* Enemy::GetMissileXLocations()
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

float* Enemy::GetMissileYLocations()
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

Transform& Enemy::GetTransform()
{
	return _EnemyGeometry->GetTransform();
}
