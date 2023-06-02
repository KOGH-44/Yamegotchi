#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <chrono>
#include <ctime>
#include <thread>
using namespace std;

class Animal {
private:
    int level = 0;    // 레벨
    int exp = 0;      // 경험치
    int hp = 100;     // 체력
    int status = 1;       // 1: 정상, 2: 비정상 (HP < 30 이하) (경고 함수 작동) (추후 확장 예정)
    char* name = nullptr; // 몬스터 이름
public:
    char* getName();
    void setName(const char* animalName);
    void startHPDecrease();
    void decreaseHP();
    void increaseEXP(int amount);
    void restoreHP(int amount);
    void checkStatus();
    void printInfo();
};

char* Animal::getName() {
    return name;
}

void Animal::setName(const char* animalName) {
    if (name != nullptr) {
        delete[] name;
    }
    name = new char[strlen(animalName) + 1];
    strcpy(name, animalName);
}

void Animal::startHPDecrease() {
    std::thread t(&Animal::decreaseHP, this);
    t.detach();
}

void Animal::decreaseHP() {
    //int totalSeconds = 30;
    int decreaseAmount = 1;

    while (hp >= 0 ) {
        std::this_thread::sleep_for(std::chrono::seconds(10));
        //totalSeconds--;
        hp -= decreaseAmount;
        checkStatus();
        if (hp <= 0) {
            std::cout << "게임 오버! " << name << "의 체력이 0이 되었습니다." << std::endl;

            exit(0); // 프로그램 종료
        }
    }
    
    
}


void Animal::increaseEXP(int amount) {
    exp += amount;
}

void Animal::restoreHP(int amount) {
    hp += amount;
    if (hp > 100) {
        hp = 100;
    }
    checkStatus();
}

void Animal::checkStatus() {
    if (hp < 30) {
        status = 2;
        
    }
    else {
        status = 1;
    }
}


void Animal::printInfo() {
    std::cout << "이름: " << name << std::endl;
    std::cout << "레벨: " << level << std::endl;
    std::cout << "경험치: " << exp << std::endl;
    std::cout << "체력: " << hp << std::endl;
    std::cout << "상태: " << (status == 1 ? "정상" : "비정상") << std::endl;
    if (status == 2) {
        std::cout << "경고: " << name << "의 체력이 30 이하입니다!" << std::endl;
    }
    
}


void text_screen() {
    std::cout << "START" << std::endl;
}

int test1()
{

    std::string filename = "size_test1.txt"; // 입력받을 파일 이름

    // 파일 열기
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "파일을 열 수 없습니다." << std::endl;
        return 1;
    }

    // 파일 내용 출력
    //text_screen();
    std::string line;
    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }
    //text_screen();
    // 파일 닫기
    file.close();
}

int test2()
{

    std::string filename = "size_test2.txt"; // 입력받을 파일 이름

    // 파일 열기
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "파일을 열 수 없습니다." << std::endl;
        return 1;
    }

    // 파일 내용 출력
    std::string line;
    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }

    // 파일 닫기
    file.close();
}

int test3()
{

    std::string filename = "size_test3.txt"; // 입력받을 파일 이름

    // 파일 열기
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "파일을 열 수 없습니다." << std::endl;
        return 1;
    }

    // 파일 내용 출력
    std::string line;
    while (std::getline(file, line))
    {
        std::cout << line << std::endl;
    }

    // 파일 닫기
    file.close();
}

int main()
{
    
    Animal myAnimal;

    char* char_name = NULL;
    std::cout << "캐릭터의 이름을 입력하세요: ";
    std::string name;
    std::getline(std::cin, name);
    myAnimal.setName(name.c_str());
    // 게임 시작
    myAnimal.startHPDecrease();
    myAnimal.printInfo();
    int x = 3;
    for (int i = 0; i < x; i--)
    {
        

        system("cls");
        test1();
        myAnimal.printInfo();
        Sleep(500);


        system("cls");
        test1();
        myAnimal.printInfo();
        Sleep(500);

        system("cls");
        test1();
        myAnimal.printInfo();
        Sleep(500);
        
        
    }
    return 0;
}