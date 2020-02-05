/*
 * cdfa.h
 *
 *  Created on: 13 oct. 2017
 *      Author: ajuvenn
 */

#ifndef CDFA_H_
#define CDFA_H_

/*
 * Abstract structure representing a regular expression
 * recognizing automaton
 */
struct cdfa__automaton;
typedef struct cdfa__automaton cdfa__automaton;

/*
 * Type representing the different states an automaton goes
 * into while being fed letters
 */
typedef unsigned int cdfa__automaton_state;

/*
 * CDFA__WELL is a cdfa__automaton_state which corresponds to a non final
 * state an automaton can't leave once it is into
 */
#define CDFA__WELL ((cdfa__automaton_state) 0)

/*
 * CDFA__INVALID_STATE is a cdfa__automaton_state returned in case of error
 */
#define CDFA__INVALID_STATE ((cdfa__automaton_state) -1)



/*
 * Returns the smallest automaton recognizing the language
 * described by the given regular expression.
 */
cdfa__automaton * cdfa__expression_recognizing_automaton(const char * const regexp);


/*
 * Reads the word from automaton's initial state and returns if its last state
 * is final. Automaton state remains the last state after the function returns.
 */
int cdfa__is_the_word_recognized(const char word[], cdfa__automaton * const a);


/*
 * Returns the state the automaton would be after reading the whole word
 */
cdfa__automaton_state cdfa__state_after_reading(const char word[], cdfa__automaton * const a);


/*
 * Reads the whole word and returns the current automaton state after this
 */
cdfa__automaton_state cdfa__move_to_state_after_reading(const char word[], cdfa__automaton * const a);


/*
 * Returns 1 if the state q is final, 0 otherwise
 */
int cdfa__is_a_final_state(const cdfa__automaton_state q, const cdfa__automaton * const a);


/*
 * Returns 1 if the current state is final, 0 otherwise
 */
cdfa__automaton_state cdfa__current_state(const cdfa__automaton * const a);


/*
 * Returns automaton starting state
 */
cdfa__automaton_state cdfa__starting_state(const cdfa__automaton * const a);


/*
 * Resets automaton current state to starting one
 */
cdfa__automaton_state cdfa__move_to_starting_state(cdfa__automaton * const a);


/*
 * Returns the state the automaton would be after reading the letter l from state q
 */
cdfa__automaton_state cdfa__next_state(const char l, const cdfa__automaton_state q, const cdfa__automaton * const a);


/*
 *	Feeds the letter l to the automaton to change its current state
 */
cdfa__automaton_state cdfa__move_to_next_state(const char l, cdfa__automaton * const a);


/*
 * Changes automaton current state to indicated state
 */
int cdfa__move_to_state(const cdfa__automaton_state q, cdfa__automaton * const a);


/*
 * Displays automaton state transition matrix
 */
void cdfa__print_automaton(const cdfa__automaton * const a);


/*
 * Frees dynamically allocated automaton
 */
void cdfa__free_automaton(cdfa__automaton * const a);



#endif /* CDFA_H_ */
