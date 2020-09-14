#include <iostream>

class Animal {
 public:
  virtual ~Animal() = default;

  virtual void MakeSound() const = 0;
};

class Dog : public Animal {
 public:
  virtual void MakeSound() const override { std::cout << "woof!" << std::endl; }
};

class NullAnimal : public Animal {
 public:
  virtual void MakeSound() const override {}
};

void DoSomething(const Animal& animal) {
  // |animal| may never be null here.
    animal.MakeSound();
}

// Function which may accept an |Animal| instance or null.
void DoSomething(const Animal* animal) {
  // |animal| may be null.
    animal->MakeSound();
}

int main()
{
    Animal* null_animal_ptr=new NullAnimal();
    DoSomething(null_animal_ptr);

    NullAnimal null_animal;
    DoSomething(null_animal);
}
