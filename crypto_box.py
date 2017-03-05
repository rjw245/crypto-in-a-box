#!/usr/bin/env python

import serial


class CryptoBox(object):
    # Largest input to encryption whose
    # result's length will still fit in
    # on byte
    MAX_LEN_TO_ENC = 239

    # Max uint8
    MAX_LEN_TO_DEC = 0xFF

    # Extra bytes tacked onto
    # encrypted data
    CRYPTO_OVERHEAD = 16

    def __init__(self, port):
        self.dev = serial.Serial(port, 115200)

    def encrypt(self, input):
        """
        @brief      Encrypt a string with crypto box.

        @param      serial_port  The serial port
        @param      input        The input, no newline at the end

        @return     The input, encrypted
        """
        if len(input) > self.MAX_LEN_TO_ENC:
            raise OverflowError("Input too long to encrypt")

        input_fmtd = chr(len(input) & 0xFF)+input+"E"
        self.dev.write(input_fmtd)
        response = ""
        while len(response) < len(input) + self.CRYPTO_OVERHEAD:
            response += self.dev.read()
        return response

    def decrypt(self, input):
        """
        @brief      Decrypt a string with crypto box.

        @param      serial_port  The serial port
        @param      input        The input, no newline at the end

        @return     The input, decrypted
        """
        if len(input) > self.MAX_LEN_TO_DEC:
            raise OverflowError("Input too long to decrypt")

        input_fmtd = chr(len(input) & 0xFF)+input+"D"
        self.dev.write(input_fmtd)
        response = ""
        while len(response) < len(input) - self.CRYPTO_OVERHEAD:
            response += self.dev.read()
        return response
