/*
 * cdfa_minimisation_intern.h
 *
 *  Created on: 22 oct. 2017
 *      Author: juven
 */

#ifndef CDFA_MINIMISATION_INTERN_H_
#define CDFA_MINIMISATION_INTERN_H_

#include "../cdfa_edition_interface.h"


unsigned int **cdfa__new_matrix(const unsigned int height, const unsigned int width);

void cdfa__free_matrix(unsigned int **m);

cdfa__automaton_state ***cdfa__new_state_triple_matrix(const unsigned int height,
												  const unsigned int width,
												  const unsigned int depth);


void cdfa__free_state_triple_matrix(cdfa__automaton_state ***m);

void cdfa__free_matrix(unsigned int **m);



cdfa__automaton *cdfa__accessible_states_automaton(const cdfa__automaton * const a);

cdfa__automaton *cdfa__coaccessible_states_automaton(const cdfa__automaton * const a);

cdfa__automaton *cdfa__states_fusion_automaton(const cdfa__automaton * const a);

cdfa__automaton * cdfa__letter_fusion_automaton(const cdfa__automaton * const a);


#endif /* CDFA_MINIMISATION_INTERN_H_ */
