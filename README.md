# crypto-in-a-box
Turns an Arduino (I used a RedStick from Sparkfun) in a cryptography token, allowing you to encrypt and decrypt messages with an unknown secret key using the NaCl encryption algorithm.

The protocol is as follows:

| Byte 0    | Byte 1 | ... | Byte N-1 | Byte N     |
| --------- | ------ | --- | -------- | ---------- |
| Input len | Input  | ... | Input    | 'E' or 'D' |

Sending an 'E' as the last character tells the Arduino to attempt to
encrypt the input, and send back the result.

Sending a 'D' as the last character tells the Arduino to attempt to
decrypt the input, and send back the result.

This was a cool opportunity to experiment with a few different things:
- NaCl encryption with the TweetNaCl library written in C
- State machine design patterns in C

The Arduino running this program effectively becomes a security "token", or in other words, a physical device one needs in order to create/parse encrypted messages. This was a cool concept to explore: secrets embedded in a physical device.

I was also inspired by the book "Patterns in C", which describes a few software design patterns and their implementations in C. This project was a great opportunity to use a state machine, as different actions need to be taken as character inputs come in. You'll notice that despite Arduino supporting C++ (and thus object-oriented design which would make implementing the STATE pattern that much easier) I've stuck to C constructs exclusively, for my own benefit. I use C day to day and want to get better at implementing desing patterns without object-oriented language support.
