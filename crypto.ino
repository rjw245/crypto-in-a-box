#include "tweetnacl.h"

#define BUFF_SIZE   256

#define STATUS_LED  13

uint8_t testKey[crypto_box_SECRETKEYBYTES];
uint8_t nonce[crypto_box_NONCEBYTES];

uint8_t serial_in_buff[BUFF_SIZE];

// Subtract one so that we store delimiting first
// char in padding space to be erased.
uint8_t char_insert_i = crypto_box_ZEROBYTES - 1;
uint8_t crypto_out_buff[BUFF_SIZE];

void setup() {
    // put your setup code here, to run once:
    Serial.begin(115200);
    pinMode(STATUS_LED, OUTPUT);
    memset(serial_in_buff, 0, sizeof(serial_in_buff));
    memset(crypto_out_buff, 0, sizeof(crypto_out_buff));
}

void loop() {
    if(Serial.available()) {
        serial_in_buff[char_insert_i++] = Serial.read();

        if(serial_in_buff[char_insert_i-1] == '\n' ||
           char_insert_i >= BUFF_SIZE) {
            char enc_or_dec = serial_in_buff[crypto_box_ZEROBYTES - 1];
            serial_in_buff[crypto_box_ZEROBYTES - 1] = 0;

            switch(enc_or_dec) {
                case 'E':
                    {
                        crypto_secretbox(crypto_out_buff, serial_in_buff, char_insert_i - 1, nonce, testKey);
                        int crypto_len = char_insert_i - 1 - crypto_box_ZEROBYTES + crypto_box_BOXZEROBYTES;
                        Serial.write(&crypto_out_buff[crypto_box_BOXZEROBYTES], crypto_len);
                    }
                    break;
                case 'D':
                    {
                        uint8_t * encrypted_start = serial_in_buff + (crypto_box_ZEROBYTES - crypto_box_BOXZEROBYTES);
                        uint8_t encrypted_len = char_insert_i - 1 - crypto_box_ZEROBYTES + crypto_box_BOXZEROBYTES;
                        int success = crypto_secretbox_open(crypto_out_buff, encrypted_start, encrypted_len, nonce, testKey);
                        if(success == -1) {
                            digitalWrite(STATUS_LED, HIGH);
                        } else {
                            digitalWrite(STATUS_LED, LOW);
                        }
                        int crypto_len = encrypted_len - crypto_box_BOXZEROBYTES;
                        Serial.write(&crypto_out_buff[crypto_box_ZEROBYTES], crypto_len);
                    }
                    break;
            }

            // Cleanup
            memset(serial_in_buff, 0, sizeof(serial_in_buff));
            memset(crypto_out_buff, 0, sizeof(crypto_out_buff));
            char_insert_i = crypto_box_ZEROBYTES - 1;
        }
    }
}
