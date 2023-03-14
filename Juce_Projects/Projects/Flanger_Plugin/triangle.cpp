#include "triangle.h"
#include "math.h"

Triangle::Triangle(float frequency, float amplitude) : Oscillator(frequency, amplitude)
{
 #if DEBUG
  std::cout << "Triangle::Triangle constructor" << frequency << "\n";
  
#endif
}

void Triangle::calculate()
{
  sample = (2/M_PI)* asin(sin((2*M_PI*phase)));
}

