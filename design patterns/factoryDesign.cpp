#include<iostream>
#include<memory>
#include<string>
using namespace std;

// interface
class INotification {
    public:
        virtual void notify() = 0;
        virtual ~INotification() {}
};

// class implementation
class EmailNotification: public INotification {
    public:
        void notify() override {
            cout << "email notification..." << endl;
        }
};

class SMSNotification: public INotification {
    public:
        void notify() override {
            cout << "sms notification..." << endl;
        }
};

class NotificationFactory {
    public:
        //Because you used unique_ptr, you don't need to write delete. When the variable mynotice goes out of scope (at the end of main), the unique_ptr automatically destroys the object and frees the memory. This concept is called RAII (Resource Acquisition Is Initialization).
        static unique_ptr<INotification> createNotification(const string &type) {
            if(type == "email") {
                // make_unique make code more concise and safer, used because unique_ptr is a smart pointer
                return make_unique<EmailNotification>();
            } else if(type == "sms") {
                return make_unique<SMSNotification>();
            } else {
                return nullptr;
            }
        }
};

int main() {
    auto mynotice = NotificationFactory::createNotification("email");
    if(mynotice) {
        mynotice->notify();
    }
    return 0;
}