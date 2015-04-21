/**
* \class Game.h
* \brief A class that reperesents a game.
* \author Johnathan Falbo
* \date April 20, 2015
*/
#pragma once

#include <GameEngine.h>
#include "Cube.h"
#include "Player.h"
#include "Enemy.h"

union SDL_Event;
class Graphics;
class Camera;
class ParallaxSystem;

class Game : public GameEngine
{
	friend class GameEngine;

public:
	/**
	* \fn void Game::~Game()
	* \brief Public deconstructor for class Game.
	*/
	~Game();

protected:
	/**
	* \fn void Game::Game()
	* \brief Protected default constructor for class Game.
	*/
	Game();

	/**
	* \fn void Game::InitializeImpl()
	* \brief A function that is called to initialize the Game class.
	* \param graphics The Graphics object pointer.
	*/
	void InitializeImpl();

	/**
	* \fn void Game::UpdateImpl(float dt)
	* \brief A function that we値l use to update the Game.
	* \param dt The time in fractions of a second since the last pass.
	*/
	void UpdateImpl(float dt);

	/**
	* \fn void Game::DrawImpl(Graphics *graphics, float dt)
	* \brief A function that we値l use to draw the game.
	* \param graphics The Graphics object pointer.
	* \param dt The time in fractions of a second since the last pass.
	*/
	void DrawImpl(Graphics *graphics, float dt);

	/**
	* \fn void Game::Reset()
	* \brief A function that we値l use to reset the game.
	*/
	void Reset();

	/**
	* \fn void Game::DrawImpl(Graphics *graphics, float dt)
	* \brief A function that we値l use to calculate the order to draw objects in.
	* \param drawOrder The order to draw.
	*/
	void CalculateDrawOrder(std::vector<GameObject *>& drawOrder);

	/**
	* \fn void Game::DrawImpl(Graphics *graphics, float dt)
	* \brief A function that we値l use to calculate the camera view point.
	* \param camera The Camera.
	*/
	void CalculateCameraViewpoint(Camera *camera);


	/**
	* \fn void Game::CheckEnemyPlayerMissileCollissions(float dt)
	* \brief A function that we値l use to check if enemies have shot the Player.
	* \param dt The time in fractions of a second since the last pass.
	* \return int 1 if the enemy has shot the player 0 if not.
	*/
	int CheckEnemyPlayerMissileCollissions(float dt);

	/**
	* \fn void Game::CheckPlayerEnemyMissileCollissions()
	* \brief A function that we値l use to check if the player has shot an enemy.
	* \return int 1 if the Player has shot an Enemy 0 if not.
	*/
	int CheckPlayerEnemyMissileCollissions();

	//game camera
	Camera *_gameCamera;

	//parallax camera
	Camera *_parallaxCamera;

	//game player
	Player *_player;

	//speed the player moves
	float _playerSpeed;

	//player score
	int _playerScore;

	//lives the player has left
	int _playerLives;

	//is the player alive
	bool _playerAliveFlag;

	//game enemies pointer
	Enemy *_enemies;

	//number of enemies
	int _numEnemies;

	//how often in seconds the enemies spawn
	float _enemySpawnInterval;

	//pointer to background parallax system
	ParallaxSystem *_backgroundParallaxSystem;

	//char * for the window title
	char* _titleString;
};