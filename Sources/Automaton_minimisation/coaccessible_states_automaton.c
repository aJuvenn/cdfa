/*
 * coaccessible_states_automaton.c

 *
 *  Created on: 22 oct. 2017
 *      Author: juven
 */

#include "../../Headers/cdfa_edition_interface.h"


unsigned int **cdfa__new_matrix(const unsigned int height, const unsigned int width){

	unsigned *array = NULL ;
	unsigned **matrix = NULL ;
	unsigned int i ;

	if (height == 0 || width == 0){
		return NULL;
	}

	array = malloc(width*height*sizeof(unsigned int));

	if (array == NULL){
		fprintf(stderr,"new_matrix : malloc returned NULL\n");
		return NULL ;
	}

	matrix = malloc(height*sizeof(unsigned int *));

	if (matrix == NULL){
		fprintf(stderr,"new_matrix : malloc returned NULL\n");
		free(array);
		return NULL ;
	}

	for (i = 0 ; i < height ; i++){
		matrix[i] = array + i*width ;
	}


	return matrix;
}



cdfa__automaton_state ***cdfa__new_state_triple_matrix(const unsigned int height,
												  const unsigned int width,
												  const unsigned int depth){

	unsigned int i;
	cdfa__automaton_state *array = NULL;
	cdfa__automaton_state **width_array = NULL;
	cdfa__automaton_state ***new_matrix = NULL;

	if (height == 0 || width == 0 || depth == 0){
		return NULL;
	}

	array = malloc(height*width*depth*sizeof(cdfa__automaton_state));

	if (array == NULL){
		fprintf(stderr,"new_state_triple_matrix : malloc returned NULL\n");
		return NULL ;
	}

	width_array = malloc(height*width*sizeof(cdfa__automaton_state *));

	if (width_array == NULL){
		fprintf(stderr,"new_state_triple_matrix : malloc returned NULL\n");
		free(array);
		return NULL ;
	}

	for (i = 0 ; i < width*height ; i++){
		width_array[i] = array + i*depth;
	}

	new_matrix = malloc(height*sizeof(cdfa__automaton_state**));

	if (new_matrix == NULL){
		fprintf(stderr,"new_state_triple_matrix : malloc returned NULL\n");
		free(array);
		free(width_array);
		return NULL ;
	}

	for (i = 0 ; i < height ; i++){
		new_matrix[i] = width_array + width*i;
	}

	return new_matrix;
}


void cdfa__free_state_triple_matrix(cdfa__automaton_state ***m)
{
	if (m == NULL){
		return;
	}

	if (m[0] == NULL){
		free(m);
		return;
	}

	if (m[0][0] == NULL){
		free(m[0]);
		free(m);
		return;
	}

	free(m[0][0]);
	free(m[0]);
	free(m);

}


void cdfa__free_matrix(unsigned int **m)
{
	if (m != NULL){

		if (m[0] != NULL){
			free(m[0]);
		}

		free(m);
	}
}


int cdfa__coaccessible_states_and_usefull_letters(int is_a_coaccessible_state[],
												   int is_a_usefull_letter[],
												   const cdfa__automaton * const a)
{
	unsigned int i,j;
	cdfa__automaton_state current_state, next_state, current_previous_state;
	cdfa__letter current_letter;

	unsigned int nb_initial_states = cdfa__number_of_states(a);

	unsigned int nb_initial_considered_letters = cdfa__number_of_considered_letters(a);
	const cdfa__letter * const initial_considered_letters = cdfa__considered_letter(a);

	unsigned int nb_current_previous_states;
	unsigned int **nb_previous_states = NULL ;
	cdfa__automaton_state ***previous_states = NULL;

	unsigned int nb_states_to_treat = 0;
	cdfa__automaton_state states_to_treat[nb_initial_states];


	nb_previous_states = cdfa__new_matrix(nb_initial_states,nb_initial_considered_letters);

	if (nb_previous_states == NULL && nb_initial_considered_letters != 0){
		fprintf(stderr,"cdfa__coaccessible_states_and_usefull_letters : cdfa__new_matrix returned NULL\n");
		return 0;
	}

	for (i = 0 ; i < nb_initial_states ; i++){
		for (j = 0 ; j < nb_initial_considered_letters ; j++){
			nb_previous_states[i][j] = 0;
		}
	}


	previous_states = cdfa__new_state_triple_matrix(nb_initial_states,nb_initial_considered_letters,nb_initial_states);

	if (previous_states == NULL && nb_initial_considered_letters != 0){
		fprintf(stderr,"cdfa__coaccessible_states_and_usefull_letters : cdfa__new_state_triple_matrix returned NULL\n");
		cdfa__free_matrix(nb_previous_states);
		return 0;
	}


	for (j = 0 ; j < nb_initial_considered_letters ; j++){

		current_letter = initial_considered_letters[j];

		for (i = 0 ; i < nb_initial_states ; i++){

			next_state = cdfa__provide_next_state(current_letter,i,a);
			previous_states[next_state][j][nb_previous_states[next_state][j]++] = i;
		}
	}

	for (i = 0 ; i < nb_initial_considered_letters ; i++){
		is_a_usefull_letter[i] = 0;
	}

	for (i = 0 ; i < nb_initial_states ; i++){

		if (cdfa__is_a_final_state(i,a)){
			is_a_coaccessible_state[i] = 1;
			states_to_treat[nb_states_to_treat++] = i;
		}
		else {
			is_a_coaccessible_state[i] = 0;
		}
	}

	while (nb_states_to_treat != 0){

		current_state = states_to_treat[--nb_states_to_treat];

		for (j = 0 ; j < nb_initial_considered_letters ; j++){

			current_letter = initial_considered_letters[j];
			nb_current_previous_states = nb_previous_states[current_state][j];

			for (i = 0 ; i < nb_current_previous_states ; i++){

				is_a_usefull_letter[j] = 1;
				current_previous_state = previous_states[current_state][j][i];

				if (!is_a_coaccessible_state[current_previous_state]){
					is_a_coaccessible_state[current_previous_state] = 1;
					states_to_treat[nb_states_to_treat++] = current_previous_state;
				}
			}
		}
	}

	cdfa__free_matrix(nb_previous_states);
	cdfa__free_state_triple_matrix(previous_states);

	return 1;
}







