#ifndef MATRIX_H_
#define MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int create_matrix(int rows, int columns, matrix_t *result);
void remove_matrix(matrix_t *A);
int eq_matrix(matrix_t *A, matrix_t *B);
int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int mult_number(matrix_t *A, double number, matrix_t *result);
int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int transpose(matrix_t *A, matrix_t *result);
int calc_complements(matrix_t *A, matrix_t *result);
int determinant(matrix_t *A, double *result);
int inverse_matrix(matrix_t *A, matrix_t *result);

double minor_search(matrix_t *A, int i, int j);
double det_search(matrix_t *result);
void null_matrix(matrix_t *result);
int check_matrix(matrix_t *A);
int comparison(matrix_t *A, matrix_t *B);
int create_columns(int rows, int columns, matrix_t *result);
int invrse_result(matrix_t *A, matrix_t *result, double det_res);
void mult_cycle(matrix_t *A, matrix_t *B, matrix_t *result);
void sorting_matrix(matrix_t *A, matrix_t *result, int i, int j);
int sum_sub_func(matrix_t *A, matrix_t *B, matrix_t *result, int check);
int sorting_matrix_2x2(matrix_t *A, int i, int j);

#endif  // MATRIX_H_