/*
 * exponentiation_automatons.c
 *
 *  Created on: 22 oct. 2017
 *      Author: juven
 */

#include "../Headers/cdfa_edition_interface.h"
#include "../Headers/intern_functions.h"



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



cdfa__automaton *cdfa__exponentiation_automaton(const unsigned int power, const cdfa__automaton * const a)
{
	cdfa__automaton *b = NULL;
	cdfa__automaton *c = NULL;

	if (power == 0){
		return cdfa__word_recognizing_automaton("");
	}

	b = cdfa__exponentiation_automaton(power/2,a);

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







cdfa__automaton *cdfa__range_exponentiation_automaton(const unsigned int min_power, const unsigned int max_power, const cdfa__automaton * const a)
{
	cdfa__automaton *b = NULL;
	cdfa__automaton *c = NULL;
	cdfa__automaton *d = NULL;

	if (min_power > max_power){
		fprintf(stderr,"cdfa__power_range_automaton : invalid range [%u;%u]\n",min_power,max_power);
		return NULL;
	}

	b = cdfa__exponentiation_automaton(min_power,a);

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

	c = cdfa__exponentiation_automaton(max_power,b);

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
