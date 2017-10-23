/*
 * regular_expression.c
 *
 *  Created on: 15 oct. 2017
 *      Author: juven
 */

#include "../Headers/cdfa_regular_expression_intern.h"


int cdfa__build_from_expression(const char **cursor,
							unsigned int *nb_automaton_stack,
							cdfa__automaton *automaton_stack[],
							char char_stack[])
{

	cdfa__token next_token;
	int no_error;
	cdfa__bool implicit_concatenation;
	enum cdfa__token_type waiting_binary_operator;
	cdfa__bool exit_reading;

	cdfa__automaton * a = NULL;
	cdfa__automaton * top_automaton = NULL;
	cdfa__automaton * top_automaton_bis = NULL;

	implicit_concatenation = CDFA_FALSE;
	exit_reading = CDFA_FALSE;
	waiting_binary_operator = CDFA_INVALID_TOKEN;


	while (!exit_reading){

		next_token = cdfa__next_token(cursor);

		switch (next_token.type){

		case CDFA_LETTER:

			no_error = cdfa__build_from_word(cursor,nb_automaton_stack,automaton_stack,char_stack,implicit_concatenation);

			if (!no_error){
				return  0;
			}

			implicit_concatenation = CDFA_TRUE;
			break;


		case CDFA_LEFT_SQUARE_BRACKET:

			no_error = cdfa__build_from_letter_choice(cursor,nb_automaton_stack,automaton_stack,char_stack,implicit_concatenation);

			if (!no_error){
				return  0;
			}

			implicit_concatenation = CDFA_TRUE;
			break;


		case CDFA_LEFT_BRACKET:

			cdfa__get_next_token_and_shift_cursor(cursor);
			no_error = cdfa__build_from_expression(cursor,nb_automaton_stack,automaton_stack,char_stack);

			if (!no_error){
				return 0;
			}

			if (implicit_concatenation){

				top_automaton = automaton_stack[--(*nb_automaton_stack)];
				top_automaton_bis = automaton_stack[--(*nb_automaton_stack)];

				a = cdfa__language_concatenation_automaton(top_automaton_bis,top_automaton);

				// TODO : error if returns NULL (free top automatons)

				automaton_stack[(*nb_automaton_stack)++] = a;


				cdfa__free_automaton(top_automaton);
				cdfa__free_automaton(top_automaton_bis);
				a = NULL;
				top_automaton = NULL;
				top_automaton_bis = NULL;

			}

			implicit_concatenation = CDFA_TRUE;
			break;


		case CDFA_LEFT_CURVED_BRACKET:
		case CDFA_STAR:
		case CDFA_PLUS:
		case CDFA_QUESTION_MARK:

			no_error = cdfa__build_from_unary_operator(cursor,nb_automaton_stack,automaton_stack,implicit_concatenation);

			if (!no_error){
				return  0;
			}

			implicit_concatenation = CDFA_TRUE;
			break;


		case CDFA_AND:
		case CDFA_OR:
		case CDFA_MINUS:

			no_error = cdfa__build_from_binary_operator(cursor,nb_automaton_stack,
						automaton_stack,implicit_concatenation,&waiting_binary_operator);

			if (!no_error){
				return  0;
			}

			implicit_concatenation = CDFA_FALSE;
			break;


		case CDFA_RIGHT_BRACKET:
		case CDFA_END_OF_STRING:

			no_error = cdfa__build_from_binary_operator(cursor,nb_automaton_stack,
					automaton_stack,implicit_concatenation,&waiting_binary_operator);

			if (!no_error){
				return  0;
			}

			exit_reading = CDFA_TRUE;
			break;

		default:
			return 0;
		}
	}

	return 1;
}



cdfa__automaton *cdfa__expression_recognizing_automaton(const char * const expression)
{

	const char * cursor = expression;
	unsigned int expression_length = strlen(expression);

	unsigned int nb_automaton_stack = 0;
	cdfa__automaton * automaton_stack[expression_length];

	char char_stack[(expression_length > CDFA_NB_LETTER)? expression_length : CDFA_NB_LETTER];

	int no_error;
	unsigned int i;


	no_error = cdfa__build_from_expression(&cursor,&nb_automaton_stack,automaton_stack,char_stack);

	if (!no_error || nb_automaton_stack != 1){

		for (i = 0 ; i < nb_automaton_stack ; i++){
			cdfa__free_automaton(automaton_stack[i]);
		}

		return NULL;
	}

	return automaton_stack[0];
}











