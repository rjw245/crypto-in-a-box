#ifndef STATE_ENCRYPT_H
#define STATE_ENCRYPT_H

#include "state.h"

#include <stdint.h>

void transition_to_encrypt(crypto_state_t * state, char * input, uint16_t input_len);

#endif // STATE_ENCRYPT_H

