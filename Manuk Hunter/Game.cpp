#include "Game.h"

//private functions
void Game::initVariables()
{
	this->window = nullptr;

	//Game logic
	//attributes
	this->maxEnemies = 5;
	this->maxItems = 2;
	this->maxAmmo = 10;
	this->bulletSpeed = 10.f;
	this->highscores = 0;
	this->birdsShot = 0;
	this->bulletsShot = 0;
	this->shotsMissed = 0;

	//conditions
	this->endGame = false;
	this->mainMenu = true;
	this->pauseGame = false;
	this->mouseHeld = false;
	this->LOSE = false;
	this->tutorial = false;
	this->stats = false;
	this->credits = false;
	this->inMenu = false;
	this->musicOff = false;

	//timer
	this->enemySpawnTimerMax = 80.f;
	this->itemTimerMax = 500.f;
	this->diffTimerMax = 200.f;

	this->f_handler.open("manukhunter_data.bin", std::ios::in | std::ios::binary);
	if (this->f_handler.is_open()) {
		f_handler.read((char*)&this->highscores, sizeof(highscores));
		f_handler.read((char*)&this->birdsShot, sizeof(birdsShot));
		f_handler.read((char*)&this->bulletsShot, sizeof(bulletsShot));
		f_handler.read((char*)&this->shotsMissed, sizeof(shotsMissed));
	}
	else if (!f_handler.is_open()) {
		std::cout << "ERROR reading \"manukhunter_data.bin\"!" << std::endl;
		std::cout << "First time running the game?" << std::endl;
	}
	this->f_handler.close();
}
void Game::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(1000, 600), "Manuk Hunter", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
	this->window->setVerticalSyncEnabled(false);
}
void Game::initFonts()
{
	this->font.loadFromFile("Fonts/angrybirds-regular.ttf");
}
void Game::initText()
{
	//score text
	this->scoreText.setFont(this->font);
	this->scoreText.setCharacterSize(20);
	this->scoreText.setFillColor(sf::Color::Cyan);
	this->scoreText.setOutlineColor(sf::Color::Black);
	this->scoreText.setOutlineThickness(3.f);
	this->scoreText.setPosition(sf::Vector2f(193.f, 485.f));

	//score text update
	this->scoreTextUpdate.setFont(this->font);
	this->scoreTextUpdate.setCharacterSize(42);
	this->scoreTextUpdate.setFillColor(sf::Color::White);
	this->scoreTextUpdate.setOutlineColor(sf::Color::Black);
	this->scoreTextUpdate.setOutlineThickness(3.f);

	//ammo text
	this->ammoText.setFont(this->font);
	this->ammoText.setCharacterSize(70);
	this->ammoText.setFillColor(sf::Color::Green);
	this->ammoText.setOutlineColor(sf::Color::Black);
	this->ammoText.setOutlineThickness(3.f);

	//birdshot text
	this->birdShotText.setFont(this->font);
	this->birdShotText.setCharacterSize(50);
	this->birdShotText.setFillColor(sf::Color::White);
	this->birdShotText.setOutlineColor(sf::Color::Black);
	this->birdShotText.setOutlineThickness(3.f);
	this->birdShotText.setPosition(sf::Vector2f(430.f, 23.f));

	//maxammo text
	this->maxAmmoText.setFont(this->font);
	this->maxAmmoText.setCharacterSize(24);
	this->maxAmmoText.setFillColor(sf::Color::Yellow);
	this->maxAmmoText.setOutlineColor(sf::Color::Black);
	this->maxAmmoText.setOutlineThickness(3.f);
	this->maxAmmoText.setPosition(sf::Vector2f(763.f, 405.f));

	//slowed text
	this->slowedText.setFont(this->font);
	this->slowedText.setCharacterSize(24);
	this->slowedText.setFillColor(sf::Color::Green);
	this->slowedText.setOutlineColor(sf::Color::Black);
	this->slowedText.setOutlineThickness(3.f);
	this->slowedText.setPosition(343.f, this->window->getSize().y / 2 - 40.f);

	//flash mode text
	this->flashModeText.setFont(this->font);
	this->flashModeText.setCharacterSize(24);
	this->flashModeText.setFillColor(sf::Color::Yellow);
	this->flashModeText.setOutlineColor(sf::Color::Black);
	this->flashModeText.setOutlineThickness(3.f);
	this->flashModeText.setPosition(380.f, this->window->getSize().y / 2 - 40.f);

	//increased difficulties text
	this->diffText.setFont(this->font);
	this->diffText.setCharacterSize(24);
	this->diffText.setFillColor(sf::Color::Red);
	this->diffText.setOutlineColor(sf::Color::Black);
	this->diffText.setOutlineThickness(3.f);
	this->diffText.setPosition(380.f, this->window->getSize().y / 2 - 70.f);
}
void Game::initPlayer()
{
	this->player = new Player();
}
void Game::initBulletTextures()
{
	this->textures["BULLET"] = new sf::Texture();
	this->textures["BULLET"]->loadFromFile("Textures/Game/Player/bullet.png");
}
void Game::initBackgroundWallpaper()
{
	this->backgroundWallpaperTexture.loadFromFile("Textures/Game/Background/background.jpeg");
	this->backgroundWallpaper.setTexture(this->backgroundWallpaperTexture);
	this->backgroundWallpaper.scale(0.725f, 0.732f);
}
void Game::initScoreBoard()
{
	//score board
	this->scoreBoardTexture.loadFromFile("Textures/Game/Boards/score_board.png");
	this->scoreBoardSprite.setTexture(this->scoreBoardTexture);
	this->scoreBoardSprite.scale(0.2f, 0.2f);
	this->scoreBoardSprite.setPosition(sf::Vector2f(130.f, 475.f));

	//ammo board
	this->ammoBoardTexture.loadFromFile("Textures/Game/Boards/ammo_board.png");
	this->ammoBoardSprite.setTexture(this->ammoBoardTexture);
	this->ammoBoardSprite.scale(0.2f, 0.2f);
	this->ammoBoardSprite.setPosition(sf::Vector2f(700.f, 435.f));

	//enemy shot board
	this->enemyBoardTexture.loadFromFile("Textures/Game/Boards/enemy_board.png");
	this->enemyBoardSprite.setTexture(this->enemyBoardTexture);
	this->enemyBoardSprite.scale(0.4f, 0.2f);
	this->enemyBoardSprite.setPosition(sf::Vector2f(375.f, -50.f));

	//bird shot symbol
	this->birdShotTexture.loadFromFile("Textures/Game/Boards/bird_shot.png");
	this->birdShotSprite.setTexture(this->birdShotTexture);
	this->birdShotSprite.scale(0.06f, 0.05f);
	this->birdShotSprite.setPosition(sf::Vector2f(505.f, 35.f));

	//ammo symbol
	this->ammoTexture.loadFromFile("Textures/Game/Boards/ammo_symbol.png");
	this->ammoSprite.setTexture(this->ammoTexture);
	this->ammoSprite.scale(0.04f, 0.04f);
	this->ammoSprite.setPosition(sf::Vector2f(768.f, 445.f));

	//pause button
	this->pauseButtonTexture.loadFromFile("Textures/Game/Boards/pause.png");
	this->pauseButtonSprite.setTexture(this->pauseButtonTexture);
	this->pauseButtonSprite.scale(0.5f, 0.5f);
	this->pauseButtonSprite.setPosition(sf::Vector2f(930.f, 10.f));

	//question button
	this->questionButtonTexture.loadFromFile("Textures/Game/Boards/faq.png");
	this->questionButtonSprite.setTexture(this->questionButtonTexture);
	this->questionButtonSprite.scale(0.3f, 0.3f);
	this->questionButtonSprite.setPosition(sf::Vector2f(10.f, 10.f));
}
void Game::initMainMenu()
{
	//play button
	this->playButtonTexture.loadFromFile("Textures/Main Menu/Buttons/play.png");
	this->playButtonSprite.setTexture(this->playButtonTexture);
	this->playButtonSprite.scale(0.22f, 0.22f);
	this->playButtonSprite.setPosition(sf::Vector2f(380.f, this->window->getSize().y / 2 + 100.f));

	//exit button
	this->exitButtonTexture.loadFromFile("Textures/Main Menu/Buttons/exit.png");
	this->exitButtonSprite.setTexture(this->exitButtonTexture);
	this->exitButtonSprite.scale(0.5f, 0.5f);
	this->exitButtonSprite.setPosition(sf::Vector2f(500.f, this->window->getSize().y / 2 + 100.f));

	//music button
	this->musicButtonTexture.loadFromFile("Textures/Main Menu/Buttons/music.png");
	this->musicButtonSprite.setTexture(this->musicButtonTexture);
	this->musicButtonSprite.scale(0.37f, 0.37f);
	this->musicButtonSprite.setPosition(sf::Vector2f(10.f, this->window->getSize().y - 85.f));

	//info button
	this->infoButtonTexture.loadFromFile("Textures/Main Menu/Buttons/info.png");
	this->infoButtonSprite.setTexture(this->infoButtonTexture);
	this->infoButtonSprite.scale(0.25f, 0.25f);
	this->infoButtonSprite.setPosition(sf::Vector2f(10.f, 10.f));

	//stats button
	this->statsButtonTexture.loadFromFile("Textures/Main Menu/Buttons/stats.png");
	this->statsButtonSprite.setTexture(this->statsButtonTexture);
	this->statsButtonSprite.scale(0.26f, 0.26f);
	this->statsButtonSprite.setPosition(sf::Vector2f(this->window->getSize().x - 85.f, this->window->getSize().y - 85.f));

	//tutorial button
	this->tutorialButtonTexture.loadFromFile("Textures/Main Menu/Buttons/faq.png");
	this->tutorialButtonSprite.setTexture(this->tutorialButtonTexture);
	this->tutorialButtonSprite.scale(0.35f, 0.35f);
	this->tutorialButtonSprite.setPosition(sf::Vector2f(this->window->getSize().x - 85.f, 10.f));

	//MANUK HUNTER
	this->manukHunterTexture.loadFromFile("Textures/Main Menu/Manuk Hunter/manuk_hunter.png");
	this->manukHunterSprite.setTexture(this->manukHunterTexture);
	this->manukHunterSprite.scale(0.45f, 0.45f);
	this->manukHunterSprite.setPosition(sf::Vector2f(190.f, 60.f));
}
void Game::initPauseScene()
{
	//pause scene
	this->pauseSceneTexture.loadFromFile("Textures/Game/Pause/pause.png");
	this->pauseSceneTexture.setSmooth(true);
	this->pauseSceneSprite.setTexture(this->pauseSceneTexture);
	this->pauseSceneSprite.scale(0.35f, 0.35f);
	this->pauseSceneSprite.setPosition(sf::Vector2f(320.f, 130.f));

	//resume button
	this->resumeButtonTexture.loadFromFile("Textures/Game/Pause/ok.png");
	this->resumeButtonSprite.setTexture(this->resumeButtonTexture);
	this->resumeButtonSprite.scale(0.35f, 0.35f);
	this->resumeButtonSprite.setPosition(sf::Vector2f(this->window->getSize().x / 2 - 90.f, this->window->getSize().y / 2 + 95.f));

	//menu button
	this->menuButtonTexture.loadFromFile("Textures/Game/Pause/menu.png");
	this->menuButtonSprite.setTexture(this->menuButtonTexture);
	this->menuButtonSprite.scale(0.35f, 0.35f);
	this->menuButtonSprite.setPosition(sf::Vector2f(this->window->getSize().x / 2, this->window->getSize().y / 2 + 95.f));
}
void Game::initLoseScene()
{
	//lose scene
	this->loseSceneTexture.loadFromFile("Textures/Game/Lose/lose.png");
	this->loseSceneTexture.setSmooth(true);
	this->loseSceneSprite.setTexture(this->loseSceneTexture);
	this->loseSceneSprite.scale(0.35f, 0.35f);
	this->loseSceneSprite.setPosition(sf::Vector2f(320.f, 45.f));

	//restart button
	this->restartButtonTexture.loadFromFile("Textures/Game/Lose/restart.png");
	this->restartButtonSprite.setTexture(this->restartButtonTexture);
	this->restartButtonSprite.scale(0.35f, 0.35f);
	this->restartButtonSprite.setPosition(sf::Vector2f(this->window->getSize().x / 2 - 90.f, this->window->getSize().y / 2 + 155.f));

	//menu button
	this->menuLoseButtonTexture.loadFromFile("Textures/Game/Lose/menu.png");
	this->menuLoseButtonSprite.setTexture(this->menuLoseButtonTexture);
	this->menuLoseButtonSprite.scale(0.35f, 0.35f);
	this->menuLoseButtonSprite.setPosition(sf::Vector2f(this->window->getSize().x / 2, this->window->getSize().y / 2 + 155.f));

	//lose score text
	this->scoreLoseText.setFont(this->font);
	this->scoreLoseText.setCharacterSize(55);
	this->scoreLoseText.setFillColor(sf::Color::Yellow);
	this->scoreLoseText.setOutlineColor(sf::Color::Black);
	this->scoreLoseText.setOutlineThickness(3.f);

	//lose highscore text
	this->highscoreLoseText.setFont(this->font);
	this->highscoreLoseText.setCharacterSize(40);
	this->highscoreLoseText.setFillColor(sf::Color::Cyan);
	this->highscoreLoseText.setOutlineColor(sf::Color::Black);
	this->highscoreLoseText.setOutlineThickness(3.f);
}
void Game::initTutorial()
{
	//tutorial
	this->tutorialTexture.loadFromFile("Textures/Main Menu/Tutorial/tutorial.png");
	this->tutorialTexture.setSmooth(true);
	this->tutorialSprite.setTexture(this->tutorialTexture);
	this->tutorialSprite.scale(0.521f, 0.5551f);

	//close button
	this->closeButtonTutorialTexture.loadFromFile("Textures/Main Menu/Tutorial/close.png");
	this->closeButtonTutorialSprite.setTexture(this->closeButtonTutorialTexture);
	this->closeButtonTutorialSprite.scale(0.5f, 0.5f);
	this->closeButtonTutorialSprite.setPosition(sf::Vector2f(460.f, 380.f));
}
void Game::initStats()
{
	//stats
	this->statsTexture.loadFromFile("Textures/Main Menu/Stats/stats.png");
	this->statsTexture.setSmooth(true);
	this->statsSprite.setTexture(this->statsTexture);
	this->statsSprite.scale(0.38f, 0.38f);
	this->statsSprite.setPosition(sf::Vector2f(300.f, 20.f));

	//close button
	this->closeButtonStatsTexture.loadFromFile("Textures/Main Menu/Stats/close.png");
	this->closeButtonStatsSprite.setTexture(this->closeButtonStatsTexture);
	this->closeButtonStatsSprite.scale(0.4f, 0.4f);
	this->closeButtonStatsSprite.setPosition(sf::Vector2f(630.f, 55.f));

	//highscore text
	this->highscoreStatsText.setFont(this->font);
	this->highscoreStatsText.setCharacterSize(37);
	this->highscoreStatsText.setFillColor(sf::Color::Yellow);
	this->highscoreStatsText.setOutlineColor(sf::Color::Black);
	this->highscoreStatsText.setOutlineThickness(3.f);
	this->highscoreStatsText.setPosition(sf::Vector2f(370.f, 208.f));

	//birds shot text
	this->birdsShotStatsText.setFont(this->font);
	this->birdsShotStatsText.setCharacterSize(37);
	this->birdsShotStatsText.setFillColor(sf::Color(255, 128, 0));
	this->birdsShotStatsText.setOutlineColor(sf::Color::Black);
	this->birdsShotStatsText.setOutlineThickness(3.f);
	this->birdsShotStatsText.setPosition(sf::Vector2f(370.f, 290.f));

	//bullets shot text
	this->bulletsShotStatsText.setFont(this->font);
	this->bulletsShotStatsText.setCharacterSize(37);
	this->bulletsShotStatsText.setFillColor(sf::Color::Green);
	this->bulletsShotStatsText.setOutlineColor(sf::Color::Black);
	this->bulletsShotStatsText.setOutlineThickness(3.f);
	this->bulletsShotStatsText.setPosition(sf::Vector2f(370.f, 375.f));

	//shots missed text
	this->shotsMissedStatsText.setFont(this->font);
	this->shotsMissedStatsText.setCharacterSize(37);
	this->shotsMissedStatsText.setFillColor(sf::Color::Red);
	this->shotsMissedStatsText.setOutlineColor(sf::Color::Black);
	this->shotsMissedStatsText.setOutlineThickness(3.f);
	this->shotsMissedStatsText.setPosition(sf::Vector2f(370.f, 455.f));
}
void Game::initAbout()
{
	//about
	this->aboutTexture.loadFromFile("Textures/Main Menu/About/about.png");
	//this->aboutTexture.setSmooth(true);
	this->aboutSprite.setTexture(this->aboutTexture);
	this->aboutSprite.scale(0.578f, 0.52f);

	//close button
	this->closeButtonAboutTexture.loadFromFile("Textures/Main Menu/About/close.png");
	this->closeButtonAboutSprite.setTexture(this->closeButtonAboutTexture);
	this->closeButtonAboutSprite.scale(0.4f, 0.4f);
	this->closeButtonAboutSprite.setPosition(sf::Vector2f(this->window->getSize().x - 100.f, 35.f));
}
void Game::initFirstGameVariables()
{
	//reset all
	this->scores = 0;
	this->scoresTemp = 0;
	this->birdShot = 0;
	this->ammo = 5;

	this->enemySpawnTimer = this->enemySpawnTimerMax;
	this->itemSpawnTimer = 500.f;
	this->virusSpawnTimer = 0.f;
	this->itemTimer = 0.f;
	this->virusSpawnTimerMax = 700.f;
	this->itemSpawnTimerMax = 1000.f;
	this->diffTimer = 0.f;
	this->shootAnimationCounter = 0;
	this->maxAnimationShoot = 7;
	this->goneAnimationCounter = 0;
	this->maxAnimationGone = 3;

	this->fireSpeedDown = false;
	this->fireSpeedUp = false;
	this->donePlaying = false;
	this->updateDiff = false;
	this->updateDiffText = false;
	this->shoot = false;
	this->birdDied = false;

	this->player->setSpawnPoint();
	this->player->setAttackCooldown(0.f);
}
void Game::initSoundEffects()
{
	//background music
	this->backgroundMusic.openFromFile("Sounds/background_music.ogg");
	this->backgroundMusic.setLoop(true);

	//button pressed sound
	this->buttonPressedBuffer.loadFromFile("Sounds/button_pressed.ogg");
	this->buttonPressedSound.setBuffer(this->buttonPressedBuffer);

	//shooting sound
	this->shootBuffer.loadFromFile("Sounds/shoot.ogg");
	this->shootSound.setBuffer(this->shootBuffer);
	this->shootSound.setVolume(50);

	//shooting sound
	this->eagleBuffer.loadFromFile("Sounds/eagle.ogg");
	this->eagleSound.setBuffer(this->eagleBuffer);

	//reg enemy died
	this->regEnemyBuffer.loadFromFile("Sounds/regular_enemy.ogg");
	this->regEnemySound.setBuffer(this->regEnemyBuffer);

	//fat enemy died
	this->fatEnemyBuffer.loadFromFile("Sounds/fat_enemy.ogg");
	this->fatEnemySound.setBuffer(this->fatEnemyBuffer);

	//fast enemy died
	this->fastEnemyBuffer.loadFromFile("Sounds/fast_enemy.ogg");
	this->fastEnemySound.setBuffer(this->fastEnemyBuffer);

	//item fire speed up
	this->itemUpBuffer.loadFromFile("Sounds/up.ogg");
	this->itemUpSound.setBuffer(this->itemUpBuffer);

	//item ammo
	this->itemAmmoBuffer.loadFromFile("Sounds/ammo.ogg");
	this->itemAmmoSound.setBuffer(this->itemAmmoBuffer);

	//hit by virus
	this->virusBuffer.loadFromFile("Sounds/cough.ogg");
	this->virusSound.setBuffer(this->virusBuffer);

	//lost
	this->loseBuffer.loadFromFile("Sounds/lose.ogg");
	this->loseSound.setBuffer(this->loseBuffer);
}
void Game::initAnimation()
{
	//shoot animation
	this->shootTexture.loadFromFile("Animation/shoot_animation.png");
	this->shootTexture.setSmooth(true);
	this->shootSprite.setTexture(this->shootTexture);
	this->shootSprite.setScale(0.3f, 0.3f);

	//bird died
	this->goneTexture.loadFromFile("Animation/bird_died.png");
	this->goneTexture.setSmooth(true);
	this->goneSprite.setTexture(this->goneTexture);
	this->goneSprite.setScale(0.7f, 0.7f);

	this->intRectShoot.left = 0;
	this->intRectShoot.top = 0;
	this->intRectShoot.width = 150.f;
	this->intRectShoot.height = 149.f;
	this->shootMaxSize = 900.f;

	this->intRectGone.left = 0;
	this->intRectGone.top = 0;
	this->intRectGone.width = 148.67f;
	this->intRectGone.height = 142.f;
	this->goneMaxSize = 297.33f;
}

