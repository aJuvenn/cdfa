/*
 * accessible_states_automaton.c
 *
 *  Created on: 22 oct. 2017
 *      Author: juven
 */


#include "../../Headers/cdfa_edition_interface.h"


cdfa__automaton *cdfa__accessible_states_automaton(const cdfa__automaton * const a)
{
	unsigned int i;
	unsigned int j;
	unsigned int initial_nb_states = cdfa__number_of_states(a);
	unsigned int nb_considered_letters = cdfa__number_of_considered_letters(a);
	cdfa__automaton *new_aut = NULL;
	cdfa__automaton_state working_state;
	cdfa__automaton_state next_state;
	cdfa__letter current_letter;
	const cdfa__letter * const considered_letters = cdfa__considered_letter(a);

	unsigned int nb_states_to_keep = 0;
	cdfa__automaton_state states_to_keep[initial_nb_states];

	int is_a_state_to_keep[initial_nb_states];
	cdfa__automaton_state new_state_value[initial_nb_states];

	unsigned int nb_states_to_treat = 0;
	cdfa__automaton_state states_to_treat[initial_nb_states];



	for (i = 0 ; i < initial_nb_states ; i++){
		is_a_state_to_keep[i] = 0;
		new_state_value[i] = CDFA_INVALID_STATE;
	}

	is_a_state_to_keep[CDFA_WELL] = 1;
	new_state_value[CDFA_WELL] = (cdfa__automaton_state) nb_states_to_keep;
	states_to_keep[nb_states_to_keep++] = CDFA_WELL;

	working_state = cdfa__starting_state(a);

	if (working_state != CDFA_WELL){
		is_a_state_to_keep[working_state] = 1;
		new_state_value[working_state] = (cdfa__automaton_state) nb_states_to_keep;
		states_to_keep[nb_states_to_keep++] = working_state;
	}

	states_to_treat[nb_states_to_treat++] = working_state;

	while (nb_states_to_treat != 0){

		working_state = states_to_treat[--nb_states_to_treat];

		for (i = 0 ; i < nb_considered_letters ; i++){

			current_letter = considered_letters[i];
			next_state = cdfa__provide_next_state(current_letter,working_state,a);

			if (!is_a_state_to_keep[next_state]){
				is_a_state_to_keep[next_state] = 1;
				states_to_treat[nb_states_to_treat++] = next_state;
				new_state_value[next_state] = (cdfa__automaton_state) nb_states_to_keep;
				states_to_keep[nb_states_to_keep++] = next_state;
			}
		}
	}

	new_aut = cdfa__empty_automaton(nb_states_to_keep,nb_considered_letters,considered_letters);

	if (new_aut == NULL){
		fprintf(stderr,"cdfa__accessible_states_automaton : cdfa__empty_automaton returned NULL\n");
		return NULL;
	}

	working_state = cdfa__starting_state(a);
	cdfa__set_as_the_starting_state(new_state_value[working_state],new_aut);

	for (i = 0 ; i < nb_states_to_keep ; i++){

		working_state = states_to_keep[i];

		for (j = 0 ; j < nb_considered_letters ; j++){

			current_letter = considered_letters[j];
			next_state = cdfa__provide_next_state(current_letter,working_state,a);
			cdfa__add_transition(i,current_letter,new_state_value[next_state],new_aut);
		}

		if (cdfa__is_a_final_state(working_state,a)){
			cdfa__set_as_a_final_state(i,new_aut);
		}
	}

	cdfa__move_to_starting_state(new_aut);

	return new_aut;
}



