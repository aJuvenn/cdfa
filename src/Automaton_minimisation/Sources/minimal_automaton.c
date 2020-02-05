/*
 * minimal_automaton.c
 *
 *  Created on: 13 oct. 2017
 *      Author: juven
 */

#include "../../../src/Automaton_minimisation/Headers/cdfa_minimisation_intern.h"


cdfa__automaton *cdfa__minimal_automaton(const cdfa__automaton * const a)
{
	cdfa__automaton * new_aut = NULL;
	cdfa__automaton * new_aut_temp = NULL;


	new_aut = cdfa__accessible_states_automaton(a);

	new_aut_temp = cdfa__coaccessible_states_automaton(new_aut);

	cdfa__free_automaton(new_aut);
	new_aut = cdfa__states_fusion_automaton(new_aut_temp);

	cdfa__free_automaton(new_aut_temp);
	new_aut_temp = cdfa__letter_fusion_automaton(new_aut);

	cdfa__free_automaton(new_aut);

	return new_aut_temp;
}


