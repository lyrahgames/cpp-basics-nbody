#pragma once

#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include <vector2.hpp>

namespace nbody {

struct particle_system {
  auto size() const noexcept { return position.size(); }

  std::vector<vector2f> position;
  std::vector<vector2f> velocity;
  std::vector<float> mass;
};

vector2f acceleration(const particle_system& ps, int index);
void advance(particle_system& ps, float dt);
void load(particle_system& ps, const std::string& file_path);
vector2f center_of_mass(const particle_system& ps);

}  // namespace nbody