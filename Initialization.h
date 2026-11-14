#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <random>
#include <memory>
#include "Cat.h"
#include "Platform.h"
#include "Button.h"
#include "Slider.h"

enum Game_states
{
	Game,
	Menu,
	GameOver,
	Settings
};

struct GameData
{
	sf::Clock clock;
	sf::RenderWindow window;
	sf::View view;
	Cat hero;
	Platform platform;
	sf::Vector2f window_size;
	sf::Vector2i mouse_position;

	Game_states game_state = Menu;
	int score_buffer = 0;
	int score = 0;
	float sounds = 100.0f;

	std::mt19937 generator;
	std::uniform_int_distribution<> dist_x;
	std::uniform_int_distribution<> dist_y;

	std::vector<Platform> simple_platforms_pool;

	sf::Texture background_texture;
	sf::Sprite background_sprite;

	sf::Font font;
	sf::Text score_text;
	sf::Text highest_text;
	sf::Text game_over_text;

	Button play_button;
	Button settings_button;
	Button quit_button;
	Button restart_button;
	Button reset_button;
	Button back_button;
	MSlider sound_slider;
	GameData();
};

bool init_game(GameData& data);