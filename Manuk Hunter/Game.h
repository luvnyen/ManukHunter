#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <map>
#include <math.h>
#include <fstream>

#include "Object.h"
#include "MovingObject.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "RegularEnemy.h"
#include "FatEnemy.h"
#include "FastEnemy.h"
#include "Item.h"
#include "FireSpeedUpItem.h"
#include "FireSpeedDownItem.h"
#include "AmmoUpItem.h"

class Game
{
private:
	//Window
	sf::RenderWindow* window;
	sf::Event ev;

	//Positions
	sf::Vector2f playerCenter;
	sf::Vector2f mousePosWindow;
	sf::Vector2i mousePosWindowi;
	sf::Vector2f mousePosView;
	sf::Vector2f itemPosWindow;
	sf::Vector2f aimDir;
	sf::Vector2f aimDirNormalize;

	//Resources
	sf::Font font;
	std::map <std::string, sf::Texture*> textures;

	//GUI Main Menu
	sf::Texture playButtonTexture;
	sf::Sprite playButtonSprite;
	sf::Texture exitButtonTexture;
	sf::Sprite exitButtonSprite;
	sf::Texture infoButtonTexture;
	sf::Sprite infoButtonSprite;
	sf::Texture statsButtonTexture;
	sf::Sprite statsButtonSprite;
	sf::Texture musicButtonTexture;
	sf::Sprite musicButtonSprite;
	sf::Texture tutorialButtonTexture;
	sf::Sprite tutorialButtonSprite;
	sf::Texture manukHunterTexture;
	sf::Sprite manukHunterSprite;

	//Tutorial
	sf::Texture tutorialTexture;
	sf::Sprite tutorialSprite;
	sf::Texture closeButtonTutorialTexture;
	sf::Sprite closeButtonTutorialSprite;

	//About
	sf::Texture aboutTexture;
	sf::Sprite aboutSprite;
	sf::Texture closeButtonAboutTexture;
	sf::Sprite closeButtonAboutSprite;

	//Stats
	sf::Texture statsTexture;
	sf::Sprite statsSprite;
	sf::Texture closeButtonStatsTexture;
	sf::Sprite closeButtonStatsSprite;
	sf::Text highscoreStatsText;
	sf::Text birdsShotStatsText;
	sf::Text bulletsShotStatsText;
	sf::Text shotsMissedStatsText;

	//GUI on Game
	sf::Texture pauseButtonTexture;
	sf::Sprite pauseButtonSprite;
	sf::Texture questionButtonTexture;
	sf::Sprite questionButtonSprite;
	sf::Texture scoreBoardTexture;
	sf::Sprite scoreBoardSprite;
	sf::Texture ammoBoardTexture;
	sf::Sprite ammoBoardSprite;
	sf::Texture enemyBoardTexture;
	sf::Sprite enemyBoardSprite;
	sf::Texture birdShotTexture;
	sf::Sprite birdShotSprite;
	sf::Texture ammoTexture;
	sf::Sprite ammoSprite;

	sf::Text scoreText;
	sf::Text scoreTextUpdate;
	sf::Text birdShotText;
	sf::Text ammoText;
	sf::Text maxAmmoText;
	sf::Text slowedText;
	sf::Text flashModeText;
	sf::Text diffText;

	//GUI Pause Scene
	sf::Texture pauseSceneTexture;
	sf::Sprite pauseSceneSprite;
	sf::Texture resumeButtonTexture;
	sf::Sprite resumeButtonSprite;
	sf::Texture menuButtonTexture;
	sf::Sprite menuButtonSprite;

	//GUI Lose Scene
	sf::Texture loseSceneTexture;
	sf::Sprite loseSceneSprite;
	sf::Texture restartButtonTexture;
	sf::Sprite restartButtonSprite;
	sf::Texture menuLoseButtonTexture;
	sf::Sprite menuLoseButtonSprite;
	sf::Text scoreLoseText;
	sf::Text highscoreLoseText;

	//Background
	sf::Texture backgroundWallpaperTexture;
	sf::Sprite backgroundWallpaper;

