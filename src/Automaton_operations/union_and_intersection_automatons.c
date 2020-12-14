/*
 * union_and_intersection_automatons.c
 *
 *  Created on: 13 oct. 2017
 *      Author: juven
 */


#include "cdfa_operation_intern.h"



unsigned int cdfa__union_of_the_letters_to_consider(cdfa__letter dest_letters[],
											  	  	 const cdfa__automaton * const a_1,
											  	  	 const cdfa__automaton * const a_2)
{
	unsigned int nb_letters = 0;
	unsigned int i;

	for (i = 0 ; i < CDFA__NB_LETTER ; i++){

		if (cdfa__is_a_considered_letter(i,a_1) || cdfa__is_a_considered_letter(i,a_2)){
			dest_letters[nb_letters++] = (cdfa__letter) i;
		}
	}

	return nb_letters;
}




cdfa__automaton *cdfa__product_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2)
{
	unsigned int i;
	unsigned int nb_states_1;
	unsigned int nb_states_2;
	unsigned int nb_letters_to_consider;
	cdfa__letter letters_to_consider[CDFA__NB_LETTER];
	cdfa__automaton *new_aut = NULL;
	cdfa__automaton_state q_1;
	cdfa__automaton_state q_2;
	cdfa__automaton_state next_state_1;
	cdfa__automaton_state next_state_2;
	cdfa__automaton_state new_q;
	cdfa__automaton_state new_next_state;
	cdfa__letter current_letter;
	cdfa__automaton_state new_starting_state;


	nb_states_1 = cdfa__get_number_of_states(a_1);
	nb_states_2 = cdfa__get_number_of_states(a_2);
	nb_letters_to_consider = cdfa__union_of_the_letters_to_consider(letters_to_consider,a_1,a_2);
	new_aut = cdfa__empty_automaton(nb_states_1 * nb_states_2,nb_letters_to_consider,letters_to_consider);


	for (i = 0 ; i < nb_letters_to_consider ; i++){

		current_letter = letters_to_consider[i];

		for (q_1 = 0 ; q_1 < nb_states_1 ; q_1++){

			next_state_1 = cdfa__get_next_state(current_letter,q_1,a_1);

			for (q_2 = 0 ; q_2 < nb_states_2 ; q_2++){

				next_state_2 = cdfa__get_next_state(current_letter,q_2,a_2);
				new_q = q_1 + nb_states_1 * q_2;
				new_next_state = next_state_1 + nb_states_1 * next_state_2;

				cdfa__add_transition(new_q,current_letter,new_next_state,new_aut);
			}
		}
	}

	new_starting_state = cdfa__get_starting_state(a_1) + nb_states_1 * cdfa__get_starting_state(a_2);
	cdfa__set_as_the_starting_state(new_starting_state,new_aut);
	cdfa__move_to_starting_state(new_aut);

	return new_aut;
}



cdfa__automaton *cdfa__raw_language_union_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2)
{
	cdfa__automaton_state q_1;
	cdfa__automaton_state q_2;
	unsigned int nb_states_1 = cdfa__get_number_of_states(a_1);
	unsigned int nb_states_2 = cdfa__get_number_of_states(a_2);
	cdfa__automaton *new_aut = NULL;


	new_aut = cdfa__product_automaton(a_1,a_2);

	for (q_1 = 0 ; q_1 < nb_states_1 ; q_1++){

		for (q_2 = 0 ; q_2 < nb_states_2 ; q_2++){

			if (cdfa__is_a_final_state(q_1,a_1) || cdfa__is_a_final_state(q_2,a_2)){
				cdfa__set_as_a_final_state(q_1 + nb_states_1 * q_2,new_aut);
			}
		}
	}

	return new_aut;
}



cdfa__automaton *cdfa__raw_language_intersection_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2)
{
	cdfa__automaton_state q_1;
	cdfa__automaton_state q_2;
	unsigned int nb_states_1 = cdfa__get_number_of_states(a_1);
	unsigned int nb_states_2 = cdfa__get_number_of_states(a_2);
	cdfa__automaton *new_aut = NULL;


	new_aut = cdfa__product_automaton(a_1,a_2);

	for (q_1 = 0 ; q_1 < nb_states_1 ; q_1++){

		for (q_2 = 0 ; q_2 < nb_states_2 ; q_2++){

			if (cdfa__is_a_final_state(q_1,a_1) && cdfa__is_a_final_state(q_2,a_2)){
				cdfa__set_as_a_final_state(q_1 + nb_states_1 * q_2,new_aut);
			}
		}
	}

	return new_aut;
}



cdfa__automaton *cdfa__raw_language_exclusion_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2)
{
	cdfa__automaton_state q_1;
	cdfa__automaton_state q_2;
	unsigned int nb_states_1 = cdfa__get_number_of_states(a_1);
	unsigned int nb_states_2 = cdfa__get_number_of_states(a_2);
	cdfa__automaton *new_aut = NULL;


	new_aut = cdfa__product_automaton(a_1,a_2);

	for (q_1 = 0 ; q_1 < nb_states_1 ; q_1++){

		for (q_2 = 0 ; q_2 < nb_states_2 ; q_2++){

			if (cdfa__is_a_final_state(q_1,a_1) && !cdfa__is_a_final_state(q_2,a_2)){
				cdfa__set_as_a_final_state(q_1 + nb_states_1 * q_2,new_aut);
			}
		}
	}

	return new_aut;
}




cdfa__automaton *cdfa__language_union_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2)
{
	cdfa__automaton *new_aut = NULL;
	cdfa__automaton *temp_aut = NULL;


	temp_aut = cdfa__raw_language_union_automaton(a_1,a_2);

	new_aut = cdfa__minimal_automaton(temp_aut);

	cdfa__free_automaton(temp_aut);

	return new_aut;
}



cdfa__automaton *cdfa__language_intersection_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2)
{
	cdfa__automaton *new_aut = NULL;
	cdfa__automaton *temp_aut = NULL;


	temp_aut = cdfa__raw_language_intersection_automaton(a_1,a_2);

	new_aut = cdfa__minimal_automaton(temp_aut);

	cdfa__free_automaton(temp_aut);

	return new_aut;
}



cdfa__automaton *cdfa__language_exclusion_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2)
{
	cdfa__automaton *new_aut = NULL;
	cdfa__automaton *temp_aut = NULL;


	temp_aut = cdfa__raw_language_exclusion_automaton(a_1,a_2);

	new_aut = cdfa__minimal_automaton(temp_aut);

	cdfa__free_automaton(temp_aut);

	return new_aut;
}







