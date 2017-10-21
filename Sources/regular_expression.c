/*
 * regular_expression.c
 *
 *  Created on: 15 oct. 2017
 *      Author: juven
 */

#include "../Headers/cdfa_edition_interface.h"
#include "../Headers/intern_functions.h"


/*
 * str must begin with '['
 */


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



char *cdfa_token_names[] = {
"INVALID_TOKEN",
"END_OF_STRING",
"LETTER",
"LEFT_BRACKET",
"RIGHT_BRACKET",
"LEFT_CURVED_BRACKET",
"RIGHT_CURVED_BRACKET",
"LEFT_SQUARE_BRACKET",
"RIGHT_SQUARE_BRACKET",
"PLUS",
"STAR",
"MINUS",
"OR",
"AND",
"COMA",
"QUESTION_MARK"};



void cdfa__print_token(cdfa__token tok)
{
	printf("<%s",cdfa_token_names[tok.type]);

	if (tok.type == CDFA_LETTER){
		printf(" (%c)",tok.character);
	}
	printf(">");
}



cdfa__bool cdfa__is_a_space(const char c)
{

	const char spaces[] = {' ','\n','\t','\v','\r','\f'};
	unsigned int i;

	for (i = 0 ; i < 6 ; i++){

		if (c == spaces[i]){
			return CDFA_TRUE;
		}
	}

	return CDFA_FALSE;
}



#define CDFA_RETURN_TOKEN_IF_MATCH(token_type,c) \
case c : \
	tok.type = token_type; \
	return tok;







cdfa__token cdfa__get_token(const char ** cursor)
{
	cdfa__token tok;

	if (cursor == NULL || *cursor == NULL){
		tok.type = CDFA_INVALID_TOKEN;
		return tok;
	}

	tok.character = **cursor;

	while (cdfa__is_a_space(tok.character)){
		(*cursor)++;
		tok.character = **cursor;
	}

	if (tok.character == '\0'){
		tok.type = CDFA_END_OF_STRING;
		return tok;
	}

	(*cursor)++;

	switch (tok.character){
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_LEFT_BRACKET,'(');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_RIGHT_BRACKET,')');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_LEFT_CURVED_BRACKET,'{');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_RIGHT_CURVED_BRACKET,'}');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_LEFT_SQUARE_BRACKET,'[');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_RIGHT_SQUARE_BRACKET,']');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_PLUS,'+');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_STAR,'*');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_MINUS,'-');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_OR,'|');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_AND,'&');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_COMA,',');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_QUESTION_MARK,'?');

	case '\\':

		tok.character = **cursor;

		if (tok.character == '\0'){
			tok.type = CDFA_INVALID_TOKEN;
			return tok;
		}

		(*cursor)++;

		switch (tok.character){

		case 'n':
			tok.character = '\n';
			tok.type = CDFA_LETTER;
			return tok;

		case 't':
			tok.character = '\t';
			tok.type = CDFA_LETTER;
			return tok;

		case 'v':
			tok.character = '\v';
			tok.type = CDFA_LETTER;
			return tok;

		case 'r':
			tok.character = '\r';
			tok.type = CDFA_LETTER;
			return tok;

		case 'f':
			tok.character = '\f';
			tok.type = CDFA_LETTER;
			return tok;

		case '(':
		case ')':
		case '{':
		case '}':
		case '[':
		case ']':
		case '+':
		case '*':
		case '-':
		case '|':
		case '&':
		case ',':
		case '?':
		case '\\':
		case ' ':
			tok.type = CDFA_LETTER;
			return tok;

		default:
			tok.type = CDFA_INVALID_TOKEN;
			return tok;
		}
		break;

	default:
		tok.type = CDFA_LETTER;
		return tok;
	}


}






