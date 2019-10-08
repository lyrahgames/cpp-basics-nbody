#pragma once
#include <string>

#include <SFML/Graphics.hpp>

#include <particle_system.hpp>
#include <vector2.hpp>

class application {
  using vector2f = nbody::vector2f;

 public:
  explicit application(const std::string& file_path);
  ~application() = default;

  void execute();

 private:
  void resize();
  void resize(int w, int h);
  void compute_viewport();
  void render();

 private:
  int screen_width = 800;
  int screen_height = 450;

  // viewport
  vector2f origin{};
  vector2f view_dim =
      2.0f * vector2f{1, static_cast<float>(screen_width) / screen_height};
  vector2f view_min;
  vector2f view_max;

  // rendering
  sf::RenderWindow window;
  bool update = true;

  nbody::particle_system ps;
  nbody::particle_system ps_start;
};