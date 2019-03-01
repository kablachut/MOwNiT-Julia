#include <gsl/gsl_ieee_utils.h>
#include <gsl/gsl_interp.h>
#include <stdio.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_vector.h>
#include <time.h>

void multiply_two_vectors(int size, FILE* file)
{
  int i;
  gsl_vector * v = gsl_vector_alloc (size);
  gsl_vector * u = gsl_vector_alloc (size);
  double* result = malloc(size);

  for (i = 0; i < size; i++)
      gsl_vector_set (v, i, 5 + i);

  for (i = 0; i < size; i++)
      gsl_vector_set (u, i, i);

  clock_t t;
  t = clock();
  gsl_blas_ddot(v, u, result);
  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
  fprintf(file, "1;%d;%f\n", size, time_taken );
  gsl_vector_free(u);
  gsl_vector_free(v);
}

void multiply_vector_and_matrix(int size, FILE *file)
{

  gsl_vector * v = gsl_vector_alloc (size);
  gsl_vector * u = gsl_vector_alloc (size);
  gsl_matrix * A = gsl_matrix_calloc(size, size);

  gsl_matrix_set_identity(A);

  for (int i = 0; i < size; i++)
      gsl_vector_set (v, i, 5 + i);

  clock_t t;
  t = clock();
  gsl_blas_dgemv(CblasNoTrans, 1.0, A, v, 1.0, u);
  t = clock() - t;
  double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
  fprintf(file, "2;%d;%f \n", size, time_taken);
  gsl_vector_free(u);
  gsl_vector_free(v);
  gsl_matrix_free(A);
}

void print_vector (int size, gsl_vector * v)
{
  for (int i = 0; i < size; i++)
      printf("v%d = %g\n", i, gsl_vector_get(v, i));
}

int main (void)
{

  int size;
  FILE *file = fopen("data.csv", "w");
  fprintf(file, "\"type\";\"size\";\"time\"\n");
  fprintf(file, "\"type\";\"size\";\"time\"\n");

  for (size = 1000; size < 10000; size += 1000){
    //  for (int i = 0; i < 10; i++)
            multiply_two_vectors(size, file);
  }


  for (size = 1000; size < 10000; size += 1000){
     // for (int i = 0; i <10; i++)
            multiply_vector_and_matrix(size, file);
  }


  fclose(file);

  return 0;
}
