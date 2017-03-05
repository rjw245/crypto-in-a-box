
#include "state_buffer.h"

#include <string.h>
#include "tweetnacl.h"

#include "state_encrypt.h"
#include "state_decrypt.h"
#include "state_idle.h"

// Need crypto_secretbox_ZEROBYTES of room at the beginning
// AND crypto_secretbox_BOXZEROBYTES at the end.
// The crypto_secretbox_BOXZEROBYTES allows an encrypted input to fit
// in the buffer when storage STARTS at index [crypto_secretbox_ZEROBYTES]
#define BUFFER_SIZE (256 + \
                     crypto_secretbox_ZEROBYTES + \
                     crypto_secretbox_BOXZEROBYTES)

static uint8_t input_len = 0;
static uint8_t input_i = 0;
static char input_buffer[BUFFER_SIZE];

static void buffer_recv_char(crypto_state_t * state, char c) {
    if(input_i < input_len) {
        input_buffer[crypto_secretbox_ZEROBYTES + input_i++] = c;
    } else {
        if(c == 'D') {
            char * decrypt_start = input_buffer + crypto_secretbox_ZEROBYTES - crypto_secretbox_BOXZEROBYTES;
            uint16_t decrypt_len = input_len + crypto_secretbox_BOXZEROBYTES;
            transition_to_decrypt(state, decrypt_start, decrypt_len);
        }
        else if(c == 'E') {
            uint16_t encrypt_len = input_len + crypto_secretbox_ZEROBYTES;
            transition_to_encrypt(state, input_buffer, encrypt_len);
        }
        else {
            transition_to_idle(state);
        }
    }
}

void transition_to_buffer(crypto_state_t * state, uint8_t input_l) {
    input_len = input_l;
    input_i = 0;
    memset(input_buffer, 0, sizeof(input_buffer));

    state_init_default(state);
    state->recv_char = buffer_recv_char;
}
