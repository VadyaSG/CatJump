#include "Button.h"

Button::Button(std::string ntext, Vector2f nposition, Font nfont) :text(ntext), position(nposition), font(nfont), sprite(texture), text_block(font)
{
	if (!texture.loadFromFile("images/Button.png"))
	{
		std::cout << "cant load buttons.png";
	}
	

	sprite.setTexture(texture, true);
	sprite.setPosition(position);
	sprite.setScale(Vector2f(0.4, 0.4));

	text_block.setFont(font);
	text_block.setFillColor(Color::White);
	text_block.setCharacterSize(32);
	text_block.setString(text);

	FloatRect text_bounds = text_block.getLocalBounds();
	text_block.setOrigin(Vector2f(text_bounds.position.x + text_bounds.size.x/ 2.f, text_bounds.position.y + text_bounds.size.y / 2.f));

	FloatRect sprite_bounds = sprite.getGlobalBounds();
	float button_x = sprite_bounds.position.x+sprite_bounds.size.x/2.f;
	float button_y = sprite_bounds.position.y + sprite_bounds.size.y / 2.f;

	text_block.setPosition(Vector2f(button_x, button_y));
}

bool Button::click(RenderWindow& window)
{
	Vector2i pixel_pos = Mouse::getPosition(window);
	Vector2f mouse_pos = window.mapPixelToCoords(pixel_pos);

	if (sprite.getGlobalBounds().contains(mouse_pos))
	{
		std::cout << text;
		return true;
	}
	else
	{
		return false;
	}
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite, states);
	target.draw(text_block, states);
}
