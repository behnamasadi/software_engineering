#include <iostream>
#include <memory>

// Base class that outlines the "template method" structure
class OrderWorkflow {
public:
    virtual ~OrderWorkflow() = default;

    // Template method
    void placeOrder(bool isGift) {
        selectItem();
        makePayment();
        if (isGift) {
            wrapGift();
        }
        deliverOrder();
    }

protected:
    virtual void selectItem() = 0;
    virtual void makePayment() = 0;
    virtual void deliverOrder() = 0;

    // Common optional step
    void wrapGift() {
        std::cout << "[Common Step] Gift has been wrapped successfully.\n";
    }
};

// Concrete class for online orders
class OnlineOrder : public OrderWorkflow {
protected:
    void selectItem() override {
        std::cout << "[OnlineOrder] Item has been added to the digital cart.\n";
        std::cout << "[OnlineOrder] Gift preference noted.\n";
        std::cout << "[OnlineOrder] Delivery address collected.\n";
    }

    void makePayment() override {
        std::cout << "[OnlineOrder] Payment through online gateway.\n";
    }

    void deliverOrder() override {
        std::cout << "[OnlineOrder] Product shipped via courier.\n";
    }
};

// Concrete class for in-store orders
class InStoreOrder : public OrderWorkflow {
protected:
    void selectItem() override {
        std::cout << "[InStoreOrder] Customer picks item from store shelf.\n";
    }

    void makePayment() override {
        std::cout << "[InStoreOrder] Payment made at the billing counter.\n";
    }

    void deliverOrder() override {
        std::cout << "[InStoreOrder] Item handed over at store delivery counter.\n";
    }
};

int main() {
    // Create an OnlineOrder and place an order with a gift request
    std::cout << "=== Online Order ===\n";
    std::unique_ptr<OrderWorkflow> onlineOrder = std::make_unique<OnlineOrder>();
    onlineOrder->placeOrder(true);

    std::cout << "\n=== In-Store Order ===\n";
    // Create an InStoreOrder and place an order without gift wrapping
    std::unique_ptr<OrderWorkflow> inStoreOrder = std::make_unique<InStoreOrder>();
    inStoreOrder->placeOrder(false);

    return 0;
}
