#include"Platform.h"

Platform::Platform():sprite(texture)
{
	if (!texture.loadFromFile("images/Platform.png"))
	{
		std::cout<<"Cant Load Platform.png";
	}

	sprite.setTexture(texture, true);
	sprite.setScale(platform_size);
	sprite.setPosition(platform_position);
}

void Platform::set_platform_pos(Vector2f pos)
{
	platform_position = pos; 
	sprite.setPosition(pos);
}
