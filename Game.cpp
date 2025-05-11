#include "Game.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

GameState currentState = GameState::MainMenu;

Game::Game()
    : window(sf::VideoMode(800, 600), "Asteroid Destroyer"),
    timePerFrame(sf::seconds(1.f / 60.f))
{
    window.setFramerateLimit(60);
    std::srand(static_cast<unsigned>(std::time(nullptr)));

    asteroidSpawnTimer = sf::Time::Zero;
    asteroidSpawnInterval = sf::seconds(1.5f);

    if (!asteroidTexture.loadFromFile("Assets/textures/asteroid.png")) {
        std::cerr << "Error loading asteroid texture\n";
    }

    score = 0;
    isGameOver = false;

    if (!font.loadFromFile("Assets/fonts/arial.ttf")) {
        std::cerr << "Failed to load font!\n";
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::Yellow);
    scoreText.setPosition(10.f, 10.f);

    gameOverText.setFont(font);
    gameOverText.setCharacterSize(40);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER\nPress R to Restart");
    gameOverText.setPosition(200.f, 250.f);

    titleText.setFont(font);
    titleText.setCharacterSize(48);
    titleText.setFillColor(sf::Color::Cyan);
    titleText.setString("ASTEROID DESTROYER");
    titleText.setPosition(100.f, 100.f);

    menuText.setFont(font);
    menuText.setCharacterSize(28);
    menuText.setFillColor(sf::Color::White);
    menuText.setString("1. Start Game\n2. High Scores\n3. Exit");
    menuText.setPosition(200.f, 250.f);

    highScoresText.setFont(font);
    highScoresText.setCharacterSize(24);
    highScoresText.setFillColor(sf::Color::Yellow);
    highScoresText.setPosition(100.f, 200.f);

    if (!shootBuffer.loadFromFile("Assets/audio/shoot.wav")) {
        std::cerr << "Failed to load shoot.wav\n";
    }
    if (!explosionBuffer.loadFromFile("Assets/audio/explosion.wav")) {
        std::cerr << "Failed to load explosion.wav\n";
    }
    shootSound.setBuffer(shootBuffer);
    explosionSound.setBuffer(explosionBuffer);

    if (!backgroundMusic.openFromFile("Assets/audio/background_music.ogg")) {
        std::cerr << "Failed to load background music\n";
    }
    backgroundMusic.setLoop(true);
    backgroundMusic.play();

    flash.setSize(sf::Vector2f(800, 600));
    flash.setFillColor(sf::Color(255, 255, 255, 150));
    flashActive = false;
}

void Game::run()
{
    sf::Clock clock;
    sf::Time elapsed = sf::Time::Zero;

    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        elapsed += dt;

        while (elapsed >= timePerFrame)
        {
            elapsed -= timePerFrame;
            processEvents();
            update(timePerFrame);
        }

        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void Game::update(sf::Time deltaTime)
{
    if (currentState == GameState::MainMenu)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
            restart();
            currentState = GameState::Playing;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
            loadHighScores();
            currentState = GameState::HighScores;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
            window.close();
        }
        return;
    }

    if (currentState == GameState::HighScores)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
            currentState = GameState::MainMenu;
        }
        return;
    }

    if (currentState == GameState::GameOver)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            currentState = GameState::MainMenu;
        }
        return;
    }

    player.update(deltaTime);
    asteroidSpawnTimer += deltaTime;

    if (asteroidSpawnTimer >= asteroidSpawnInterval)
    {
        asteroidSpawnTimer = sf::Time::Zero;
        float x = static_cast<float>(std::rand() % 760 + 20);
        asteroids.emplace_back(x, asteroidTexture);
    }

    for (auto& asteroid : asteroids)
        asteroid.update(deltaTime);

    asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(),
        [](Asteroid& a) { return a.isOffScreen(); }), asteroids.end());

    auto& bullets = player.getBullets();
    for (auto b = bullets.begin(); b != bullets.end();)
    {
        bool hit = false;
        for (auto a = asteroids.begin(); a != asteroids.end();)
        {
            if (b->getBounds().intersects(a->getBounds()))
            {
                explosionSound.play();
                flashActive = true;
                flashClock.restart();
                a = asteroids.erase(a);
                hit = true;
                score += 10;
                break;
            }
            else ++a;
        }
        if (hit) b = bullets.erase(b);
        else ++b;
    }

    for (auto& asteroid : asteroids)
    {
        if (asteroid.getBounds().intersects(player.getBounds()))
        {
            saveHighScore(score);
            currentState = GameState::GameOver;
            break;
        }
    }

    scoreText.setString("Score: " + std::to_string(score));
}

void Game::render()
{
    window.clear();

    switch (currentState)
    {
    case GameState::MainMenu:
        window.draw(titleText);
        window.draw(menuText);
        break;

    case GameState::HighScores:
        window.draw(titleText);
        window.draw(highScoresText);
        break;

    case GameState::Playing:
        player.draw(window);
        for (auto& asteroid : asteroids)
            asteroid.draw(window);
        window.draw(scoreText);
        break;

    case GameState::GameOver:
        window.draw(titleText);
        window.draw(gameOverText);
        break;
    }

    // Improved flash effect
    if (flashActive)
    {
        if (flashClock.getElapsedTime() < flashDuration)
            window.draw(flash);
        else
            flashActive = false;
    }

    window.display();
}


void Game::restart()
{
    score = 0;
    isGameOver = false;
    asteroids.clear();
    player.getBullets().clear();
    scoreText.setString("0");  
}

void Game::saveHighScore(int score)
{
    std::ofstream file("highscores.txt", std::ios::app);
    if (file.is_open())
    {
        file << score << "\n";
        file.close();
    }
}

void Game::loadHighScores()
{
    highScores.clear();
    std::ifstream file("highscores.txt");
    int val;
    while (file >> val)
        highScores.push_back(val);

    std::sort(highScores.rbegin(), highScores.rend());

    std::string hs = "High Scores:\n";
    for (int i = 0; i < std::min(5, (int)highScores.size()); ++i)
        hs += std::to_string(i + 1) + ". " + std::to_string(highScores[i]) + "\n";

    hs += "\nPress ESC to return";
    highScoresText.setString(hs);
}