//const
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
	this->initBackgroundWallpaper();
	this->initBulletTextures();
	this->initPlayer();
	this->initScoreBoard();
	this->initMainMenu();
	this->initPauseScene();
	this->initLoseScene();
	this->initTutorial();
	this->initStats();
	this->initAbout();
	this->initSoundEffects();
	this->initAnimation();
}
Game::~Game()
{
	delete this->window;
	delete this->player;

	//delete textures
	for (auto &i : this->textures)
	{
		delete i.second;
	}

	//delete bullets
	this->bullets.clear();

	//delete enemies
	this->enemy.clear();

	//delete items
	this->item.clear();
}

//accessors
const bool Game::running() const
{
	return this->window->isOpen();
}
const bool Game::getEndGame() const
{
	return this->endGame;
}

//functions
void Game::run()
{
	if (this->musicOff == false) {
		this->backgroundMusic.play();
	}
	while (this->window->isOpen()) {
		this->update();
		this->render();
	}

	std::cout << "Thank you for playing MANUK HUNTER!\n";
	std::cout << "Have a nice day.\n\n";

	std::cout << "Copyright (c) 2020 Manuk Hunter Developer Team\n";
}
void Game::spawnEnemy()
{
	//Randomize enemy type
	int type = rand() % 3;
	Enemy* temp = new Enemy;
	if (type == 0) {
		temp = new RegularEnemy;
		temp->setSpawnPoint(*this->window, -60.f, 300.f);
	}
	if (type == 1) {
		temp = new FatEnemy;
		temp->setSpawnPoint(*this->window, -250.f, 400.f);
	}
	if (type == 2) {
		temp = new FastEnemy;
		temp->setSpawnPoint(*this->window, -250.f, 400.f);

		if (this->musicOff == false) {
			this->eagleSound.play();
		}
	}

	//spawn the enemy
	this->enemy.push_back(temp);
}
void Game::spawnItem()
{
	//Randomize item type
	int type = rand() % 2;
	Item* temp = new Item;
	if (type == 0) {
		temp = new FireSpeedUpItem;
		temp->setSpawnPoint(*this->window, -60.f, 500.f);
	}
	if (type == 1) {
		temp = new AmmoUpItem;
		temp->setSpawnPoint(*this->window, -60.f, 500.f);
	}

	//spawn the item
	this->item.push_back(temp);
}
void Game::spawnVirus()
{
	Item* temp = new Item;
	temp = new FireSpeedDownItem;
	temp->setSpawnPoint(*this->window, 100.f, -70.f);

	//spawn the virus
	this->item.push_back(temp);
}
void Game::pollEvents()
{
	//Event polling
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape) {
				if (this->mainMenu == true) {
					this->window->close();
				}
				if (this->pauseGame == false) {
					this->pauseGame = true;
				}
				else {
					this->pauseGame = false;
					this->backgroundMusic.play();
				}
			}
			break;
		}
	}
}

