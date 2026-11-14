#include "Initialization.h"
#include <fstream>
#include <iostream>

using namespace sf;

GameData::GameData() : 
	window(VideoMode(Vector2u(800, 1000)), "Cat Jump", Style::Default),
    view(FloatRect(Vector2f(0, 0), Vector2f(800, 1000))),
	dist_x(0, 700),
	dist_y(60, 90),
	simple_platforms_pool(25, platform),
	background_sprite(background_texture),
	font("fonts/orithdisplay-regular.otf"),
	score_text(font),
	highest_text(font),
	game_over_text(font),
	play_button("Play", Vector2f(330, 420), font),
	settings_button("Settings", Vector2f(330, 490), font),
	quit_button("Quit", Vector2f(330, 560), font),
	restart_button("Restart", Vector2f(330, 420), font),
	reset_button("Reset", Vector2f(330, 420), font),
	back_button("Back", Vector2f(330, 550), font),
	sound_slider("Sound", font){}

bool init_game(GameData& data)
{
	std::random_device rd;
	data.generator.seed(rd());

	float button_x_offset = 70;
	float button_y_offset = 80;
	data.window_size = Vector2f(data.window.getSize().x / 2.0f - button_x_offset,data.window.getSize().y / 2.0f - button_y_offset);

	float current_y_pos = data.window.getSize().y - 100.0f;

	for (int i = 0; i < 25; ++i)
	{
		float current_x_pos = static_cast<float>(data.dist_x(data.generator));
		data.simple_platforms_pool[i].set_platform_pos(Vector2f(current_x_pos, current_y_pos));
		current_y_pos -= data.dist_y(data.generator);
	}

	std::ifstream read("high_score.txt");
	if (read.is_open())
	{
		read >> data.score_buffer;
		read.close();
	}

	if (!data.background_texture.loadFromFile("images/back2.png"))
	{
		return false;
	}
	
	data.background_sprite.setTexture(data.background_texture, true);

	data.score_text.setCharacterSize(34);
	data.score_text.setFillColor(Color::White);
	data.score_text.setPosition(Vector2f(50, 50));

	data.highest_text.setCharacterSize(34);
	data.highest_text.setFillColor(Color::White);
	data.highest_text.setPosition(Vector2f(500, 50));

	data.game_over_text.setCharacterSize(72);
	data.game_over_text.setFillColor(Color::White);
	data.game_over_text.setPosition(Vector2f(data.window_size.x / 2.0f, 300.0f));
	data.game_over_text.setString("Game   Over");
    data.sound_slider.set_pos(Vector2f(data.play_button.get_pos().x, data.play_button.get_pos().y + 90),data.play_button.get_pos().y + 90);

	return true;
}
