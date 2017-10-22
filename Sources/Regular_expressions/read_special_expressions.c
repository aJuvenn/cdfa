/*
 * read_special_expressions.c
 *
 *  Created on: 22 oct. 2017
 *      Author: juven
 */




int cdfa__read_exponentiation_expression(const char **cursor, unsigned int *out_minimum, unsigned int *out_maximum)
{

	cdfa__token tok;
	cdfa__bool no_first_number = CDFA_FALSE;
	unsigned int number_size = 0;
	char number[MAX_NUMBER_DIGIT+1];

	tok = cdfa__get_next_token_and_shift_cursor(cursor);

	while (tok.type == CDFA_LETTER
			&& tok.character >= '0'
			&& tok.character <= '9'
			&& number_size < MAX_NUMBER_DIGIT){
		number[number_size++] = tok.character;
		tok = cdfa__get_next_token_and_shift_cursor(cursor);
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
		tok = cdfa__get_next_token_and_shift_cursor(cursor);

		while (tok.type == CDFA_LETTER
				&& tok.character >= '0'
				&& tok.character <= '9'
				&& number_size < MAX_NUMBER_DIGIT){
			number[number_size++] = tok.character;
			tok = cdfa__get_next_token_and_shift_cursor(cursor);
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


unsigned int cdfa__read_letter_choice_expression(const char **cursor, char out_characters[])
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

	tok = cdfa__get_next_token_and_shift_cursor(cursor);

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

			tok = cdfa__get_next_token_and_shift_cursor(cursor);

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

		tok = cdfa__get_next_token_and_shift_cursor(cursor);
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