cdfa__token cdfa__next_token(const char ** const cursor)
{
	cdfa__token tok;
	const char *new_cursor = NULL;

	if (cursor == NULL || *cursor == NULL){
		tok.type = CDFA_INVALID_TOKEN;
		return tok;
	}

	new_cursor = *cursor;

	tok.character = *new_cursor;

	while (cdfa__is_a_space(tok.character)){
		new_cursor++;
		tok.character = *new_cursor;
	}

	if (tok.character == '\0'){
		tok.type = CDFA_END_OF_STRING;
		return tok;
	}

	switch (tok.character){
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_LEFT_BRACKET,'(');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_RIGHT_BRACKET,')');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_LEFT_CURVED_BRACKET,'{');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_RIGHT_CURVED_BRACKET,'}');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_LEFT_SQUARE_BRACKET,'[');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_RIGHT_SQUARE_BRACKET,']');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_PLUS,'+');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_STAR,'*');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_MINUS,'-');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_OR,'|');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_AND,'&');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_COMA,',');
		CDFA_RETURN_TOKEN_IF_MATCH(CDFA_QUESTION_MARK,'?');

	case '\\':

		new_cursor++;
		tok.character = *new_cursor;

		if (tok.character == '\0'){
			tok.type = CDFA_INVALID_TOKEN;
			return tok;
		}

		//new_cursor++;

		switch (tok.character){

		case 'n':
			tok.character = '\n';
			tok.type = CDFA_LETTER;
			return tok;

		case 't':
			tok.character = '\t';
			tok.type = CDFA_LETTER;
			return tok;

		case 'v':
			tok.character = '\v';
			tok.type = CDFA_LETTER;
			return tok;

		case 'r':
			tok.character = '\r';
			tok.type = CDFA_LETTER;
			return tok;

		case 'f':
			tok.character = '\f';
			tok.type = CDFA_LETTER;
			return tok;

		case '(':
		case ')':
		case '{':
		case '}':
		case '[':
		case ']':
		case '+':
		case '*':
		case '-':
		case '|':
		case '&':
		case ',':
		case '?':
		case '\\':
		case ' ':
			tok.type = CDFA_LETTER;
			return tok;

		default:
			tok.type = CDFA_INVALID_TOKEN;
			return tok;
		}
		break;

	default:
		tok.type = CDFA_LETTER;
		return tok;
	}


}






















void cdfa__print_token_decomposition(const char str[])
{
	cdfa__token tok;
	const char *cursor = str;

	printf("String : %s\n\t",str);

	do {

		tok = cdfa__get_token(&cursor);
		cdfa__print_token(tok);
		printf("\n\t");

	} while (tok.type != CDFA_INVALID_TOKEN && tok.type != CDFA_END_OF_STRING);

	printf("\n");
}


#define MAX_NUMBER_DIGIT 10



int cdfa__read_power_operator(const char **cursor, unsigned int *out_minimum, unsigned int *out_maximum)
{

	cdfa__token tok;
	cdfa__bool no_first_number = CDFA_FALSE;
	unsigned int number_size = 0;
	char number[MAX_NUMBER_DIGIT+1];

	tok = cdfa__get_token(cursor);

	while (tok.type == CDFA_LETTER
			&& tok.character >= '0'
			&& tok.character <= '9'
			&& number_size < MAX_NUMBER_DIGIT){
		number[number_size++] = tok.character;
		tok = cdfa__get_token(cursor);
	}

	switch (tok.type) {

	case CDFA_RIGHT_CURVED_BRACKET:

		if (number_size == 0){
			return 0;
		}

		number[number_size] = '\0';
		*out_minimum = *out_maximum = (unsigned int) atoi(number);
		return 1;

	case CDFA_COMA:

		if (number_size == 0){
			no_first_number = CDFA_TRUE;
		}

		number[number_size] = '\0';
		*out_minimum = (unsigned int) atoi(number);

		number_size = 0;
		tok = cdfa__get_token(cursor);

		while (tok.type == CDFA_LETTER
				&& tok.character >= '0'
				&& tok.character <= '9'
				&& number_size < MAX_NUMBER_DIGIT){
			number[number_size++] = tok.character;
			tok = cdfa__get_token(cursor);
		}

		switch (tok.type) {

			case CDFA_RIGHT_CURVED_BRACKET:

				if (number_size == 0){

					if (no_first_number){
						return 0;
					}

					*out_maximum = (unsigned int) -1;

					return 1;
				}

				number[number_size] = '\0';
				*out_maximum = (unsigned int) atoi(number);

				return 1;

			default:
				return 0;
		}
		break;

	default:
		return 0;

	}
}



/*
'[dqfzbb-dqskn-dqsn],[-sdsdf] nop,[sdr-] nop, '
*/

