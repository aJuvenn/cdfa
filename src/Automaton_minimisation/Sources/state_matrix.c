/*
 * state_matrix.c
 *
 *  Created on: 31 oct. 2017
 *      Author: juven
 */

#include "../../../src/Automaton_minimisation/Headers/cdfa_minimisation_intern.h"



unsigned int **cdfa__new_matrix(const unsigned int height, const unsigned int width)
{

	unsigned *array = NULL ;
	unsigned **matrix = NULL ;
	unsigned int i ;

	if (height == 0 || width == 0){
		return NULL;
	}

	CDFA__MALLOC(array,width*height*sizeof(unsigned int));
	CDFA__MALLOC(matrix,height*sizeof(unsigned int *));

	for (i = 0 ; i < height ; i++){
		matrix[i] = array + i*width ;
	}

	return matrix;
}



cdfa__automaton_state ***cdfa__new_state_triple_matrix(const unsigned int height,
												  const unsigned int width,
												  const unsigned int depth)
{

	unsigned int i;
	cdfa__automaton_state *array = NULL;
	cdfa__automaton_state **width_array = NULL;
	cdfa__automaton_state ***new_matrix = NULL;

	if (height == 0 || width == 0 || depth == 0){
		return NULL;
	}

	CDFA__MALLOC(array,height*width*depth*sizeof(cdfa__automaton_state));
	CDFA__MALLOC(width_array,height*width*sizeof(cdfa__automaton_state *));

	for (i = 0 ; i < width*height ; i++){
		width_array[i] = array + i*depth;
	}

	CDFA__MALLOC(new_matrix,height*sizeof(cdfa__automaton_state**));

	for (i = 0 ; i < height ; i++){
		new_matrix[i] = width_array + width*i;
	}

	return new_matrix;
}


void cdfa__free_state_triple_matrix(cdfa__automaton_state ***m)
{
	if (m == NULL){
		return;
	}

	if (m[0] == NULL){
		free(m);
		return;
	}

	if (m[0][0] == NULL){
		free(m[0]);
		free(m);
		return;
	}

	free(m[0][0]);
	free(m[0]);
	free(m);

}


void cdfa__free_matrix(unsigned int **m)
{
	if (m != NULL){

		if (m[0] != NULL){
			free(m[0]);
		}

		free(m);
	}
}

