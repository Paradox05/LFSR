# LFSR Image Encryption and Decryption

This project provides a program for **encrypting** and **decrypting** images using a **Linear Feedback Shift Register (LFSR)** to hide a message within an image. The encryption and decryption processes ensure that both the image content and the hidden message are secured.

## Features

- **Hide messages** in an image using LFSR-based encryption.
- **Encrypt** and **decrypt** the image using a seed and a tap position for the LFSR.
- **Secure the hidden message** by encrypting the least significant bits (LSBs) of the image pixels.
- Supports images in formats like `.png`.

## How It Works

- **Encryption**: The program hides the message in the LSBs of the image pixels, then encrypts the entire image using LFSR-based XOR encryption.
- **Decryption**: The program reverses the encryption and extracts the hidden message from the LSBs of the decrypted image.

## Prerequisites

- **C++17** or higher
- **SFML** (Simple and Fast Multimedia Library)
- [SFML Installation Instructions](https://www.sfml-dev.org/download.php)

On macOS, you can install SFML with Homebrew:

```bash
brew install sfml
```
## Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/LFSR-Image-Encryption.git
   cd LFSR-Image-Encryption
   ```
2. Compile the project using the Makefile:
    ```bash
    make
    ```
This will compile two executables:

- photomagic: For encrypting images and hiding messages.
- photomagicdecrypt: For decrypting images and extracting hidden messages.


## Usage
### Encrypt an Image and Hide a Message

To encrypt an image and hide a message, use the photomagic program:

  ```bash
  ./photomagic <input_image> <output_encrypted_image> -p <password> <tap_number>
  ```
- The program will prompt you to enter a message to hide in the image.

### Decrypt an Image and Retrieve the Hidden Message

To decrypt an image and retrieve the hidden message, use the photomagicdecrypt program:

  ```bash 
  ./photomagicdecrypt <input_encrypted_image> <output_decrypted_image> -p <password> <tap_number>
  ```
- The program will prompt you to enter the length of the hidden message.
- The decrypted image will be saved to the specified output file, and the extracted message will be displayed.

## Example Workflow
1.) Encrypting an image:
  ```bash
  ./photomagic astronaut_skull.png encrypted_astronaut.png -p pass 16
  ```
output:
  ```mathematica
  Enter a message to hide in the image: hello
  Message fully embedded at pixel (13, 0)
  Total LFSR calls during encryption: 14
  Image saved as encrypted_astronaut.png
  ```
2.) Decrypting the image:
  ```bash
  ./photomagicdecrypt encrypted_astronaut.png decrypted_astronaut.png -p pass 16
  ```
ouput:
  ```yaml
  Enter the length of the hidden message: 5
  Decryption complete at pixel (13, 0)
  Total LFSR calls during decryption: 14
  Extracted message: hello
  ```

## Project Structure
  ```bash
  .
  ├── LFSR.hpp               # LFSR class header
  ├── LFSR.cpp               # LFSR class implementation
  ├── photomagic.cpp         # Encryption program
  ├── photomagicdecrypt.cpp  # Decryption program
  ├── Makefile               # Build instructions
  └── README.md              # Project description
  ```
## How the LFSR Works

The Linear Feedback Shift Register (LFSR) is used to generate a pseudo-random sequence of bits, which is used for encryption. The LFSR takes a seed (binary string) and a tap position to generate this sequence. The output of the LFSR is XORed with the image pixel data during both encryption and decryption.


## Author

- **Paradox05**
- [GitHub Profile](https://github.com/Paradox05)
