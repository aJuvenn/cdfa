/*
 * cdfa_module_interface.h
 *
 *  Created on: 22 oct. 2017
 *      Author: juven
 */

#ifndef CDFA_MODULE_INTERFACE_H_
#define CDFA_MODULE_INTERFACE_H_

#include "../cdfa_interface.h"


/*
 * Module : basic automatons
 */


/*
 * Creates an automaton only recognizing the word given
 */
cdfa__automaton *cdfa__word_recognizing_automaton(const char word[]);


/*
 * Creates an automaton recognizing single letter words, made of one of the 
 *  the letters in char_stack
 */
cdfa__automaton *cdfa__letter_choice_automaton(const cdfa__letter char_stack[]);






/*
 * Module : minimal automaton
 */


/*
 * Returns the smallest automaton recognizing the same language as the
 * given automaton
 */
cdfa__automaton *cdfa__minimal_automaton(const cdfa__automaton * const a);



/*
 * Module : Automaton operations
 */



/*
 * Returns the smallest automaton recognizing only words made of : 
 * - a word recognized by the first automaton a_1
 * - followed by a word recognized by the second automaton a_2
 */
cdfa__automaton *cdfa__language_concatenation_automaton
(
 const cdfa__automaton * const a_1, 
 const cdfa__automaton * const a_2
);


/*
 * Returns the smallest automaton recognizing only words that are
 * recognized either by the fist automaton a_1 or the second a_2
 */
cdfa__automaton *cdfa__language_union_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2);


/*
 * Returns the smallest automaton only recognizing words that are recognized
 * by both automatons a_1 and a_2
 */
cdfa__automaton *cdfa__language_intersection_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2);


/*
 * Returns the smallest automaton recognizing words that are recognized by
 * the first automaton a_1, but not by the second automaton a_2 
 */
cdfa__automaton *cdfa__language_exclusion_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2);



/*
 * Returns the smallest automaton recognizing only words made of a succession of 
 * "power" words recognized by the given automaton a
 * If power is equal to 0, it returns an automaton only recognizing the empty
 * word.
 */
cdfa__automaton *cdfa__language_exponentiation_automaton(const unsigned int power, const cdfa__automaton * const a);



/*
 * Returns the smallest automaton recognizing only words made of a
 * succession of at least "min_power" and at most "max_power" words 
 * recognized by the given automaton a.
 * 
 * PRECOND : min_power <= max_power
 * If max_power is equal to ((unsigned int) -1), it means that there
 * is no maximum number of succession.
 */
cdfa__automaton *cdfa__language_range_exponentiation_automaton(const unsigned int min_power, const unsigned int max_power, const cdfa__automaton * const a);




cdfa__automaton *cdfa__language_or_epsilon_automaton(const cdfa__automaton *a);

cdfa__automaton *cdfa__kleen_plus_automaton(const cdfa__automaton * const a);

cdfa__automaton *cdfa__kleen_star_automaton(const cdfa__automaton * const a);







cdfa__automaton *cdfa__expression_recognizing_automaton(const char * const expression);



#endif /* CDFA_MODULE_INTERFACE_H_ */
