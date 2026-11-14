#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
class Cat
{
public:
	Cat();
	Sprite& get_jump_sprite() { return cat_jump_srite; }
	

	void movement();
	void update(float delta_t, RenderWindow& game_window);
	void set_is_ground(bool ground) { is_ground = ground; }
	float get_jump_velocity(){ return jump_velocity; }

	void reset_position();
	void set_sound_volume(float new_volume);
private:
	
	const float speed{500};
	const float gravity{1200.f};
	const float start_jump_velocity{ -600.f};
	float jump_velocity = start_jump_velocity;
	bool is_left_moving{ false };
	bool is_right_moving{ false };
	bool is_ground{ true };
	bool is_right = false;
	Vector2f cat_sprite_scale;
	Vector2f cat_pos;

	Texture cat_jump_txt;
	Texture cat_fall_txt;
	Texture cat_jump_l_txt;
	Texture cat_fall_l_txt;
	
	Sprite cat_jump_srite;

	SoundBuffer jump_sound_buffer;
	Sound jump_sound;
	
};
