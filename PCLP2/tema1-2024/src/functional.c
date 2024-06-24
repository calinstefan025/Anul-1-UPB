#include "functional.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void for_each(void (*func)(void *), array_t list)
{
	char *start = (char *)list.data;
	char *end = start + list.len * list.elem_size;

	while (start < end) {
		func(start);
		start += list.elem_size;
	}
}

array_t map(void (*func)(void *, void *),
			int new_list_elem_size,
			void (*new_list_destructor)(void *),
			array_t list)
{
	array_t new_list;
	new_list.elem_size = new_list_elem_size;
	new_list.destructor = new_list_destructor;
	new_list.len = list.len;

	new_list.data = malloc(new_list.len * new_list.elem_size);
	if (!new_list.data)
		return (array_t){0};

	char *start = (char *)list.data;
	char *end = start + list.len * list.elem_size;
	char *start2 = (char *)new_list.data;

	while (start < end) {
		func(start2, start);
		start += list.elem_size;
		start2 += new_list.elem_size;
	}

	if (list.destructor) {
		start = (char *)list.data;
		end = start + list.len * list.elem_size;
		while (start < end) {
			list.destructor(start);
			start += list.elem_size;
		}
	}

	free(list.data);

	return new_list;
}

array_t filter(boolean(*func)(void *), array_t list)
{
	array_t new_list;
	new_list.elem_size = list.elem_size;
	new_list.destructor = list.destructor;
	int lungime_noua = 0;

	new_list.data = malloc(list.len * list.elem_size);
	if (!new_list.data)
		return (array_t){0};

	char *start = (char *)list.data;
	char *end = start + list.len * list.elem_size;
	char *start2 = (char *)new_list.data;

	while (start < end) {
		if (func(start)) {
			memcpy(start2, start, list.elem_size);
			start2 += list.elem_size;
			lungime_noua++;
		}
		start += list.elem_size;
	}

	new_list.len = lungime_noua;
	new_list.data = realloc(new_list.data, new_list.len * new_list.elem_size);

	free(list.data);

	return new_list;
}

void *reduce(void (*func)(void *, void *), void *acc, array_t list)
{
	char *start = (char *)list.data;
	char *end = start + list.len * list.elem_size;

	while (start < end) {
		func(acc, start);
		start += list.elem_size;
	}

	return acc;
}

void for_each_multiple(void(*func)(void **), int varg_c, ...)
{
	va_list liste;
	va_start(liste, varg_c);
	int lungime_minima = 0, i;

	array_t *liste_array = malloc(varg_c * sizeof(array_t));
	for (int i = 0; i < varg_c; i++) {
		liste_array[i] = va_arg(liste, array_t);
		// daca lungime_minima = 0 => ii atribuim prima dimensiune de lista
		if (liste_array[i].len < lungime_minima || lungime_minima == 0)
			lungime_minima = liste_array[i].len;
	}

	va_end(liste);

	char **start_pointers = malloc(varg_c * sizeof(char *));
	char **end_pointers = malloc(varg_c * sizeof(char *));

	for (int i = 0; i < varg_c; i++) {
		start_pointers[i] = (char *)liste_array[i].data;
		end_pointers[i] = start_pointers[i] +
							lungime_minima * liste_array[i].elem_size;
	}

	while (start_pointers[0] < end_pointers[0]) {
		void **elem = malloc(varg_c * sizeof(array_t));
		for (i = 0; i < varg_c; i++) {
			elem[i] = start_pointers[i];
			start_pointers[i] += liste_array[i].elem_size;
		}
		func(elem);
		free(elem);
	}

	free(liste_array);
	free(start_pointers);
	free(end_pointers);
}

array_t map_multiple(void (*func)(void *, void **),
					 int new_list_elem_size,
					 void (*new_list_destructor)(void *),
					 int varg_c, ...)
{
	va_list liste;
	va_start(liste, varg_c);
	int lungime_minima = 0, i;

	array_t *liste_array = malloc(varg_c * sizeof(array_t));

	for (i = 0; i < varg_c; i++) {
		liste_array[i] = va_arg(liste, array_t);
		if (liste_array[i].len < lungime_minima || lungime_minima == 0)
			lungime_minima = liste_array[i].len;
	}

	va_end(liste);

	array_t new_list;
	new_list.elem_size = new_list_elem_size;
	new_list.destructor = new_list_destructor;
	new_list.len = lungime_minima;

	new_list.data = malloc(lungime_minima * new_list.elem_size);
	if (!new_list.data)
		return (array_t){0};

	char **start_pointers = malloc(varg_c * sizeof(char *));
	char **end_pointers = malloc(varg_c * sizeof(char *));

	for (i = 0; i < varg_c; i++) {
		start_pointers[i] = (char *)liste_array[i].data;
		end_pointers[i] = start_pointers[i] +
							lungime_minima * liste_array[i].elem_size;
	}

	char *start2 = (char *)new_list.data;

	while (start_pointers[0] < end_pointers[0]) {
		void **elem = malloc(varg_c * sizeof(array_t));
		for (i = 0; i < varg_c; i++) {
			elem[i] = start_pointers[i];
			start_pointers[i] += liste_array[i].elem_size;
		}
		func(start2, elem);
		start2 += new_list.elem_size;
		free(elem);
	}

	for (i = 0; i < varg_c; i++) {
		if (liste_array[i].destructor) {
			char *start = (char *)liste_array[i].data;
			char *end = start + liste_array[i].len * liste_array[i].elem_size;
			while (start < end) {
				liste_array[i].destructor(start);
				start += liste_array[i].elem_size;
			}
		}
		free(liste_array[i].data);
	}

	free(liste_array);
	free(start_pointers);
	free(end_pointers);

	return new_list;
}

void *reduce_multiple(void(*func)(void *, void **), void *acc, int varg_c, ...)
{
	va_list liste;
	va_start(liste, varg_c);
	int lungime_minima = 0, i;

	array_t *liste_array = malloc(varg_c * sizeof(array_t));

	for (i = 0; i < varg_c; i++) {
		liste_array[i] = va_arg(liste, array_t);
		if (liste_array[i].len < lungime_minima || lungime_minima == 0)
			lungime_minima = liste_array[i].len;
	}

	va_end(liste);

	char **start_pointers = malloc(varg_c * sizeof(char *));
	char **end_pointers = malloc(varg_c * sizeof(char *));

	for (i = 0; i < varg_c; i++) {
		start_pointers[i] = (char *)liste_array[i].data;
		end_pointers[i] = start_pointers[i] +
							lungime_minima * liste_array[i].elem_size;
	}

	while (start_pointers[0] < end_pointers[0]) {
		void **elem = malloc(varg_c * sizeof(array_t));
		for (i = 0; i < varg_c; i++) {
			elem[i] = start_pointers[i];
			start_pointers[i] += liste_array[i].elem_size;
		}
		func(acc, elem);
		free(elem);
	}

	free(liste_array);
	free(start_pointers);
	free(end_pointers);

	return acc;
}
