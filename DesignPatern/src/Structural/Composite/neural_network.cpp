// Composite — a Layer is a group of Neurons, but a Layer can also be wired
// to other Layers just like a single Neuron can. Both types implement the
// same `connect_to(SomeNeurons&)` interface, so the client connects layers
// and neurons interchangeably.

#include <iostream>
#include <utility>
#include <vector>

class Neuron;

// Common interface — anything that can be connected to a set of neurons.
class SomeNeurons {
public:
    virtual ~SomeNeurons() = default;
    virtual std::vector<Neuron*> neurons() = 0;

    void connect_to(SomeNeurons& other) {
        for (Neuron* a : neurons())
            for (Neuron* b : other.neurons())
                connect(a, b);
    }

private:
    static void connect(Neuron* a, Neuron* b);
};

class Neuron : public SomeNeurons {
public:
    explicit Neuron(int id) : id_(id) {}

    std::vector<Neuron*> neurons() override { return {this}; }

    int id() const { return id_; }

private:
    int id_;
    std::vector<Neuron*> in_;
    std::vector<Neuron*> out_;
    friend class SomeNeurons;
};

void SomeNeurons::connect(Neuron* a, Neuron* b) {
    a->out_.push_back(b);
    b->in_.push_back(a);
    std::cout << "  neuron " << a->id() << " -> neuron " << b->id() << '\n';
}

class Layer : public SomeNeurons {
public:
    Layer(int first_id, int count) {
        for (int i = 0; i < count; ++i) neurons_.emplace_back(first_id + i);
    }

    std::vector<Neuron*> neurons() override {
        std::vector<Neuron*> out;
        out.reserve(neurons_.size());
        for (auto& n : neurons_) out.push_back(&n);
        return out;
    }

private:
    std::vector<Neuron> neurons_;
};

int main() {
    Neuron a(1), b(2);
    Layer  l1(10, 3);
    Layer  l2(20, 2);

    std::cout << "neuron-to-neuron:\n";
    a.connect_to(b);

    std::cout << "neuron-to-layer:\n";
    a.connect_to(l1);

    std::cout << "layer-to-layer:\n";
    l1.connect_to(l2);
}
