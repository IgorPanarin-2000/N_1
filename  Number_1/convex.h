#ifndef CONVEX_H
#define CONVEX_H
#include <iostream>
#include "list.h"

class convex
{
  list points;
  list boundary;
public:
  convex ();
  convex (list &new_points);
  ~convex (){}
  void delete_point_by_index (int ind);
  void delete_point_by_value (point p);
  bool is_inside (point p);
  bool is_outside (point p);
  bool is_in_bnd (point p);
  list &get_points ();
  list &get_boundary ();
  int get_num_of_points ();
  void add_point (point p);
  void build_convex ();
  void rebuild_convex ()
  {
    boundary.reset ();
    build_convex ();
  }
  void create_line (point p1, point p2, double &a, double &b, double &c);
  double count_area ();
  double count_perimeter ();
  void get_bounds (point &min, point &max);
  void print ()
  {
    printf ("Boundary:\n");
    boundary.print ();
    printf ("All points:\n");
    points.print ();

  }
  int get_size ()
  {
    return points.get_size ();
  }
};

#endif // CONVEX_H
