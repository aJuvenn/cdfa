/*
 * cdfa_operation_intern.h
 *
 *  Created on: 22 oct. 2017
 *      Author: juven
 */

#ifndef CDFA_OPERATION_INTERN_H_
#define CDFA_OPERATION_INTERN_H_

#include "../../../cdfa_edition_interface.h"
#include "../../cdfa_module_interface.h"

#define CDFA_INVALID_INDEX ((unsigned int) -1)


struct cdfa__dynamic_states_set_array {
	unsigned int nb_states_per_element;
	unsigned int nb_states_sets;
	unsigned int maximum_nb_states_sets;
	cdfa__bool **states_sets;
};

typedef struct cdfa__dynamic_states_set_array cdfa__dynamic_states_set_array;

cdfa__dynamic_states_set_array *cdfa__new_dynamic_states_set_array(const unsigned int nb_states_in_an_element,
																	 const unsigned int initial_max_nb_elements);

void cdfa__free_dynamic_states_set_array(cdfa__dynamic_states_set_array *array);

int cdfa__extend_dynamic_array(cdfa__dynamic_states_set_array * const array);

cdfa__bool cdfa__is_the_array_empty(const cdfa__dynamic_states_set_array * const array);

int cdfa__add_in_array_if_not_already_in(cdfa__bool set[], cdfa__dynamic_states_set_array * const array);

cdfa__bool *cdfa__remove_last_element_from_array(cdfa__dynamic_states_set_array * const array);

unsigned int cdfa__index_of_element_in_array(const cdfa__bool set[],
											  cdfa__dynamic_states_set_array * const array);

cdfa__bool cdfa__are_equal_states_set(const unsigned int set_size, const cdfa__bool set_1[], const cdfa__bool set_2[]);

void cdfa__empty_the_states_set(const unsigned int set_size, cdfa__bool state_set[]);

cdfa__bool *cdfa__new_empty_states_set(const unsigned int set_size);

int cdfa__add_in_array(cdfa__bool set[], cdfa__dynamic_states_set_array * const array);

cdfa__bool cdfa__is_in_array(const cdfa__bool set[], cdfa__dynamic_states_set_array * const array);




unsigned int cdfa__union_of_the_letters_to_consider(cdfa__letter dest_letters[],
											  	  	 const cdfa__automaton * const a_1,
											  	  	 const cdfa__automaton * const a_2);

#endif /* CDFA_OPERATION_INTERN_H_ */
