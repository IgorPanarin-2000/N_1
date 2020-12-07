#include "convex.h"
int crossProduct(point a, point b, point c);//векторное произведение
double area (point a, point b, point c);

convex::convex ()//сама структура выпуклой оболочки-в ней находится 2 листа-граница и абсолютно все точки которые внутри лежат(включая границу в том числе)
{
}

convex::convex (list &new_points)//есть функция подсчёта периметра( просто проходите по границе и считаете)
{
  points = new_points;//функция подсчёта площади(просто проходитесь по границе и суммируете все точки и делите на среднее арифметическое, чтобы получить точку внутри)
  build_convex ();
}

void convex::delete_point_by_index (int ind)
{
  bool res;
  if (ind < 0 || ind >= points.get_size ())
    return;
  if (ind == 0)
    {
      list_node *h = points.get_head ();
      res = is_inside (points.get_head ()->get_point ());
      points.set_head (points.get_head ()->get_next ());
      delete h;
      points.reduce_size ();
    }
  else
    {
      list_node *node = &points[ind - 1];
      list_node *n = node->get_next ();
      res = is_inside (n->get_point ());
      node->set_next (n->get_next ());
      delete n;
      points.reduce_size ();
    }

  if (!res)
    rebuild_convex ();
}

void convex::delete_point_by_value (point p)
{
  bool res = is_inside (p);
  list_node *prev = points.get_head ();
  for (list_node *curr = prev->get_next (); curr;)
    {
      if (curr->get_point () == p)
        {
          prev->set_next (curr->get_next ());
          delete curr;
          curr = prev->get_next ();
          points.reduce_size ();
        }
      else
        {
          prev = curr;//предыдущий=текущий
          curr = curr->get_next ();
        }
    }
  if (points.get_head ()->get_point () == p)
    {
      list_node *h = points.get_head ();
      points.set_head (points.get_head ()->get_next ());
      delete h;
      points.reduce_size ();
    }
  if (!res)
    rebuild_convex ();
}

bool convex::is_inside (point p)
{
  if (is_in_bnd (p))
    return false;
  bool result = false;
  list_node *prev = boundary.get_tail ();
  for (list_node *curr = boundary.get_head (); curr; curr = curr->get_next ())
    {
      point p_pr = prev->get_point ();
      point p_cr = curr->get_point ();
      if (((p_cr.y < p.y && p_pr.y >= p.y) || (p_pr.y < p.y && p_cr.y >= p.y))
          && (p_cr.x + (p.y - p_cr.y) / (p_pr.y - p_cr.y) * (p_pr.x - p_cr.x) < p.x))
        result = !result;
      prev = curr;
    }
  return result;
}


bool convex::is_outside (point p)
{
  return !(is_inside (p) || is_in_bnd (p));
}

bool convex::is_in_bnd (point p)
{
  list_node *prev = boundary.get_tail ();
  for (list_node *curr = boundary.get_head (); curr; curr = curr->get_next ())
    {
      if (crossProduct (prev->get_point (), p, curr->get_point ()) == 0)
        return true;
      prev = curr;
    }
  return false;
}

list &convex::get_points ()
{
  return points;
}

list &convex::get_boundary ()
{
  return boundary;
}
int convex::get_num_of_points ()
{
  return points.get_size ();
}

void convex::add_point (point p)
{
  if (points.get_size () < 3)
    {
      points.add_node (p);
    }
  else
    {
      if (is_inside (p))
        points.add_node (p);
      else
        {
          points.add_node (p);
          rebuild_convex ();
        }
    }

}

void convex::build_convex ()
{
  int n = points.get_size ();

  int l = 0;
  for (int i = 1; i < n; i++)
    if (points[i].get_point ().x < points[l].get_point ().x)
      l = i;

  int p = l, q;
  do
    {
      q = (p + 1) % n;
      for (int i = 0; i < n; i++)
        if (crossProduct (points[p].get_point (), points[i].get_point (), points[q].get_point ()) > 0)
          q = i;
      boundary.add_node (points[q].get_point ());
      p = q;
    }
  while (p != l);
}

void convex::create_line (point p1, point p2, double &a, double &b, double &c)
{
  a = (p1.y - p2.y);
  b = (p2.x - p1.x);
  c = (p1.x * p2.y - p2.x * p1.y);
}

double convex::count_area ()
{
  double s = 0;
  point middle;
  for (list_node *curr = boundary.get_head (); curr; curr = curr->get_next ())
    {
      middle += curr->get_point ();
    }
  middle /= boundary.get_size ();
  list_node *prev = boundary.get_head ();
  for (list_node *curr = prev->get_next (); curr; curr = curr->get_next ())
    {
      s += area (prev->get_point (), curr->get_point (), middle);
      prev = curr;
    }
  s += area (prev->get_point (), boundary.get_head ()->get_point (), middle);

  return s;
}

double convex::count_perimeter ()
{
  double p = 0;
  list_node *prev = boundary.get_head ();
  for (list_node *curr = prev->get_next (); curr; curr = curr->get_next ())
    {
      p += length (prev->get_point () - curr->get_point ());
      prev = curr;
    }
  p += length (prev->get_point () - boundary.get_head ()->get_point ());
  return p;
}

void convex::get_bounds (point &min, point &max)
{
  min = points.get_head ()->get_point ();
  max = points.get_head ()->get_point ();

  for (list_node *curr = points.get_head ()->get_next (); curr; curr = curr->get_next ())
    {
      point p = curr->get_point ();
      if (p.x < min.x)
        {
          min.x = p.x;
        }
      if (p.y < min.y)
        {
          min.y = p.y;
        }
      if (p.x > max.x)
        {
          max.x = p.x;
        }
      if (p.y > max.y)
        {
          max.y = p.y;
        }
    }

}

/////////////////////////////
int crossProduct (point a, point b, point c)
{    //finds the place of c from ab vector
  double y1 = a.y - b.y;
  double y2 = a.y - c.y;
  double x1 = a.x - b.x;
  double x2 = a.x - c.x;

  double res =  y2 * x1 - y1 * x2;
  if (res > 0)
    return 1;
  else if (res < 0)
    return -1;

  return 0;
}

double area (point a, point b, point c)
{
  double len1 = length (a - b);
  double len2 = length (a - c);
  double len3 = length (b - c);
  double p = (len1 + len2 + len3) / 2;
  double s = sqrt ((p - len1) * (p - len2) * (p - len3) * p);
  return s;
}
