// building a desktop PC

#include<iostream>
#include<string>
#include<memory>

using namespace std;

// product
class DesktopPC {
    public:
        string CPU;
        string GPU;
        int ram = 0;
        int storage = 0;
        bool hasRGB = false;

        void DisplaySpecs() {
            cout << "Desktop PC Specs:" << endl;
            cout << "CPU: " << CPU << endl;
            cout << "GPU: " << GPU << endl;
            cout << "RAM: " << ram << " GB" << endl;
            cout << "Storage: " << storage << " GB" << endl;
            cout << "RGB Lighting: " << (hasRGB ? "Yes" : "No") << endl;
        }
};

// builder
class DesktopPCBuilder {
    private:
        unique_ptr<DesktopPC> pc;
    public:
        DesktopPCBuilder() {
            pc = make_unique<DesktopPC>();
        }

        DesktopPCBuilder& addCPU(string cpu) {
            pc->CPU = cpu;
            return *this;
        }

        DesktopPCBuilder& addGPU(string gpu) {
            pc->GPU = gpu;
            return *this;
        }

        DesktopPCBuilder& setRam(int ram) {
            pc->ram = ram;
            return *this;
        }

        DesktopPCBuilder& setStorage(int storage) {
            pc->storage = storage;
            return *this;
        }

        DesktopPCBuilder& setRGB(bool hasRGB) {
            pc->hasRGB = hasRGB;
            return *this;
        }

        unique_ptr<DesktopPC> build() {
            return move(pc);
        }
};

int main() {
    DesktopPCBuilder builder;

    unique_ptr<DesktopPC> myPC = builder.addCPU("Intel i9")
                                        .addGPU("NVIDIA RTX 4090")
                                        .setRam(32)
                                        .setStorage(2000)
                                        .setRGB(true)
                                        .build();

    myPC->DisplaySpecs();
    return 0;
}