void Game::updateInput()
{
	//add new bullet
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->player->canAttack() && !this->pauseButtonSprite.getGlobalBounds().contains(this->mousePosView) && !this->questionButtonSprite.getGlobalBounds().contains(this->mousePosView) && this->ammo > 0) {
		this->playerCenter = sf::Vector2f(this->player->getPos().x, this->player->getPos().y);
		this->mousePosWindow = sf::Vector2f(sf::Mouse::getPosition(*this->window));
		this->aimDir = mousePosWindow - playerCenter;
		this->aimDirNormalize = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

		this->bullets.push_back(new Bullet(this->textures["BULLET"], this->player->getPos().x + 1.f, this->player->getPos().y, this->aimDirNormalize * this->bulletSpeed));

		//reduce ammo
		this->ammo -= 1;
		this->bulletsShot += 1;

		if (this->musicOff == false) {
			this->shootSound.play();
		}
		this->shoot = true;
	}

	//move player
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		this->player->move(-1.f, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		this->player->move(1.f, 0.f);
	}
}
void Game::updateBullets()
{
	unsigned counter = 0;
	for (auto* i : this->bullets) {
		i->update();

		//bullet outside the screen
		if (i->getBounds().top < 0.f || //atas
			i->getBounds().top > this->window->getSize().y || //bawah
			i->getBounds().left < 0.f || //kiri
			i->getBounds().left > this->window->getSize().x) { //kanan
			this->bullets.erase(this->bullets.begin() + counter);
			this->shotsMissed += 1;
			--counter;
		}
		++counter;
	}
}
void Game::updateText()
{
	std::stringstream score;
	score << "SCORES";
	this->scoreText.setString(score.str());

	if (this->scores < 0) {
		this->scores = 0;
	}

	std::stringstream scoreupdate;
	scoreupdate << this->scores;
	this->scoreTextUpdate.setString(scoreupdate.str());

	if (this->scores > 9 && this->scores < 100) {
		this->scoreTextUpdate.setPosition(sf::Vector2f(200.f, 510.f));
	}
	else if (this->scores > 99 && this->scores < 1000) {
		this->scoreTextUpdate.setPosition(sf::Vector2f(190.f, 510.f));
	}
	else if (this->scores > 999 && this->scores < 10000) {
		this->scoreTextUpdate.setPosition(sf::Vector2f(180.f, 510.f));
	}
	else if (this->scores > 9999) {
		this->scoreTextUpdate.setPosition(sf::Vector2f(170.f, 510.f));
	}
	else {
		this->scoreTextUpdate.setPosition(sf::Vector2f(210.f, 510.f));
	}

	if (this->ammo > this->maxAmmo) {
		this->ammo = this->maxAmmo;
	}

	std::stringstream ammo;
	ammo << this->ammo;
	this->ammoText.setString(ammo.str());

	if (this->ammo < 3) {
		this->ammoText.setFillColor(sf::Color::Red);
	}
	else if (this->ammo > 2 && this->ammo < 5) {
		this->ammoText.setFillColor(sf::Color::Yellow);
	}
	else if (this->ammo == 10) {
		this->ammoText.setFillColor(sf::Color::Blue);

		std::stringstream maxammo;
		maxammo << "FULL!";
		this->maxAmmoText.setString(maxammo.str());
	}
	else {
		this->ammoText.setFillColor(sf::Color::Green);

		std::stringstream maxammo;
		maxammo << "";
		this->maxAmmoText.setString(maxammo.str());
	}
	if (this->ammo > 9) {
		this->ammoText.setPosition(sf::Vector2f(750.f, 490.f));
	}
	else {
		this->ammoText.setPosition(sf::Vector2f(770.f, 490.f));
	}

	std::stringstream birdshot;
	birdshot << this->birdShot;
	this->birdShotText.setString(birdshot.str());

	if (this->fireSpeedDown == true) {
		std::stringstream slowed;
		slowed << "YOU ARE SLOWED BY THE VIRUS!";
		this->slowedText.setString(slowed.str());
	}
	else {
		std::stringstream slowed;
		slowed << "";
		this->slowedText.setString(slowed.str());
	}

	if (this->fireSpeedUp == true) {
		std::stringstream flash;
		flash << "YOU ARE IN FLASH MODE!";
		this->flashModeText.setString(flash.str());
	}
	else {
		std::stringstream flash;
		flash << "";
		this->flashModeText.setString(flash.str());
	}

	if (this->updateDiff == false && this->scores >= 150 && this->scores < 350 ||
		this->updateDiff == true && this->scores >= 350 && this->scores < 550 ||
		this->updateDiff == false && this->scores >= 550 && this->scores < 800 ||
		this->updateDiff == true && this->scores >= 800) {
			this->updateDiffText = true;	
	}
	if (this->updateDiffText == true) {
		if (this->diffTimer >= this->diffTimerMax) {
			this->diffTimer = 0;
			this->updateDiffText = false;
		}
		else {
			this->diffTimer += 1.f;

			std::stringstream diff;
			diff << "DIFFICULTIES INCREASED!";
			this->diffText.setString(diff.str());
		}
	}
	else {
		std::stringstream diff;
		diff << "";
		this->diffText.setString(diff.str());
	}
}
void Game::updateEnemies()
{
	//updating timer every spawning
	if (this->enemy.size() < this->maxEnemies) {
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) {
			this->spawnEnemy();

			//reset the timer
			this->enemySpawnTimer = 0.f;
		}
		else {
			this->enemySpawnTimer += 1.f;
		}
	}

	//moving and updating the enemies
	for (int i = 0; i < this->enemy.size(); i++)
	{
		this->enemy[i]->move(1.f, 0.f);

		//if the enemy is past the edge of the screen
		if (this->enemy[i]->getPos().x > this->window->getSize().x) {
			this->enemy.erase(this->enemy.begin() + i);
		}
	}

	//bullet collission
	for (int i = 0; i < this->enemy.size(); i++)
	{
		for (int j = 0; j < this->bullets.size(); j++)
		{
			if (this->bullets[j]->getBounds().intersects(this->enemy[i]->getBounds())) {
				//delete the enemy if health <= 0
				this->enemy[i]->setHealth(this->enemy[i]->getHealth() - 1);

				if (this->enemy[i]->getHealth() < 3 && this->enemy[i]->getType() == "Fat") {
					if (this->enemy[i]->getHealth() == 2) {
						this->enemy[i]->setTexture("Textures/Game/Enemies/fat_enemy2.png");
						this->enemy[i]->setSprite(1.f, 1.f);
					}
					else if (this->enemy[i]->getHealth() == 1) {
						this->enemy[i]->setTexture("Textures/Game/Enemies/fat_enemy3.png");
						this->enemy[i]->setSprite(1.f, 1.f);
					}
				}

				if (this->enemy[i]->getHealth() <= 0) {
					//scores
					if (this->enemy[i]->getType() == "Regular") {
						this->scores += 10;
						this->ammo += 1;

						if (this->musicOff == false) {
							this->regEnemySound.play();
						}
					}
					else if (this->enemy[i]->getType() == "Fat") {
						this->scores += 20;
						this->ammo += 4;

						if (this->musicOff == false) {
							this->fatEnemySound.play();
						}
					}
					else if (this->enemy[i]->getType() == "Fast") {
						this->scores += 35;
						this->ammo += 1;

						if (this->musicOff == false) {
							this->fastEnemySound.play();
						}
					}

					this->goneSprite.setPosition(this->enemy[i]->getPos().x + 10.f, this->enemy[i]->getPos().y);
					this->birdDied = true;

					this->enemy.erase(this->enemy.begin() + i);
					this->birdShot += 1;
					this->birdsShot += 1;
				}

				//delete bullet
				this->bullets.erase(this->bullets.begin() + j);
			}
		}
	}
}
void Game::updateItems()
{
	//updating timer every spawning
	if (this->item.size() < this->maxItems) {
		if (this->itemSpawnTimer >= this->itemSpawnTimerMax) {
			this->spawnItem();

			//reset the timer
			this->itemSpawnTimer = 0.f;
		}
		else {
			this->itemSpawnTimer += 1.f;
		}
	}
	if (this->item.size() < this->maxItems) {
		if (this->virusSpawnTimer >= this->virusSpawnTimerMax) {
			this->spawnVirus();

			//reset the timer
			this->virusSpawnTimer = 0.f;
		}
		else {
			this->virusSpawnTimer += 1.f;
		}
	}

	//moving and updating the items
	for (int i = 0; i < this->item.size(); i++)
	{
		if (this->item[i]->getType() == "FireSpeedDown") {
			this->playerCenter = sf::Vector2f(this->player->getPos().x, this->player->getPos().y);
			this->itemPosWindow = sf::Vector2f(this->item[i]->getPos().x, this->item[i]->getPos().y);
			this->aimDir = playerCenter - itemPosWindow;
			this->aimDirNormalize = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

			this->item[i]->update(aimDirNormalize * 2.f);

			//if virus hits player
			if (this->item[i]->getBounds().intersects(this->player->getBounds())) {
				this->item.erase(this->item.begin() + i);
				this->fireSpeedDown = true;
				if (this->fireSpeedUp == true) {
					this->fireSpeedUp = false;
				}
				this->itemTimer = 0.f;
				this->scores -= 5;
				this->ammo -= 1;

				if (this->musicOff == false) {
					this->virusSound.play();
				}

				this->backgroundWallpaperTexture.loadFromFile("Textures/Game/Background/illusion.jpg");
				this->backgroundWallpaper.setTexture(this->backgroundWallpaperTexture);
			}
		}
		else {
			if (this->item[i]->getMoveTimer() >= this->item[i]->getMoveTimerMax()) {
				//reset the timer
				this->item[i]->setMoveTimer(0.f);

				if (this->item[i]->getCounter() == false) {
					this->item[i]->setCounter(true);
				}
				else {
					this->item[i]->setCounter(false);
				}
			}
			else {
				//zig-zag
				if (this->item[i]->getCounter() == false) {
					this->item[i]->move(1.f, 1.f);
				}
				else {
					this->item[i]->move(1.f, -1.f);
				}

				this->item[i]->setMoveTimer(this->item[i]->getMoveTimer() + 1.f);
			}

			//if the item is past the edge of the screen
			if (this->item[i]->getPos().x > this->window->getSize().x) {
				this->item.erase(this->item.begin() + i);
			}
		}

	}

	//collission
	for (int i = 0; i < this->item.size(); i++)
	{
		for (int j = 0; j < this->bullets.size(); j++)
		{
			//if bullet hits item
			if (this->bullets[j]->getBounds().intersects(this->item[i]->getBounds())) {
				if (this->item[i]->getType() == "FireSpeedUp") {
					this->fireSpeedUp = true;
					if (this->fireSpeedDown == true) {
						this->fireSpeedDown = false;

						this->backgroundWallpaperTexture.loadFromFile("Textures/Game/Background/background.jpeg");
						this->backgroundWallpaper.setTexture(this->backgroundWallpaperTexture);
					}
					this->itemTimer = 0.f;

					if (this->musicOff == false) {
						this->itemUpSound.play();
					}
				}
				else if (this->item[i]->getType() == "AmmoUp") {
					this->ammo += 3;

					if (this->musicOff == false) {
						this->itemAmmoSound.play();
					}
				}
				else if (this->item[i]->getType() == "FireSpeedDown") {
					this->scores += 5;

					this->goneSprite.setPosition(this->item[i]->getPos().x, this->item[i]->getPos().y);
					this->birdDied = true;
				}

				//delete bullet and item (kalau kena virus tetap tembus)
				if (this->item[i]->getType() != "FireSpeedDown") {
					this->bullets.erase(this->bullets.begin() + j);
				}
				this->item.erase(this->item.begin() + i);
			}
		}
	}
}
void Game::updatePlayerConditions()
{
	if (this->fireSpeedDown == true || this->fireSpeedUp == true) {
		if (this->fireSpeedDown == true && this->fireSpeedUp == false) {
			this->bulletSpeed = 5.f;
			this->player->setAttackCooldownMax(30.f);
			this->player->setMovementSpeed(1.f);
		}
		else if (this->fireSpeedUp == true && this->fireSpeedDown == false) {
			this->bulletSpeed = 10.f;
			this->player->setAttackCooldownMax(20.f);
			this->player->setMovementSpeed(3.f);
		}

		if (this->itemTimer >= this->itemTimerMax) {
			this->bulletSpeed = 10.f;
			this->player->setAttackCooldownMax(30.f);
			this->player->setMovementSpeed(3.f);

			//reset the timer
			this->itemTimer = 0.f;

			this->backgroundWallpaperTexture.loadFromFile("Textures/Game/Background/background.jpeg");
			this->backgroundWallpaper.setTexture(this->backgroundWallpaperTexture);

			this->fireSpeedDown = false;
			this->fireSpeedUp = false;
		}
		else {
			this->itemTimer += 1.f;
		}
	}
	else {
		this->bulletSpeed = 10.f;
		this->player->setAttackCooldownMax(30.f);
		this->player->setMovementSpeed(3.f);
	}
}
void Game::updateMainMenu()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->mouseHeld == false) {
			this->mouseHeld = true;

			if (this->playButtonSprite.getGlobalBounds().contains(this->mousePosView)) {
				this->mainMenu = false;
				this->initFirstGameVariables();

				enemy.clear();
				item.clear();

				if (this->musicOff == false) {
					this->buttonPressedSound.play();
				}
			}
			if (this->exitButtonSprite.getGlobalBounds().contains(this->mousePosView)) {
				this->endGame = true;
				this->window->close();

				if (this->musicOff == false) {
					this->buttonPressedSound.play();
				}
			}
			if (this->tutorialButtonSprite.getGlobalBounds().contains(this->mousePosView)) {
				this->mainMenu = false;
				this->tutorial = true;
				this->inMenu = true;

				if (this->musicOff == false) {
					this->buttonPressedSound.play();
				}
			}
			if (this->statsButtonSprite.getGlobalBounds().contains(this->mousePosView)) {
				this->mainMenu = false;
				this->stats = true;
				this->inMenu = true;

				if (this->musicOff == false) {
					this->buttonPressedSound.play();
				}
			}
			if (this->infoButtonSprite.getGlobalBounds().contains(this->mousePosView)) {
				this->mainMenu = false;
				this->credits = true;
				this->inMenu = true;

				if (this->musicOff == false) {
					this->buttonPressedSound.play();
				}
			}
			if (this->musicButtonSprite.getGlobalBounds().contains(this->mousePosView)) {
				if (this->musicOff == false) {
					this->musicButtonTexture.loadFromFile("Textures/Main Menu/Buttons/music_off.png");
					this->musicOff = true;

					this->backgroundMusic.pause();
					this->eagleSound.pause();
				}
				else {
					this->musicButtonTexture.loadFromFile("Textures/Main Menu/Buttons/music.png");
					this->musicOff = false;
					this->backgroundMusic.play();

					if (this->musicOff == false) {
						this->buttonPressedSound.play();
					}
				}
			}
		}
	}
	else {
		this->mouseHeld = false;
	}
}
void Game::updatePauseScene()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->mouseHeld == false) {
			this->mouseHeld = true;

			if (this->resumeButtonSprite.getGlobalBounds().contains(this->mousePosView)) {
				if (this->musicOff == false) {
					this->backgroundMusic.play();
				}
				this->pauseGame = false;

				if (this->musicOff == false) {
					this->buttonPressedSound.play();
				}
			}
			if (this->menuButtonSprite.getGlobalBounds().contains(this->mousePosView)) {
				if (this->musicOff == false) {
					this->backgroundMusic.play();
				}
				this->pauseGame = false;
				this->mainMenu = true;

				enemy.clear();
				item.clear();

				if (this->musicOff == false) {
					this->buttonPressedSound.play();
				}

				this->backgroundWallpaperTexture.loadFromFile("Textures/Game/Background/background.jpeg");
				this->backgroundWallpaper.setTexture(this->backgroundWallpaperTexture);
			}
		}
	}
	else {
		this->mouseHeld = false;
	}
}
void Game::updateLoseScene()
{
	std::stringstream scorelose;
	scorelose << this->scores;
	this->scoreLoseText.setString(scorelose.str());

	std::stringstream highscorelose;
	highscorelose << this->highscores;
	this->highscoreLoseText.setString(highscorelose.str());

	if (this->scores > 9 && this->scores < 100) {
		this->scoreLoseText.setPosition(460.f, this->window->getSize().y / 2 - 20.f);
	}
	else if (this->scores > 99 && this->scores < 1000) {
		this->scoreLoseText.setPosition(450.f, this->window->getSize().y / 2 - 20.f);
	}
	else if (this->scores > 999 && this->scores < 10000) {
		this->scoreLoseText.setPosition(440.f, this->window->getSize().y / 2 - 20.f);
	}
	else if (this->scores > 9999) {
		this->scoreLoseText.setPosition(430.f, this->window->getSize().y / 2 - 20.f);
	}
	else {
		this->scoreLoseText.setPosition(470.f, this->window->getSize().y / 2 - 20.f);
	}

	if (this->highscores > 9 && this->highscores < 100) {
		this->highscoreLoseText.setPosition(475.f, this->window->getSize().y / 2 + 75.f);
	}
	else if (this->highscores > 99 && this->highscores < 1000) {
		this->highscoreLoseText.setPosition(465.f, this->window->getSize().y / 2 + 75.f);
	}
	else if (this->highscores > 999 && this->highscores < 10000) {
		this->highscoreLoseText.setPosition(455.f, this->window->getSize().y / 2 + 75.f);
	}
	else if (this->highscores > 9999) {
		this->highscoreLoseText.setPosition(445.f, this->window->getSize().y / 2 + 75.f);
	}
	else {
		this->highscoreLoseText.setPosition(485.f, this->window->getSize().y / 2 + 75.f);
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->mouseHeld == false) {
			this->mouseHeld = true;

			if (this->restartButtonSprite.getGlobalBounds().contains(this->mousePosView)) {
				this->LOSE = false;
				this->endGame = false;

				enemy.clear();
				item.clear();
				this->initFirstGameVariables();

				if (this->musicOff == false) {
					this->buttonPressedSound.play();
				}

				this->backgroundWallpaperTexture.loadFromFile("Textures/Game/Background/background.jpeg");
				this->backgroundWallpaper.setTexture(this->backgroundWallpaperTexture);
			}
			if (this->menuLoseButtonSprite.getGlobalBounds().contains(this->mousePosView)) {
				this->LOSE = false;
				this->endGame = false;
				this->mainMenu = true;

				enemy.clear();
				item.clear();
				this->initFirstGameVariables();

				if (this->musicOff == false) {
					this->buttonPressedSound.play();
				}

				this->backgroundWallpaperTexture.loadFromFile("Textures/Game/Background/background.jpeg");
				this->backgroundWallpaper.setTexture(this->backgroundWallpaperTexture);
			}
		}
	}
	else {
		this->mouseHeld = false;
	}
}
void Game::updateTutorial()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->mouseHeld == false) {
			this->mouseHeld = true;

			if (this->closeButtonTutorialSprite.getGlobalBounds().contains(this->mousePosView)) {
				this->tutorial = false;
				if (this->inMenu == true) {
					this->mainMenu = true;
					this->inMenu = false;
				}

				if (this->musicOff == false) {
					this->buttonPressedSound.play();
				}
			}
		}
	}
	else {
		this->mouseHeld = false;
	}
}
void Game::updateStats()
{
	std::stringstream hscorestats;
	hscorestats << this->highscores;
	this->highscoreStatsText.setString(hscorestats.str());

	std::stringstream birdsshotstats;
	birdsshotstats << this->birdsShot;
	this->birdsShotStatsText.setString(birdsshotstats.str());

	std::stringstream bulletsshotstats;
	bulletsshotstats << this->bulletsShot;
	this->bulletsShotStatsText.setString(bulletsshotstats.str());

	std::stringstream shotsmissedstats;
	shotsmissedstats << this->shotsMissed;
	this->shotsMissedStatsText.setString(shotsmissedstats.str());

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->mouseHeld == false) {
			this->mouseHeld = true;

			if (this->closeButtonStatsSprite.getGlobalBounds().contains(this->mousePosView)) {
				this->stats = false;
				if (this->inMenu == true) {
					this->mainMenu = true;
					this->inMenu = false;
				}

				if (this->musicOff == false) {
					this->buttonPressedSound.play();
				}
			}
		}
	}
	else {
		this->mouseHeld = false;
	}
}
void Game::updateAbout()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->mouseHeld == false) {
			this->mouseHeld = true;

			if (this->closeButtonAboutSprite.getGlobalBounds().contains(this->mousePosView)) {
				this->credits = false;
				if (this->inMenu == true) {
					this->mainMenu = true;
					this->inMenu = false;
				}

				if (this->musicOff == false) {
					this->buttonPressedSound.play();
				}
			}
		}
	}
	else {
		this->mouseHeld = false;
	}
}
void Game::updateMousePositions()
{
	this->mousePosWindowi = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindowi);
}
void Game::updateInGameButtons()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (this->mouseHeld == false) {
			this->mouseHeld = true;

			if (this->pauseButtonSprite.getGlobalBounds().contains(this->mousePosView)) {
				this->pauseGame = true;

				if (this->musicOff == false) {
					this->buttonPressedSound.play();
				}
			}
			if (this->questionButtonSprite.getGlobalBounds().contains(this->mousePosView)) {
				this->tutorial = true;

				if (this->musicOff == false) {
					this->buttonPressedSound.play();
				}
			}
		}
	}
	else {
		this->mouseHeld = false;
	}
}
void Game::updateGameDifficulties()
{
	if (this->scores >= 150 && this->scores < 350) {
		//increase the enemies movement speed
		for (auto& e : this->enemy) {
			if (e->getType() == "Regular") {
				e->setMovementSpeed(2.5f);
			}
			else if (e->getType() == "Fat") {
				e->setMovementSpeed(2.f);
			}
			else if (e->getType() == "Fast") {
				e->setMovementSpeed(9.f);
			}
		}
		//increase the items movement speed
		for (auto& i : this->item) {
			if (i->getType() == "FireSpeedDown") {
				i->update(aimDirNormalize * 2.25f);
			}
		}
		//decrease virus timer spawn
		this->virusSpawnTimerMax = 600.f;

		if (this->updateDiff == false) {
			this->updateDiff = true;
		}
	}
	else if (this->scores >= 350 && this->scores < 550) {
		//increase the enemies movement speed
		for (auto& e : this->enemy) {
			if (e->getType() == "Regular") {
				e->setMovementSpeed(3.5f);
			}
			else if (e->getType() == "Fat") {
				e->setMovementSpeed(3.f);
			}
			else if (e->getType() == "Fast") {
				e->setMovementSpeed(10.f);
			}
		}
		//increase the items movement speed
		for (auto& i : this->item) {
			if (i->getType() == "FireSpeedDown") {
				i->update(aimDirNormalize * 2.5f);
			}
		}
		//decrease virus timer spawn
		this->virusSpawnTimerMax = 500.f;
		this->itemSpawnTimerMax = 800.f;
		this->maxItems = 3;

		if (this->updateDiff == true) {
			this->updateDiff = false;
		}
	}
	else if (this->scores >= 550 && this->scores < 800) {
		//increase the enemies movement speed
		for (auto& e : this->enemy) {
			if (e->getType() == "Regular") {
				e->setMovementSpeed(4.5f);
			}
			else if (e->getType() == "Fat") {
				e->setMovementSpeed(4.f);
			}
			else if (e->getType() == "Fast") {
				e->setMovementSpeed(11.f);
			}
		}
		//increase the items movement speed
		for (auto& i : this->item) {
			if (i->getType() == "FireSpeedDown") {
				i->update(aimDirNormalize * 2.75f);
			}
		}
		//decrease virus timer spawn
		this->virusSpawnTimerMax = 400.f;

		if (this->updateDiff == false) {
			this->updateDiff = true;
		}
	}
	else if (this->scores >= 800) {
		//increase the enemies movement speed
		for (auto& e : this->enemy) {
			if (e->getType() == "Regular") {
				e->setMovementSpeed(5.5f);
			}
			else if (e->getType() == "Fat") {
				e->setMovementSpeed(5.f);
			}
			else if (e->getType() == "Fast") {
				e->setMovementSpeed(12.f);
			}
		}
		//increase the items movement speed
		for (auto& i : this->item) {
			if (i->getType() == "FireSpeedDown") {
				i->update(aimDirNormalize * 3.f);
			}
		}
		//decrease virus timer spawn
		this->virusSpawnTimerMax = 300;
		this->itemSpawnTimerMax = 600.f;

		if (this->updateDiff == true) {
			this->updateDiff = false;
		}
	}
}
void Game::updateAnimation()
{
	//update shoot animation
	if (this->shoot && this->shootAnimationCounter < this->maxAnimationShoot) {
		if (this->shootClock.getElapsedTime().asSeconds() > 0.05f) {
			if (this->intRectShoot.left >= this->shootMaxSize) {
				this->intRectShoot.left = 0;
			}
			else {
				this->intRectShoot.left += this->intRectShoot.width;
			}
			this->shootSprite.setTextureRect(this->intRectShoot);
			this->shootClock.restart();
			this->shootAnimationCounter++;
		}
		this->shootSprite.setPosition(this->player->getPos().x, this->player->getPos().y - 20.f);
	}
	else if (this->shootAnimationCounter >= 7) {
		this->shootAnimationCounter = 0;
		this->shoot = false;
		this->intRectShoot.left = 0;
	}

	//update bird died animation
	if (this->birdDied && this->goneAnimationCounter < this->maxAnimationGone) {
		if (this->goneClock.getElapsedTime().asSeconds() > 0.3f) {
			if (this->intRectGone.left >= this->goneMaxSize) {
				this->intRectGone.left = 0;
			}
			else {
				this->intRectGone.left += this->intRectGone.width;
			}
			this->goneSprite.setTextureRect(this->intRectGone);
			this->goneClock.restart();
			this->goneAnimationCounter++;
		}
	}
	else if (this->goneAnimationCounter >= 3) {
		this->goneAnimationCounter = 0;
		this->birdDied = false;
		this->intRectGone.left = 0;
	}
}
void Game::update()
{
	this->pollEvents();

	this->updateMousePositions();

	if (this->mainMenu == true) {
		this->updateMainMenu();
		this->updateEnemies();
	}
	else if (this->tutorial == true) {
		this->updateTutorial();
	}
	else if (this->stats == true) {
		this->updateStats();
	}
	else if (this->credits == true) {
		this->updateAbout();
	}
	else {
		if (this->tutorial == true) {
			this->updateTutorial();
		}
		if (this->pauseGame == true) {
			this->backgroundMusic.pause();
			this->eagleSound.pause();
			this->updatePauseScene();
		}
		else if (this->endGame == false) {
			this->updateInput();
			this->player->update(this->window);
			this->updateBullets();
			this->updateEnemies();
			this->updateItems();
			this->updatePlayerConditions();
			this->updateText();
			this->updateInGameButtons();
			this->updateGameDifficulties();
			this->updateAnimation();
		}
		else if (this->LOSE == true) {
			if (this->musicOff == false && !donePlaying) {
				this->loseSound.play();
				this->donePlaying = true;
			}
			this->updateLoseScene();
		}

		//end game condition
		if (this->bullets.size() <= 0 && this->ammo <= 0) {
			this->endGame = true;
			this->LOSE = true;

			this->f_handler.open("manukhunter_data.bin", std::ios::out | std::ios::binary);
			if (this->f_handler.is_open()) {
				if (this->scores > this->highscores) {
					this->highscores = this->scores;
				}
				f_handler.write((char*)&this->highscores, sizeof(highscores));
				f_handler.write((char*)&this->birdsShot, sizeof(birdsShot));
				f_handler.write((char*)&this->bulletsShot, sizeof(bulletsShot));
				f_handler.write((char*)&this->shotsMissed, sizeof(shotsMissed));
			}
			else if (!f_handler.is_open()) {
				std::cout << "ERROR reading \"manukhunter_data.bin\"!" << std::endl;
				std::cout << "First time running the game?" << std::endl;
			}
			this->f_handler.close();
		}
	}
}

