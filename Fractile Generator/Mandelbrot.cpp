#include "Mandelbrot.h"
#include <complex>

int Mandelbrot::getIterations(double p_x, double p_y)
{
	std::complex<double> z{ 0 };
	std::complex<double> c(p_x, p_y);
	int iterations{ 0 };

	while (iterations < maxIterations)
	{
		z = z * z + c;
		if (abs(z) > 2)
		{
			break;
		}
		iterations++;
	}

	return iterations;
}
