/*
 * dynamic_states_sets_arrays.c
 *
 *  Created on: 5 oct. 2017
 *      Author: juven
 */


#include "../Headers/cdfa_operation_intern.h"



cdfa__dynamic_states_set_array *cdfa__new_dynamic_states_set_array(const unsigned int nb_states_in_an_element,
																	 const unsigned int initial_max_nb_elements)
{
	cdfa__dynamic_states_set_array *new_array = NULL;

	new_array = malloc(sizeof(cdfa__dynamic_states_set_array));

	if (new_array == NULL){
		fprintf(stderr,"cdfa__new_dynamic_states_set_array : malloc returned NULL\n");
		return NULL;
	}

	new_array->nb_states_per_element = nb_states_in_an_element;
	new_array->nb_states_sets = 0;
	new_array->maximum_nb_states_sets = initial_max_nb_elements;

	new_array->states_sets = malloc(initial_max_nb_elements*sizeof(cdfa__bool*));

	if (new_array->states_sets == NULL){
		fprintf(stderr,"cdfa__new_dynamic_states_set_array : malloc returned NULL\n");
		free(new_array);
		return NULL;
	}

	return new_array;
}


void cdfa__free_dynamic_states_set_array(cdfa__dynamic_states_set_array *array)
{
	unsigned int i;

	for (i = 0 ; i < array->nb_states_sets ; i++){
		free(array->states_sets[i]);
	}

	free(array);
}


int cdfa__extend_dynamic_array(cdfa__dynamic_states_set_array * const array)
{
	unsigned int new_maximum_size = 2*array->maximum_nb_states_sets;
	cdfa__bool **new_data = realloc(array->states_sets,new_maximum_size*sizeof(cdfa__bool *));

	if (new_data == 0){
		fprintf(stderr,"cdfa__extend_dynamic_array : realloc returned NULL\n");
		return 0;
	}

	array->maximum_nb_states_sets = new_maximum_size;
	array->states_sets = new_data;

	return 1;
}



cdfa__bool cdfa__is_the_array_empty(const cdfa__dynamic_states_set_array * const array)
{
	return ((cdfa__bool) array->nb_states_sets == 0);
}


int cdfa__add_in_array_if_not_already_in(cdfa__bool set[], cdfa__dynamic_states_set_array * const array)
{
	int success_value;

	if (cdfa__is_in_array(set,array)){
		return 1;
	}

	success_value = cdfa__add_in_array(set,array);

	if (!success_value){
		fprintf(stderr,"cdfa__add_in_array_if_not_already_in : cdfa__add_in_array returned 0\n");
		return 0;
	}

	return 1;
}


cdfa__bool *cdfa__remove_last_element_from_array(cdfa__dynamic_states_set_array * const array)
{
	cdfa__bool *set = NULL;

	if (array->nb_states_sets == 0){
		fprintf(stderr,"cdfa__remove_last_element_from_array : the array is empty\n");
		return NULL;
	}

	set = array->states_sets[--array->nb_states_sets];

	return set;
}


unsigned int cdfa__index_of_element_in_array(const cdfa__bool set[],
											  cdfa__dynamic_states_set_array * const array)
{
	unsigned int i;

	for (i = 0 ; i < array->nb_states_sets ; i++){

		if (cdfa__are_equal_states_set(array->nb_states_per_element,set,array->states_sets[i])){
			return i;
		}
	}

	return CDFA_INVALID_INDEX;
}




cdfa__bool cdfa__are_equal_states_set(const unsigned int set_size, const cdfa__bool set_1[], const cdfa__bool set_2[])
{
	unsigned int i;

	for (i = 0 ; i < set_size ; i++){
		if (set_1[i] != set_2[i]){
			return CDFA_FALSE;
		}
	}

	return CDFA_TRUE;
}


void cdfa__empty_the_states_set(const unsigned int set_size, cdfa__bool state_set[])
{
	unsigned int i;

	for (i = 0 ; i < set_size ; i++){
		state_set[i] = CDFA_FALSE;
	}
}


cdfa__bool *cdfa__new_empty_states_set(const unsigned int set_size)
{
	unsigned int i;
	cdfa__bool *new_set = malloc(set_size*sizeof(cdfa__bool));

	if (new_set == NULL){
		fprintf(stderr,"cdfa__new_empty_states_set : malloc returned NULL\n");
		return NULL;
	}

	for (i = 0 ; i < set_size ; i++){
		new_set[i] = CDFA_FALSE;
	}

	return new_set;
}




int cdfa__add_in_array(cdfa__bool set[], cdfa__dynamic_states_set_array * const array)
{
	int success_value;

	if (array->nb_states_sets == array->maximum_nb_states_sets){

		success_value = cdfa__extend_dynamic_array(array);

		if (!success_value || array->maximum_nb_states_sets <= array->nb_states_sets){
			fprintf(stderr,"cdfa__add_in_array : cdfa__extend_dynamic_array returned 0 or did not extend the array\n");
			return 0;
		}
	}

	array->states_sets[array->nb_states_sets++] = set;

	return 1;
}

cdfa__bool cdfa__is_in_array(const cdfa__bool set[], cdfa__dynamic_states_set_array * const array)
{
	unsigned int i;

	for (i = 0 ; i < array->nb_states_sets ; i++){

		if (cdfa__are_equal_states_set(array->nb_states_per_element,set,array->states_sets[i])){
			return CDFA_TRUE;
		}
	}

	return CDFA_FALSE;
}











