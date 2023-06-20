#include <"LFSR.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <bitset>
#include <cstring>
#include <iostream>
#include <string>

sf::Image transform_image(sf::Image, LFSR)

    inline void show_usage() {
  std::cout << "Invalid arguments usage." << std::endl;
  std::cout << "------- Usage -------" << std::endl;
  std::cout << "Example:" << std::endl;
  std::cout << "PhotoMagic <input file name> <output file name> "
               "<binary string> <tap number>"
            << std::endl;
  std::cout << "Using alpha numeric password:" << std::endl;
  std::cout << "PhotoMagic <input file name> <output file name> "
               "-p <password string> <tap number>"
            << std::endl;
}

std::string convert_to_binary(std::string);

int main(int argc, char *argv[]) {
  if (argc < 5) {
    show_usage();
    return EXIT_FAILURE;
  }

  std::string init_seed;
  int tap = atoi(argv[4]);

  // This means they are using a alphanumeric password
  if (strcmp(argv[3], "-p") == 0) {
    if (strlen(argv[4]) > 16) {
      std::cout << "The length of the password must be less "
                   "or equal to 16 characters."
                << std::endl;
      show_usage();
      return EXIT_FAILURE;
    }

    // Convert the password to binary
    init_seed = convert_to_binary(argv[4]);
  } else {
    // Initialize the seed to the binary string from argument
    init_seed = argv[3];
  }

  sf::Image input_file, out_file;
  sf::Texture input_texture, output_texture;
  sf::Sprite input_sprite, output_sprite;

  // Try to load the file from the passed argument,
  // if fail, return EXIT_FAILURE
  if (!input_file.loadFromFile(argv[1])) {
    return EXIT_FAILURE;
  }

  photomagic
      .cpp
          // Load image to the texture object
          input_texture.loadFromImage(input_file);
  // Set the sprite with the texture of the input
  input_sprite.setTexture(input_texture);

  LFSR lsfr(init_seed, tap);

  out_file = transform_image(input_file, lsfr);
  output_texture.loadFromImage(out_file);
  output_sprite.setTexture(output_texture);

  // Get the size of the input image
  sf::Vector2u input_size = input_file.getSize();

  // Instanciate to RenderWindow with the size of the input image
  sf::RenderWindow window_one(sf::VideoMode(input_size.x, input_size.y),
                              "Input"),
      window_two(sf::VideoMode(input_size.x, input_size.y), "Output");

  // This vector holds the position for the output window,
  // relative to the input window
  sf::Vector2i win_two_position(
      window_one.getPosition().x + input_file.getSize().x,
      window_one.getPosition().y + input_file.getSize().y);

  while (window_one.isOpen() && window_two.isOpen()) {
    sf::Event event;
    while (window_one.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window_one.close();
    }
    while (window_two.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window_two.close();
    }

    window_one.clear(sf::Color::White);
    window_one.draw(input_sprite);
    window_one.display();

    window_two.setPosition(win_two_position);
    window_two.clear(sf::Color::White);
    window_two.draw(output_sprite);
    window_two.display();
  }
  if (!out_file.saveToFile(argv[2])) {
    return EXIT_FAILURE;
  }
  return 0;
}

sf::Image transform_image(sf::Image img, LFSR lsfr) {
  sf::Color p;

  for (int y = 0; y < img.getSize().y; y++) {
    for (int x = 0; x < img.getSize().x; x++) {
      p = img.getPixel(x, y);
      p.r = lsfr.generate(8) ^ p.r;
      p.g = lsfr.generate(8) ^ p.g;
      p.b = lsfr.generate(8) ^ p.b;
      photomagic.cpp Tue Feb 26 10 : 28 : 49 2019 3 img.setPixel(x, y, p);
    }
  }
  return img;
}

std::string convert_to_binary(std::string password_input) {
  std::string binary_string;
  for (std::size_t i = 0; i < password_input.length(); i++) {
    binary_string.append(std::bitset<2>(password_input.c_str()[i]).to_string());
  }
  return binary_string;
}
