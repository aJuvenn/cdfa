/*
 * minimal_automaton.c
 *
 *  Created on: 13 oct. 2017
 *      Author: juven
 */

#include "../Headers/cdfa_edition_interface.h"



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







unsigned int **cdfa__new_matrix(const unsigned int height, const unsigned int width){

	unsigned *array = NULL ;
	unsigned **matrix = NULL ;
	unsigned int i ;

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
	if (m != NULL){

		if (m[0] != NULL){

			if (m[0][0] != NULL){
				free(m[0][0]);
			}

			free(m[0]);
		}

		free(m);
	}
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

	if (nb_previous_states == NULL){
		fprintf(stderr,"cdfa__coaccessible_states_and_usefull_letters : cdfa__new_matrix returned NULL\n");
		return 0;
	}

	for (i = 0 ; i < nb_initial_states ; i++){
		for (j = 0 ; j < nb_initial_considered_letters ; j++){
			nb_previous_states[i][j] = 0;
		}
	}


	previous_states = cdfa__new_state_triple_matrix(nb_initial_states,nb_initial_considered_letters,nb_initial_states);

	if (previous_states == NULL){
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






unsigned int **cdfa__equivalent_states_matrix(const cdfa__automaton * const a)
{
	unsigned int i,j,k;
	cdfa__automaton_state i_next_state, j_next_state;
	cdfa__letter current_letter;

	unsigned int nb_initial_states = cdfa__number_of_states(a);
	unsigned int nb_considered_letters = cdfa__number_of_considered_letters(a);
	const cdfa__letter * const considered_letters = cdfa__considered_letter(a);

	cdfa__bool is_a_final_state;
	cdfa__bool set_is_reducing;
	unsigned int **are_equivalent = cdfa__new_matrix(nb_initial_states,nb_initial_states);


	if (are_equivalent == NULL){
		fprintf(stderr,"cdfa__equivalent_states_matrix : cdfa__new_matrix returned NULL\n");
		return NULL;
	}


	for (i = 0 ; i < nb_initial_states ; i++){

		is_a_final_state = cdfa__is_a_final_state(i,a);

		for (j = 0 ; j < nb_initial_states ; j++){
			are_equivalent[i][j] =  (is_a_final_state == cdfa__is_a_final_state(j,a));
		}
	}

	do {

		set_is_reducing = CDFA_FALSE;

		for (i = 0 ; i < nb_initial_states ; i++){

			for (j = 0 ; j < i ; j++){

				if (are_equivalent[i][j]){

					for (k = 0 ; k < nb_considered_letters ; k++){

						current_letter = considered_letters[k];
						i_next_state = cdfa__provide_next_state(current_letter,i,a);
						j_next_state = cdfa__provide_next_state(current_letter,j,a);

						if (!are_equivalent[i_next_state][j_next_state]){
							are_equivalent[i][j] = CDFA_FALSE;
							are_equivalent[j][i] = CDFA_FALSE;
							set_is_reducing  = CDFA_TRUE;
							break;
						}
					}
				}
			}
		}

	} while (set_is_reducing);

	return are_equivalent;
}




cdfa__automaton *cdfa__states_fusion_automaton(const cdfa__automaton * const a)
{

	unsigned int i,j;
	cdfa__letter current_letter;
	cdfa__automaton_state new_state,new_next_state;

	unsigned int nb_initial_states = cdfa__number_of_states(a);
	unsigned int nb_considered_letters = cdfa__number_of_considered_letters(a);
	const cdfa__letter * const considered_letters = cdfa__considered_letter(a);

	unsigned int nb_representatives = 0;
	cdfa__automaton_state representatives[nb_initial_states];
	cdfa__automaton_state index_of_representative_of[nb_initial_states];

	cdfa__automaton *new_aut = NULL;
	unsigned int **are_equivalent = NULL;
	int has_a_representative;

	are_equivalent = cdfa__equivalent_states_matrix(a);

	if (are_equivalent == NULL){
		fprintf(stderr,"cdfa__states_fusion_automaton : cdfa__equivalent_states_matrix returned NULL\n");
		return NULL;
	}

	for (i = 0 ; i < nb_initial_states ; i++){

		has_a_representative = 0;

		for (j = 0 ; j < nb_representatives ; j++){

			if (are_equivalent[i][representatives[j]]){
				index_of_representative_of[i] = j;
				has_a_representative = 1;
				break;
			}
		}

		if (!has_a_representative){
			representatives[nb_representatives] = i;
			index_of_representative_of[i] = nb_representatives;
			nb_representatives++;
		}
	}

	new_aut = cdfa__empty_automaton(nb_representatives,nb_considered_letters,considered_letters);

	if (new_aut == NULL){
		fprintf(stderr,"cdfa__empty_automaton : cdfa__equivalent_states_matrix returned NULL\n");
		cdfa__free_matrix(are_equivalent);
		return NULL;
	}


	for (i = 0 ; i < nb_initial_states ; i++){

		new_state = index_of_representative_of[i];

		for (j = 0 ; j < nb_considered_letters ; j++){

			current_letter = considered_letters[j];
			new_next_state = index_of_representative_of[cdfa__provide_next_state(current_letter,i,a)];

			cdfa__add_transition(new_state,current_letter,new_next_state,new_aut);
		}

		if (cdfa__is_a_final_state(i,a)){
			cdfa__set_as_a_final_state(new_state,new_aut);
		}
	}

	new_state = index_of_representative_of[cdfa__starting_state(a)];
	cdfa__set_as_the_starting_state(new_state,new_aut);
	cdfa__move_to_starting_state(new_aut);

	cdfa__free_matrix(are_equivalent);

	return new_aut;
}





cdfa__automaton *cdfa__minimal_automaton(const cdfa__automaton * const a)
{
	cdfa__automaton * new_aut = NULL;
	cdfa__automaton * new_aut_temp = NULL;


	new_aut = cdfa__accessible_states_automaton(a);

	if (new_aut == NULL){
		fprintf(stderr,"cdfa__minimal_automaton : cdfa__accessible_states_automaton returned NULL\n");
		return NULL;
	}

	new_aut_temp = cdfa__coaccessible_states_automaton(new_aut);

	if (new_aut_temp == NULL){
		fprintf(stderr,"cdfa__minimal_automaton : cdfa__coaccessible_states_automaton returned NULL\n");
		cdfa__free_automaton(new_aut);
		return NULL;
	}

	cdfa__free_automaton(new_aut);
	new_aut = cdfa__states_fusion_automaton(new_aut_temp);

	if (new_aut == NULL){
		fprintf(stderr,"cdfa__minimal_automaton : cdfa__states_fusion_automaton returned NULL\n");
		cdfa__free_automaton(new_aut_temp);
		return NULL;
	}

	cdfa__free_automaton(new_aut_temp);

	return new_aut;
}


