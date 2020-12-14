/*
 * equivalent_letters_automaton.c
 *
 *  Created on: 22 oct. 2017
 *      Author: juven
 */


#include "cdfa_minimisation_intern.h"





cdfa__bool cdfa__are_equivalent_letters(cdfa__letter l_1, cdfa__letter l_2, const cdfa__automaton * const a)
{
	cdfa__automaton_state current_state;
	cdfa__automaton_state next_state_1;
	cdfa__automaton_state next_state_2;

	const unsigned int nb_states = cdfa__get_number_of_states(a);


	for (current_state = CDFA__WELL ; current_state < nb_states ; current_state++){

		next_state_1 = cdfa__get_next_state(l_1,current_state,a);
		next_state_2 = cdfa__get_next_state(l_2,current_state,a);

		if (next_state_1 != next_state_2){
			return CDFA__FALSE;
		}
	}

	return CDFA__TRUE;
}




cdfa__automaton * cdfa__letter_fusion_automaton(const cdfa__automaton * const a)
{

	unsigned int i,j,k;
	cdfa__letter current_letter;
	cdfa__letter current_representative;
	cdfa__automaton_state next_state;

	const unsigned int nb_considered_letters = cdfa__number_of_considered_letters(a);
	const cdfa__letter *considered_letters = cdfa__considered_letter(a);
	const unsigned int nb_states = cdfa__get_number_of_states(a);

	cdfa__bool has_a_representative;

	unsigned int nb_representatives = 0;
	cdfa__letter representatives[nb_considered_letters];

	cdfa__letter representative_of[nb_considered_letters];

	cdfa__automaton * new_aut = NULL;


	for (i = 0 ; i < nb_considered_letters ; i++){

		current_letter = considered_letters[i];
		has_a_representative = CDFA__FALSE;

		for (j = 0 ; j < nb_representatives ; j++){

			current_representative = representatives[j];

			if (cdfa__are_equivalent_letters(current_letter,current_representative,a)){
				representative_of[i] = current_representative;
				has_a_representative = CDFA__TRUE;
				break;
			}
		}

		if (!has_a_representative){
			representative_of[i] = current_letter;
			representatives[nb_representatives++] = current_letter;
		}
	}

	new_aut = cdfa__empty_automaton(nb_states,nb_representatives,representatives);

	for (k = 0 ; k < nb_states ; k++){

		for (j = 0 ; j < nb_representatives ; j++){

			current_representative = representatives[j];
			next_state = cdfa__get_next_state(current_representative,k,a);
			cdfa__add_transition(k,current_representative,next_state,new_aut);
		}

		if (cdfa__is_a_final_state(k,a)){
			cdfa__set_as_a_final_state(k,new_aut);
		}
	}

	cdfa__set_as_the_starting_state(cdfa__get_starting_state(a),new_aut);

	for (i = 0 ; i < nb_considered_letters ; i++){

		current_letter = considered_letters[i];
		current_representative = representative_of[i];

		if (current_letter != current_representative){
			cdfa__give_same_meaning_as(current_letter,current_representative,new_aut);
		}
	}

	return new_aut;
}
