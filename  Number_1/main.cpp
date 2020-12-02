#include <iostream>
#include "convex.h"
void print (bool res);

void print (bool res)
{
  if (res)
    printf ("True\n");
  else
    printf ("False\n");
}

int main()
{
  convex a, b;
  point p;
  printf("Test add points and creation by points\n");
  a.add_point ({-2, -2});
  a.add_point ({-2, 2});
  a.add_point ({2, 2});
  a.add_point ({2, -2});
  a.add_point ({0, 0});
  a.add_point ({1, 0});
  a.add_point ({1, 1});


  printf("Test print\n");
  a.print ();

  printf("Test delete\n");
  a.delete_point_by_index (5);
  a.delete_point_by_value ({100, 100});
  a.delete_point_by_index (100000);
  a.delete_point_by_value ({2, 2});


  a.print ();

  printf ("Check =\n");
  b = a;
  b.print ();

  printf ("Size = %d\n", a.get_size ());

  printf ("Check is {2, 1} in boundary?\n");
  print (a.is_in_bnd ({2, 1}));
  printf ("Check is {3, 3} in boundary?\n");
  print (a.is_in_bnd ({3, 3}));

  printf ("Check is {0, 0} inside?\n");
  print (a.is_inside ({0, 0}));
  printf ("Check is {3, 3} inside?\n");
  print (a.is_inside ({3, 3}));

  printf ("Check is {0, 0} outside?\n");
  print (a.is_outside ({0, 0}));
  printf ("Check is {3, 3} outside?\n");
  print (a.is_outside ({3, 3}));

  printf ("Perimetr is %lf\n", a.count_perimeter ());

  printf ("Area is %lf\n", a.count_area ());

  point min, max;
  a.get_bounds (min, max);
  printf ("Bounds are:\n min: (%lf %lf)\n max: (%lf %lf)\n", min.x, min.y, max.x, max.y);



  return 0;
}