void Game::renderText(sf::RenderTarget& target)
{
	target.draw(this->scoreText);
	target.draw(this->scoreTextUpdate);
	target.draw(this->ammoText);
	target.draw(this->birdShotText);
	target.draw(this->maxAmmoText);
	target.draw(this->slowedText);
	target.draw(this->flashModeText);
	target.draw(this->diffText);
}
void Game::renderEnemies(sf::RenderTarget& target)
{
	for (auto& e : this->enemy)
	{
		e->render(*this->window);
	}
}
void Game::renderItems(sf::RenderTarget& target)
{
	for (auto& e : this->item)
	{
		e->render(*this->window);
	}
}
void Game::renderScoreBoard(sf::RenderTarget& target)
{
	target.draw(this->scoreBoardSprite);
	target.draw(this->ammoBoardSprite);
	target.draw(this->enemyBoardSprite);
	target.draw(this->birdShotSprite);
	target.draw(this->ammoSprite);
	target.draw(this->pauseButtonSprite);
	target.draw(this->questionButtonSprite);
}
void Game::renderMainMenu(sf::RenderTarget& target)
{
	target.draw(this->playButtonSprite);
	target.draw(this->exitButtonSprite);
	target.draw(this->musicButtonSprite);
	target.draw(this->infoButtonSprite);
	target.draw(this->statsButtonSprite);
	target.draw(this->tutorialButtonSprite);
	target.draw(this->manukHunterSprite);
}
void Game::renderPauseScene(sf::RenderTarget& target)
{
	target.draw(this->pauseSceneSprite);
	target.draw(this->resumeButtonSprite);
	target.draw(this->menuButtonSprite);
}
void Game::renderLoseScene(sf::RenderTarget& target)
{
	target.draw(this->loseSceneSprite);
	target.draw(this->restartButtonSprite);
	target.draw(this->menuLoseButtonSprite);
	target.draw(this->scoreLoseText);
	target.draw(this->highscoreLoseText);
}
void Game::renderTutorial(sf::RenderTarget& target)
{
	target.draw(this->tutorialSprite);
	target.draw(this->closeButtonTutorialSprite);
}
void Game::renderStats(sf::RenderTarget& target)
{
	target.draw(this->statsSprite);
	target.draw(this->closeButtonStatsSprite);
	target.draw(this->highscoreStatsText);
	target.draw(this->birdsShotStatsText);
	target.draw(this->bulletsShotStatsText);
	target.draw(this->shotsMissedStatsText);
}
void Game::renderAbout(sf::RenderTarget& target)
{
	target.draw(this->aboutSprite);
	target.draw(this->closeButtonAboutSprite);
}
void Game::renderAnimation(sf::RenderTarget& target)
{
	if (this->shoot) {
		target.draw(this->shootSprite);
	}
	if (this->birdDied) {
		target.draw(this->goneSprite);
	}
}
void Game::render()
{
	this->window->clear(); //clear screen

	this->window->draw(this->backgroundWallpaper);

	if (this->mainMenu == true) {
		this->renderEnemies(*this->window);
		this->renderMainMenu(*this->window);	
	}
	else if (this->tutorial == true) {
		this->renderTutorial(*this->window);
	}
	else if (this->stats == true) {
		this->renderStats(*this->window);
	}
	else if (this->credits == true) {
		this->renderAbout(*this->window);
	}
	else {
		if (this->pauseGame == true) {
			this->renderPauseScene(*this->window);
		}
		else if (this->tutorial == true) {
			this->renderTutorial(*this->window);
		}
		else if (this->LOSE == true) {
			this->renderLoseScene(*this->window);
		}
		else {
			//draw game objects
			this->renderScoreBoard(*this->window);
			this->renderText(*this->window);
			this->player->render(*this->window);
			for (auto* i : this->bullets) {
				i->render(this->window);
			}
			this->renderItems(*this->window);
			this->renderEnemies(*this->window);
			this->renderAnimation(*this->window);
		}
	}

	this->window->display();
}