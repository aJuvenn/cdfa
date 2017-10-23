/*
 * cdfa_module_interface.h
 *
 *  Created on: 22 oct. 2017
 *      Author: juven
 */

#ifndef CDFA_MODULE_INTERFACE_H_
#define CDFA_MODULE_INTERFACE_H_

#include "../cdfa_interface.h"


cdfa__automaton *cdfa__word_recognizing_automaton(const char word[]);

cdfa__automaton *cdfa__letter_choice_automaton(const cdfa__letter char_stack[]);



cdfa__automaton *cdfa__minimal_automaton(const cdfa__automaton * const a);




cdfa__automaton *cdfa__language_concatenation_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2);

cdfa__automaton *cdfa__range_exponentiation_automaton(const unsigned int min_power, const unsigned int max_power, const cdfa__automaton * const a);

cdfa__automaton *cdfa__exponentiation_automaton(const unsigned int power, const cdfa__automaton * const a);

cdfa__automaton *cdfa__language_or_epsilon_automaton(const cdfa__automaton *a);

cdfa__automaton *cdfa__kleen_plus_automaton(const cdfa__automaton * const a);

cdfa__automaton *cdfa__kleen_star_automaton(const cdfa__automaton * const a);

cdfa__automaton *cdfa__language_union_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2);

cdfa__automaton *cdfa__language_intersection_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2);




cdfa__automaton *cdfa__expression_recognizing_automaton(const char * const expression);



#endif /* CDFA_MODULE_INTERFACE_H_ */
