#ifndef MEASURE_H_INCLUDED
#define MEASURE_H_INCLUDED

typedef int* sort_algorithm(int* arr, int length);
void measure(sort_algorithm alg);

typedef void algorithm(int length);
void measure(algorithm alg, algorithm preparator);

void basic_measure(algorithm alg, algorithm prepare)

#endif // MEASURE_H_INCLUDED