unsigned int cdfa__letter_choice_expression(const char **cursor, char out_characters[])
{

	unsigned int nb_out_characters;
	cdfa__bool is_considered[CDFA_NB_LETTER];
	cdfa__token tok;
	cdfa__bool can_be_followed_by_a_range;
	unsigned int i;
	char last_char;

	for (i = 0 ; i < CDFA_NB_LETTER ; i++){
		is_considered[i] = CDFA_FALSE;
	}

	tok = cdfa__get_token(cursor);

	if (tok.type != CDFA_LETTER){
		return 0;
	}

	while (tok.type == CDFA_LETTER || tok.type == CDFA_MINUS){

		if (tok.type == CDFA_LETTER){

			last_char = tok.character;
			is_considered[(unsigned int) last_char] = CDFA_TRUE;
			can_be_followed_by_a_range = CDFA_TRUE;

		} else {

			if (!can_be_followed_by_a_range){
				return 0;
			}

			tok = cdfa__get_token(cursor);

			if (tok.type != CDFA_LETTER){
				return 0;
			}

			if ((unsigned int) last_char > (unsigned int) tok.character){
				return 0;
			}

			for (i = (unsigned int) last_char ; i <= (unsigned int) tok.character ; i++){
				is_considered[i] = CDFA_TRUE;
			}

			can_be_followed_by_a_range = CDFA_FALSE;
		}

		tok = cdfa__get_token(cursor);
	}

	if (tok.type != CDFA_RIGHT_SQUARE_BRACKET){
		return 0;
	}

	nb_out_characters = 0;

	for (i = 0 ; i < CDFA_NB_LETTER ; i++){

		if (is_considered[i]){
			out_characters[nb_out_characters++] = (char) i;
		}
	}

	out_characters[nb_out_characters] = '\0';

	return nb_out_characters;

}


cdfa__automaton *cdfa__letter_choice_automaton(const cdfa__letter char_stack[])
{
	cdfa__automaton *new_aut = NULL;
	unsigned int size;
	unsigned int i;
	cdfa__letter first_known_letter;

	size = 0;

	while (char_stack[size] != 0){
		size++;
	}

	if (size == 0){
		fprintf(stderr,"cdfa__letter_choice_automaton : no letter into the stack\n");
		return NULL;
	}

	new_aut = cdfa__empty_automaton(3,1,char_stack);

	if (new_aut == NULL){
		fprintf(stderr,"cdfa__letter_choice_automaton : cdfa__empty_automaton returned NULL\n");
		return NULL;
	}

	first_known_letter = char_stack[0];
	cdfa__add_transition(1,first_known_letter,2,new_aut);

	for (i = 1 ; i < size ; i++){
		cdfa__give_same_meaning_as(char_stack[i],first_known_letter,new_aut);
	}

	cdfa__set_as_the_starting_state(1,new_aut);
	cdfa__set_as_a_final_state(2,new_aut);

	return new_aut;
}





enum cdfa__operator_type {
	CDFA_NO_OP = 0,
	CDFA_PLUS_OP,
	CDFA_POWER_OP,
	CDFA_QUESTION_MARK_OP,
	CDFA_OR_OP,
	CDFA_AND_OP,
	CDFA_MINUS_OP,
	CDFA_CONCATENATION_OP,
};


struct cdfa__operator_sheet {
	enum cdfa__token_type type;
	unsigned int min_power_value;
	unsigned int max_power_value;
	const char *out_characters;
};

typedef struct cdfa__operator_sheet cdfa__operator_sheet;






cdfa__automaton *cdfa__power_automaton(const unsigned int power, const cdfa__automaton * const a)
{
	cdfa__automaton *b = NULL;
	cdfa__automaton *c = NULL;

	if (power == 0){
		return cdfa__word_recognizing_automaton("");
	}

	b = cdfa__power_automaton(power/2,a);

	if (b == NULL){
		fprintf(stderr,"cdfa__power_automaton : self call returned NULL\n");
		return NULL;
	}

	c = cdfa__language_concatenation_automaton(b,b);

	if (c == NULL){
		fprintf(stderr,"cdfa__power_automaton : cdfa__language_concatenation_automaton returned NULL\n");
		cdfa__free_automaton(b);
		return NULL;
	}

	cdfa__free_automaton(b);

	if (power%2 == 0){
		return c;
	}

	b = cdfa__language_concatenation_automaton(c,a);

	if (b == NULL){
		fprintf(stderr,"cdfa__power_automaton : cdfa__language_concatenation_automaton returned NULL\n");
		cdfa__free_automaton(c);
		return NULL;
	}

	cdfa__free_automaton(c);

	return b;
}




