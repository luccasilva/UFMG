#include <stdio.h>
#include <math.h>

float cauchy (float x){
	return 1/(M_PI*(1+x*x));
}

float gumbel (float x,float u,float b){
	float z;
	z=(x-u)/b;
	return (1/b)*exp(-1*(z+exp(-z)));
}

float laplace (float x,float u,float b){
	return 1/(2*b)*exp(-1*(fabs((x-u)/b)));
}
