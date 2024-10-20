#include "LFSR.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <bitset>
#include <iostream>
#include <string>

sf::Image decrypt_image(sf::Image img, LFSR lsfr, size_t message_length);
std::string extract_message_from_image(sf::Image img, size_t message_length);
std::string convert_to_binary(const std::string &input);  // Function to convert password to binary

inline void show_usage() {
    std::cout << "Invalid arguments usage." << std::endl;
    std::cout << "------- Usage -------" << std::endl;
    std::cout << "PhotoMagicDecrypt <input file name> <output file name> <binary string or -p password> <tap number>" << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc < 5) {
        show_usage();
        return EXIT_FAILURE;
    }

    std::string init_seed;
    int tap = atoi(argv[4]);

    if (strcmp(argv[3], "-p") == 0) {
        if (strlen(argv[4]) > 16) {
            std::cout << "The length of the password must be less than or equal to 16 characters." << std::endl;
            show_usage();
            return EXIT_FAILURE;
        }

        init_seed = convert_to_binary(argv[4]);
    } else {
        init_seed = argv[3];
    }

    sf::Image encrypted_image;
    if (!encrypted_image.loadFromFile(argv[1])) {
        std::cerr << "Failed to load the image file." << std::endl;
        return EXIT_FAILURE;
    }

    LFSR lsfr(init_seed, tap);

    // Ask for the length of the hidden message
    size_t message_length;
    std::cout << "Enter the length of the hidden message: ";
    std::cin >> message_length;

    // Decrypt the image using the LFSR
    sf::Image decrypted_image = decrypt_image(encrypted_image, lsfr, message_length);

    // Extract the hidden message from the decrypted image
    std::string extracted_message = extract_message_from_image(decrypted_image, message_length);
    std::cout << "Extracted message: " << extracted_message << std::endl;

    // Save the decrypted image
    if (!decrypted_image.saveToFile(argv[2])) {
        std::cerr << "Failed to save the decrypted image." << std::endl;
        return EXIT_FAILURE;
    }

    return 0;
}


// Decrypt the image using the same LFSR sequence (XOR symmetric)
sf::Image decrypt_image(sf::Image img, LFSR lsfr, size_t message_length) {
    sf::Color p;

    size_t message_bits = message_length * 8;  // Total bits in the message
    int pixels_needed = (message_bits + 2) / 3;  // Number of pixels needed
    int pixels_processed = 0;
    int lfsr_call_count = 0;

    for (int y = 0; y < img.getSize().y && pixels_processed < pixels_needed; y++) {
        for (int x = 0; x < img.getSize().x && pixels_processed < pixels_needed; x++) {
            p = img.getPixel(x, y);

            // Generate LFSR value for the pixel
            int lfsr_value = lsfr.generate(8);
            lfsr_call_count++;  // Increment LFSR call counter

            // Reverse the LFSR XOR encryption
            p.r = lfsr_value ^ p.r;
            p.g = lfsr_value ^ p.g;
            p.b = lfsr_value ^ p.b;

            img.setPixel(x, y, p);

            pixels_processed++;

            if (pixels_processed >= pixels_needed) {
                std::cout << "Decryption complete at pixel (" << x << ", " << y << ")" << std::endl;
                break;
            }
        }
    }

    std::cout << "Total LFSR calls during decryption: " << lfsr_call_count << std::endl;

    return img;
}





// Extract the hidden message from the least significant bits of the image pixels
std::string extract_message_from_image(sf::Image img, size_t message_length) {
    std::string binary_message;
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

// Convert a string (password) to a binary representation
std::string convert_to_binary(const std::string &input) {
    std::string binary_string;
    for (char c : input) {
        binary_string.append(std::bitset<8>(c).to_string());
    }
    return binary_string;
}
