/*
 * main.c
 *
 *  Created on: 26 sept. 2017
 *      Author: juven
 */

#include "Modules/cdfa_module_interface.h"


cdfa__bool cdfa__is_the_word_recognized(const cdfa__letter word[], cdfa__automaton * const a)
{

	const cdfa__letter *ptr;
	cdfa__automaton_state current_state;


	current_state = cdfa__move_to_starting_state(a);

	for (ptr = word ; *ptr != 0 ; ptr++){

		if (current_state == CDFA__WELL){
			return CDFA__FALSE;
		}

		current_state = cdfa__move_to_next_state(*ptr,a);

	}

	return cdfa__is_a_final_state(current_state,a);
}




int main(int argc, char **argv)
{
	char str[2000];
	char str2[1000];
	cdfa__automaton *aut;

	while (1){

		printf("\nEnter regular expression : ");
		fgets(str,256,stdin);
		str[strlen(str) - 1] = 0;

		if (!strcmp(str,"stop")){
			break;
		}

		aut = cdfa__expression_recognizing_automaton(str);

		if (aut == NULL){
			printf("Invalid string\n");
		} else {
			cdfa__print_automaton(aut);

			while (1){

				printf("\nEnter word to recognize : ");
				fgets(str2,256,stdin);
				str2[strlen(str2) - 1] = 0;

				if (!strcmp(str2,"stop")){
					break;
				}

				if (cdfa__is_the_word_recognized(str2,aut)){

					printf("\t Recognized !\n\n");

				} else {
					printf("\t Not recognized\n\n");
				}
			}


			cdfa__free_automaton(aut);
		}
	}

	printf("\n\n\nEND\n");

	return 0;
}
