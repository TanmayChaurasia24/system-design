#include<iostream>
#include<memory>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;

class Iobserver {
public:
    virtual ~Iobserver() {}
    virtual void update(float prices) = 0;
};

class Stock {
private:
    vector<Iobserver*> observers; // list of subs
    float price;
    string symbol;
public:
    Stock(string symbol, float price) {
        this->symbol = symbol;
        this->price = price;
    }

    void subscribe(Iobserver* observer) {
        observers.push_back(observer);
    }
    void unsubscribe(Iobserver* observer) {
        observers.erase(remove(observers.begin(), observers.end(), observer), observers.end());
    }
    void setPrice(float newPrice) {
        price = newPrice;
        notify();
    }
    float getPrice() {
        return price;
    }
    void notify() {
        for(auto observer : observers) {
            observer->update(price);
        }
    }
};

class MobileApp : public Iobserver {
public:
    void update(float prices) override {
        cout << "Mobile App Notification: Stock price updated to " << prices << endl;
    }
};

class Email : public Iobserver {
public:
    void update(float prices) override {
        cout << "Email Notification: Stock price updated to " << prices << endl;
    }
};

int main() {
    Stock apple("APPL", 150.0f);

    MobileApp iphone;
    Email workEmail;

    apple.subscribe(&iphone);
    apple.subscribe(&workEmail);
    cout << "market price of APPL is " << apple.getPrice() << endl;
    apple.setPrice(160.0f);
    apple.unsubscribe(&workEmail);
    cout << "market price of APPL is " << apple.getPrice() << endl;
    apple.setPrice(170.0f);

}