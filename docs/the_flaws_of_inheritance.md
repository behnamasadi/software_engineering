Inheritance is a core concept in object-oriented programming, but it has several flaws that can make it problematic if not used carefully. Here’s an explanation of these flaws, along with minimalistic C++ examples.

---

### 1. **Tight Coupling**
When you use inheritance, the child class becomes tightly coupled to the parent class. Any change in the parent class can unintentionally affect all child classes.

**Example:**
```cpp
#include <iostream>

class Animal {
public:
    virtual void makeSound() {
        std::cout << "Some generic sound\n";
    }
};

class Dog : public Animal {
public:
    void makeSound() override {
        std::cout << "Bark\n";
    }
};

int main() {
    Dog dog;
    dog.makeSound(); // Outputs "Bark"
}
```

**Problem:**
If you modify `Animal` to include another behavior or change `makeSound` in a way that breaks assumptions in `Dog`, the `Dog` class is indirectly impacted. This creates a fragile codebase.

---

### 2. **Violates Encapsulation**
Inheritance exposes the internal details of the parent class to the child class, which can lead to misuse or incorrect assumptions.

**Example:**
```cpp
class Base {
protected:
    int protectedData;

public:
    void setProtectedData(int value) { protectedData = value; }
};

class Derived : public Base {
public:
    void printData() {
        std::cout << "Accessing protected data: " << protectedData << "\n";
    }
};

int main() {
    Derived d;
    d.setProtectedData(10);
    d.printData(); // Works, but violates the encapsulation of `Base`
}
```

**Problem:**
The derived class can manipulate the protected member, which should ideally be private. This breaks encapsulation principles.

---

### 3. **Inheritance Hierarchies Can Be Inflexible**
Deep inheritance hierarchies can make it difficult to understand and modify code. Overuse of inheritance leads to a rigid structure that's hard to refactor.

**Example:**
```cpp
class Animal {
public:
    virtual void eat() {
        std::cout << "Eating food\n";
    }
};

class Mammal : public Animal {
public:
    void eat() override {
        std::cout << "Eating as a mammal\n";
    }
};

class Bat : public Mammal {
public:
    void eat() override {
        std::cout << "Eating insects\n";
    }
};

int main() {
    Bat bat;
    bat.eat(); // Outputs "Eating insects"
}
```

**Problem:**
If a `Bat` class suddenly needs to eat fruits, changing the hierarchy requires modifying multiple classes or restructuring, which can be complex.

---

### 4. **Leads to Fragile Base Class Problem**
If you add new methods or members to the base class, it may unintentionally conflict with names or behaviors in the derived class.

**Example:**
```cpp
class Base {
public:
    void display() { std::cout << "Base display\n"; }
};

class Derived : public Base {
public:
    void display() { std::cout << "Derived display\n"; } // Hides Base's display
};

int main() {
    Derived obj;
    obj.display(); // Outputs "Derived display"
}
```

**Problem:**
If you call `Base::display` from a base pointer to `Derived`, it might cause unexpected behavior, especially if `Derived` overrides without using `virtual`.

---

### 5. **Substitution Principle Can Be Broken**
Inheritance assumes an "is-a" relationship. If the derived class does not truly follow this relationship, it violates the **Liskov Substitution Principle (LSP)**.

**Example:**
```cpp
class Rectangle {
public:
    virtual void setWidth(int w) { width = w; }
    virtual void setHeight(int h) { height = h; }
    int getArea() const { return width * height; }

protected:
    int width, height;
};

class Square : public Rectangle {
public:
    void setWidth(int w) override {
        width = height = w; // Violates LSP
    }
    void setHeight(int h) override {
        width = height = h; // Violates LSP
    }
};

int main() {
    Rectangle* rect = new Square();
    rect->setWidth(4);
    rect->setHeight(5);
    std::cout << rect->getArea() << "\n"; // Outputs 25, which is incorrect for a rectangle
    delete rect;
}
```

**Problem:**
A `Square` is not a true `Rectangle`, as it cannot independently set width and height. This breaks the "is-a" relationship.

---

### 6. **Code Reuse Often Misapplied**
Inheritance is often misused for code reuse when composition would be a better choice.

**Example of Better Composition:**
```cpp
class Engine {
public:
    void start() { std::cout << "Engine started\n"; }
};

class Car {
private:
    Engine engine;

public:
    void start() {
        engine.start();
        std::cout << "Car is running\n";
    }
};

int main() {
    Car car;
    car.start();
}
```

**Why Composition is Better:**
Here, `Car` uses `Engine` through composition, which is more flexible and avoids tightly coupling the two classes.

---

### Takeaways:
- Use inheritance sparingly and only when there is a clear **is-a** relationship.
- Prefer composition over inheritance for code reuse and flexibility.
- Be cautious of tight coupling and breaking encapsulation.
- Avoid deep inheritance hierarchies that make the code harder to maintain and refactor.

Refs: [1](https://www.youtube.com/watch?v=hxGOiiR9ZKg)
