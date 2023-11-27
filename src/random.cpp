#include "random.h"

Random::Random()
{
}

float Random::get1D()
{
  return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}

Point2f Random::get2D()
{
  return Point2f(get1D(), get1D());
}

int Random::getInt(int min, int max)
{
  // Return a random integer between min (inclusive) and max (exclusive)
  return min + (rand() % (max - min));
}
