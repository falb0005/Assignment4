/**
* \class Player.h
* \brief A class that reperesents a game player.
* \author Johnathan Falbo
* \date April 20, 2015
*/
#pragma once

#include "Cube.h"
#include "Missile.h"

class Cube;

class Player
{
public:
	/**
	* \fn void Player::Player()
	* \brief Public default constructor for class Player.
	*/
	Player();

	/**
	* \fn void Player::~Player()
	* \brief Public destructor for class Player
	*/
	~Player();

	/**
	* \fn void Player::Inintialize(Graphics *graphics)
	* \brief A function that is called to initialize the Player class.
	* \param graphics The Graphics object pointer.
	*/
	void Inintialize(Graphics *graphics);

	/**
	* \fn void Player::Update(float dt)
	* \brief A function that we値l use to update the Player.
	* \param dt The time in fractions of a second since the last pass.
	* \param playerPos The position of the player.
	*/
	void Update(float dt);

	/**
	* \fn void Player::Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt)
	* \brief A function that we値l use as to define how our
	* object is drawn to the screen.
	* \param graphics The Graphics object pointer.
	* \param relativeTo The Matrix4x4 to draw the Player relative too.
	* \param dt The time in fractions of a second since the last pass.
	*/
	void Draw(Graphics *graphics, Matrix4x4 relativeTo, float dt);

	/**
	* \fn void Player::FireMissile(float dt)
	* \brief A function that we値l to fire missiles at the player.
	* \param dt The time in fractions of a second since the last pass.
	*/
	void FireMissile(float dt);

	/**
	* \fn void Player::ResetMissiles()
	* \brief A function that we値l use to reset the Enemies missiles after the Player dies.
	*/
	void ResetMissiles();

	/**
	* \fn void Player::GetMissileXLocations()
	* \brief A function that we値l use as to get the X axis locations of the missiles that have been fired
	* \return float* containing all X locations of fired missiles. Array is terminated with -100000.
	*/
	float* GetMissileXLocations();

	/**
	* \fn void Player::GetMissileYLocations()
	* \brief A function that we値l use as to get the Y axis locations of the missiles that have been fired
	* \return float* containing all Y locations of fired missiles. Array is terminated with -100000.
	*/
	float* GetMissileYLocations();

	/**
	* \fn void Player::Transform& GetTransform()
	* \brief A function that we値l use to get the Transform object of the Player Geometry.
	* \return Transform& the reference to the Transform object of the Player Geometry.
	*/
	Transform& GetTransform();

protected:
	//player geometry
	Cube *_playerGeometry;

	//player missiles
	Missile *_missiles;

	//number of player missiles
	int _numMissiles;

	//array of x axis positions of fired missiles
	float* _missileXLocations;

	//array of y axis positions of fired missiles
	float* _missileYLocations;
};

