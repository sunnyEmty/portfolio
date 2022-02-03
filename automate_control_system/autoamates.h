//
// Created by egdan on 01.05.2021.
//

#ifndef PRACTICE9_AUTOAMATES_H
#define PRACTICE9_AUTOAMATES_H
#if defined(__cplusplus)
extern "C" {
#endif

#include "stdbool.h"
#include "time.h"
#define MOVE_UP 1
#define MOVE_DOWN 0
#define A_TIME time(NULL) - engine->ticks

enum States {
    STATE_0 = 0,
    STATE_1 = 1,
    STATE_2 = 2,
    STATE_3 = 3,
    STATE_4 = 4,
    STATE_5 = 5,
    STATE_6 = 6,
    STATE_7 = 7,
    STATE_8 = 8,
    STATE_9 = 9,
    STATE_10 = 10,
    STATE_11 = 11,
    STATE_12 = 12,
    STATE_13 = 13,
    STATE_14 = 14,
    STATE_15 = 15,
    STATE_16 = 16,
    STATE_17 = 17,
    STATE_18 = 18,
    S_ERR = -1,

};


// В
struct Automate {
    int state;
    bool at_bottom;
    bool at_top;
    bool output;
    long int ticks;
    bool can_change;
};
bool set_switch_times(int a);
void init(struct Automate* engine, int size);
bool synchro(struct Automate* structs, bool commands[8][18], int h);
bool update_state(struct Automate* engine, bool* commands);
bool send_com(struct Automate* engine, int state, bool com);
bool resolve_ex(struct Automate* structs, const int size, const int start_st, bool commands[8][18]);
bool control_chang_st(struct Automate* engine, enum States start_state, bool com);
void set_err(struct Automate* structs, int size);


#if defined(__cplusplus)
}
#endif
#endif //PRACTICE9_AUTOAMATES_H
