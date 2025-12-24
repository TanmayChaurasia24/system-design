#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>

// 1. The Prototype Interface
class Monster {
public:
    virtual ~Monster() {}
    virtual std::unique_ptr<Monster> clone() const = 0; // The magic "copy" method
    virtual void sayHello() = 0;
};

// 2. Concrete Prototype A
class Ghost : public Monster {
private:
    int transparency;
public:
    Ghost(int t) : transparency(t) {}
    
    // Copy Constructor (used by clone)
    Ghost(const Ghost& other) : transparency(other.transparency) {}

    std::unique_ptr<Monster> clone() const override {
        return std::make_unique<Ghost>(*this); // Returns a copy of itself
    }

    void sayHello() override {
        std::cout << "I am a Ghost with " << transparency << "% transparency!\n";
    }
};

// 3. Concrete Prototype B
class Zombie : public Monster {
private:
    std::string healthState;
public:
    Zombie(std::string state) : healthState(state) {}
    
    std::unique_ptr<Monster> clone() const override {
        return std::make_unique<Zombie>(*this);
    }

    void sayHello() override {
        std::cout << "I am a " << healthState << " Zombie!\n";
    }
};

int main() {
    // Create "Master" templates
    Ghost prototypeGhost(50);
    Zombie prototypeZombie("Rotting");

    // Imagine we are in the middle of a game loop
    // We don't want to re-calculate stats; we just want a copy
    auto spawnedGhost = prototypeGhost.clone();
    auto spawnedZombie = prototypeZombie.clone();

    spawnedGhost->sayHello();
    spawnedZombie->sayHello();

    return 0;
}