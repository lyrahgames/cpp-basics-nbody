#include <iostream>

#include <application.hpp>

using namespace std;

int main(int argc, char** argv) {
  if (2 != argc) {
    cout << "usage: " << argv[0] << " <file_path>\n";
    return -1;
  }

  // Use RAII principle for application.
  // Construct, initialize, execute and automatically destroy.
  application app{argv[1]};
  app.execute();
}