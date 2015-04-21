/**
* \class Enemy.h
* \brief A class that reperesents a game enemy.
* \author Johnathan Falbo
* \date April 20, 2015
*/
#pragma once

#include "Cube.h"
#include "Missile.h"

class Enemy
{
public:
	/**
	* \fn void Enemy::Enemy()
	* \brief Public default constructor for class Enemy.
	*/
	Enemy();

	/**
	* \fn void Enemy::~Enemy()
	* \brief Public destructor for class Enemy
	*/
	~Enemy();

	/**
	* \fn void Enemy::Inintialize(Graphics *graphics)
	* \brief A function that is called to initialize the Enemy class.
	* \param graphics The Graphics object pointer.
	*/
	void Inintialize(Graphics *graphics);

	/**
	* \fn void Enemy::Update(float dt, Vector3 playerPos)
	* \brief A function that we値l use to update the Enemy.
	* \param dt The time in fractions of a second since the last pass.
	* \param playerPos The position of the player.
	*/
	void Update(float dt, Vector3 playerPos);

	/**
	* \fn void Enemy::Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt)
	* \brief A function that we値l use to draw the Enemy.
	* \param graphics The Graphics object pointer.
	* \param relativeTo The Matrix4x4 to draw the Enemy relative too.
	* \param dt The time in fractions of a second since the last pass.
	*/
	void Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt);

	/**
	* \fn void Enemy::FireMissile(float dt)
	* \brief A function that we値l to fire missiles at the player.
	* \param dt The time in fractions of a second since the last pass.
	*/
	void FireMissile(float dt);

	/**
	* \fn void Enemy::ResetMissiles()
	* \brief A function that we値l use to reset the Enemies missiles after the enemy dies.
	*/
	void ResetMissiles();

	/**
	* \fn void Enemy::SetIsAliveFlag(bool isAlive)
	* \brief A function that we値l use to set if the Enemy is Alive or Dead.
	* \param isAlive The boolean if true the enemy is Alive if false the enemy is Dead.
	*/
	void SetIsAliveFlag(bool isAlive);

	/**
	* \fn bool Enemy::GetIsAliveFlag()
	* \brief A function that we値l use as to Get Wether or not the Enemy is Alive.
	* \return boolean true if Enemy is Alive False if Dead.
	*/
	bool GetIsAliveFlag();

	/**
	* \fn void Enemy::GetMissileXLocations()
	* \brief A function that we値l use as to get the X axis locations of the missiles that have been fired
	* \return float* containing all X locations of fired missiles. Array is terminated with -100000.
	*/
	float* GetMissileXLocations();

	/**
	* \fn void Enemy::GetMissileYLocations()
	* \brief A function that we値l use as to get the Y axis locations of the missiles that have been fired
	* \return float* containing all Y locations of fired missiles. Array is terminated with -100000.
	*/
	float* GetMissileYLocations();

	/**
	* \fn void Enemy::Transform& GetTransform()
	* \brief A function that we値l use to get the Transform object of the Enemy Geometry.
	* \return Transform& the reference to the Transform object of the Enemy Geometry.
	*/
	Transform& GetTransform();

protected:
	//enemy geometry
	Cube *_EnemyGeometry;

	//speed the enemies will move
	float _enemySpeed;

	//enemy missiles
	Missile *_missiles;

	//number of enemy missiles
	int _numMissiles;

	//if the enemy is alive of dead
	bool _isAlive;

	//array of x axis positions of fired missiles
	float* _missileXLocations;

	//array of y axis positions of fired missiles
	float* _missileYLocations;
};

