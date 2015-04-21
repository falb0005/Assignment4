#include "Game.h"
#include <GameObject.h>
#include <SDL.h>
#include <math.h>
#include <SDL_image.h>
#include <SDL_opengl.h>
#include <InputManager.h>
#include <Graphics/GraphicsOpenGL.h>

#include "Cube.h"
#include <Cameras/Camera.h>
#include <Cameras/PerspectiveCamera.h>
#include <Cameras/OrthographicCamera.h>

#include <Parallax/ParallaxLayer.h>
#include <Parallax/ParallaxSystem.h>

// Initializing our static member pointer.
GameEngine* GameEngine::_instance = nullptr;

GameEngine* GameEngine::CreateInstance()
{
	if (_instance == nullptr)
	{
		_instance = new Game();
	}
	return _instance;
}

Game::Game() : GameEngine()
{

}

Game::~Game()
{
	// Clean up our pointers.
	delete _parallaxCamera;
	_parallaxCamera = nullptr;

	ParallaxLayer *layerToDelete = nullptr;
	while (_backgroundParallaxSystem->LayerCount() > 0)
	{
		// Delete all of the layers inside of our parallax system.
		layerToDelete = _backgroundParallaxSystem->PopLayer();

		delete layerToDelete;
		layerToDelete = nullptr;
	}

	free(_titleString);

	delete _player;

	delete[] _enemies;

	delete _backgroundParallaxSystem;
	_backgroundParallaxSystem;
}

SDL_Renderer *_renderer;
SDL_Texture *_texture;

void Game::InitializeImpl()
{
	srand(34569098464565);
	_playerScore = 0;
	_playerLives = 5;
	_titleString = (char*)malloc(sizeof(char)* 100);

	sprintf_s(_titleString, 80, "The Game That Can't Be Defeated: Lives %d Score %d", _playerLives, _playerScore);
	SDL_SetWindowTitle(_window, _titleString);

	float nearPlane = 0.01f;
	float farPlane = 100.0f;
	Vector4 position(0, 0, 0, 0.0f);
	Vector4 lookAt = Vector4::Normalize(Vector4::Difference(Vector4(0.0f, 0.0f, 0.0f, 0.0f), position));
	Vector4 up(0.0f, 1.0f, 0.0f, 0.0f);

	//_camera = new PerspectiveCamera(100.0f, 1.0f, nearPlane, farPlane, position, lookAt, up);
	_gameCamera = new OrthographicCamera(-10.0f, 10.0f, 10.0f, -10.0f, nearPlane, farPlane, position, lookAt, up);

	position = Vector4(0.0f, 0.0f, 2.5f, 0.0f);
	lookAt = Vector4::Normalize(Vector4::Difference(Vector4(0.0f, 0.0f, 0.0f, 0.0f), position));
	_parallaxCamera = new OrthographicCamera(-10.0f, 10.0f, 10.0f, -10.0f, nearPlane, farPlane, position, lookAt, up);

	_backgroundParallaxSystem = new ParallaxSystem();

	//initialize player
	_player = new Player();
	_player->Inintialize(_graphicsObject);
	_player->GetTransform().position.y = -5;
	_playerSpeed = 5;
	_playerAliveFlag = true;

	//initialize enemies
	_numEnemies = 10;
	_enemies = new Enemy[_numEnemies]();
	for (int index = 0; index < _numEnemies; index++)
	{
		_enemies[index].Inintialize(_graphicsObject);
		_enemies[index].SetIsAliveFlag(false);
	}
	_enemySpawnInterval = 3;

	for (auto itr = _objects.begin(); itr != _objects.end(); itr++)
	{
		(*itr)->Initialize(_graphicsObject);
	}

	_backgroundParallaxSystem->Initialize(_graphicsObject);
}

