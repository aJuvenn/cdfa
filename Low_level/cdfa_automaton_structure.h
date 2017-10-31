/*
 * cdfa_automaton_structure.h
 *
 *  Created on: 22 oct. 2017
 *      Author: juven
 */

#ifndef CDFA_AUTOMATON_STRUCTURE_H_
#define CDFA_AUTOMATON_STRUCTURE_H_

#include "../cdfa_interface.h"

struct cdfa__automaton {

	cdfa__automaton_state starting_state;
	cdfa__automaton_state current_state;

	unsigned int nb_states;
	int *is_a_final_state;

	unsigned int nb_considered_letters;
	cdfa__letter considered_letters[CDFA__NB_LETTER];

	unsigned int char_translation_table[CDFA__NB_LETTER];

	unsigned int transition_matrix_width;
	cdfa__automaton_state **transitions;
};

#endif /* CDFA_AUTOMATON_STRUCTURE_H_ */
