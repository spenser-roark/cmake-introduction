#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double mysqrt(double val) {
	// if we have both log and exp then use them
	#if defined (HAVE_LOG) && defined (HAVE_EXP)
		fprintf(stdout, "Using log and exp to get sqrt of value\n");
  		result = exp(log(x)*0.5);
	#else // otherwise use an iterative approach
  		fprintf(stdout, "no log or exp, using sqrt from math.h\n");
		return sqrt(val);
	#endif
}
