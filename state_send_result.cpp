
#include "state_send_result.h"

#include <stdint.h>
#include <string.h>

#include "state_idle.h"

static const char * result = NULL;
static uint8_t result_len = 0;

extern void print(const char * buf, uint16_t len);

static void send_result_fsm_step(crypto_state_t * state) {
    print(result, result_len);
    transition_to_idle(state);
}


void transition_to_send_result(crypto_state_t * state, const char * res, uint16_t res_len) {
    result = res;
    result_len = res_len;

    state_init_default(state);
    state->fsm_step = send_result_fsm_step;
}
