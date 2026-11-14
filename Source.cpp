#include <fstream>
#include <iostream>
#include "Initialization.h"

using namespace sf;

int main()
{
	auto game = std::make_unique<GameData>();
	if (!init_game(*game))
	{
		return -1;
	}

	GameData& g = *game;

	while (g.window.isOpen())
	{
		float delta_time = g.clock.restart().asSeconds();
		while (const std::optional event = g.window.pollEvent())
		{
			if (event->is<Event::Closed>())
			{
				g.window.close();
			}

			if (event->is<Event::MouseMoved>())
			{
				g.mouse_position = Mouse::getPosition(g.window);
			}

			if (const auto* key_pressed = event->getIf<Event::KeyPressed>())
			{
				if (key_pressed->scancode == Keyboard::Scancode::Escape)
				{
					g.game_state = Menu;
					g.view = g.window.getDefaultView();
					g.background_sprite.setPosition(Vector2f(0.f, 0.f));
					g.window.setView(g.view);
				}
			}

			if (const auto* mouse_pressed = event->getIf<Event::MouseButtonPressed>())
			{
				if (mouse_pressed->button == Mouse::Button::Left)
				{
					switch (g.game_state)
					{
					case Menu:
						if (g.play_button.click(g.window)) { g.game_state = Game; }
						else if (g.settings_button.click(g.window)) { g.game_state = Settings; }
						else if (g.quit_button.click(g.window)) { g.window.close(); }
						break;

					case Settings:
						if (g.back_button.click(g.window)) { g.game_state = Menu; }
						else if (g.reset_button.click(g.window))
						{
							std::ofstream save("high_score.txt");
							save << 0;
							save.close();
							g.score_buffer = 0;
						}
						break;

					case GameOver:
						if (g.restart_button.click(g.window)) { g.game_state = Game; g.score = 0; }
						else if (g.quit_button.click(g.window)) { g.game_state = Menu; }
						break;
					}
				}
			}
		}

		switch (g.game_state)
		{
		case Menu:
			g.window.clear();
			g.highest_text.setString("Record: " + std::to_string(g.score_buffer));

			g.window.draw(g.background_sprite);
			g.window.draw(g.play_button);
			g.window.draw(g.settings_button);
			g.window.draw(g.quit_button);
			g.window.draw(g.highest_text);
			g.window.display();
			break;

		case GameOver:
		{
			g.window.clear();
			g.score_text.setString("Score: " + std::to_string(g.score));
			g.highest_text.setString("Record: " + std::to_string(g.score_buffer));

			float current_y_pos = g.window.getSize().y - 100.f;

			for (int i = 0; i < 25; ++i)
			{
				float current_x_pos = static_cast<float>(g.dist_x(g.generator));
				g.simple_platforms_pool[i].set_platform_pos(Vector2f(current_x_pos, current_y_pos));
				current_y_pos -= g.dist_y(g.generator);
			}

			g.hero.reset_position();
			g.window.draw(g.background_sprite);
			g.window.draw(g.highest_text);
			g.window.draw(g.game_over_text);
			g.window.draw(g.score_text);
			g.window.draw(g.restart_button);
			g.window.draw(g.quit_button);
            g.window.display();

			break;
		}

		case Settings:
			g.window.clear();
			g.hero.set_sound_volume(g.sound_slider.drag_operation(g.mouse_position, g.window));
			g.window.draw(g.background_sprite);
			g.window.draw(g.back_button);
			g.window.draw(g.sound_slider);
			g.window.draw(g.reset_button);
			g.window.display();
			break;

		case Game:
		{
			g.hero.movement();
			g.hero.update(delta_time, g.window);

			FloatRect h = g.hero.get_jump_sprite().getGlobalBounds();
			float view_center_y = g.view.getCenter().y;
			float hero_y = h.position.y;

			if (hero_y < view_center_y)
			{
				float target_y = hero_y;
				float current_y = view_center_y;
				float new_view_y = current_y + (target_y - current_y) * 5.f * delta_time;

				g.view.setCenter(Vector2f(400.f, new_view_y));
			}

			g.window.setView(g.view);

			float screen_top_y = g.view.getCenter().y - (1000.f / 2.f);
			float screen_bottom_y = g.view.getCenter().y + (1000.f / 2.f);

			g.background_sprite.setPosition(Vector2f(g.view.getCenter().x - 400.f, screen_top_y));

			g.window.clear();

			g.window.draw(g.background_sprite);
			g.window.setView(g.window.getDefaultView());

			g.score_text.setString(std::to_string(g.score));
			g.window.draw(g.score_text);
			g.window.setView(g.view);

			for (auto& plat : g.simple_platforms_pool)
			{
				if (plat.get_sprite().getPosition().y > screen_bottom_y + 50.f)
				{
					float highest_y = screen_bottom_y;
					for (auto& p_check : g.simple_platforms_pool)
					{
						if (p_check.get_sprite().getPosition().y < highest_y && p_check.get_sprite().getPosition().y < screen_bottom_y)
						{
							highest_y = p_check.get_sprite().getPosition().y;
						}
					}

					if (highest_y == screen_bottom_y)
					{
						highest_y = screen_top_y;
					}

					float new_x = static_cast<float>(g.dist_x(g.generator));
					float new_y = highest_y - g.dist_y(g.generator);
					plat.set_platform_pos(Vector2f(new_x, new_y));

					++g.score;
				}

				FloatRect p = plat.get_sprite().getGlobalBounds();
				if (p.findIntersection(h) && g.hero.get_jump_velocity() > 0)
				{
					if ((h.position.y + h.size.y) - p.position.y <= 15.f)
					{
						g.hero.set_is_ground(true);
					}
				}

				g.window.draw(plat);
			}

			if (g.hero.get_jump_sprite().getPosition().y >= screen_bottom_y)
			{
				g.game_state = GameOver;
				g.view = g.window.getDefaultView();
				g.window.setView(g.view);
				g.background_sprite.setPosition(Vector2f(0.f, 0.f));

				if (g.score > g.score_buffer)
				{
					g.score_buffer = g.score;
					std::ofstream save("high_score.txt");
					save << g.score;
					save.close();
				}

				std::cout << "GameOver";
			}

			g.window.draw(g.hero.get_jump_sprite());
			g.window.display();
			break;
		}
		}
	}

	return 0;
}