cdfa__automaton *cdfa__language_or_epsilon_automaton(const cdfa__automaton *a)
{

	cdfa__automaton *b = NULL;
	cdfa__automaton *c = NULL;

	b = cdfa__word_recognizing_automaton("");

	if (b == NULL){
		fprintf(stderr,"cdfa__language_or_epsilon_automaton : cdfa__word_recognizing_automaton returned NULL\n");
		return NULL;
	}

	c = cdfa__language_union_automaton(a,b);

	if (c == NULL){
		fprintf(stderr,"cdfa__language_or_epsilon_automaton : cdfa__raw_language_union_automaton returned NULL\n");
		cdfa__free_automaton(b);
		return NULL;
	}

	cdfa__free_automaton(b);

	return c;
}




cdfa__automaton *cdfa__power_range_automaton(const unsigned int min_power, const unsigned int max_power, const cdfa__automaton * const a)
{
	cdfa__automaton *b = NULL;
	cdfa__automaton *c = NULL;
	cdfa__automaton *d = NULL;

	if (min_power > max_power){
		fprintf(stderr,"cdfa__power_range_automaton : invalid range [%u;%u]\n",min_power,max_power);
		return NULL;
	}

	b = cdfa__power_automaton(min_power,a);

	if (b == NULL){
		fprintf(stderr,"cdfa__power_range_automaton : cdfa__power_automaton returned NULL\n");
		return NULL;
	}

	if (min_power == max_power){
		return b;
	}

	c = cdfa__kleen_star_automaton(a);

	if (c == NULL){
		fprintf(stderr,"cdfa__power_range_automaton : cdfa__kleen_star_automaton returned NULL\n");
		cdfa__free_automaton(b);
		return NULL;
	}

	d = cdfa__language_concatenation_automaton(b,c);

	if (d == NULL){
		fprintf(stderr,"cdfa__power_range_automaton : cdfa__language_concatenation_automaton returned NULL\n");
		cdfa__free_automaton(b);
		cdfa__free_automaton(c);
		return NULL;
	}

	cdfa__free_automaton(b);
	cdfa__free_automaton(c);

	if (max_power == -1){
		return d;
	}

	b = cdfa__language_or_epsilon_automaton(a);

	if (b == NULL){
		fprintf(stderr,"cdfa__power_range_automaton : cdfa__language_or_epsilon_automaton returned NULL\n");
		cdfa__free_automaton(d);
		return NULL;
	}

	c = cdfa__power_automaton(max_power,b);

	if (c == NULL){
		fprintf(stderr,"cdfa__power_range_automaton : cdfa__power_automaton returned NULL\n");
		cdfa__free_automaton(b);
		cdfa__free_automaton(d);
		return NULL;
	}

	cdfa__free_automaton(b);

	b = cdfa__language_intersection_automaton(c,d);

	if (b == NULL){
		fprintf(stderr,"cdfa__power_range_automaton : cdfa__language_intersection_automaton returned NULL\n");
		cdfa__free_automaton(c);
		cdfa__free_automaton(d);
		return NULL;
	}

	cdfa__free_automaton(c);
	cdfa__free_automaton(d);

	return b;
}


