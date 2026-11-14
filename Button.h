#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
class Button:public Drawable
{
public:
	Button(std::string text, Vector2f position,Font font);
	Vector2f get_pos() { return position; }
	bool click(RenderWindow& window);
private:
	Texture texture;
	Sprite sprite;
	std::string text;
	Vector2f position;
	Text text_block;
	Font font;
protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};