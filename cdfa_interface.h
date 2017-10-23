/*
 * cdfa_interface.h
 *
 *  Created on: 13 oct. 2017
 *      Author: juven
 */

#ifndef CDFA_INTERFACE_H_
#define CDFA_INTERFACE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned int cdfa__automaton_state;
#define CDFA_WELL ((cdfa__automaton_state) 0)
#define CDFA_INVALID_STATE ((cdfa__automaton_state) -1)

typedef unsigned char cdfa__letter;
#define CDFA_NB_LETTER 256
#define CDFA_UNKNOWN_CHAR ((unsigned int) -1)

typedef unsigned char cdfa__bool;
#define CDFA_TRUE ((cdfa__bool) 1)
#define CDFA_FALSE ((cdfa__bool) 0)

struct cdfa__automaton;
typedef struct cdfa__automaton cdfa__automaton;



unsigned int cdfa__number_of_states(const cdfa__automaton * const a);

cdfa__automaton_state cdfa__starting_state(const cdfa__automaton * const a);

cdfa__automaton_state cdfa__current_state(const cdfa__automaton * const a);

cdfa__automaton_state cdfa__provide_next_state(const cdfa__letter l, const cdfa__automaton_state q, const cdfa__automaton * const a);

cdfa__automaton_state cdfa__move_to_next_state(const cdfa__letter l, cdfa__automaton * const a);

int cdfa__is_a_final_state(const cdfa__automaton_state q, const cdfa__automaton * const a);

void cdfa__move_to_starting_state(cdfa__automaton * const a);

int cdfa__move_to_state(const cdfa__automaton_state q, cdfa__automaton * const a);


void cdfa__print_automaton(const cdfa__automaton * const a);

void cdfa__free_automaton(cdfa__automaton * const a);







#endif /* CDFA_INTERFACE_H_ */
