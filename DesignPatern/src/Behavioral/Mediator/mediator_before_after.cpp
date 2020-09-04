#include <iostream>
#include <vector>

using namespace std;

namespace before
{
class Node
{
  public:
    Node(int v)
    {
        m_val = v;
        m_next = 0;
    }
    void add_node(Node *n)
    {
        if (m_next)
          m_next->add_node(n);
        else
          m_next = n;
    }
    void traverse()
    {
        cout << m_val << "  ";
        if (m_next)
          m_next->traverse();
        else
          cout << '\n';
    }
    void remove_node(int v)
    {
        if (m_next)
          if (m_next->m_val == v)
            m_next = m_next->m_next;
          else
            m_next->remove_node(v);
    }
  private:
    int m_val;
    Node *m_next;
};

}

namespace after
{
class Node
{
  public:
    Node(int v)
    {
        m_val = v;
    }
    int get_val()
    {
        return m_val;
    }
  private:
    int m_val;
};

class List
{
  public:
    void add_node(Node *n)
    {
        m_arr.push_back(n);
    }
    void traverse()
    {
        for (int i = 0; i < m_arr.size(); ++i)
          cout << m_arr[i]->get_val() << "  ";
        cout << '\n';
    }
    void remove_node(int v)
    {
        for (vector<Node*>::iterator it = m_arr.begin(); it != m_arr.end(); ++it)
        if ((*it)->get_val() == v)
        {
            m_arr.erase(it);
            break;
        }
    }
  private:
    vector<Node*> m_arr;
};

}


int main()
{
    {
        before::Node lst(11);
        before::Node two(22), thr(33), fou(44);
        lst.add_node(&two);
        lst.add_node(&thr);
        lst.add_node(&fou);
        lst.traverse();
        lst.remove_node(44);
        lst.traverse();
        lst.remove_node(22);
        lst.traverse();
        lst.remove_node(11);
        lst.traverse();
    }
    {
        after::List lst;
        after::Node one(11), two(22);
        after::Node thr(33), fou(44);
        lst.add_node(&one);
        lst.add_node(&two);
        lst.add_node(&thr);
        lst.add_node(&fou);
        lst.traverse();
        lst.remove_node(44);
        lst.traverse();
        lst.remove_node(22);
        lst.traverse();
        lst.remove_node(11);
        lst.traverse();
    }
}
