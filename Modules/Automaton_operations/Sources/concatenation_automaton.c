/*
 * concatenation_automaton.c
 *
 *  Created on: 13 oct. 2017
 *      Author: juven
 */


#include "../Headers/cdfa_operation_intern.h"


cdfa__dynamic_states_set_array *cdfa__language_concatenation_new_states(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2)
{
	unsigned int i;
	unsigned int j;
	cdfa__letter current_letter;
	cdfa__automaton_state next_state;

	const unsigned int nb_initial_states_1 = cdfa__number_of_states(a_1);
	const unsigned int nb_considered_letters_1 = cdfa__number_of_considered_letters(a_1);
	const cdfa__automaton_state initial_starting_state_1 = cdfa__starting_state(a_1);

	const unsigned int nb_initial_states_2 = cdfa__number_of_states(a_2);
	const unsigned int nb_considered_letters_2 = cdfa__number_of_considered_letters(a_2);
	const cdfa__automaton_state initial_starting_state_2 = cdfa__starting_state(a_2);

	const unsigned int nb_initial_states_sum = nb_initial_states_1 + nb_initial_states_2;
	cdfa__letter new_letters_to_consider[nb_considered_letters_1 + nb_considered_letters_2];
	const unsigned int nb_new_letters_to_consider = cdfa__union_of_the_letters_to_consider(new_letters_to_consider,a_1,a_2);

	cdfa__dynamic_states_set_array *treated_states_sets = NULL;
	cdfa__dynamic_states_set_array *states_sets_to_treat = NULL;

	cdfa__bool *current_states_set = NULL;
	cdfa__bool *next_states_set = NULL;



	treated_states_sets = cdfa__new_dynamic_states_set_array(nb_initial_states_sum,nb_initial_states_sum*nb_initial_states_sum);

	if (treated_states_sets == NULL){
		fprintf(stderr,"cdfa__language_concatenation_new_states : cdfa__new_dynamic_states_set_array returned NULL\n");
		return NULL;
	}



	states_sets_to_treat = cdfa__new_dynamic_states_set_array(nb_initial_states_sum,nb_initial_states_sum*nb_initial_states_sum);

	if (states_sets_to_treat == NULL){
		fprintf(stderr,"cdfa__language_concatenation_new_states : cdfa__new_dynamic_states_set_array returned NULL\n");
		free(treated_states_sets);
		return NULL;
	}



	current_states_set = cdfa__new_empty_states_set(nb_initial_states_sum);

	if (current_states_set == NULL){
		fprintf(stderr,"cdfa__language_concatenation_new_states : cdfa__new_empty_states_set returned NULL\n");
		free(treated_states_sets);
		free(states_sets_to_treat);
		return NULL;
	}

	current_states_set[initial_starting_state_1] = CDFA_TRUE;

	if (cdfa__is_a_final_state(initial_starting_state_1,a_1)){
		current_states_set[initial_starting_state_2 + nb_initial_states_1] = CDFA_TRUE;
	}


	next_states_set = cdfa__new_empty_states_set(nb_initial_states_sum);

	if (next_states_set == NULL){
		fprintf(stderr,"cdfa__kleen_plus_new_states : cdfa__new_empty_states_set returned NULL\n");
		free(treated_states_sets);
		free(states_sets_to_treat);
		free(current_states_set);
		return NULL;
	}



	cdfa__add_in_array(current_states_set,states_sets_to_treat);

	while (!cdfa__is_the_array_empty(states_sets_to_treat)){

		current_states_set = cdfa__remove_last_element_from_array(states_sets_to_treat);
		cdfa__add_in_array(current_states_set,treated_states_sets);

		for (i = 0 ; i < nb_new_letters_to_consider ; i++){

			current_letter = new_letters_to_consider[i];

			for (j = 0 ; j < nb_initial_states_1 ; j++){

				if (current_states_set[j]){

					next_state = cdfa__provide_next_state(current_letter,j,a_1);
					next_states_set[next_state] = CDFA_TRUE;

					if (cdfa__is_a_final_state(next_state,a_1)){
						next_states_set[initial_starting_state_2 + nb_initial_states_1] = CDFA_TRUE;
					}
				}
			}

			for (j = 0 ; j < nb_initial_states_2 ; j++){

				if (current_states_set[j + nb_initial_states_1]){
					next_state = cdfa__provide_next_state(current_letter,j,a_2);
					next_states_set[next_state + nb_initial_states_1] = CDFA_TRUE;
				}
			}

			if (!cdfa__is_in_array(next_states_set,treated_states_sets)
				&& !cdfa__is_in_array(next_states_set,states_sets_to_treat)){

				cdfa__add_in_array(next_states_set,states_sets_to_treat);
				next_states_set = cdfa__new_empty_states_set(nb_initial_states_sum);
			}
			else {
				cdfa__empty_the_states_set(nb_initial_states_sum,next_states_set);
			}
		}
	}

	cdfa__free_dynamic_states_set_array(states_sets_to_treat);
	free(next_states_set);

	return treated_states_sets;
}








