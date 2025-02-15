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
#include <iostream>
#include <memory>

namespace before
{
class Image
{
    int m_id;
    static int s_next;

public:
    Image() : m_id(s_next++)
    {
        std::cout << "📷 Constructing Image: " << m_id << '\n';
    }

    ~Image()
    {
        std::cout << "❌ Destroying Image: " << m_id << '\n';
    }

    void render()
    {
        std::cout << "🖼️ Rendering Image " << m_id << '\n';
    }
};

int Image::s_next = 1;
}

namespace after
{
class HighResImage
{
    int m_id;

public:
    explicit HighResImage(int id) : m_id(id)
    {
        std::cout << "📷 Loading High-Res Image: " << m_id << '\n';
    }

    ~HighResImage()
    {
        std::cout << "❌ Unloading High-Res Image: " << m_id << '\n';
    }

    void render()
    {
        std::cout << "🖼️ Displaying High-Res Image " << m_id << '\n';
    }
};

class LazyImage
{
    std::unique_ptr<HighResImage> real_image;  // Using smart pointer for safe memory management
    int m_id;
    static int s_next;

public:
    LazyImage() : m_id(s_next++) {}

    void render()
    {
        // Lazy loading: create the real image only when needed
        if (!real_image)
        {
            std::cout << "⚡ Lazy Loading Image " << m_id << '\n';
            real_image = std::make_unique<HighResImage>(m_id);
        }
        real_image->render();
    }
};

int LazyImage::s_next = 1;
}

int main()
{
    std::cout << "\n====== Before Proxy ======\n";
    {
        before::Image images[5];

        while (true)
        {
            int i;
            std::cout << "Exit[0], Image[1-5]: ";
            std::cin >> i;

            if (i == 0)
                break;
            if (i < 1 || i > 5)
            {
                std::cout << "❌ Invalid choice! Please enter a number between 1-5.\n";
                continue;
            }

            images[i - 1].render();
        }
    }

    std::cout << "\n====== After Proxy (Lazy Loading) ======\n";
    {
        after::LazyImage images[5];

        while (true)
        {
            int i;
            std::cout << "Exit[0], Image[1-5]: ";
            std::cin >> i;

            if (i == 0)
                break;
            if (i < 1 || i > 5)
            {
                std::cout << "❌ Invalid choice! Please enter a number between 1-5.\n";
                continue;
            }

            images[i - 1].render();
        }
    }

    return 0;
}
