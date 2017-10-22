/*
 * minimal_automaton.c
 *
 *  Created on: 13 oct. 2017
 *      Author: juven
 */

#include "../../Headers/cdfa_edition_interface.h"



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

	new_aut_temp = cdfa__letter_fusion_automaton(new_aut);

	if (new_aut_temp == NULL){
		fprintf(stderr,"cdfa__minimal_automaton : cdfa__letter_fusion_automaton returned NULL\n");
		cdfa__free_automaton(new_aut);
		return NULL;
	}

	cdfa__free_automaton(new_aut);

	return new_aut_temp;
}


