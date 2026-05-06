// Null Object — provide a "do-nothing" subclass so callers don't need to
// check for nullptr. The point: turn `if (a) a->bark();` into `a.bark();`.

#include <iostream>
#include <memory>
#include <string>

class Animal {
public:
    virtual ~Animal() = default;
    virtual void bark() const = 0;
    virtual const char* name() const = 0;
};

class Dog : public Animal {
public:
    void bark() const override { std::cout << "Woof!\n"; }
    const char* name() const override { return "Dog"; }
};

class NullAnimal : public Animal {
public:
    void bark() const override { /* silent */ }
    const char* name() const override { return "<none>"; }
};

void greet(const Animal& a) {
    std::cout << a.name() << ": ";
    a.bark();
}

// Returns a NullAnimal instead of nullptr when the lookup fails — caller
// uses the result uniformly.
std::unique_ptr<Animal> findAnimal(const std::string& kind) {
    if (kind == "dog") return std::make_unique<Dog>();
    return std::make_unique<NullAnimal>();
}

int main() {
    greet(*findAnimal("dog"));
    greet(*findAnimal("unicorn"));  // no nullptr check needed
}
