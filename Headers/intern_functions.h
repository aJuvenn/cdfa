/*
 * intern_functions.h
 *
 *  Created on: 13 oct. 2017
 *      Author: juven
 */

#ifndef INTERN_FUNCTIONS_H_
#define INTERN_FUNCTIONS_H_

#include "cdfa_interface.h"


cdfa__automaton *cdfa__word_recognizing_automaton(const char word[]);

cdfa__automaton *cdfa__language_concatenation_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2);

cdfa__automaton *cdfa__kleen_plus_automaton(const cdfa__automaton * const a);

cdfa__automaton *cdfa__kleen_star_automaton(const cdfa__automaton * const a);

cdfa__automaton *cdfa__minimal_automaton(const cdfa__automaton * const a);

unsigned int cdfa__union_of_the_letters_to_consider(cdfa__letter dest_letters[],
											  	  	 const cdfa__automaton * const a_1,
											  	  	 const cdfa__automaton * const a_2);

cdfa__automaton *cdfa__language_union_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2);

cdfa__automaton *cdfa__language_intersection_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2);

unsigned int cdfa__union_of_the_letters_to_consider(cdfa__letter dest_letters[],
											  	  	 const cdfa__automaton * const a_1,
											  	  	 const cdfa__automaton * const a_2);



#endif /* INTERN_FUNCTIONS_H_ */
