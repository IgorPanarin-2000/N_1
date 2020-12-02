#include "list.h"

bool operator == (const point &p1, const point &p2)
{
  return p1.x <= p2.x && p1.x >= p2.x
      && p1.y <= p2.y && p1.y >= p2.y;
}

double length (const point &p1)
{
  return sqrt (p1.x * p1.x + p1.y * p1.y);
}
