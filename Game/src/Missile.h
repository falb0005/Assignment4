/**
* \class Missile.h
* \brief A class that reperesents a game missile.
* \author Johnathan Falbo
* \date April 20, 2015
*/
#pragma once

#include "Cube.h"

class Cube;

class Missile
{
public:
	/**
	* \fn void Missile::Missile()
	* \brief Public default constructor for class Missile.
	*/
	Missile();

	/**
	* \fn void Missile::~Missile()
	* \brief Public destructor for class Missile
	*/
	~Missile();

	/**
	* \fn void Missile::Inintialize(Graphics *graphics, bool isEnemy)
	* \brief A function that is called to initialize the Missile class.
	* \param graphics The Graphics object pointer.
	* \param isEnemy True if Enemy false if player.
	*/
	void Inintialize(Graphics *graphics, bool isEnemy);

	/**
	* \fn void Missile::Update(float dt, bool direction)
	* \brief A function that we値l use to update the Missile.
	* \param dt The time in fractions of a second since the last pass.
	* \param playerPos The position of the player.
	*/
	void Update(float dt, bool direction);

	/**
	* \fn void Missile::Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt)
	* \brief A function that we値l use to draw the Missile.
	* \param graphics The Graphics object pointer.
	* \param relativeTo The Matrix4x4 to draw the Missile relative too.
	* \param dt The time in fractions of a second since the last pass.
	*/
	void Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt);

	/**
	* \fn void Missile::SetIsAliveFlag(bool isAlive)
	* \brief A function that we値l use to set if the Missile is Alive or Dead.
	* \param isAlive The boolean if true the Missile is Alive if false the Missile is Dead.
	*/
	void SetIsAliveFlag(bool isAlive);

	/**
	* \fn bool Missile::GetIsAliveFlag()
	* \brief A function that we値l use as to Get Wether or not the Missile is Alive.
	* \return boolean true if Missile is Alive False if Dead.
	*/
	bool GetIsAliveFlag();

	/**
	* \fn void Missile::Transform& GetTransform()
	* \brief A function that we値l use to get the Transform object of the Missile Geometry.
	* \return Transform& the reference to the Transform object of the Missile Geometry.
	*/
	Transform& GetTransform();

protected:
	//missile geometry
	Cube *_MissileGeometry;

	//wether the missile is alive or dead
	bool _isAliveFlag;

	//speed the missile moves
	float _missileSpeed;
};