int cdfa__read_word(const char **cursor,
		unsigned int *nb_automaton_stack,
							cdfa__automaton *automaton_stack[],
							char char_stack[],
							cdfa__bool implicit_concatenation){

	unsigned int nb_char_stack;
	cdfa__token tok;

	cdfa__automaton * a = NULL;
	cdfa__automaton * top_automaton = NULL;
	cdfa__automaton * top_automaton_bis = NULL;

	tok = cdfa__get_token(cursor);
	nb_char_stack = 0;

	while (cdfa__next_token(cursor).type == CDFA_LETTER){
		char_stack[nb_char_stack++] = tok.character;
		tok = cdfa__get_token(cursor);
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


int cdfa__read_power(const char **cursor,
		unsigned int *nb_automaton_stack,
							cdfa__automaton *automaton_stack[],
							cdfa__bool implicit_concatenation){


	cdfa__automaton * a = NULL;
	cdfa__automaton * top_automaton = NULL;

	unsigned int min_power_value;
	unsigned int max_power_value;
	int no_error;

	cdfa__get_token(cursor);

	no_error = cdfa__read_power_operator(cursor,&min_power_value,&max_power_value);

	if (!no_error){
		return 0;
	}

	if (implicit_concatenation){

		top_automaton = automaton_stack[--(*nb_automaton_stack)];

		a = cdfa__power_range_automaton(min_power_value,max_power_value,top_automaton);
		//TODO error if retuns NULL (then free top automaton)

		automaton_stack[(*nb_automaton_stack)++] = a;

		cdfa__free_automaton(top_automaton);

	} else {
		return 0;
	}


	return 1;
}



int cdfa__read_letter_choice(const char **cursor,
		unsigned int *nb_automaton_stack,
							cdfa__automaton *automaton_stack[],
							char char_stack[],
							cdfa__bool implicit_concatenation){


	cdfa__automaton * a = NULL;
	cdfa__automaton * top_automaton = NULL;
	cdfa__automaton * top_automaton_bis = NULL;

	unsigned int nb_char_stack;

	cdfa__get_token(cursor);

	nb_char_stack = cdfa__letter_choice_expression(cursor,char_stack);

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






int cdfa__read_unary_operator(const char **cursor,
		unsigned int *nb_automaton_stack,
							cdfa__automaton *automaton_stack[],
							cdfa__bool implicit_concatenation){

	cdfa__token tok;

	cdfa__automaton * a = NULL;
	cdfa__automaton * top_automaton = NULL;

	unsigned int min_power_value;
	unsigned int max_power_value;
	int no_error;

	tok = cdfa__get_token(cursor);

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

		no_error = cdfa__read_power_operator(cursor,&min_power_value,&max_power_value);

		if (!no_error){
			return 0;
		}

		a = cdfa__power_range_automaton(min_power_value,max_power_value,top_automaton);
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





int cdfa__read_binary_operator(const char **cursor,
		unsigned int *nb_automaton_stack,
							cdfa__automaton *automaton_stack[],
							cdfa__bool implicit_concatenation,
							enum cdfa__token_type * const waiting_binary_operator){

	cdfa__token tok;

	cdfa__automaton * a = NULL;
	cdfa__automaton * top_automaton = NULL;
	cdfa__automaton * top_automaton_bis = NULL;

	tok = cdfa__get_token(cursor);

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
			//TODO error if returns NULL (then free top automatons)
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







int cdfa__read_expression(const char **cursor,
							unsigned int *nb_automaton_stack,
							cdfa__automaton *automaton_stack[],
							char char_stack[]){

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

			no_error = cdfa__read_word(cursor,nb_automaton_stack,automaton_stack,char_stack,implicit_concatenation);

			if (!no_error){
				return  0;
			}

			implicit_concatenation = CDFA_TRUE;
			break;

		case CDFA_LEFT_BRACKET:

			cdfa__get_token(cursor);
			no_error = cdfa__read_expression(cursor,nb_automaton_stack,automaton_stack,char_stack);

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


		case CDFA_LEFT_SQUARE_BRACKET:

			no_error = cdfa__read_letter_choice(cursor,nb_automaton_stack,automaton_stack,char_stack,implicit_concatenation);

			if (!no_error){
				return  0;
			}

			implicit_concatenation = CDFA_TRUE;
			break;


		case CDFA_LEFT_CURVED_BRACKET:
		case CDFA_STAR:
		case CDFA_PLUS:
		case CDFA_QUESTION_MARK:

			no_error = cdfa__read_unary_operator(cursor,nb_automaton_stack,automaton_stack,implicit_concatenation);

			if (!no_error){
				return  0;
			}

			implicit_concatenation = CDFA_TRUE;
			break;


		//case CDFA_MINUS: TODO minus automaton
		case CDFA_AND:
		case CDFA_OR:

			no_error = cdfa__read_binary_operator(cursor,nb_automaton_stack,
						automaton_stack,implicit_concatenation,&waiting_binary_operator);

			if (!no_error){
				return  0;
			}

			implicit_concatenation = CDFA_FALSE;
			break;


		case CDFA_RIGHT_BRACKET:
		case CDFA_END_OF_STRING:

			no_error = cdfa__read_binary_operator(cursor,nb_automaton_stack,
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



