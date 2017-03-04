
#ifndef STATE_DECRYPT_H
#define STATE_DECRYPT_H

#include "state.h"

#include <stdint.h>

void transition_to_decrypt(crypto_state_t * state, char * input, uint16_t input_len);

#endif // STATE_DECRYPT_H
