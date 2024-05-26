#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void free_matrix(int** matrix, int rows) {
  for (int i = 0; i < rows; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

void print_matrix(int** matrix, int row, int cols) {
  for (int i = 0; i < row; i++) {
    printf("| ");
    for (int j = 0; j < cols; j++) {
      printf("%d ", matrix[i][j]);
    }
    printf(" |\n");
  }
  printf("\n");
}

int* get_matrix_size(char* matrix_name) {
  int rows, cols;
  printf("Rows and columns for %s matrix(row col): ", matrix_name);
  scanf("%d%d", &rows, &cols);

  int* matrix_size = (int*)malloc(2 * sizeof(int));

  if (matrix_size == NULL) {
    fprintf(stderr, "Memory allocation failed\n");
    exit(1);
  }

  matrix_size[0] = rows;
  matrix_size[1] = cols;

  return matrix_size;
}

int** get_matrix(int row, int col) {
  int** matrix = (int**)malloc(row * sizeof(int*));
  for (int i = 0; i < row; i++) {
    matrix[i] = (int*)malloc(col * sizeof(int));
    for (int j = 0; j < col; j++) {
      // printf("Enter the element at position (%d, %d): ", i, j);
      // scanf("%d", &matrix[i][j]);

      matrix[i][j] = rand() % 10;
    }
  }

  return matrix;
}

void matrices_arithmetic(int sign) {
  int* matrix_size = get_matrix_size("both");

  int rows = matrix_size[0];
  int cols = matrix_size[1];

  int** matrix_1 = get_matrix(rows, cols);
  int** matrix_2 = get_matrix(rows, cols);

  printf("Matrix 1:\n");
  print_matrix(matrix_1, rows, cols);

  printf("Matrix 2:\n");
  print_matrix(matrix_2, rows, cols);

  int** result_matrix = (int**)malloc(rows * sizeof(int*));

  for (int i = 0; i < rows; i++) {
    result_matrix[i] = (int*)malloc(cols * sizeof(int));
    for (int j = 0; j < cols; j++) {
      result_matrix[i][j] = matrix_1[i][j] + (matrix_2[i][j] * sign);
    }
  }

  printf("Result:\n");
  print_matrix(result_matrix, rows, cols);

  free_matrix(matrix_1, rows);
  free_matrix(matrix_2, rows);
  free_matrix(result_matrix, rows);
  free(matrix_size);
}

void matrices_multiplication() {
  int* matrix_1_size = get_matrix_size("first");
  int* matrix_2_size = get_matrix_size("second");

  int matrix_1_rows = matrix_1_size[0], matrix_1_cols = matrix_1_size[1];
  int matrix_2_rows = matrix_2_size[0], matrix_2_cols = matrix_2_size[1];

  if (matrix_1_cols != matrix_2_rows) {
    fprintf(stderr,
            "Matrix multiplication is not possible. The column of "
            "first matrix and row of second matrix is not same.\n");
    exit(1);
  }

  int** matrix_1 = get_matrix(matrix_1_rows, matrix_1_cols);
  int** matrix_2 = get_matrix(matrix_2_rows, matrix_2_cols);

  printf("Matrix 1:\n");
  print_matrix(matrix_1, matrix_1_rows, matrix_1_cols);

  printf("Matrix 2:\n");
  print_matrix(matrix_2, matrix_2_rows, matrix_2_cols);

  int** result_matrix = (int**)malloc(matrix_1_rows * sizeof(int*));

  for (int i = 0; i < matrix_1_rows; i++) {
    result_matrix[i] = (int*)malloc(matrix_2_cols * sizeof(int));
    for (int j = 0; j < matrix_2_cols; j++) {
      /**
       * How it works?
       * We are multiplying the (i)th row of first matrix with the (j)th column
       * of second matrix. So, we are iterating through the columns of first
       * matrix and rows of second matrix and multiplying the corresponding
       * elements and adding them to get the result.
       */
      result_matrix[i][j] = 0;
      for (int k = 0; k < matrix_1_cols; k++) {
        result_matrix[i][j] += matrix_1[i][k] * matrix_2[k][j];
      }
    }
  }

  printf("Result:\n");
  print_matrix(result_matrix, matrix_1_rows, matrix_2_cols);

  free_matrix(matrix_1, matrix_1_rows);
  free_matrix(matrix_2, matrix_2_rows);
  free_matrix(result_matrix, matrix_1_rows);
  free(matrix_1_size);
  free(matrix_2_size);
}

void matrix_transpose() {
  int* matrix_size = get_matrix_size("");

  int rows = matrix_size[0];
  int cols = matrix_size[1];

  int** matrix = get_matrix(rows, cols);

  printf("Matrix:\n");
  print_matrix(matrix, rows, cols);

  int** result_matrix = (int**)malloc(cols * sizeof(int*));

  for (int i = 0; i < cols; i++) {
    result_matrix[i] = (int*)malloc(rows * sizeof(int));
    for (int j = 0; j < rows; j++) {
      result_matrix[i][j] = matrix[j][i];
    }
  }

  printf("Result:\n");
  print_matrix(result_matrix, cols, rows);

  free_matrix(matrix, rows);
  free_matrix(result_matrix, cols);
  free(matrix_size);
}

enum Operation { Plus = 1, Minus = 2, Multiply = 3, Transpose = 4 };

int main() {
  srand(time(NULL));

  enum Operation op;

  printf("Enter the operation you want to perform:\n");
  printf("1. Plus, 2. Minus, 3. Multiply, 4. Transpose\n");
  scanf("%d", &op);

  switch (op) {
    case Plus:
      matrices_arithmetic(1);
      break;
    case Minus:
      matrices_arithmetic(-1);
      break;
    case Multiply:
      matrices_multiplication();
      break;
    case Transpose:
      matrix_transpose();
      break;
    default:
      printf("Invalid operation\n");
      break;
  }
}