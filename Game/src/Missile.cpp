#include "Missile.h"

Missile::Missile()
{

}

Missile::~Missile()
{
	delete _MissileGeometry;
}

void Missile::Inintialize(Graphics *graphics, bool isEnemy)
{
	_MissileGeometry = new Cube();
	_MissileGeometry->GetTransform().scale = Vector3(0.25, 0.25, 0.25);
	_isAliveFlag = false;
	_MissileGeometry->Initialize(graphics);
	if (isEnemy)
	{
		_MissileGeometry->SetVertex(0, /*pos*/-0.5f, 0.5f, 0.5f,  /*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
		_MissileGeometry->SetVertex(1, /*pos*/0.5f, 0.5f, 0.5f,   /*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
		_MissileGeometry->SetVertex(2, /*pos*/-0.5f, -0.5f, 0.5f, /*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
		_MissileGeometry->SetVertex(3, /*pos*/0.5f, -0.5f, 0.5f,  /*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
		_MissileGeometry->SetVertex(4, /*pos*/-0.5f, 0.5f, -0.5f, /*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
		_MissileGeometry->SetVertex(5, /*pos*/0.5f, 0.5f, -0.5f,  /*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
		_MissileGeometry->SetVertex(6, /*pos*/-0.5f, -0.5f, -0.5f,/*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
		_MissileGeometry->SetVertex(7, /*pos*/0.5f, -0.5f, -0.5f, /*color*/ 0.0f, 0.0f, 0.0f, 1.0f);
	}

	_missileSpeed = 10;
}

void Missile::Update(float dt, bool direction)
{
	if (_isAliveFlag)
	{
		if (direction){
			_MissileGeometry->GetTransform().position.y += _missileSpeed * dt;
			if (_MissileGeometry->GetTransform().position.y > 10){ _isAliveFlag = false; }
		}
		else{
			_MissileGeometry->GetTransform().position.y -= _missileSpeed * dt;
			if (_MissileGeometry->GetTransform().position.y < -10){ _isAliveFlag = false; }
		}

		_MissileGeometry->Update(dt);
	}
}

void Missile::Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt)
{
	if (_isAliveFlag)
	{
		_MissileGeometry->Draw(graphics, relativeTo, dt);
	}
}

void Missile::SetIsAliveFlag(bool isAlive)
{
	_isAliveFlag = isAlive;
}

bool Missile::GetIsAliveFlag()
{
	return _isAliveFlag;
}

Transform& Missile::GetTransform()
{
	return _MissileGeometry->GetTransform();
}
