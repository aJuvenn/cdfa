/*
 * cdfa_regular_expression.h
 *
 *  Created on: 22 oct. 2017
 *      Author: juven
 */

#ifndef CDFA_REGULAR_EXPRESSION_H_
#define CDFA_REGULAR_EXPRESSION_H_


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







#endif /* CDFA_REGULAR_EXPRESSION_H_ */
