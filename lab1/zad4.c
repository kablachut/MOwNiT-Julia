#include <stdio.h>
#include <math.h>

int main(void) {

  double a = 0.25;
  double b = 18.0;
  double c = 1.0;
  double delta = pow(b, 2);
  double x1 = (-b + sqrt(delta))/2*a;
  double x2 = (-b - sqrt(delta))/2*a;
  printf("Results of quadratic equation where:\n");
  printf("a=%f, b=%f, c=%f\n", a, b, c);
  printf("Using standard algorithm\n");
  printf("%f\t%f\n",x1,x2);

  double x3 = (c/a *2*a)/(-b - sqrt(delta));
  double x4 = c/(a*x3);
  printf("Using fixed algorithm\n");
  printf("%f\t%f\n",x3, x4);
  return 0;
}
