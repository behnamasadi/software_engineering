#include <iostream>
/*

There are four common situations in which the Proxy pattern is applicable.

A virtual proxy is a placeholder for "expensive to create" objects. The real object is only created when a client first requests/accesses the object.
A remote proxy provides a local representative for an object that resides in a different address space. This is what the "stub" code in RPC and CORBA provides.
A protective proxy controls access to a sensitive master object. The "surrogate" object checks that the caller has the access permissions required prior to forwarding the request.
A smart proxy interposes additional actions when an object is accessed. Typical uses include:
Counting the number of references to the real object so that it can be freed automatically when there are no more references (aka smart pointer),
Loading a persistent object into memory when it's first referenced,
Checking that the real object is locked before it is accessed to ensure that no other object can change it.
*/
namespace before
{
class Image
{
    int m_id;
    static int s_next;
  public:
    Image()
    {
        m_id = s_next++;
        std::cout << "   $$ ctor: " << m_id << '\n';
    }
    ~Image()
    {
        std::cout << "   dtor: " << m_id << '\n';
    }
    void draw()
    {
        std::cout << "   drawing image " << m_id << '\n';
    }
};

}

namespace after
{
class RealImage
{
    int m_id;
  public:
    RealImage(int i)
    {
        m_id = i;
        std::cout << "   $$ ctor: " << m_id << '\n';
    }
    ~RealImage()
    {
        std::cout << "   dtor: " << m_id << '\n';
    }
    void draw()
    {
        std::cout << "   drawing image " << m_id << '\n';
    }
};

class Image
{
    RealImage *m_the_real_thing;
    int m_id;
    static int s_next;
  public:
    Image()
    {
        m_id = s_next++;
        // 3. Initialized to null
        m_the_real_thing = 0;
    }
    ~Image()
    {
        delete m_the_real_thing;
    }
    void draw()
    {
        // 4. When a request comes in, the real object is
        //    created "on first use"
        if (!m_the_real_thing)
          m_the_real_thing = new RealImage(m_id);
        // 5. The request is always delegated
        m_the_real_thing->draw();
    }
};


}


int before::Image::s_next = 1;
int after::Image::s_next = 1;

int main()
{

/////////////////////////////////Before////////////////////////////////
    {
        before::Image images[5];

        for (int i; true;)
        {
            std::cout << "Exit[0], Image[1-5]: ";
            std::cin >> i;
            if (i == 0)
              break;
            images[i - 1].draw();
        }
    }


/////////////////////////////////After////////////////////////////////

    {
        after::Image images[5];

        for (int i; true;)
        {
          std::cout << "Exit[0], Image[1-5]: ";
          std::cin >> i;
          if (i == 0)
            break;
          images[i - 1].draw();
        }
    }

}

