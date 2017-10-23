/*
 * main.c
 *
 *  Created on: 26 sept. 2017
 *      Author: juven
 */

#include "Modules/cdfa_module_interface.h"




int main(int argc, char **argv)
{
	char str[2000];
	str[0] = 0;
	cdfa__automaton *aut;

	while (str[0] != 's'){

		printf("\nEnter string : ");
		fgets(str,256,stdin);

		aut = cdfa__expression_recognizing_automaton(str);

		if (aut == NULL){
			printf("Invalid string\n");
		} else {
			cdfa__print_automaton(aut);
			cdfa__free_automaton(aut);
		}
	}



	return 0;
}
