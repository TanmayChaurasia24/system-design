#include <iostream>
#include <memory>

// 1. The Strategy Interface: Defines the "Contract"
class IPaymentStrategy {
public:
    virtual ~IPaymentStrategy() {}
    virtual void collectPayment(double amount) = 0;
};

// 2. Concrete Strategy A: Credit Card
class CreditCardStrategy : public IPaymentStrategy {
public:
    void collectPayment(double amount) override {
        std::cout << "Paid $" << amount << " using Credit Card (2% fee).\n";
    }
};

// 3. Concrete Strategy B: Bitcoin
class BitcoinStrategy : public IPaymentStrategy {
public:
    void collectPayment(double amount) override {
        std::cout << "Paid $" << amount << " using Bitcoin (Network fee applies).\n";
    }
};

// 4. The Context: The object that uses the strategy
class ShoppingCart {
private:
    std::unique_ptr<IPaymentStrategy> strategy; // Composition
public:
    // We can change the strategy at any time (Runtime)
    void setPaymentMethod(std::unique_ptr<IPaymentStrategy> s) {
        strategy = std::move(s);
    }

    void checkout(double total) {
        if (strategy) {
            strategy->collectPayment(total);
        } else {
            std::cout << "Please select a payment method!\n";
        }
    }
};

int main() {
    ShoppingCart cart;

    // User chooses Credit Card
    cart.setPaymentMethod(std::make_unique<CreditCardStrategy>());
    cart.checkout(100.0);

    // User changes mind and wants to use Bitcoin
    cart.setPaymentMethod(std::make_unique<BitcoinStrategy>());
    cart.checkout(100.0);

    return 0;
}