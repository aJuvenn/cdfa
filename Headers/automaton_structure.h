/*
 * automaton_structure.h
 *
 *  Created on: 30 sept. 2017
 *      Author: juven
 */

#ifndef AUTOMATON_STRUCTURE_H_
#define AUTOMATON_STRUCTURE_H_


#include "cdfa_interface.h"



struct cdfa__automaton {

	cdfa__automaton_state starting_state;
	cdfa__automaton_state current_state;

	unsigned int nb_states;
	int *is_a_final_state;

	unsigned int nb_considered_letters;
	cdfa__letter considered_letters[CDFA_NB_LETTER];
	unsigned int char_translation_table[CDFA_NB_LETTER];

	cdfa__automaton_state **transitions;
};


#endif /* AUTOMATON_STRUCTURE_H_ */
