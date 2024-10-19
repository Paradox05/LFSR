# LFSR Image Encryption and Decryption

This project demonstrates the use of a Linear Feedback Shift Register (LFSR) to encrypt and decrypt images. An LFSR is a type of shift register that operates on a binary sequence, using the XOR (exclusive OR) function to produce pseudorandom outputs. These outputs are then used for encryption.

The encryption process works as follows: we input a key, perform XOR operations with the image data, and shift the bits through the LFSR. This scrambles the image, producing the encrypted output. To decrypt the image, we simply repeat the XOR operation with the same key, which reverts the image back to its original form.

The core of this project is the correct implementation of the LFSR and the associated XOR operations. Ensuring both are properly executed is crucial for successful encryption and decryption. Without them, the process would fail, and the original image could not be restored.

Through this project, I gained a deeper understanding of LFSRs and their application in encryption. I also explored the XOR operation's properties and how it can be leveraged for reversible encryption in secure communication.
