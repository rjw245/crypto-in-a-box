
#include "state_decrypt.h"

#include <string.h>
#include "tweetnacl.h"

#include "state.h"
#include "secrets.h"
#include "state_send_result.h"

static char * to_decrypt = NULL;
static uint16_t to_decrypt_len = 0;

static void decrypt_fsm_step(crypto_state_t * state) {
    const uint8_t * nonce = get_nonce();
    const uint8_t * secret_key = get_secret_key();
    crypto_secretbox_open((unsigned char *)to_decrypt,
                          (unsigned char *)to_decrypt,
                          to_decrypt_len,
                          nonce,
                          secret_key);
    const char * result = &to_decrypt[crypto_secretbox_ZEROBYTES];
    const uint8_t result_len = to_decrypt_len - crypto_secretbox_ZEROBYTES;
    transition_to_send_result(state, result, result_len);
}

void transition_to_decrypt(crypto_state_t * state, char * input, uint16_t input_len){
    to_decrypt = input;
    to_decrypt_len = input_len;

    state_init_default(state);
    state->fsm_step = decrypt_fsm_step;
}