void Game::UpdateImpl(float dt)
{
	//if the player is in death state and has lives left
	if (!_playerAliveFlag && _playerLives > 0)
	{
		sprintf_s(_titleString, 80, "Death State: Lives %d Score %d", _playerLives, _playerScore);
		SDL_SetWindowTitle(_window, _titleString);
		static float timeElapsed = 0;
		timeElapsed += dt;
		//when death state is over
		if (timeElapsed > 2)
		{
			sprintf_s(_titleString, 80, "The Game That Can't Be Defeated: Lives %d Score %d", _playerLives, _playerScore);
			SDL_SetWindowTitle(_window, _titleString);
			_player->GetTransform().position = Vector3(0, -5, 0);
			int colllision = CheckEnemyPlayerMissileCollissions(dt);
			while (colllision == 1)
			{
				_player->GetTransform().position.x += 1;
				colllision = CheckEnemyPlayerMissileCollissions(dt);
				if (_player->GetTransform().position.x > 9){ _player->GetTransform().position.x = -9;  _player->GetTransform().position.y -= 1; }
				if (_player->GetTransform().position.y < -9){ _player->GetTransform().position.y = 9; }
			}
			for (int index = 0; index < _numEnemies; index++)
			{
				_enemies[index].SetIsAliveFlag(false);
			}
			timeElapsed = 0;
			_playerAliveFlag = true;
		}
		return;
	}

	InputManager::GetInstance()->Update(dt);

	// Check controls.
	if (InputManager::GetInstance()->IsKeyDown(SDLK_UP) == true)
	{
		_player->GetTransform().position.y += _playerSpeed * dt;
		if (_player->GetTransform().position.y > 9){ _player->GetTransform().position.y = 9; }
	}
	else if (InputManager::GetInstance()->IsKeyDown(SDLK_DOWN) == true)
	{
		_player->GetTransform().position.y -= _playerSpeed * dt;
		if (_player->GetTransform().position.y < -9){ _player->GetTransform().position.y = -9; }
	}
	else if (InputManager::GetInstance()->IsKeyDown(SDLK_LEFT) == true)
	{
		_player->GetTransform().position.x -= _playerSpeed * dt;
		if (_player->GetTransform().position.x < -9){ _player->GetTransform().position.x = -9; }
	}
	else if (InputManager::GetInstance()->IsKeyDown(SDLK_RIGHT) == true)
	{
		_player->GetTransform().position.x += _playerSpeed * dt;
		if (_player->GetTransform().position.x > 9){ _player->GetTransform().position.x = 9; }
	}
	else if (InputManager::GetInstance()->IsKeyDown(SDLK_SPACE) == true)
	{
		_player->FireMissile(dt);
	}

	for (auto itr = _objects.begin(); itr != _objects.end(); itr++)
	{
		(*itr)->Update(dt);
	}

	//update enemies
	for (int index = 0; index < _numEnemies; index++)
	{
		_enemies[index].Update(dt, _player->GetTransform().position);
	}

	//update player
	_player->Update(dt);

	_backgroundParallaxSystem->Update(Vector2::Zero(), dt);

	//check if enemies have shot the player
	CheckEnemyPlayerMissileCollissions(dt);

	//check if player has shot enemies
	CheckPlayerEnemyMissileCollissions();

	//deploy enemies
	static float timeSinceLastSpawn = 0;
	timeSinceLastSpawn += dt;
	if (timeSinceLastSpawn > _enemySpawnInterval)
	{
		for (int index = 0; index < _numEnemies; index++)
		{
			if (_enemies[index].GetIsAliveFlag() == false)
			{
				_enemies[index].SetIsAliveFlag(true);
				_enemies[index].GetTransform().position.y = 9;
				_enemies[index].GetTransform().position.x = (rand() % 20) - 10;
				timeSinceLastSpawn = 0;
				break;
			}
		}
	}

	//make sure an enemy is on the field
	bool anyAlive = false;
	for (int index = 0; index < _numEnemies; index++)
	{
		if (_enemies[index].GetIsAliveFlag()){ anyAlive = true; break; }
	}
	if (!anyAlive)
	{
		for (int index = 0; index < _numEnemies; index++)
		{
			if (!_enemies[index].GetIsAliveFlag())
			{
				_enemies[index].SetIsAliveFlag(true);
				_enemies[index].GetTransform().position.y = 9;
				_enemies[index].GetTransform().position.x = (rand() % 20) - 10;
				break;
			}
		}
	}

	//update window title
	sprintf_s(_titleString, 80, "The Game That Can't Be Defeated: Lives %d Score %d", _playerLives, _playerScore);
	SDL_SetWindowTitle(_window, _titleString);
}

void Game::DrawImpl(Graphics *graphics, float dt)
{
	std::vector<GameObject *> renderOrder = _objects;
	//CalculateDrawOrder(renderOrder);

	// Draw parallax backgrounds
	glPushMatrix();
	{
		CalculateCameraViewpoint(_parallaxCamera);

		_backgroundParallaxSystem->Draw(graphics, _gameCamera->GetProjectionMatrix(), dt);
	}
	glPopMatrix();

	// Draw scenery on top.
	glPushMatrix();
	{
		glClear(GL_DEPTH_BUFFER_BIT);
		CalculateCameraViewpoint(_gameCamera);

		//draw enemies
		for (int index = 0; index < _numEnemies; index++)
		{
			_enemies[index].Draw(graphics, _gameCamera->GetProjectionMatrix(), dt);
		}

		//draw player
		_player->Draw(graphics, _gameCamera->GetProjectionMatrix(), dt);

		for (auto itr = renderOrder.begin(); itr != renderOrder.end(); itr++)
		{
			(*itr)->Draw(graphics, _gameCamera->GetProjectionMatrix(), dt);
		}
	}
	glPopMatrix();
}

void Game::CalculateDrawOrder(std::vector<GameObject *>& drawOrder)
{
	// SUPER HACK GARBAGE ALGO.
	drawOrder.clear();

	auto objectsCopy = _objects;
	auto farthestEntry = objectsCopy.begin();
	while (objectsCopy.size() > 0)
	{
		bool entryFound = true;
		for (auto itr = objectsCopy.begin(); itr != objectsCopy.end(); itr++)
		{
			if (farthestEntry != itr)
			{
				if ((*itr)->GetTransform().position.y < (*farthestEntry)->GetTransform().position.y)
				{
					entryFound = false;
					farthestEntry = itr;
					break;
				}
			}
		}

		if (entryFound)
		{
			GameObject *farthest = *farthestEntry;

			drawOrder.push_back(farthest);
			objectsCopy.erase(farthestEntry);
			farthestEntry = objectsCopy.begin();
		}
	}
}

