/*
 * read_next_token.c
 *
 *  Created on: 22 oct. 2017
 *      Author: juven
 */



#include "../Headers/cdfa_regular_expression_intern.h"



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

cdfa__token cdfa__get_next_token_and_shift_cursor(const char ** cursor)
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
	const char * new_cursor = *cursor;
	cdfa__token next_token = cdfa__get_next_token_and_shift_cursor(&new_cursor);

	return next_token;
}





