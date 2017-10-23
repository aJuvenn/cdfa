/*
 * cdfa_edition_interface.h
 *
 *  Created on: 13 oct. 2017
 *      Author: juven
 */

#ifndef CDFA_EDITION_INTERFACE_H_
#define CDFA_EDITION_INTERFACE_H_

#include "cdfa_interface.h"

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
