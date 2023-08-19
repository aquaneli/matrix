#include "matrix.h"

double minor_search(matrix_t *A, int i, int j) {
  double res = 0.0;
  matrix_t result = {NULL, 0, 0};

  if (A->rows > 2 && A->columns > 2) {
    create_matrix(A->rows - 1, A->columns - 1, &result);
    sorting_matrix(A, &result, i, j);
    res = det_search(&result);
    remove_matrix(&result);
  } else if (A->rows == 2 && A->columns == 2) {
    res = sorting_matrix_2x2(A, i, j);
  } else if (A->rows == 1 && A->columns == 1) {
    res = A->matrix[i][j];
  }
  return res;
}

double det_search(matrix_t *result) {
  double res = 0.0f;
  double buff[100] = {0.0f};
  if (result->columns == 2) {
    res = (result->matrix[0][0] * result->matrix[1][1]) -
          (result->matrix[0][1] * result->matrix[1][0]);
  } else {
    for (int j = 0; j < result->columns; j++) {
      buff[j] = minor_search(result, 0, j);
      res = (pow(-1, j) * buff[j] * result->matrix[0][j]) + res;
    }
  }
  return res;
}

void null_matrix(matrix_t *result) {
  result->matrix = NULL;
  result->rows = 0;
  result->columns = 0;
}

int check_matrix(matrix_t *A) {
  int res = SUCCESS;
  if (A->matrix == NULL || A->rows <= 0 || A->columns <= 0) {
    res = FAILURE;
  } else {
    for (int i = 0; i < A->rows && res; i++) {
      if (A->matrix[i] == NULL) res = FAILURE;
    }
  }
  return res;
}

int comparison(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (A->rows != B->rows || A->columns != B->columns) {
    res = FAILURE;
  }
  return res;
}

int create_columns(int rows, int columns, matrix_t *result) {
  int res = 0;
  for (int i = 0; i < rows && !res; i++) {
    result->matrix[i] = (double *)malloc(columns * sizeof(double));
    if (result->matrix[i] == NULL) {
      res = 1;
      remove_matrix(result);
    } else {
      for (int j = 0; j < columns; j++) {
        result->matrix[i][j] = 0.0f;
      }
    }
  }
  return res;
}

void mult_cycle(matrix_t *A, matrix_t *B, matrix_t *result) {
  for (int l = 0; l < result->rows; l++) {
    double sum = 0.0;
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        for (int k = 0; k < A->columns; k++) {
          sum = A->matrix[i][k] * B->matrix[k][j] + sum;
        }
        result->matrix[i][j] = sum;
        sum = 0.0;
      }
    }
  }
}

int invrse_result(matrix_t *A, matrix_t *result, double det_res) {
  int res = 0;
  matrix_t B = {NULL, 0, 0};
  matrix_t C = {NULL, 0, 0};
  res = calc_complements(A, &B);
  if (res == 0) {
    if (B.rows == 1) {
      res = create_matrix(1, 1, result);
      if (res == 0) result->matrix[0][0] = 1 / B.matrix[0][0];
    } else {
      res = transpose(&B, &C);
      if (res == 0) res = mult_number(&C, 1 / det_res, result);
    }
    remove_matrix(&B);
    remove_matrix(&C);
  }
  return res;
}

void sorting_matrix(matrix_t *A, matrix_t *result, int i, int j) {
  int k = 0;
  int l = 0;
  for (int m = 0; m < A->rows; m++) {
    for (int n = 0; n < A->columns; n++) {
      if (m != i && n != j) {
        result->matrix[k][l] = A->matrix[m][n];
        l++;
        if (l == result->columns) k++, l = 0;
      }
    }
  }
}

int sum_sub_func(matrix_t *A, matrix_t *B, matrix_t *result, int check) {
  int res = 0;
  if (!check_matrix(A) || !check_matrix(B)) {
    res = 1;
  } else if (!comparison(A, B)) {
    res = 2;
  } else {
    res = create_matrix(A->rows, A->columns, result);
    if (res == 0) {
      for (int i = 0; i < result->rows; i++)
        for (int j = 0; j < result->columns; j++)
          if (check == 0)
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
          else if (check == 1)
            result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
  return res;
}

int sorting_matrix_2x2(matrix_t *A, int i, int j) {
  double res = 0.0f;
  for (int m = 0; m < A->rows; m++) {
    for (int n = 0; n < A->columns; n++) {
      if (m != i && n != j) {
        res = A->matrix[m][n];
      }
    }
  }
  return res;
}