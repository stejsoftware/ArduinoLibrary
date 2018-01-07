#ifndef __List_h_
#define __List_h_

#include <Arduino.h>

template<class T>
class Node
{
public:
  Node(T item) :
      next(NULL),
      _item(item)
  {
  }

  ~Node()
  {
  }

  T item() const
  {
    return _item;
  }

  Node * next;

private:
  Node(const Node & rhs);
  Node & operator=(const Node & rhs);

  T _item;
};

template<class T>
class List
{
public:
  List()
  {
  }

  ~List()
  {
    T item;

    while (pop(item))
    {
    }
  }

  bool push(T item)
  {
    Node<T> * node = new Node<T>(item);

    if (node != NULL)
    {
      // the list is empty
      if (m_begin == NULL)
      {
        m_begin = node;
      }
      // the list has items
      else
      {
        // find the end of the list
        Node<T> * end = m_begin;

        while (end->next != NULL)
        {
          end = end->next;
        }

        end->next = node;
      }

      return true;
    }

    return false;
  }

  bool pop(T & item)
  {
    Node<T> * node = m_begin;

    if (node != NULL)
    {
      item = node->item();
      m_begin = node->next;

      delete node;

      return true;
    }

    return false;
  }

private:
  List(const List&rhs);
  List & operator=(const List&rhs);

  Node<T> * m_begin;

};

#endif // __List_h_
