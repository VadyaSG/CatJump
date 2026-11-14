#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

class MSlider:public Drawable
{
public:
	MSlider(std::string slider_text,Font nfont);

	void set_pos(Vector2f new_recrt_pos, float new_slider_pos);
	float drag_operation(Vector2i mouse_pos, RenderWindow& window);
private:
	Texture slider;
	Sprite slider_sp;
	Text text;
	Font font;
	RectangleShape slider_rect{ Vector2f(300, 25) };
	RectangleShape back_slider_rect{ Vector2f(300, 25) };
	float sound{ 100.f };
	bool is_drugging{ false };
protected:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

};