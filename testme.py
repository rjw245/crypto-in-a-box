import serial
import time
import sys
import unittest
import random
import string

from crypto_box import CryptoBox

RESET_DELAY = 2


class TestCryptoBox(unittest.TestCase):
    def test_encrypt_then_decrypt_matches_input(self):
        crypto = CryptoBox("/dev/ttyUSB0")
        time.sleep(RESET_DELAY)

        print ""
        for i in xrange(0, 100):
            input_len = 239 #random.randint(1, 233)
            possible_chars = [chr(x) for x in xrange(0, 256)]
            input = ''.join(random.choice(possible_chars) for _ in range(input_len))
            encrypted = crypto.encrypt(input)

            decrypted = crypto.decrypt(encrypted)
            self.assertTrue(decrypted == input)
            sys.stdout.write(".")
            sys.stdout.flush()

if __name__ == "__main__":
    suite = unittest.TestLoader().loadTestsFromTestCase(TestCryptoBox)
    unittest.TextTestRunner(verbosity=2).run(suite)
