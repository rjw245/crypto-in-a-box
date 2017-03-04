
#include "state_encrypt.h"

#include <string.h>
#include "tweetnacl.h"

#include "state.h"
#include "secrets.h"
#include "state_send_result.h"

static char * to_encrypt = NULL;
static uint16_t to_encrypt_len = 0;

static void encrypt_fsm_step(crypto_state_t * state) {
    const uint8_t * nonce = get_nonce();
    const uint8_t * secret_key = get_secret_key();
    crypto_secretbox((unsigned char *)to_encrypt,
                          (unsigned char *)to_encrypt,
                          to_encrypt_len,
                          nonce,
                          secret_key);
    const char * result = &to_encrypt[crypto_secretbox_BOXZEROBYTES];
    const uint8_t result_len = to_encrypt_len - crypto_secretbox_BOXZEROBYTES;
    transition_to_send_result(state, result, result_len);
}

void transition_to_encrypt(crypto_state_t * state, char * input, uint16_t input_len){
    to_encrypt = input;
    to_encrypt_len = input_len;

    state_init_default(state);
    state->fsm_step = encrypt_fsm_step;
}
