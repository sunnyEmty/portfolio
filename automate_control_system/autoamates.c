//
// Created by egdan on 02.05.2021.
//

#include "autoamates.h"

static int G_T[19];
static int G_D[19];
int ALL_GOOD = 1;

bool set_switch_times(int a) {
    if (!a) return 0;
    const int d = 1;
    G_T[0] = -1;
    G_D[0] = -1;
    G_T[4 + d] = G_T[15 + d] = G_T[16 + d] = 120;
    G_T[1 + d] = G_T[2 + d] = G_T[3 + d] = G_T[5 + d] = G_T[11 + d] = G_T[14 + d] = 56;
    G_T[18] = G_T[0 + d] = G_T[8 + d] = G_T[9 + d] = 60;
    G_T[7 + d] = G_T[10 + d] = G_T[12 + d] = G_T[13 + d] = 45;
    G_T[6 + d] = 30;

    G_D[2 + d] = G_D[3 + d] = 33;
    G_D[5 + d] = G_D[10 + d] = G_D[11 + d] = G_D[15 + d] = 70;
    G_D[4 + d] = G_D[8 + d] = G_D[9 + d] = G_D[13 + d] = G_D[14 + d] = G_D[16 + d] = 60;
    G_D[6 + d] = G_D[7 + d] = 45;
    G_D[18] = G_D[0 + d] = G_D[1 + d] = G_D[12 + d] = 78;
    //G_T[2] = 1;
    //G_T[4] = 2;
    return true;
}

void init(struct Automate *engine, int size) {
    for (int i = 0; i < size; i++) {
        engine[i].state = STATE_0;
        engine[i].ticks = time(NULL);
        engine[i].output = 0;
        engine[i].at_bottom = 0;
        engine[i].at_top = 0;
        engine[i].can_change = 1;
    }
}

bool control_chang_st(struct Automate *engine, enum States start_state, bool com) {
    int next_state = engine->state + 1;
    if (engine->state == STATE_18) next_state = STATE_1;
    if (engine->state == start_state && A_TIME > G_T[next_state]) // ????
        return false;


    if ((engine->at_top * com || engine->at_bottom * !com)) {
        engine->ticks = time(NULL);
        engine->state = next_state;
        //ALL_GOOD = next_state;
        engine->can_change = false;
        return true;
    }

    if (engine->at_bottom || engine->at_top) {
        engine->output = com;
        engine->ticks = time(NULL);
        return true;
    } else {
        engine->output = com;
    }
    return true;
}

bool send_com(struct Automate *engine, int state, bool com) {
    if (engine->can_change) {
        return control_chang_st(engine, state, com);
    } else if (A_TIME >= G_D[state]) { //
        engine->can_change = true;
        engine->ticks = time(NULL);
        return control_chang_st(engine, state, com);
    }
    return true;
}

bool update_state(struct Automate *engine, bool *commands) {
    switch (engine->state) {

        case STATE_0:
            //return control_chang_st(engine, STATE_0, commands[0]);
            return send_com(engine, STATE_0, commands[0]);

        case STATE_1:
            return send_com(engine, STATE_1, commands[1]);

        case STATE_2:
            return send_com(engine, STATE_2, commands[2]);

        case STATE_3:
            return send_com(engine, STATE_3, commands[3]);

        case STATE_4:
            return send_com(engine, STATE_4, commands[4]);

        case STATE_5:
            return send_com(engine, STATE_5, commands[5]);

        case STATE_6:
            return send_com(engine, STATE_6, commands[6]);

        case STATE_7:
            return send_com(engine, STATE_7, commands[7]);

        case STATE_8:
            return send_com(engine, STATE_8, commands[8]);

        case STATE_9:
            return send_com(engine, STATE_9, commands[9]);

        case STATE_10:
            return send_com(engine, STATE_10, commands[10]);

        case STATE_11:
            return send_com(engine, STATE_11, commands[11]);

        case STATE_12:
            return send_com(engine, STATE_12, commands[12]);

        case STATE_13:
            return send_com(engine, STATE_13, commands[13]);

        case STATE_14:
            return send_com(engine, STATE_14, commands[14]);

        case STATE_15:
            return send_com(engine, STATE_15, commands[15]);

        case STATE_16:
            return send_com(engine, STATE_16, commands[16]);

        case STATE_17:
            return send_com(engine, STATE_17, commands[17]);

        case STATE_18:
            return send_com(engine, STATE_18, commands[0]);

    }
    return false;
}

bool resolve_ex(struct Automate *structs, const int size, const int start_st, bool commands[8][18]) {
    bool ext = true;
    for (int i = 0; i < size; i++) {
        (structs + i)->state = start_st;
        (structs + i)->ticks = time(NULL);
        (structs + i)->can_change = true;
    }
    for (int i = 0; i < size; i++) {
        ext = update_state((structs + i), commands[i]);
        if (!ext) return false;
    }

    return true;
}

void set_err(struct Automate *structs, int size) {
    for (int i = 0; i < size; i++) {
        (structs + i)->state = S_ERR;
        (structs + i)->output = 0;
    }
}

bool synchro(struct Automate *structs, bool commands[8][18], int h) {
    for (int i = 0; i < h; i++) {
        if (!update_state(structs + i, commands[i])) {
            bool success = false;
            switch ((structs + i)->state) {
                case STATE_2: //2
                    success = resolve_ex(structs, h, STATE_4, commands);
                    break;

                case STATE_3:
                    ALL_GOOD = 3222;
                    success = resolve_ex(structs, h, STATE_14, commands);
                    break;

                case STATE_5:
                    success = resolve_ex(structs, h, STATE_9, commands);
                    break;

                case STATE_6:
                    success = resolve_ex(structs, h, STATE_12, commands);
                    break;

                case STATE_7:
                    success = resolve_ex(structs, h, STATE_2, commands);
                    break;

            }

            if (!success) {
                set_err(structs, h);
                return false;
            }
            break;

        }
    }
    return true;

}
