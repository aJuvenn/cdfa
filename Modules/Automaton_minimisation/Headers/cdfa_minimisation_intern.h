/*
 * cdfa_minimisation_intern.h
 *
 *  Created on: 22 oct. 2017
 *      Author: juven
 */

#ifndef CDFA_MINIMISATION_INTERN_H_
#define CDFA_MINIMISATION_INTERN_H_

#include "../../../cdfa_edition_interface.h"



cdfa__automaton *cdfa__accessible_states_automaton(const cdfa__automaton * const a);

cdfa__automaton *cdfa__coaccessible_states_automaton(const cdfa__automaton * const a);

cdfa__automaton *cdfa__states_fusion_automaton(const cdfa__automaton * const a);

cdfa__automaton * cdfa__letter_fusion_automaton(const cdfa__automaton * const a);


#endif /* CDFA_MINIMISATION_INTERN_H_ */
