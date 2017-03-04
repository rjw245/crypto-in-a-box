

#ifndef STATE_H
#define STATE_H

typedef struct crypto_state_struct crypto_state_t;

typedef void (*event_recv_char) (crypto_state_t * state, char c);
typedef void (*event_fsm_step) (crypto_state_t * state);

struct crypto_state_struct {
    event_recv_char recv_char;
    event_fsm_step fsm_step;
};

void state_init_default(crypto_state_t * state);

#endif // STATE_H
