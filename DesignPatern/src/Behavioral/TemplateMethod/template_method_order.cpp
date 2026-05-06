// Template Method — order workflow.
// placeOrder() is the template method: the order in which select/pay/wrap/
// deliver run is fixed. Concrete order types only customize the steps.

#include <iostream>
#include <memory>

class OrderWorkflow {
public:
    virtual ~OrderWorkflow() = default;

    // Template method.
    void placeOrder(bool isGift) {
        selectItem();
        makePayment();
        if (isGift) wrapGift();
        deliverOrder();
    }

protected:
    virtual void selectItem() = 0;
    virtual void makePayment() = 0;
    virtual void deliverOrder() = 0;

    // Shared optional step.
    void wrapGift() {
        std::cout << "  [common] gift wrapped\n";
    }
};

class OnlineOrder : public OrderWorkflow {
protected:
    void selectItem() override {
        std::cout << "  [online] item added to cart\n";
    }
    void makePayment() override {
        std::cout << "  [online] paid via online gateway\n";
    }
    void deliverOrder() override {
        std::cout << "  [online] shipped by courier\n";
    }
};

class InStoreOrder : public OrderWorkflow {
protected:
    void selectItem() override {
        std::cout << "  [store]  picked from shelf\n";
    }
    void makePayment() override {
        std::cout << "  [store]  paid at the counter\n";
    }
    void deliverOrder() override {
        std::cout << "  [store]  handed over at the counter\n";
    }
};

int main() {
    std::cout << "=== Online order (gift) ===\n";
    std::unique_ptr<OrderWorkflow> online = std::make_unique<OnlineOrder>();
    online->placeOrder(true);

    std::cout << "\n=== In-store order ===\n";
    std::unique_ptr<OrderWorkflow> store = std::make_unique<InStoreOrder>();
    store->placeOrder(false);
}
