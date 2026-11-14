#include "Slider.h"

MSlider::MSlider(std::string slider_text,Font nfont):slider_sp(slider), font(nfont), text(font)
{

	if (!slider.loadFromFile("images/slider.png"))
	{
		std::cout << "cant't load slider";
	}
	

	slider_sp.setScale(Vector2f(0.15, 0.10));
	FloatRect bounds = slider_sp.getLocalBounds();
	
	slider_sp.setOrigin(Vector2f(bounds.size.x / 2, bounds.size.y / 2));

	slider_sp.setTexture(slider, true);
	slider_rect.setFillColor(Color::Yellow);
	slider_rect.setOutlineThickness(2.f);
	slider_rect.setOutlineColor(Color::Blue);

	back_slider_rect.setFillColor(Color::Green);
	
	text.setFont(font);
	text.setFillColor(Color::Black);
	text.setCharacterSize(15);
	text.setString(slider_text);
	
}

void MSlider::set_pos(Vector2f new_rect_pos, float new_slider_pos)
{
	slider_rect.setPosition(new_rect_pos);
	back_slider_rect.setPosition(new_rect_pos);

	float start_x = slider_rect.getPosition().x;
	float max_slider_pos = slider_rect.getSize().x-34;
	float current_x = start_x + (max_slider_pos * (sound / 100.f));
	
	slider_sp.setPosition(Vector2f(current_x,new_slider_pos));
	text.setPosition(slider_rect.getPosition());
}

float MSlider::drag_operation(Vector2i mouse_pos, RenderWindow& window)
{
	Vector2f mouse_position_f = window.mapPixelToCoords(mouse_pos);

	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		FloatRect slider_sp_rect = slider_sp.getGlobalBounds();
		if (!is_drugging && slider_sp.getGlobalBounds().contains(mouse_position_f) ||
			slider_sp.getGlobalBounds().contains(mouse_position_f))
		{
			is_drugging = true;
		}
	}
	else
	{
		is_drugging = false;
	}

	if (is_drugging)
	{
		float start_x = slider_rect.getPosition().x ;
		float max_slider_pos = slider_rect.getPosition().x - 63.f;
		float clmped_pos = std::clamp(mouse_position_f.x, start_x, start_x + max_slider_pos);
		sound = ((clmped_pos - start_x) / max_slider_pos) * 100.f;
		slider_sp.setPosition(Vector2f(clmped_pos, slider_sp.getPosition().y));

		back_slider_rect.setSize(Vector2f(clmped_pos-start_x, slider_rect.getSize().y));
	}
	return sound;
}

void MSlider::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(slider_rect, states);
	target.draw(back_slider_rect, states);
	target.draw(text, states);
	target.draw(slider_sp, states);

}