	//Music and Sound Effects
	sf::Music backgroundMusic;
	sf::SoundBuffer buttonPressedBuffer;
	sf::Sound buttonPressedSound;
	sf::SoundBuffer shootBuffer;
	sf::Sound shootSound;
	sf::SoundBuffer eagleBuffer;
	sf::Sound eagleSound;
	sf::SoundBuffer regEnemyBuffer;
	sf::Sound regEnemySound;
	sf::SoundBuffer fatEnemyBuffer;
	sf::Sound fatEnemySound;
	sf::SoundBuffer fastEnemyBuffer;
	sf::Sound fastEnemySound;
	sf::SoundBuffer itemUpBuffer;
	sf::Sound itemUpSound;
	sf::SoundBuffer itemAmmoBuffer;
	sf::Sound itemAmmoSound;
	sf::SoundBuffer virusBuffer;
	sf::Sound virusSound;
	sf::SoundBuffer loseBuffer;
	sf::Sound loseSound;

	//animation
	sf::Texture shootTexture;
	sf::Sprite shootSprite;
	sf::Texture goneTexture;
	sf::Sprite goneSprite;

	sf::IntRect intRectShoot;
	sf::IntRect intRectGone;
	sf::Clock shootClock;
	sf::Clock goneClock;

	int shootMaxSize;
	int goneMaxSize;
	int shootAnimationCounter;
	int maxAnimationShoot;
	int goneAnimationCounter;
	int maxAnimationGone;

	//Game logic
	//timer
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxItems;
	float itemSpawnTimer;
	float itemSpawnTimerMax;
	float virusSpawnTimer;
	float virusSpawnTimerMax;
	float itemTimer;
	float itemTimerMax;
	float diffTimer;
	float diffTimerMax;

	//attributes
	long int scores;
	long int scoresTemp;
	unsigned birdShot;
	int maxEnemies;
	int ammo;
	int maxAmmo;
	float bulletSpeed;

	//conditions
	bool endGame;
	bool mainMenu;
	bool pauseGame;
	bool mouseHeld;
	bool LOSE;
	bool tutorial;
	bool stats;
	bool credits;
	bool inMenu;
	bool musicOff;
	bool donePlaying;
	bool fireSpeedUp;
	bool fireSpeedDown;
	bool updateDiff;
	bool updateDiffText;
	bool shoot;
	bool birdDied;

	//Game objects
	Player* player;
	std::vector <Bullet*> bullets;
	std::vector <Enemy*> enemy;
	std::vector <Item*> item;

	//Data saving
	std::fstream f_handler;
	long int highscores;
	long int birdsShot;
	long int bulletsShot;
	long int shotsMissed;

	//Private functions
	void initVariables();
	void initWindow();
	void initFonts();
	void initText();
	void initPlayer();
	void initBulletTextures();
	void initBackgroundWallpaper();
	void initScoreBoard();
	void initMainMenu();
	void initPauseScene();
	void initLoseScene();
	void initTutorial();
	void initStats();
	void initAbout();
	void initFirstGameVariables();
	void initSoundEffects();
	void initAnimation();

public:
	//const
	Game();
	~Game();
	 
	//accessors
	const bool running() const;
	const bool getEndGame() const;

	//functions
	void run();
	void spawnEnemy();
	void spawnItem();
	void spawnVirus();

	void pollEvents();
	void updateInput();
	void updateBullets();
	void updateText();
	void updateEnemies();
	void updateItems();
	void updatePlayerConditions();
	void updateMainMenu();
	void updatePauseScene();
	void updateLoseScene();
	void updateTutorial();
	void updateStats();
	void updateAbout();
	void updateMousePositions();
	void updateInGameButtons();
	void updateGameDifficulties();
	void updateAnimation();
	void update();

	void renderText(sf::RenderTarget& target);
	void renderEnemies(sf::RenderTarget& target);
	void renderItems(sf::RenderTarget& target);
	void renderScoreBoard(sf::RenderTarget& target);
	void renderMainMenu(sf::RenderTarget& target);
	void renderPauseScene(sf::RenderTarget& target);
	void renderLoseScene(sf::RenderTarget& target);
	void renderTutorial(sf::RenderTarget& target);
	void renderStats(sf::RenderTarget& target);
	void renderAbout(sf::RenderTarget& target);
	void renderAnimation(sf::RenderTarget& target);
	void render();
};