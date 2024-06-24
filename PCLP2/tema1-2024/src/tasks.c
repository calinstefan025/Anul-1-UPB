#include "functional.h"
#include "tasks.h"
#include "tests.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void reverse_func(void *new_list, void *value) {
	array_t *list = (array_t *)new_list;
	list->data = list->data - list->elem_size;
	memcpy(list->data, value, list->elem_size);
}

array_t reverse(array_t list) {
	array_t new_list;
	new_list.data = malloc(list.len * list.elem_size);
	new_list.len = list.len;
	new_list.elem_size = list.elem_size;
	new_list.data = new_list.data + (list.len) * list.elem_size;
	reduce(reverse_func, &new_list, list);
	return new_list;
}

void new_number_create(void *num, void **values) {
	number_t *number = (number_t *)num;

	number->integer_part = *(int *)values[0];
	number->fractional_part = *(int *)values[1];
	number->string = malloc(20 * sizeof(char));

	sprintf(number->string, "%d.%d", number->integer_part,
			number->fractional_part);
}

void new_number_destroy(void *num) {
	number_t *number = (number_t *)num;
	free(number->string);
}

array_t create_number_array(array_t integer_part, array_t fractional_part) {
	array_t new_list;
	new_list =  map_multiple(new_number_create, sizeof(number_t),
							 new_number_destroy, 2, integer_part,
							 fractional_part);
	return new_list;
}

boolean pass(void *student) {
	student_t *stud = (student_t *)student;

	if (stud->grade >= 5.0)
		return true;
	return false;
}

array_t get_passing_students_names(array_t list) {
	array_t new_list = filter(pass, list);
	return new_list;
}

void func_suma(void *sum, void *value) {
	int *suma = (int *)sum;
	int *val = (int *)value;
	*suma += *val;
}

void verif_suma(void *ok, void **values) {
	array_t list = *(array_t *)values[0];
	int sum = 0;
	reduce(func_suma, &sum, list);

	int *val = (int *)values[1];
	if (sum >= *val)
		*(boolean *)ok = true;
	else
		*(boolean *)ok = false;
}

array_t check_bigger_sum(array_t list_list, array_t int_list) {
	array_t new_list;
	new_list = map_multiple(verif_suma, sizeof(boolean), NULL, 2, list_list,
							int_list);
	return new_list;
}

array_t get_even_indexed_strings(array_t list) {
	(void)list;
	return (array_t){0};
}

array_t generate_square_matrix(int n) {
	(void)n;
	return (array_t){0};
}
