#include <iostream>
#include <fstream>
#include <chrono>
#include <thread>

class Tamagotchi {
public:
    std::string name;
    int happiness;
    int hunger;

    Tamagotchi(const std::string& name) : name(name), happiness(50), hunger(50) {}

    void feed() {
        hunger -= 10;
        if (hunger < 0)
            hunger = 0;
        happiness += 5;
        if (happiness > 100)
            happiness = 100;
    }

    void play() {
        happiness += 10;
        if (happiness > 100)
            happiness = 100;
        hunger += 5;
        if (hunger > 100)
            hunger = 100;
    }

    void displayPortrait() {
        std::ifstream file("portrait.txt");
        if (file) {
            std::cout << file.rdbuf();
            file.close();
        }
        else {
            std::cout << "Unable to load portrait." << std::endl;
        }
    }

    void displayStatus() {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Happiness: " << happiness << std::endl;
        std::cout << "Hunger: " << hunger << std::endl;
    }

    void update() {
        hunger += 5;
        happiness -= 5;
        if (hunger > 100)
            hunger = 100;
        if (happiness < 0)
            happiness = 0;
    }
};

int main() {
    std::string name;
    std::cout << "Enter your Tamagotchi's name: ";
    std::cin >> name;

    Tamagotchi tamagotchi(name);

    while (true) {
        tamagotchi.displayPortrait();
        tamagotchi.displayStatus();

        std::this_thread::sleep_for(std::chrono::seconds(3));
        tamagotchi.update();

        if (tamagotchi.hunger >= 100 || tamagotchi.happiness <= 0) {
            std::cout << "Game over! " << tamagotchi.name << " has passed away." << std::endl;
            break;
        }
    }

    return 0;
}