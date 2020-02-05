/*
 * kleen_closure_automatons.c
 *
 *  Created on: 13 oct. 2017
 *      Author: juven
 */


#include "../../../src/Automaton_operations/Headers/cdfa_operation_intern.h"


cdfa__dynamic_states_set_array *cdfa__kleen_plus_new_states(const cdfa__automaton * const a)
{
	unsigned int i;
	unsigned int j;
	cdfa__letter current_letter;
	cdfa__automaton_state next_state;

	const unsigned int nb_initial_states = cdfa__number_of_states(a);
	const unsigned int nb_considered_letters = cdfa__number_of_considered_letters(a);
	const cdfa__letter * const considered_letters = cdfa__considered_letter(a);
	const cdfa__automaton_state initial_starting_state = cdfa__starting_state(a);

	cdfa__dynamic_states_set_array *treated_states_sets = NULL;
	cdfa__dynamic_states_set_array *states_sets_to_treat = NULL;

	cdfa__bool *current_states_set = NULL;
	cdfa__bool *next_states_set = NULL;


	treated_states_sets = cdfa__new_dynamic_states_set_array(nb_initial_states,nb_initial_states*nb_initial_states);
	states_sets_to_treat = cdfa__new_dynamic_states_set_array(nb_initial_states,nb_initial_states*nb_initial_states);

	current_states_set = cdfa__new_empty_states_set(nb_initial_states);
	current_states_set[initial_starting_state] = CDFA__TRUE;

	next_states_set = cdfa__new_empty_states_set(nb_initial_states);

	cdfa__add_in_array(current_states_set,states_sets_to_treat);

	while (!cdfa__is_the_array_empty(states_sets_to_treat)){

		current_states_set = cdfa__remove_last_element_from_array(states_sets_to_treat);
		cdfa__add_in_array(current_states_set,treated_states_sets);

		for (i = 0 ; i < nb_considered_letters ; i++){

			current_letter = considered_letters[i];

			for (j = 0 ; j < nb_initial_states ; j++){

				if (current_states_set[j]){

					next_state = cdfa__next_state(current_letter,j,a);
					next_states_set[next_state] = CDFA__TRUE;

					if (cdfa__is_a_final_state(next_state,a)){
						next_states_set[initial_starting_state] = CDFA__TRUE;
					}
				}
			}

			if (!cdfa__is_in_array(next_states_set,treated_states_sets)
				&& !cdfa__is_in_array(next_states_set,states_sets_to_treat)){

				cdfa__add_in_array(next_states_set,states_sets_to_treat);
				next_states_set = cdfa__new_empty_states_set(nb_initial_states);

			} else {
				cdfa__empty_the_states_set(nb_initial_states,next_states_set);
			}
		}
	}

	cdfa__free_dynamic_states_set_array(states_sets_to_treat);
	free(next_states_set);

	return treated_states_sets;
}





cdfa__automaton *cdfa__raw_kleen_plus_automaton(const cdfa__automaton * const a)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;
	cdfa__letter current_letter;
	cdfa__automaton_state next_state;

	const unsigned int nb_initial_states = cdfa__number_of_states(a);
	const unsigned int nb_considered_letters = cdfa__number_of_considered_letters(a);
	const cdfa__letter * const considered_letters = cdfa__considered_letter(a);
	const cdfa__automaton_state initial_starting_state = cdfa__starting_state(a);

	cdfa__automaton * new_aut = NULL;
	cdfa__dynamic_states_set_array *new_states_array = NULL;

	cdfa__bool *current_states_set = NULL;
	cdfa__bool next_states_set[nb_initial_states];
	unsigned int next_states_set_index;


	new_states_array = cdfa__kleen_plus_new_states(a);

	new_aut = cdfa__empty_automaton(new_states_array->nb_states_sets + 1,nb_considered_letters,considered_letters);

	for (i = 0 ; i < new_states_array->nb_states_sets ; i++){

		current_states_set = new_states_array->states_sets[i];

		for (j = 0 ; j < nb_considered_letters ; j++){

			current_letter = considered_letters[j];

			for (k = 0 ; k < nb_initial_states ; k++){
				next_states_set[k] = CDFA__FALSE;
			}

			for (k = 0 ; k < nb_initial_states ; k++){

				if (current_states_set[k]){
					next_state = cdfa__next_state(current_letter,k,a);
					next_states_set[next_state] = CDFA__TRUE;

					if (cdfa__is_a_final_state(next_state,a)){
						next_states_set[initial_starting_state] = CDFA__TRUE;
					}
				}
			}

			next_states_set_index = cdfa__index_of_element_in_array(next_states_set,new_states_array);

			if (next_states_set_index == CDFA_INVALID_INDEX){
				fprintf(stderr,"cdfa__raw_kleen_plus_automaton : cdfa__index_of_element_in_array returned CDFA_INVALID_INDEX\n");
				cdfa__free_dynamic_states_set_array(new_states_array);
				cdfa__free_automaton(new_aut);
				return NULL;
			}

			cdfa__add_transition(i+1,current_letter,next_states_set_index+1,new_aut);
		}

		for (k = 0 ; k < nb_initial_states ; k++){

			if (current_states_set[k] && cdfa__is_a_final_state(k,a)){
				cdfa__set_as_a_final_state(i+1,new_aut);
				break;
			}
		}
	}

	cdfa__set_as_the_starting_state(1,new_aut);

	cdfa__free_dynamic_states_set_array(new_states_array);

	return new_aut;
}




cdfa__automaton *cdfa__kleen_plus_automaton(const cdfa__automaton * const a)
{
	cdfa__automaton *new_aut = NULL;
	cdfa__automaton *temp_aut = NULL;


	temp_aut = cdfa__raw_kleen_plus_automaton(a);

	if (temp_aut == NULL){
		fprintf(stderr,"cdfa__kleen_plus_automaton : cdfa__raw_kleen_plus_automaton returned NULL\n");
		return NULL;
	}

	new_aut = cdfa__minimal_automaton(temp_aut);

	cdfa__free_automaton(temp_aut);

	return new_aut;
}





cdfa__automaton *cdfa__kleen_star_automaton(const cdfa__automaton * const a)
{
	cdfa__automaton *new_aut = NULL;
	cdfa__automaton *temp_aut_1 = NULL;
	cdfa__automaton *temp_aut_2 = NULL;

	temp_aut_1 = cdfa__kleen_plus_automaton(a);

	if (temp_aut_1 == NULL){
		fprintf(stderr,"cdfa__kleen_star_automaton : cdfa__kleen_plus_automaton returned NULL\n");
		return NULL;
	}

	if (cdfa__is_a_final_state(cdfa__starting_state(a),a)){
		return temp_aut_1;
	}

	temp_aut_2 = cdfa__word_recognizing_automaton("");
	new_aut = cdfa__language_union_automaton(temp_aut_1,temp_aut_2);

	cdfa__free_automaton(temp_aut_1);
	cdfa__free_automaton(temp_aut_2);

	return new_aut;
}


