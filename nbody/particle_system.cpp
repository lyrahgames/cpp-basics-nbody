#include <particle_system.hpp>

namespace nbody {

vector2f acceleration(const particle_system& ps, int index) {
  using namespace std;

  vector2f result{};
  for (int i = 0; i < ps.size(); ++i) {
    // if (i == index) continue;
    const float gamma = 1.0f;
    const float epsilon = 1e-4f;
    const auto direction = ps.position[i] - ps.position[index];
    const auto squared_distance = squared_norm(direction);
    result += gamma * ps.mass[i] /
              (squared_distance * sqrt(squared_distance) + epsilon) * direction;
  }
  return result;
}

void advance(particle_system& ps, float dt) {
  for (int i = 0; i < ps.size(); ++i) {
    ps.velocity[i] += dt * acceleration(ps, i);
  }

  for (int i = 0; i < ps.size(); ++i) {
    ps.position[i] += dt * ps.velocity[i];
  }
}

void load(particle_system& ps, const std::string& file_path) {
  std::fstream file{file_path, std::ios::in};
  if (!file.is_open())
    throw std::runtime_error(
        "Could not load the particle system. The given file '" + file_path +
        "' could not be opened.");
  std::string command;
  std::string arguments;

  while (file >> command) {
    getline(file, arguments);
    std::stringstream input{arguments};
    if (command == "particle") {
      ps.position.push_back({});
      ps.velocity.push_back({});
      ps.mass.push_back(1);
    } else if (command == "r") {
      input >> ps.position.back().x >> ps.position.back().y;
    } else if (command == "v") {
      input >> ps.velocity.back().x >> ps.velocity.back().y;
    } else if (command == "m") {
      input >> ps.mass.back();
    }
  }
}

vector2f center_of_mass(const particle_system& ps) {
  vector2f result{};
  float mass{};
  for (int i = 0; i < ps.size(); ++i) {
    result += ps.mass[i] * ps.position[i];
    mass += ps.mass[i];
  }
  return (1 / mass) * result;
}

}  // namespace nbody