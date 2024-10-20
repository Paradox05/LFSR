#include "LFSR.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <bitset>
#include <cstring>
#include <iostream>
#include <string>

sf::Image transform_image(sf::Image img, LFSR lsfr, const std::string &binary_message);
std::string convert_to_binary(const std::string &input);
std::string extract_message_from_image(sf::Image img, size_t message_length);

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

int main(int argc, char *argv[]) {
    if (argc < 5) {
        show_usage();
        return EXIT_FAILURE;
    }

    std::string init_seed;
    int tap = atoi(argv[4]);

    // This means they are using an alphanumeric password
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
        //std::cout << "Binary seed: " << init_seed << std::endl;

    } else {
        // Initialize the seed to the binary string from argument
        init_seed = argv[3];
    }

    sf::Image input_file, out_file;
    sf::Texture input_texture, output_texture;
    sf::Sprite input_sprite, output_sprite;

    // Try to load the file from the passed argument
    if (!input_file.loadFromFile(argv[1])) {
        return EXIT_FAILURE;
    }

    // Load image to the texture object
    input_texture.loadFromImage(input_file);
    // Set the sprite with the texture of the input
    input_sprite.setTexture(input_texture);

    // Initialize the LFSR
    LFSR lsfr(init_seed, tap);

    // Ask the user for a message to embed in the image
    std::string message;
    std::cout << "Enter a message to hide in the image: ";
    std::getline(std::cin, message);

    // Convert the message to binary
    std::string binary_message = convert_to_binary(message);

    // Transform the image and embed the message
    out_file = transform_image(input_file, lsfr, binary_message);

    // Save the output image with the hidden message
    if (!out_file.saveToFile(argv[2])) {
        return EXIT_FAILURE;
    }
    std::cout << "Image saved as " << argv[2] << std::endl;

    // Optionally, extract the hidden message to verify
    std::string extracted_message = extract_message_from_image(out_file, message.length());
    std::cout << "Extracted message: " << extracted_message << std::endl;

    return 0;
}

// Transform the image using LFSR and embed the message into the LSB of the pixels
sf::Image transform_image(sf::Image img, LFSR lsfr, const std::string &binary_message) {
    sf::Color p;
    size_t message_index = 0;
    size_t message_length = binary_message.length();

    int lfsr_call_count = 0;  // Counter for LFSR calls

    for (unsigned int y = 0; y < img.getSize().y && message_index < message_length; y++) {
        for (unsigned int x = 0; x < img.getSize().x && message_index < message_length; x++) {
            p = img.getPixel(x, y);

            // **First, embed the message bits into the LSBs**
            if (message_index < message_length) {
                p.r = (p.r & ~1) | (binary_message[message_index++] - '0');
            }
            if (message_index < message_length) {
                p.g = (p.g & ~1) | (binary_message[message_index++] - '0');
            }
            if (message_index < message_length) {
                p.b = (p.b & ~1) | (binary_message[message_index++] - '0');
            }

            // **Then, apply LFSR encryption to the pixel**
            int lfsr_value = lsfr.generate(8);
            lfsr_call_count++;

            p.r = lfsr_value ^ p.r;
            p.g = lfsr_value ^ p.g;
            p.b = lfsr_value ^ p.b;

            img.setPixel(x, y, p);

            if (message_index >= message_length) {
                std::cout << "Message fully embedded at pixel (" << x << ", " << y << ")" << std::endl;
                break;
            }
        }
    }

    std::cout << "Total LFSR calls during encryption: " << lfsr_call_count << std::endl;

    return img;
}





// Convert a string message to a binary representation
std::string convert_to_binary(const std::string &input) {
    std::string binary_string;
    for (char c : input) {
        binary_string.append(std::bitset<8>(c).to_string());
    }
    return binary_string;
}

// Extract the hidden message from the image
std::string extract_message_from_image(sf::Image img, size_t message_length) {
    std::string binary_message;
    std::cout << message_length << std::endl;
    binary_message.reserve(message_length * 8); // Reserve space for binary message

    sf::Color p;

    for (unsigned int y = 0; y < img.getSize().y; ++y) {
        for (unsigned int x = 0; x < img.getSize().x; ++x) {
            p = img.getPixel(x, y);

            // Extract bits from the LSB of the RGB channels
            binary_message.push_back((p.r & 1) + '0');
            if (binary_message.size() >= message_length * 8) break;

            binary_message.push_back((p.g & 1) + '0');
            if (binary_message.size() >= message_length * 8) break;

            binary_message.push_back((p.b & 1) + '0');
            if (binary_message.size() >= message_length * 8) break;
        }
        if (binary_message.size() >= message_length * 8) break;
    }

    // Convert the binary string back to the original message
    std::string message;
    for (size_t i = 0; i < binary_message.length(); i += 8) {
        std::bitset<8> char_bits(binary_message.substr(i, 8));
        message.push_back(static_cast<char>(char_bits.to_ulong()));
    }

    return message;
}
