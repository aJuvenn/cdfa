/*
 * equivalent_states_fusion.c
 *
 *  Created on: 22 oct. 2017
 *      Author: juven
 */

#include "../Headers/cdfa_minimisation_intern.h"


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
