/*
 * tokenizer.c
 *
 *  Created on: 5 févr. 2020
 *      Author: ajuvenn
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../cdfa.h"


int tokenize(char * word, unsigned nb_automatons, cdfa__automaton * automatons[], unsigned * out__word_size, unsigned * out__automaton_id)
{
	unsigned nb_still_running_automatons = nb_automatons;

	char still_running[nb_automatons];
	memset(still_running, 1, nb_automatons);

	for (unsigned i = 0 ; i < nb_automatons ; i++){
		cdfa__move_to_starting_state(automatons[i]);
	}

	unsigned char_id = 0;
	unsigned last_valid_char_id = (unsigned) -1;
	unsigned last_valid_automaton_id = (unsigned) -1;

	while (nb_still_running_automatons != 0){

		char c = word[char_id];

		if (c == '\0' || c == EOF){
			break;
		}

		for (unsigned i = 0 ; i < nb_automatons ; i++){

			if (!still_running[i]){
				continue;
			}

			cdfa__automaton_state state = cdfa__move_to_next_state(c, automatons[i]);

			if (state == CDFA__WELL){
				still_running[i] = 0;
				nb_still_running_automatons--;

			} else if (cdfa__is_a_final_state(state, automatons[i])){

				last_valid_char_id = char_id;
				last_valid_automaton_id = i;
			}
		}
	}

	if (nb_still_running_automatons != 0 || last_valid_char_id == (unsigned) -1){
		return 1;
	}

	*out__word_size = last_valid_char_id;
	*out__automaton_id = last_valid_automaton_id;

	return 0;
}

