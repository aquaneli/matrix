#include "matrix.h"

// создание матрицы
int create_matrix(int rows, int columns, matrix_t *result) {
  null_matrix(result);
  int res = 0;
  if (rows <= 0 || columns <= 0) {
    res = 1;
  } else {
    result->matrix = (double **)malloc(rows * sizeof(double *));
    if (result->matrix == NULL) {
      res = 1;
    } else {
      result->rows = rows;
      result->columns = columns;
      res = create_columns(rows, columns, result);
    }
  }
  return res;
}

// очистка матрицы
void remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      if (A->matrix[i] != NULL) free(A->matrix[i]);
    }
    free(A->matrix);
  }
  null_matrix(A);
}

// сравнение матриц
int eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (!check_matrix(A) || !check_matrix(B) || !comparison(A, B)) {
    res = FAILURE;
  } else {
    for (int i = 0; i < A->rows && res; i++) {
      for (int j = 0; j < A->columns && res; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
          res = FAILURE;
        }
      }
    }
  }
  return res;
}

// сумма двух матриц
int sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int check = 0;
  null_matrix(result);
  return sum_sub_func(A, B, result, check);
}

// Разница двух матриц
int sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int check = 1;
  null_matrix(result);
  return sum_sub_func(A, B, result, check);
}

// умножение матрицы на число
int mult_number(matrix_t *A, double number, matrix_t *result) {
  null_matrix(result);
  int res = 0;
  if (!check_matrix(A)) {
    res = 1;
  } else {
    res = create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return res;
}

// умножение двух матриц
int mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  null_matrix(result);
  int res = 0;
  if (!check_matrix(A) || !check_matrix(B)) {
    res = 1;
  } else {
    if (A->columns != B->rows) {
      res = 2;
    } else {
      res = create_matrix(A->rows, B->columns, result);
      if (res == 0) {
        mult_cycle(A, B, result);
      }
    }
  }
  return res;
}

// транспонирование
int transpose(matrix_t *A, matrix_t *result) {
  null_matrix(result);
  int res = 0;
  if (!check_matrix(A)) {
    res = 1;
  } else {
    if (A->rows != A->columns) {
      res = create_matrix(A->columns, A->rows, result);
    } else {
      res = create_matrix(A->rows, A->columns, result);
    }
    if (res == 0) {
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
          result->matrix[j][i] = A->matrix[i][j];
    }
  }
  return res;
}

// таблица миноров алгебраических дополнений
int calc_complements(matrix_t *A, matrix_t *result) {
  null_matrix(result);
  int res = 0;
  if (!check_matrix(A)) {
    res = 1;
  } else {
    if (A->rows != A->columns)
      res = 2;
    else {
      res = create_matrix(A->rows, A->columns, result);
      if (res == 0) {
        for (int i = 0; i < A->rows; i++) {
          for (int j = 0; j < A->columns; j++) {
            result->matrix[i][j] = minor_search(A, i, j) * pow(-1, i + j);
            if (result->matrix[i][j] == -0) result->matrix[i][j] = 0;
          }
        }
      }
    }
  }
  return res;
}

// определитель
int determinant(matrix_t *A, double *result) {
  int res = 0;
  *result = 0.0f;
  if (!check_matrix(A)) {
    res = 1;
  } else {
    matrix_t B = {NULL, 0, 0};
    res = calc_complements(A, &B);
    if (res == 0) {
      if (A->columns > 1) {
        for (int j = 0; j < B.columns; j++)
          *result = (A->matrix[0][j] * B.matrix[0][j]) + (*result);
      } else
        *result = A->matrix[0][0];
    }
    remove_matrix(&B);
  }
  return res;
}

// инверсия матрицы
int inverse_matrix(matrix_t *A, matrix_t *result) {
  null_matrix(result);
  double det_res = 0.0f;
  int res = 0;
  if (!check_matrix(A)) {
    res = 1;
  } else {
    res = determinant(A, &det_res);
    if (res == 0) {
      if (fabs(det_res) < 1e-7) {
        res = 2;
      } else {
        invrse_result(A, result, det_res);
      }
    }
  }
  return res;
}
