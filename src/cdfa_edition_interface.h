/*
 * cdfa_edition_interface.h
 *
 *  Created on: 13 oct. 2017
 *      Author: juven
 */

#ifndef CDFA_EDITION_INTERFACE_H_
#define CDFA_EDITION_INTERFACE_H_


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../cdfa_modules.h"


#define CDFA__MALLOC(ptr,size) \
		do {\
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
		} while(0)\


typedef unsigned char cdfa__bool;
#define CDFA__TRUE ((cdfa__bool) 1)
#define CDFA__FALSE ((cdfa__bool) 0)

#define CDFA__NB_LETTER (256)
#define CDFA__UNKNOWN_CHAR ((unsigned int) -1)

typedef char cdfa__letter;

unsigned int cdfa__number_of_states(const cdfa__automaton * const a);

cdfa__automaton *cdfa__empty_automaton(const unsigned int nb_states,
										 const unsigned int nb_considered_letters,
										 const cdfa__letter considered_letters[]);

int cdfa__set_as_the_starting_state(const cdfa__automaton_state q, cdfa__automaton * const a);

int cdfa__set_as_a_final_state(const cdfa__automaton_state q, cdfa__automaton * const a);

int cdfa__add_transition(const cdfa__automaton_state src,
						  const cdfa__letter l,
						  const cdfa__automaton_state dst,
						  cdfa__automaton * const a);

int cdfa__give_same_meaning_as(const cdfa__letter letter_to_give_meaning_to,
		const cdfa__letter considered_letter_with_meaning,
		cdfa__automaton * const a);

int cdfa__is_a_considered_letter(const cdfa__letter l, const cdfa__automaton * const a);

unsigned int cdfa__number_of_considered_letters(const cdfa__automaton * const a);

const cdfa__letter * const cdfa__considered_letter(const cdfa__automaton * const a);


#endif /* CDFA_EDITION_INTERFACE_H_ */
