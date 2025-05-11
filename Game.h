#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Player.h"
#include "Asteroid.h"
#include <vector>
#include <ctime>

enum class GameState { MainMenu, Playing, GameOver, HighScores };
extern GameState currentState;

class Game
{
public:
    Game();
    void run();
    void restart();
    void saveHighScore(int score);
    void loadHighScores();
    std::vector<int> highScores;

private:
    Player player;
    void processEvents();
    void update(sf::Time deltaTime);
    void render();
    std::vector<Asteroid> asteroids;
    sf::Time asteroidSpawnTimer;
    sf::Time asteroidSpawnInterval;
    sf::Texture asteroidTexture;

    int score;
    bool isGameOver;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;

    sf::Text titleText;
    sf::Text menuText;
    sf::Text highScoresText;

    sf::SoundBuffer shootBuffer;
    sf::SoundBuffer explosionBuffer;
    sf::Sound shootSound;
    sf::Sound explosionSound;

    sf::Music backgroundMusic;

    sf::RectangleShape flash;
    sf::Clock flashClock;
    bool flashActive;
    sf::Time flashDuration = sf::milliseconds(100);
    sf::RenderWindow window;
    sf::Time timePerFrame;
};
