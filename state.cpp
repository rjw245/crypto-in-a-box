

#include "state.h"

static void default_event_recv_char(crypto_state_t * state, char c) {
    // Spin in same state
    return;
}

static void default_event_fsm_step(crypto_state_t * state) {
    // Spin in same state
    return;
}

void state_init_default(crypto_state_t * state) {
    state->recv_char = default_event_recv_char;
    state->fsm_step = default_event_fsm_step;
}