cdfa__automaton *cdfa__coaccessible_states_automaton(const cdfa__automaton * const a)
{

	unsigned int i,j;
	cdfa__letter current_letter;
	cdfa__automaton_state next_state, new_current_state, new_next_state;

	unsigned int nb_initial_states = cdfa__number_of_states(a);
	unsigned int nb_initial_considered_letters = cdfa__number_of_considered_letters(a);
	const cdfa__letter * const initial_considered_letters = cdfa__considered_letter(a);

	int is_a_coaccessible_state[nb_initial_states];
	int is_a_usefull_letter[nb_initial_considered_letters];

	unsigned int nb_states_to_keep = 0;
	cdfa__automaton_state new_states_traduction_table[nb_initial_states];

	unsigned int nb_letters_to_keep = 0;
	cdfa__letter letters_to_keep[nb_initial_considered_letters];

	cdfa__automaton *new_aut = NULL;


	if (cdfa__coaccessible_states_and_usefull_letters(is_a_coaccessible_state,is_a_usefull_letter,a) == 0){
		fprintf(stderr,"cdfa__coaccessible_states_automaton : cdfa__coaccessible_states_and_usefull_letters returned 0\n");
		return NULL;
	}


	for (i = 0 ; i < nb_initial_states ; i++){

		if (is_a_coaccessible_state[i] || i == CDFA_WELL){
			new_states_traduction_table[i] = nb_states_to_keep++;
		}
		else {
			new_states_traduction_table[i] = CDFA_INVALID_STATE;
		}
	}


	for (i = 0 ; i < nb_initial_considered_letters ; i++){

		if (is_a_usefull_letter[i]){
			letters_to_keep[nb_letters_to_keep++] = initial_considered_letters[i];
		}
	}


	new_aut = cdfa__empty_automaton(nb_states_to_keep,nb_letters_to_keep,letters_to_keep);

	if (new_aut == NULL){
		fprintf(stderr,"cdfa__coaccessible_states_automaton : cdfa__empty_automaton returned NULL\n");
		return NULL;
	}


	for (i = 0 ; i < nb_initial_states ; i++){

		if (is_a_coaccessible_state[i]){

			new_current_state = new_states_traduction_table[i];

			for (j = 0 ; j < nb_letters_to_keep ; j++){

				current_letter = letters_to_keep[j];
				next_state = cdfa__provide_next_state(current_letter,i,a);

				if (is_a_coaccessible_state[next_state]){
					new_next_state = new_states_traduction_table[next_state];
					cdfa__add_transition(new_current_state,current_letter,new_next_state,new_aut);
				}
			}

			if (cdfa__is_a_final_state(i,a)){
				cdfa__set_as_a_final_state(new_current_state,new_aut);
			}

		}
	}


	i = cdfa__starting_state(a);

	if (is_a_coaccessible_state[i]){
		cdfa__set_as_the_starting_state(new_states_traduction_table[i],new_aut);
	} else {
		cdfa__set_as_the_starting_state(CDFA_WELL,new_aut);
	}

	cdfa__move_to_starting_state(new_aut);

	return new_aut;
}




