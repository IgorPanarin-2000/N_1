#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <math.h>

struct point
{
  double x;
  double y;
  point ()
  {
    x = 0;
    y = 0;
  }
  point (double x_, double y_)
  {
    x = x_;
    y = y_;
  }
  point (point const &p)
  {
    x = p.x;
    y = p.y;
  }
  struct point& operator+= (const point& rhs)
  {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
  struct point& operator= (const point& rhs)
  {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }
  struct point& operator= (point &&rhs)
  {
    x = rhs.x;
    y = rhs.y;
    return *this;
  }
  struct point& operator/= (double k)
  {
    x /= k;
    y /= k;
    return *this;
  }
  struct point operator- (const point& rhs)
  {
    point p;
    p.x = x - rhs.x;
    p.y = y - rhs.y;
    return p;
  }

};

bool operator == (const point &p1, const point &p2);
double length (const point &p1);

////////////////////////////////////////////////
////////////////////////////////////////////////

struct list_node
{
  point p;
  list_node *next;
  list_node ()
  {
    next = nullptr;
  }
  list_node (point p_, list_node *next_)
  {
    p = p_;
    next = next_;
  }
  list_node (list_node &&node)
  {
    p = node.p;
    next = node.next;
  }
  struct list_node& operator= (list_node &&rhs)
  {
    p = rhs.p;
    next = rhs.next;
    return *this;
  }
  struct list_node& operator= (list_node &rhs)
  {
    p = rhs.p;
    next = rhs.next;
    return *this;
  }
  list_node *get_next ()
  {
    return next;
  }
  void set_next (list_node &&node)
  {
    next = &node;
  }
  void set_next (list_node *node)
  {
    next = node;
  }
  point get_point ()
  {
    return p;
  }
};

class list
{
private:
  list_node *head;
  list_node *tail;
  int size;
public:
  list ()
  {
    head = nullptr;
    tail = nullptr;
  }
  list (list &l) : list ()
  {
    for (list_node* curr = l.get_head (); curr; curr = curr->get_next ())
      add_node (curr->p);
  }
  ~list ()
  {
    reset ();
  }
  list& operator= (list &l)
  {
    for (list_node* curr = l.get_head (); curr; curr = curr->get_next ())
      add_node (curr->p);
    return *this;
  }
  list& operator= (list &&l)
  {
    for (list_node* curr = l.get_head (); curr; curr = curr->get_next ())
      add_node (curr->p);
    return *this;
  }
  void add_node (point p)
  {
    if (tail)
      {
        list_node *h = new list_node (p, nullptr);
        tail->next = h;
        tail = tail->next;
      }
    else
      {
        list_node *h = new list_node (p, nullptr);
        head = h;
        tail = head;
      }
    size++;
  }
  void add_node (list_node *p)
  {
    if (tail)
      {
        list_node *h = new list_node (p->get_point (), nullptr);
        tail->next = h;
        tail = h;
      }
    else
      {
        list_node *h = new list_node (p->get_point (), nullptr);
        head = h;
        tail = h;
      }
    size++;
  }
  void reset ()
  {
    while (head)
      {
        list_node *t = head->next;
        delete head;
        head = t;
      }
    head = nullptr;
    tail = nullptr;
  }
  list_node *get_head ()
  {
    return head;
  }
  list_node *get_tail ()
  {
    return tail;
  }
  void reduce_size ()
  {
    size--;
  }
  void set_head (list_node *x)
  {
    head = x;
  }
  void print ()
  {
    list_node *curr = head;
    int i = 0;
    while (curr && i < 10)
      {
        printf("(%.3lf %.3lf)\n", curr->get_point ().x, curr->get_point ().y);
        curr = curr->next;
        i++;
      }
  }
  int get_size ()
  {
    return size;
  }

  list_node& operator[] (int index)
  {
    list_node *curr = head;
    for (int i = 0; i < index; i++)
      {
        curr = curr->get_next ();
      }
    return *curr;
  }
};


#endif // LIST_H
