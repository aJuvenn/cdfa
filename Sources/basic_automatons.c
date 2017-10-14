#include "../Headers/cdfa_interface.h"
#include "../Headers/cdfa_edition_interface.h"


cdfa__automaton *cdfa__word_recognizing_automaton(const char word[])
{

	unsigned int i,j;
	int is_considered;
	unsigned int nb_considered_letters = 0;
	unsigned int word_size;
	cdfa__automaton *a = NULL;


	if (word == NULL){

		a = cdfa__empty_automaton(1,0,NULL);

		if (a == NULL){
			fprintf(stderr,"cdfa__word_recognizing_automaton : cdfa__empty_automaton returned NULL\n");
			return NULL;
		}

		cdfa__set_as_the_starting_state(CDFA_WELL,a);
		cdfa__move_to_starting_state(a);

		return a;
	}

	word_size = 0;

	while (word[word_size] != 0){
		word_size++;
	}

	cdfa__letter considered_letters[word_size];

	for (i = 0 ; i < word_size ; i++){

		is_considered = 0;

		for (j = 0 ; j < nb_considered_letters ; j++){

			if (((cdfa__letter) word[i]) == considered_letters[j]){
				is_considered = 1;
				break;
			}

		}

		if (!is_considered){
			considered_letters[nb_considered_letters++] = (cdfa__letter) word[i];
		}
	}

	a = cdfa__empty_automaton(word_size + 2, nb_considered_letters, considered_letters);

	if (a == NULL){
		fprintf(stderr,"cdfa__word_recognizing_automaton : cdfa__empty_automaton returned NULL\n");
		return NULL;
	}

	for (i = 0 ; i < word_size ; i++){
		cdfa__add_transition(i+1,(cdfa__letter) word[i],i+2,a);
	}

	cdfa__set_as_the_starting_state(1,a);
	cdfa__set_as_a_final_state(word_size + 1,a);

	cdfa__move_to_starting_state(a);

	return a;
}



