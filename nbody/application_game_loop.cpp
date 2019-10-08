#include <application.hpp>

#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

void application::execute() {
  using nbody::vector2f;

  int old_mouse_x = 0;
  int old_mouse_y = 0;

  // Start the actual game loop of the application to show, render and interact
  // with the window.
  while (window.isOpen()) {
    // Get new mouse position and compute movement in space.
    const auto mouse_pos = sf::Mouse::getPosition(window);
    const int mouse_x = mouse_pos.x;
    const int mouse_y = mouse_pos.y;
    const vector2f mouse_move{
        view_dim.x / screen_width * (mouse_x - old_mouse_x),
        view_dim.y / screen_height * (mouse_y - old_mouse_y)};

    // Poll every event from the system and user.
    // Otherwise the window will not be displayed.
    sf::Event event{};
    while (window.pollEvent(event)) {
      // Decide what to do if certain events are happening.
      switch (event.type) {
        case sf::Event::Closed:
          window.close();
          break;

        case sf::Event::Resized:
          resize(event.size.width, event.size.height);
          break;

        case sf::Event::MouseWheelMoved:
          view_dim.y *= exp(-event.mouseWheel.delta * 0.05f);
          view_dim.y = clamp(view_dim.y, 1e-6f, 1000.f);
          break;

        case sf::Event::KeyPressed:
          switch (event.key.code) {
            case sf::Keyboard::Escape:
              window.close();
              break;

            case sf::Keyboard::Space:
              update = !update;
              break;

            case sf::Keyboard::R:
              ps = ps_start;
              break;
          }
          break;
      }
    }
    // Move origin with left mouse button.
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      origin = origin - mouse_move;
    }

    if (update) {
      compute_viewport();
      nbody::advance(ps, 1e-2);
    }

    // Double Buffering and Rendering
    window.clear();
    render();
    window.display();

    old_mouse_x = mouse_x;
    old_mouse_y = mouse_y;
  }
}

void application::render() {
  for (int i = 0; i < ps.size(); ++i) {
    const float p_x = (ps.position[i].x - view_min.x) /
                      (view_max.x - view_min.x) * screen_width;
    const float p_y = (ps.position[i].y - view_min.y) /
                      (view_max.y - view_min.y) * screen_height;
    const float radius =
        clamp(10.0f * pow(ps.mass[i], 1.0f / 3.0f) / view_dim.y, 3.0f, 50.0f);
    sf::CircleShape circle{radius};
    circle.setPosition(p_x, p_y);
    circle.setOrigin(radius, radius);
    window.draw(circle);
  }
}