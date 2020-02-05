/*
 * automaton_creation_basis.c
 *
 *  Created on: 30 sept. 2017
 *      Author: juven
 */

#include "../Automaton/cdfa_automaton_structure.h"




/*
 * Creation of a new empty automaton
 */


cdfa__automaton_state **cdfa__new_transition_matrix(const unsigned int nb_state, const unsigned int nb_letter){

	cdfa__automaton_state *state_array = NULL ;
	cdfa__automaton_state **transition_matrix = NULL ;
	unsigned int i ;
	unsigned int j ;

	if (nb_letter == 0){
		return NULL;
	}

	CDFA__MALLOC(state_array,nb_state*nb_letter*sizeof(cdfa__automaton_state));
	CDFA__MALLOC(transition_matrix,nb_state*sizeof(cdfa__automaton_state *));

	for (i = 0 ; i < nb_state ; i++){
		transition_matrix[i] = state_array + i*nb_letter ;
	}

	for (i = 0 ; i < nb_state ; i++){
		for (j = 0 ; j < nb_letter ; j++){
			transition_matrix[i][j] = CDFA__WELL ;
		}
	}

	return transition_matrix;
}





cdfa__automaton *cdfa__empty_automaton(const unsigned int nb_states,
										 const unsigned int nb_considered_letters,
										 const cdfa__letter considered_letters[])
{
	unsigned int i;
	unsigned int actual_nb_states;
	cdfa__automaton *a = NULL ;


	actual_nb_states = nb_states + (nb_states == 0);
	CDFA__MALLOC(a,sizeof(cdfa__automaton));
	a->transitions = NULL;
	a->is_a_final_state = NULL;
	a->nb_considered_letters = nb_considered_letters;
	memcpy(a->considered_letters, considered_letters, nb_considered_letters*sizeof(cdfa__letter));

	for (i = 0 ; i < CDFA__NB_LETTER ; i++){
		a->char_translation_table[i] = CDFA__UNKNOWN_CHAR;
	}

	for (i = 0 ; i < nb_considered_letters ; i++){
		a->char_translation_table[(unsigned char) considered_letters[i]] = i;
	}

	a->nb_states = actual_nb_states;
	a->current_state = CDFA__WELL;
	a->starting_state = CDFA__WELL;
	a->transition_matrix_width = nb_considered_letters;

	CDFA__MALLOC(a->is_a_final_state,actual_nb_states*sizeof(int));

	for (i = 0 ; i < actual_nb_states ; i++){
		a->is_a_final_state[i] = 0;
	}

	a->transitions = cdfa__new_transition_matrix(actual_nb_states,nb_considered_letters);

	return a;
}



/*
 * Edit a new empty automaton
 */


int cdfa__set_as_the_starting_state(const cdfa__automaton_state q, cdfa__automaton * const a){

	if (q >= a->nb_states){
		fprintf(stderr,"cdfa__set_as_the_starting_state : given state \"%u\" out of range [0 ; %u[\n",q,a->nb_states);
		return 0;
	}

	a->starting_state = q;

	return 1;
}


int cdfa__set_as_a_final_state(const cdfa__automaton_state q, cdfa__automaton * const a)
{

	if (q >= a->nb_states){
		fprintf(stderr,"cdfa__set_as_a_final_state : given state \"%u\" out of range [0 ; %u[\n",q,a->nb_states);
		return 0;
	}

	a->is_a_final_state[q] = 1;

	return 1;
}



int cdfa__add_transition(const cdfa__automaton_state src,
						  const cdfa__letter l,
						  const cdfa__automaton_state dst,
						  cdfa__automaton * const a)
{
	unsigned int translated_index = a->char_translation_table[(unsigned char) l];

	if (translated_index == CDFA__UNKNOWN_CHAR){
		fprintf(stderr,"cdfa__add_transition :  unknown given letter \"%c\"\n",(char) l);
		return 0;
	}

	if (src >= a->nb_states || dst >= a->nb_states){
		fprintf(stderr,"cdfa__add_transition : given source state \"%u\" or destination \"%u\" state out of range [0 ; %u[\n",src,dst,a->nb_states);
		return 0;
	}

	a->transitions[src][translated_index] = dst;

	return 1;
}


int cdfa__give_same_meaning_as(const cdfa__letter letter_to_give_meaning_to,
		const cdfa__letter considered_letter_with_meaning,
		cdfa__automaton * const a)
{

	unsigned int new_translated_index;

	new_translated_index = a->char_translation_table[(unsigned char) considered_letter_with_meaning];

	if (new_translated_index == CDFA__UNKNOWN_CHAR){
		fprintf(stderr,"cdfa__give_same_meaning_as : provided considered letter is not\n");
		return 0;
	}

	if (a->char_translation_table[(unsigned char) letter_to_give_meaning_to] != CDFA__UNKNOWN_CHAR){
		fprintf(stderr,"cdfa__give_same_meaning_as : provided unknown letter is not\n");
		return 0;
	}

	a->considered_letters[a->nb_considered_letters++] = letter_to_give_meaning_to;
	a->char_translation_table[(unsigned char) letter_to_give_meaning_to] = new_translated_index;

	return 1;
}






int cdfa__is_a_considered_letter(const cdfa__letter l, const cdfa__automaton * const a)
{
	return a->char_translation_table[(unsigned char) l] != CDFA__UNKNOWN_CHAR;
}


unsigned int cdfa__number_of_considered_letters(const cdfa__automaton * const a)
{
	return a->nb_considered_letters;
}

const cdfa__letter * const cdfa__considered_letter(const cdfa__automaton * const a)
{
	return a->considered_letters;
}













