#ifndef HEAP_H_INCLUDED
#define HEAP_H_INCLUDED

int* heap_sort(int* arr, int length);
int left_child(int i);
int right_child(int i);
int parent(int i);

#endif // HEAP_H_INCLUDED
