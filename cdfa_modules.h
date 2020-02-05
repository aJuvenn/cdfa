/*
 * cdfa_modules.h
 *
 *  Created on: 5 févr. 2020
 *      Author: ajuvenn
 */

#ifndef CDFA_MODULES_H_
#define CDFA_MODULES_H_


#include "cdfa.h"


/***********************************************************
 * 				Module : regular expressions
 ***********************************************************/

/*
 * Returns the smallest automaton recognizing the language
 * described by the given regular expression.
 */
cdfa__automaton *cdfa__expression_recognizing_automaton(const char * const regexp);





/***********************************************************
 * 				Module : basic automatons
 ***********************************************************/


/*
 * Creates an automaton only recognizing the word given
 */
cdfa__automaton *cdfa__word_recognizing_automaton(const char word[]);


/*
 * Creates an automaton recognizing single letter words, made of one of the
 *  the letters in char_stack
 */
cdfa__automaton *cdfa__letter_choice_automaton(const char char_stack[]);





/***********************************************************
 * 				Module : minimal automaton
 ***********************************************************/


/*
 * Returns the smallest automaton recognizing the same language as the
 * given automaton. Returns NULL if an error has occurred.
 */
cdfa__automaton *cdfa__minimal_automaton(const cdfa__automaton * const a);





/***********************************************************
 * 				Module : automaton operations
 ***********************************************************/


/*
 * Returns the smallest automaton recognizing only words
 * recognized either by the fist automaton a_1, or the second a_2.
 * Returns NULL if an error has occurred.
 */
cdfa__automaton *cdfa__language_union_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2);


/*
 * Returns the smallest automaton only recognizing words recognized
 * by both automatons a_1 and a_2. Returns NULL if an error has occurred.
 */
cdfa__automaton *cdfa__language_intersection_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2);


/*
 * Returns the smallest automaton recognizing only words made of :
 * - a word recognized by the first automaton a_1
 * - followed by a word recognized by the second automaton a_2
 * Returns NULL if an error has occurred.
 */
cdfa__automaton *cdfa__language_concatenation_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2);


/*
 * Returns the smallest automaton recognizing words recognized by
 * the first automaton a_1 but not by the second automaton a_2.
 * Returns NULL if an error has occurred.
 */
cdfa__automaton *cdfa__language_exclusion_automaton(const cdfa__automaton * const a_1, const cdfa__automaton * const a_2);


/*
 * Returns the smallest automaton recognizing only words made of a succession of
 * "power" words recognized by the given automaton.
 * If power is equal to 0, it returns an automaton only recognizing the empty
 * word. Returns NULL if an error has occurred.
 */
cdfa__automaton *cdfa__language_exponentiation_automaton(const unsigned int power, const cdfa__automaton * const a);


/*
 * Returns the smallest automaton recognizing only words made of a
 * succession of at least "min_power" and at most "max_power" words
 * recognized by the given automaton a.
 *
 * PRECOND : min_power <= max_power
 * If max_power is equal to ((unsigned int) -1), it means that there
 * is no maximum number of successions.
 * Returns NULL if an error has occurred.
 */
cdfa__automaton *cdfa__language_range_exponentiation_automaton(const unsigned int min_power, const unsigned int max_power, const cdfa__automaton * const a);


/*
 * Returns the smallest automaton recognizing the empty word,
 * and every words recognized by the given automaton.
 */
cdfa__automaton *cdfa__language_or_epsilon_automaton(const cdfa__automaton * const a);


/*
 * Returns the smallest automaton recognizing only the empty word
 * and words made of a succession of words recognized by the given
 * automaton. Returns NULL if an error has occurred.
 */
cdfa__automaton *cdfa__kleen_star_automaton(const cdfa__automaton * const a);


/*
 * Returns the smallest automaton recognizing only words made of
 * a succession of at least one word recognized by the given
 * automaton. Returns NULL if an error has occurred.
 */
cdfa__automaton *cdfa__kleen_plus_automaton(const cdfa__automaton * const a);



#endif /* CDFA_MODULES_H_ */
