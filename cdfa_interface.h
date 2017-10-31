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
#define CDFA__WELL ((cdfa__automaton_state) 0)
#define CDFA__INVALID_STATE ((cdfa__automaton_state) -1)

typedef char cdfa__letter;
#define CDFA__NB_LETTER 256
#define CDFA__UNKNOWN_CHAR ((unsigned int) -1)

typedef unsigned char cdfa__bool;
#define CDFA__TRUE ((cdfa__bool) 1)
#define CDFA__FALSE ((cdfa__bool) 0)

struct cdfa__automaton;
typedef struct cdfa__automaton cdfa__automaton;

#define CDFA__MALLOC(ptr,size) \
	if ((size) == 0){ \
		ptr = NULL; \
	} else { \
		ptr = malloc(size); \
		if (ptr == NULL){ \
			fprintf(stderr,"CDFA FATAL ERROR : malloc returned NULL for a size of %u bytes.\n",(unsigned int) (size)); \
			fflush(stderr); \
			exit(1); \
		} \
	} \



unsigned int cdfa__number_of_states(const cdfa__automaton * const a);

cdfa__automaton_state cdfa__starting_state(const cdfa__automaton * const a);

cdfa__automaton_state cdfa__current_state(const cdfa__automaton * const a);

cdfa__automaton_state cdfa__provide_next_state(const cdfa__letter l, const cdfa__automaton_state q, const cdfa__automaton * const a);

cdfa__automaton_state cdfa__move_to_next_state(const cdfa__letter l, cdfa__automaton * const a);

int cdfa__is_a_final_state(const cdfa__automaton_state q, const cdfa__automaton * const a);

cdfa__automaton_state cdfa__move_to_starting_state(cdfa__automaton * const a);

int cdfa__move_to_state(const cdfa__automaton_state q, cdfa__automaton * const a);


void cdfa__print_automaton(const cdfa__automaton * const a);

void cdfa__free_automaton(cdfa__automaton * const a);







#endif /* CDFA_INTERFACE_H_ */