cdfa__automaton *cdfa__raw_language_concatenation_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2)
{
	unsigned int i;
	unsigned int j;
	unsigned int k;
	cdfa__letter current_letter;
	cdfa__automaton_state next_state;

	const unsigned int nb_initial_states_1 = cdfa__number_of_states(a_1);
	const unsigned int nb_considered_letters_1 = cdfa__number_of_considered_letters(a_1);

	const unsigned int nb_initial_states_2 = cdfa__number_of_states(a_2);
	const unsigned int nb_considered_letters_2 = cdfa__number_of_considered_letters(a_2);
	const cdfa__automaton_state initial_starting_state_2 = cdfa__starting_state(a_2);

	const unsigned int nb_initial_states_sum = nb_initial_states_1 + nb_initial_states_2;
	cdfa__letter new_letters_to_consider[nb_considered_letters_1 + nb_considered_letters_2];
	const unsigned int nb_new_letters_to_consider = cdfa__union_of_the_letters_to_consider(new_letters_to_consider,a_1,a_2);

	cdfa__automaton * new_aut = NULL;
	cdfa__dynamic_states_set_array *new_states_array = NULL;

	cdfa__bool *current_states_set = NULL;
	cdfa__bool next_states_set[nb_initial_states_sum];
	unsigned int next_states_set_index;

	new_states_array = cdfa__language_concatenation_new_states(a_1,a_2);

	if (new_states_array == NULL){
		fprintf(stderr,"cdfa___raw_language_concatenation_automaton : cdfa__language_concatenation_new_states returned NULL\n");
		return NULL;
	}

	new_aut = cdfa__empty_automaton(new_states_array->nb_states_sets + 1,nb_new_letters_to_consider,new_letters_to_consider);

	if (new_aut == NULL){
		fprintf(stderr,"cdfa___raw_language_concatenation_automaton : cdfa__empty_automaton returned NULL\n");
		free(new_states_array);
		return NULL;
	}


	for (i = 0 ; i < new_states_array->nb_states_sets ; i++){

		current_states_set = new_states_array->states_sets[i];

		for (j = 0 ; j < nb_new_letters_to_consider ; j++){

			current_letter = new_letters_to_consider[j];

			for (k = 0 ; k < nb_initial_states_sum ; k++){
				next_states_set[k] = CDFA_FALSE;
			}

			for (k = 0 ; k < nb_initial_states_1 ; k++){

				if (current_states_set[k]){
					next_state = cdfa__provide_next_state(current_letter,k,a_1);
					next_states_set[next_state] = CDFA_TRUE;

					if (cdfa__is_a_final_state(next_state,a_1)){
						next_states_set[initial_starting_state_2 + nb_initial_states_1] = CDFA_TRUE;
					}
				}
			}

			for (k = 0 ; k < nb_initial_states_2 ; k++){

				if (current_states_set[k + nb_initial_states_1]){
					next_state = cdfa__provide_next_state(current_letter,k,a_2);
					next_states_set[next_state + nb_initial_states_1] = CDFA_TRUE;
				}
			}

			next_states_set_index = cdfa__index_of_element_in_array(next_states_set,new_states_array);

			if (next_states_set_index == CDFA_INVALID_INDEX){
				fprintf(stderr,"cdfa___raw_language_concatenation_automaton : cdfa__index_of_element_in_array returned CDFA_INVALID_INDEX\n");
				cdfa__free_dynamic_states_set_array(new_states_array);
				cdfa__free_automaton(new_aut);
				return NULL;
			}

			cdfa__add_transition(i+1,current_letter,next_states_set_index+1,new_aut);
		}

		for (k = 0 ; k < nb_initial_states_2 ; k++){

			if (current_states_set[k + nb_initial_states_1] && cdfa__is_a_final_state(k,a_2)){
				cdfa__set_as_a_final_state(i+1,new_aut);
				break;
			}
		}
	}

	cdfa__set_as_the_starting_state(1,new_aut);

	cdfa__free_dynamic_states_set_array(new_states_array);

	return new_aut;
}


cdfa__automaton *cdfa__language_concatenation_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2)
{
	cdfa__automaton *new_aut = NULL;
	cdfa__automaton *temp_aut = NULL;


	temp_aut = cdfa__raw_language_concatenation_automaton(a_1,a_2);

	if (temp_aut == NULL){
		fprintf(stderr,"cdfa__language_concatenation_automaton : cdfa__raw_language_concatenation_automaton returned NULL\n");
		return NULL;
	}

	new_aut = cdfa__minimal_automaton(temp_aut);

	if (new_aut == NULL){
		fprintf(stderr,"cdfa__language_concatenation_automaton : cdfa__minimal_automaton returned NULL\n");
		cdfa__free_automaton(temp_aut);
		return NULL;
	}

	cdfa__free_automaton(temp_aut);

	return new_aut;
}




