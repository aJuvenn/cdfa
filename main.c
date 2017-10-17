/*
 * main.c
 *
 *  Created on: 26 sept. 2017
 *      Author: juven
 */

#include "Headers/cdfa_interface.h"
#include "Headers/intern_functions.h"






int cdfa__read_expression(const char **cursor,
							unsigned int *nb_automaton_stack,
							cdfa__automaton *automaton_stack[],
							char char_stack[]);



int main(int argc, char **argv)
{
	char str[256];
	char char_stack[256];
	cdfa__automaton *automaton_stack[256];
	unsigned int nb_automaton_stack = 0;
	const char *cursor = NULL;
	int no_error;

	str[0] = 0;

	while (str[0] != 's'){

		cursor = str;
		nb_automaton_stack = 0;
		printf("\nEnter string : ");
		fgets(str,256,stdin);

		no_error = cdfa__read_expression(&cursor,&nb_automaton_stack,automaton_stack,char_stack);

		if (!no_error){
			printf("Invalid string\n");
		} else {
			printf("Valid string : %u automatons in stack\n",nb_automaton_stack);
			cdfa__print_automaton(*automaton_stack);
		}
	}

	return 0;
}
