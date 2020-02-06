/*
 * cdfa_regular_expression_intern.h
 *
 *  Created on: 22 oct. 2017
 *      Author: juven
 */

#ifndef CDFA_REGULAR_EXPRESSION_INTERN_H_
#define CDFA_REGULAR_EXPRESSION_INTERN_H_

#include "../cdfa_edition_interface.h"


#define MAX_NUMBER_DIGIT 9

enum cdfa__token_type {

	CDFA_INVALID_TOKEN = 0,
	CDFA_END_OF_STRING,
	CDFA_LETTER,
	CDFA_LEFT_BRACKET,
	CDFA_RIGHT_BRACKET,
	CDFA_LEFT_CURVED_BRACKET,
	CDFA_RIGHT_CURVED_BRACKET,
	CDFA_LEFT_SQUARE_BRACKET,
	CDFA_RIGHT_SQUARE_BRACKET,
	CDFA_PLUS,
	CDFA_STAR,
	CDFA_MINUS,
	CDFA_OR,
	CDFA_AND,
	CDFA_COMA,
	CDFA_QUESTION_MARK
};

struct cdfa__token {
	char character;
	enum cdfa__token_type type;
};

typedef struct cdfa__token cdfa__token;





cdfa__token cdfa__get_next_token_and_shift_cursor(const char ** cursor);

cdfa__token cdfa__next_token(const char ** const cursor);


int cdfa__read_exponentiation_expression(const char **cursor, unsigned int *out_minimum, unsigned int *out_maximum);

unsigned int cdfa__read_letter_choice_expression(const char **cursor, char out_characters[]);


int cdfa__build_from_word(const char **cursor,
		unsigned int *nb_automaton_stack,
		cdfa__automaton *automaton_stack[],
		char char_stack[],
		cdfa__bool implicit_concatenation);



int cdfa__build_from_letter_choice(const char **cursor,
		unsigned int *nb_automaton_stack,
		cdfa__automaton *automaton_stack[],
		char char_stack[],
		cdfa__bool implicit_concatenation);



int cdfa__build_from_unary_operator(const char **cursor,
		unsigned int *nb_automaton_stack,
		cdfa__automaton *automaton_stack[],
		cdfa__bool implicit_concatenation);



int cdfa__build_from_binary_operator(const char **cursor,
		unsigned int *nb_automaton_stack,
		cdfa__automaton *automaton_stack[],
		cdfa__bool implicit_concatenation,
		enum cdfa__token_type * const waiting_binary_operator);



#endif /* CDFA_REGULAR_EXPRESSION_INTERN_H_ */
