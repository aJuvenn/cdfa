/*
 * main.c
 *
 *  Created on: 26 sept. 2017
 *      Author: juven
 */

#include "Headers/cdfa_interface.h"
#include "Headers/intern_functions.h"





int main(int argc, char **argv)
{
	cdfa__automaton *a = cdfa__word_recognizing_automaton("caca");

	cdfa__print_automaton(a);

	cdfa__automaton *b = cdfa__kleen_star_automaton(a);

	cdfa__print_automaton(b);

	cdfa__automaton *c = cdfa__word_recognizing_automaton("capouca");
	cdfa__print_automaton(c);

	cdfa__automaton *d = cdfa__language_concatenation_automaton(b,c);
	cdfa__print_automaton(d);

	cdfa__automaton *e = cdfa__kleen_plus_automaton(d);
	cdfa__print_automaton(e);

	cdfa__automaton *f = cdfa__minimal_automaton(e);
	cdfa__print_automaton(f);

	return 0;
}
