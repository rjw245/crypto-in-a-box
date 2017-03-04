import serial
import time
import sys
import unittest
import random
import string

RESET_DELAY = 2
DELAY = 0.5


def encrypt(serial_port, input):
    """
    @brief      Encrypt a string with crypto box.
    @warning    Can't encrypt newlines

    @param      serial_port  The serial port
    @param      input        The input, no newline at the end

    @return     The input, encrypted
    """
    s = serial_port
    s.write("E"+input+"\n")
    time.sleep(DELAY)
    response = ""
    while s.inWaiting():
            response += s.read()
    return response


def decrypt(serial_port, input):
    """
    @brief      Decrypt a string with crypto box.
    @warning    Can't decrypt newlines

    @param      serial_port  The serial port
    @param      input        The input, no newline at the end

    @return     The input, decrypted
    """
    s = serial_port
    s.write("D"+input+"\n")
    time.sleep(DELAY)
    response = ""
    while s.inWaiting():
            response += s.read()
    return response


class TestCryptoBox(unittest.TestCase):
    def test_encrypt_then_decrypt_matches_input(self):
        s = serial.Serial("/dev/ttyUSB0", 115200)
        time.sleep(RESET_DELAY)

        for i in xrange(0, 100):
            rand_len = random.randint(1, 20)
            input = ''.join(random.choice(string.ascii_uppercase) for _ in range(rand_len))
            print "Input:", input
            encrypted = encrypt(s, input)
            print "Encrypted:", encrypted

            decrypted = decrypt(s, encrypted)
            print "Decrypted:", decrypted

            self.assertTrue(decrypted == input)

if __name__ == "__main__":
    suite = unittest.TestLoader().loadTestsFromTestCase(TestCryptoBox)
    unittest.TextTestRunner(verbosity=2).run(suite)
