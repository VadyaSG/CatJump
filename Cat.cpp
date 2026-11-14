#include"Cat.h"
Cat::Cat():cat_sprite_scale(2.5f, 2.5f), cat_jump_srite(cat_jump_txt),jump_sound(jump_sound_buffer)
{
	if (!cat_jump_txt.loadFromFile("images/Cat_jump.png"))
	{
		std::cout << "Can't load Cat_jump.png ";
	}

	if (!cat_fall_txt.loadFromFile("images/Cat_fall.png"))
	{
		std::cout << "Can't load Cat_fall.png ";
	}
	if (!cat_jump_l_txt.loadFromFile("images/Cat_jump_l.png"))
	{
		std::cout << "Can't load_l.png ";
	}

	if (!cat_fall_l_txt.loadFromFile("images/Cat_fall_l.png"))
	{
		std::cout << "Can't load Cat_fall_l.png ";
	}

	if (!jump_sound_buffer.loadFromFile("Sounds/Jump.wav"))
	{
		std::cout << "Cant load jump sound";
	}


	cat_pos = Vector2f(400, 500);
	cat_jump_srite.setTexture(cat_jump_txt, true);
	
	cat_jump_srite.setScale(cat_sprite_scale);
	cat_jump_srite.setPosition(cat_pos);

	jump_sound.setBuffer(jump_sound_buffer);
	jump_sound.setPitch(1.f);
	jump_sound.setVolume(100.f);
}

void Cat::movement()
{
	is_left_moving = Keyboard::isKeyPressed(Keyboard::Key::Left);
	is_right_moving = Keyboard::isKeyPressed(Keyboard::Key::Right);
}

void Cat::update(float delta_t, RenderWindow& game_window)
{
	
	if (is_ground)
	{
		jump_sound.play();
		jump_velocity = start_jump_velocity;
		is_ground = false;
	}
	
	if (!is_ground)
	{
		if (jump_velocity >= 0)
		{
			if (is_right)
			{
				cat_jump_srite.setTexture(cat_fall_txt, true);
			}
			else
			{
				cat_jump_srite.setTexture(cat_fall_l_txt, true);
			}
			
		}

		jump_velocity += gravity*delta_t;
		cat_pos.y += jump_velocity * delta_t;
		float ground_level = game_window.getSize().y-110;

		if (cat_pos.y >= ground_level)
		{
			if (is_right)
			{
				cat_jump_srite.setTexture(cat_jump_txt, true);
			}
			else
			{
				cat_jump_srite.setTexture(cat_jump_l_txt, true);
			}
			
			cat_pos.y = ground_level;
			jump_velocity = 0;
			
			is_ground = true;
		}
		
	}
	cat_jump_srite.setPosition(cat_pos);

	if (is_left_moving)
	{
		if (cat_pos.x < 0.f)
		{
			cat_pos.x = game_window.getSize().x;
			cat_jump_srite.setPosition(cat_pos);

		}
		is_right = false;
		cat_pos = cat_jump_srite.getPosition();
		cat_pos.x -= speed * delta_t;
		cat_jump_srite.setPosition(cat_pos);
	}

	if (is_right_moving)
	{
		if (cat_pos.x > game_window.getSize().x)
		{
			cat_pos.x = -2.f;
			cat_jump_srite.setPosition(cat_pos);
		}
		is_right = true;
		cat_pos = cat_jump_srite.getPosition();
		cat_pos.x += speed * delta_t;
		cat_jump_srite.setPosition(cat_pos);
	}
}

void Cat::reset_position()
{
	cat_pos = Vector2f(400, 500);
	cat_jump_srite.setPosition(cat_pos);
	is_ground = true;
}

void Cat::set_sound_volume(float new_volume)
{
	jump_sound.setVolume(new_volume);
}



