#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class Platform:public Drawable
{
public:
	Platform();
	Sprite& get_sprite() { return sprite; }

	void set_platform_pos(Vector2f pos);
private:
	Texture texture;
	mutable Sprite sprite;
	Vector2f platform_size{0.25f,0.15f};
	Vector2f platform_position;

protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override { target.draw(sprite, states); }


};