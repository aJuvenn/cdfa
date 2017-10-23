/*
 * read_and_build_basic_automatons.c
 *
 *  Created on: 22 oct. 2017
 *      Author: juven
 */


#include "../Headers/cdfa_regular_expression_intern.h"


int cdfa__build_from_word(const char **cursor,
		unsigned int *nb_automaton_stack,
							cdfa__automaton *automaton_stack[],
							char char_stack[],
							cdfa__bool implicit_concatenation){

	unsigned int nb_char_stack;
	cdfa__token tok;

	cdfa__automaton * a = NULL;
	cdfa__automaton * top_automaton = NULL;
	cdfa__automaton * top_automaton_bis = NULL;

	tok = cdfa__get_next_token_and_shift_cursor(cursor);
	nb_char_stack = 0;

	while (cdfa__next_token(cursor).type == CDFA_LETTER){
		char_stack[nb_char_stack++] = tok.character;
		tok = cdfa__get_next_token_and_shift_cursor(cursor);
	}

	char_stack[nb_char_stack++] = tok.character;
	char_stack[nb_char_stack] = '\0';

	a = cdfa__word_recognizing_automaton(char_stack);

	//TODO error if retuns NULL (no need to free)

	if (implicit_concatenation){

		top_automaton = automaton_stack[--(*nb_automaton_stack)];

		top_automaton_bis = cdfa__language_concatenation_automaton(top_automaton,a);
		//TODO error if retuns NULL (then free top automatons and a)

		automaton_stack[(*nb_automaton_stack)++] = top_automaton_bis;

		cdfa__free_automaton(a);
		cdfa__free_automaton(top_automaton);

	} else {
		automaton_stack[(*nb_automaton_stack)++] = a;
	}

	return 1;
}




int cdfa__build_from_letter_choice(const char **cursor,
		unsigned int *nb_automaton_stack,
							cdfa__automaton *automaton_stack[],
							char char_stack[],
							cdfa__bool implicit_concatenation){


	cdfa__automaton * a = NULL;
	cdfa__automaton * top_automaton = NULL;
	cdfa__automaton * top_automaton_bis = NULL;

	unsigned int nb_char_stack;

	cdfa__get_next_token_and_shift_cursor(cursor);

	nb_char_stack = cdfa__read_letter_choice_expression(cursor,char_stack);

	if (nb_char_stack == 0){
		return 0;
	}

	a = cdfa__letter_choice_automaton((cdfa__letter *) char_stack);

	//TODO error if retuns NULL (no need to free)


	if (implicit_concatenation){

		top_automaton = automaton_stack[--(*nb_automaton_stack)];

		top_automaton_bis = cdfa__language_concatenation_automaton(top_automaton,a);

		//TODO error if returns NULL (then free a and top automaton)

		automaton_stack[(*nb_automaton_stack)++] = top_automaton_bis;

		cdfa__free_automaton(a);
		cdfa__free_automaton(top_automaton);

	} else {
		automaton_stack[(*nb_automaton_stack)++] = a;
	}

	return 1;
}




int cdfa__build_from_unary_operator(const char **cursor,
		unsigned int *nb_automaton_stack,
							cdfa__automaton *automaton_stack[],
							cdfa__bool implicit_concatenation)
{

	cdfa__token tok;

	cdfa__automaton * a = NULL;
	cdfa__automaton * top_automaton = NULL;

	unsigned int min_power_value;
	unsigned int max_power_value;
	int no_error;

	tok = cdfa__get_next_token_and_shift_cursor(cursor);

	if (!implicit_concatenation){
		return 0;
	}

	top_automaton = automaton_stack[--(*nb_automaton_stack)];

	switch (tok.type){

	case CDFA_STAR:
		a = cdfa__kleen_star_automaton(top_automaton);
		break;

	case CDFA_PLUS:
		a = cdfa__kleen_plus_automaton(top_automaton);
		break;

	case CDFA_QUESTION_MARK:
		a = cdfa__language_or_epsilon_automaton(top_automaton);
		break;

	case CDFA_LEFT_CURVED_BRACKET:

		no_error = cdfa__read_exponentiation_expression(cursor,&min_power_value,&max_power_value);

		if (!no_error){
			return 0;
		}

		a = cdfa__range_exponentiation_automaton(min_power_value,max_power_value,top_automaton);
		break;

	default:
		//TODO free top automaton
		return 0;
	}

	//TODO error if retuns NULL (then free top automatons)

	automaton_stack[(*nb_automaton_stack)++] = a;
	cdfa__free_automaton(top_automaton);

	return 1;
}





int cdfa__build_from_binary_operator(const char **cursor,
		unsigned int *nb_automaton_stack,
							cdfa__automaton *automaton_stack[],
							cdfa__bool implicit_concatenation,
							enum cdfa__token_type * const waiting_binary_operator)
{

	cdfa__token tok;

	cdfa__automaton * a = NULL;
	cdfa__automaton * top_automaton = NULL;
	cdfa__automaton * top_automaton_bis = NULL;

	tok = cdfa__get_next_token_and_shift_cursor(cursor);

	if (!implicit_concatenation){
		return 0;
	}

	if (*waiting_binary_operator != CDFA_INVALID_TOKEN){

		top_automaton = automaton_stack[--(*nb_automaton_stack)];
		top_automaton_bis = automaton_stack[--(*nb_automaton_stack)];

		switch (*waiting_binary_operator){

		case CDFA_OR:
			a = cdfa__language_union_automaton(top_automaton_bis,top_automaton);
			break;

		case CDFA_AND:
			a = cdfa__language_intersection_automaton(top_automaton_bis,top_automaton);
			break;

		//case CDFA_MINUS:
			//a = //TODO write minus automaton
			//break;

		default:
			//TODO error
			return 0;

		}
		//TODO error if a is NULL (then free top automatons)

		automaton_stack[(*nb_automaton_stack)++] = a;

		cdfa__free_automaton(top_automaton);
		cdfa__free_automaton(top_automaton_bis);

	}

	*waiting_binary_operator = tok.type;

	return 1;
}





