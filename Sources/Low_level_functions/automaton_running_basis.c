/*
 * automaton_running_basis.c
 *
 *  Created on: 30 sept. 2017
 *      Author: juven
 */

#include "../../Headers/automaton_structure.h"



unsigned int cdfa__number_of_states(const cdfa__automaton * const a)
{
	return a->nb_states;
}


cdfa__automaton_state cdfa__starting_state(const cdfa__automaton * const a)
{
	return a->starting_state;
}


cdfa__automaton_state cdfa__current_state(const cdfa__automaton * const a)
{
	return a->current_state;
}


cdfa__automaton_state cdfa__provide_next_state(const cdfa__letter l, const cdfa__automaton_state q, const cdfa__automaton * const a)
{
	const unsigned int char_index = a->char_translation_table[l];

	if (char_index == CDFA_UNKNOWN_CHAR || q >= a->nb_states){
		return CDFA_WELL;
	}

	return a->transitions[q][char_index];
}


cdfa__automaton_state cdfa__move_to_next_state(const cdfa__letter l, cdfa__automaton * const a)
{
	return a->current_state = cdfa__provide_next_state(l,a->current_state,a);
}


int cdfa__is_a_final_state(const cdfa__automaton_state q, const cdfa__automaton * const a)
{
	if (q >= a->nb_states){
		return 0;
	}

	return a->is_a_final_state[q];
}


void cdfa__move_to_starting_state(cdfa__automaton * const a)
{
	a->current_state = a->starting_state;
}


int cdfa__move_to_state(const cdfa__automaton_state q, cdfa__automaton * const a)
{
	if (q >= a->nb_states){
		return 0;
	}

	a->current_state = q;

	return 1;
}



/*
 * Display an automaton
 */




void cdfa__print_automaton(const cdfa__automaton * const a)
{
	unsigned int i;
	unsigned int j;
	unsigned int nb_considered_char = 0;

	printf("\n\n PRINT AUTOMATON \nnb_states : %u\n",a->nb_states);
	printf("starting_state : %u\n",a->starting_state);
	printf("current_state : %u\n",a->current_state);

	printf("List of the final states :\n\t{ ");

	for (i = 0 ; i < a->nb_states ; i++){
		if (a->is_a_final_state[i]){
			printf("%d ",i);
		}
	}
	printf("}\n");



	printf("Number of considered letters : %u\n",a->nb_considered_letters);
	printf("Considered letters : \n\t{ ");

	for (i = 0 ; i < CDFA_NB_LETTER ; i++){
		if (a->char_translation_table[i] != CDFA_UNKNOWN_CHAR){
			nb_considered_char++;
			printf("%c(%u) ",(char) i,a->char_translation_table[i]);
		}
	}
	printf("}\n");

	if (nb_considered_char != a->nb_considered_letters){
		printf("WARNING : number of found letters does not match !\n");
	}

	printf("Transitions :\n\t      ");

	for (j = 0 ; j < a->nb_considered_letters ; j++){

		i = 0;

		while (a->char_translation_table[i] != j){
			i++;
		}

		printf("%c ",(char)i);
	}

	printf("\n");

	for (i = 0 ; i < a->nb_states ; i++){

		printf("\t%u : { ",i);

		for (j = 0 ; j < a->nb_considered_letters ; j++){

			if (a->transitions[i][j] == CDFA_WELL){
				printf(". ");
			} else {
				printf("%u ",a->transitions[i][j]);
			}
		}
		printf("}");

		if (a->is_a_final_state[i]){
			printf("*");
		}
		if (i == a->starting_state){
			printf(" <--");
		}
		printf("\n");

	}
	printf("\n\n");
}


/*
 * Free automaton
 */



void cdfa__free_automaton(cdfa__automaton * const a)
{

	if (a != NULL){

		if (a->is_a_final_state != NULL){
			free(a->is_a_final_state);
		}

		if (a->transitions != NULL){

			if (a->transitions[0] != NULL){
				free(a->transitions[0]);
			}

			free(a->transitions);
		}

		free(a);
	}
}



