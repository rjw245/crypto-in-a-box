

#ifndef STATE_BUFFER_H
#define STATE_BUFFER_H

#include "state.h"

#include <stdint.h>

void transition_to_buffer(crypto_state_t * state, uint8_t input_l);

#endif // STATE_BUFFER_H
