#include<iostream>
#include<string>
#include<memory>
using namespace std;

// abstract products
class IButton {
    public:
        virtual void paint() = 0;
        virtual ~IButton() {}
};
class ICheckbox {
    public:
        virtual void paint() = 0;
        virtual ~ICheckbox() {}
};

// concrete products
class WindowsButton: public IButton {
    public:
        void paint() override {
            cout << "windows button painted." << endl;
        }
};
class WindowsCheckbox: public ICheckbox {
    public:
        void paint() override {
            cout << "windows checkbox painted." << endl;
        }
};

class MacButton: public IButton {
    public:
        void paint() override {
            cout << "mac button painted." << endl;
        }
};
class MacCheckbox: public ICheckbox {
    public:
        void paint() override {
            cout << "mac checkbox painted." << endl;
        }
};

// abstract factory
class IGUIFactory {
    public:
        virtual unique_ptr<IButton> createButton() = 0;
        virtual unique_ptr<ICheckbox> createCheckbox() = 0;
        virtual ~IGUIFactory() {}
};

// concrete factory
class WindowsFactory: public IGUIFactory {
    public:
        unique_ptr<IButton> createButton() override {
            return make_unique<WindowsButton>();
        }
        unique_ptr<ICheckbox> createCheckbox() override {
            return make_unique<WindowsCheckbox>();
        }
};

class MacFactory: public IGUIFactory {
    public:
        unique_ptr<IButton> createButton() override {
            return make_unique<MacButton>();
        }
        unique_ptr<ICheckbox> createCheckbox() override {
            return make_unique<MacCheckbox>();
        }
};

int main() {
    unique_ptr<IGUIFactory> factory;

    string osType = "mac"; 

    if(osType == "windows") {
        factory = make_unique<WindowsFactory>();
    } else if(osType == "mac") {
        factory = make_unique<MacFactory>();
    } else {
        cout << "unknown os type." << endl;
        return 1;
    }

    auto button = factory->createButton();
    auto checkbox = factory->createCheckbox();

    button->paint();
    checkbox->paint();

    return 0;
}