void Game::CalculateCameraViewpoint(Camera *camera)
{
	camera->Apply();

	Vector4 xAxis(1.0f, 0.0f, 0.0f, 0.0f);
	Vector4 yAxis(0.0f, 1.0f, 0.0f, 0.0f);
	Vector4 zAxis(0.0f, 0.0f, 1.0f, 0.0f);

	Vector3 cameraVector(camera->GetLookAtVector().x, camera->GetLookAtVector().y, camera->GetLookAtVector().z);
	Vector3 lookAtVector(0.0f, 0.0f, -1.0f);

	Vector3 cross = Vector3::Normalize(Vector3::Cross(cameraVector, lookAtVector));
	float dot = MathUtils::ToDegrees(Vector3::Dot(lookAtVector, cameraVector));

	glRotatef(cross.x * dot, 1.0f, 0.0f, 0.0f);
	glRotatef(cross.y * dot, 0.0f, 1.0f, 0.0f);
	glRotatef(cross.z * dot, 0.0f, 0.0f, 1.0f);

	glTranslatef(-camera->GetPosition().x, -camera->GetPosition().y, -camera->GetPosition().z);
}

void Game::Reset()
{
	//reset player
	_playerScore = 0;
	_playerLives = 5;
	_player->GetTransform().position = Vector3(0, -5, 0);
	_playerAliveFlag = true;

	//kill all enemies
	for (int index = 0; index < _numEnemies; index++)
	{
		_enemies[index].SetIsAliveFlag(false);
		_enemies[index].ResetMissiles();
	}
	_enemySpawnInterval = 3;

	//reset window title
	sprintf_s(_titleString, 80, "The Game That Can't Be Defeated: Lives %d Score %d", _playerLives, _playerScore);
	SDL_SetWindowTitle(_window, _titleString);
}

int Game::CheckEnemyPlayerMissileCollissions(float dt)
{
	Vector3 playerPos = _player->GetTransform().position;
	for (int index = 0; index < _numEnemies; index++)
	{
		float *enemyMissileXLocations = _enemies[index].GetMissileXLocations();
		float *enemyMissileYLocations = _enemies[index].GetMissileYLocations();
		while (*enemyMissileXLocations != -100000)
		{
			if (_enemies[index].GetIsAliveFlag())
			{
				//if enemy missile is within 1 unit of the player pos
				if ((*enemyMissileXLocations - playerPos.x) * (*enemyMissileXLocations - playerPos.x) < 1 && (*enemyMissileYLocations - playerPos.y) * (*enemyMissileYLocations - playerPos.y) < 1)
				{
					printf("Enemy Hit Player\n");
					if (_playerAliveFlag){ _playerLives -= 1; }
					_playerAliveFlag = false;
					//check player lives
					if (_playerLives == 0)
					{
						sprintf_s(_titleString, 80, "Press The 'R' Key To Restart... Finishing Score: %d", _playerScore);
						SDL_SetWindowTitle(_window, _titleString);
						//loop until user presses enter
						while (1){
							InputManager::GetInstance()->Update(dt);
							//check if user has pressed enter
							if (InputManager::GetInstance()->IsKeyDown(SDLK_r) == true)
							{
								break;
							}
						}
						Reset();
					}
					return 1;
				}
			}
			//printf("Pos X: %f\n", *enemyMissileXLocations);
			//printf("Pos Y: %f\n", *enemyMissileYLocations);
			enemyMissileXLocations++;
			enemyMissileYLocations++;
		}
	}
	return 0;
}

int Game::CheckPlayerEnemyMissileCollissions()
{
	float *playerMissileXLocations = _player->GetMissileXLocations();
	float *playerMissileYLocations = _player->GetMissileYLocations();
	Vector3 enemyPos;
	Vector3 playerPos = _player->GetTransform().position;
	while (*playerMissileXLocations != -100000)
	{
		for (int index = 0; index < _numEnemies; index++)
		{
			if (_enemies[index].GetIsAliveFlag())
			{
				enemyPos = _enemies[index].GetTransform().position;
				//if player missile is within 1 unit of the enemy pos
				if ((*playerMissileXLocations - enemyPos.x) * (*playerMissileXLocations - enemyPos.x) < 1 && (*playerMissileYLocations - enemyPos.y) * (*playerMissileYLocations - enemyPos.y) < 1)
				{
					printf("Player Hit Enemy\n");
					_enemies[index].SetIsAliveFlag(false);
					_enemies[index].ResetMissiles();
					_enemySpawnInterval -= 0.02;
					_playerScore += 5;
					return 1;
				}
			}
		}
		//printf("Pos X: %f\n", *playerMissileXLocations);
		//printf("Pos Y: %f\n", *playerMissileYLocations);
		playerMissileXLocations++;
		playerMissileYLocations++;
	}
	return 0;
}