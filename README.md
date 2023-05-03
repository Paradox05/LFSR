# LFSR

This program uses a linear feedback shift register, this is a register that takes a Boolean exclusive 
OR function and performs various steps to it. This includes shifting the bits one position to the left, and 
replaces the remaining bits by exclusive OR. The reason we use an LFSR is because when we encrypt 
the key we can always go back to it by XOR. Basically we give it a key we XOR it, and that's 
encrypted then we XOR it again and we are back to the original. I was able to accomplish this to and 
I was able to take an image encrypt it and decoded it to get back to the original image. 

 The main design to be able to get this assignment working was a working implementation of how 
the Linear Feedback Shift Register (LFSR). Making sure this was implemented correctly was the most 
important part of the assignment because if this dint work then we wouldn't be able to encrypt the 
image, and we also had to make sure our XOR operations worked properly otherwise we wouldn't be 
able to go back to our original image. 

I learned how to use an LFSR to encrypt and decode images to be able to send secret messages. I 
also learned more about how the XOR operation worked and the uses for it aswell. 
