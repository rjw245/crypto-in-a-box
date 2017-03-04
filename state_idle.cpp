

#include "state_idle.h"

#include <stdint.h>

#include "state_buffer.h"

static void idle_recv_char(crypto_state_t * state, char c) {
    transition_to_buffer(state, (uint8_t)c);
}

void transition_to_idle(crypto_state_t * state) {
    state_init_default(state);
    state->recv_char = idle_recv_char;
}
