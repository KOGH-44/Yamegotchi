#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>
#include <string>
#include <Windows.h>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <random>
using namespace std;
class Animal {
private:
	int level = 0;    // 레벨
	int exp;      // 경험치
	int hp = 100;     // 체력
	int status = 1;       // 1: 정상, 2: 비정상 (HP < 30 이하) (경고 함수 작동) (추후 확장 예정)
	char* name = nullptr; // 몬스터 이름
public:
	char* getName();
	void setName(const char* animalName);
	void levelUp();
	void startHPDecrease();
	void decreaseHP();
	void increaseEXP(int amount);
	void restoreHP(int amount);
	void checkStatus();
	void printInfo();
	void playMonster();
	int getlevel();
};

int Animal::getlevel() {
	return level;
}
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

	while (hp >= 0) {
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
	static int level_cnt = 100;
	if (exp >= level_cnt)
	{
		Animal::levelUp();
		level_cnt = level_cnt * 2;
	}

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

void Animal::playMonster(void)
{
	// 시드 설정
	srand(static_cast<unsigned int>(time(nullptr)));
	const int default_EXP = 20;

	// 0부터 RAND_MAX 사이의 랜덤한 숫자 생성
	int randomNumber = rand();
	float random_case = randomNumber % 16;
	// 0, 1, 2, 3, 4, 5 <= 0.2 곱해주기
	// 6, 7, 8, 9 <= 0.5곱해주기
	// 10, 11, 12 <= 1 곱해주기
	// 13, 14 <= 1.2 곱해주기
	// 15 <= 2 곱해주기 
	if (random_case >= 0 && random_case < 6) { random_case = 0.2; cout << "경험치를 " << random_case * default_EXP << "만큼 획득하였습니다." << endl; }
	else if (random_case >= 6 && random_case < 10) {
		random_case = 0.5; cout << "경험치를 " << random_case * default_EXP << "만큼 획득하였습니다." << endl;
	}
	else if (random_case >= 10 && random_case < 13) {
		random_case = 1; cout << "경험치를 " << random_case * default_EXP << "만큼 획득하였습니다." << endl;
	}
	else if (random_case >= 13 && random_case < 15) {
		random_case = 1.2;  cout << "경험치를 " << random_case * default_EXP << "만큼 획득하였습니다." << endl;
	}
	else {
		random_case = 2; cout << "경험치를 " << random_case * default_EXP << "만큼 획득하였습니다." << endl;
	}


	Animal::increaseEXP(default_EXP * random_case);
}

void Animal::levelUp(void)
{
	Animal::level++;
	Animal::hp = 100;
}

void text_screen() {
	std::cout << "START" << std::endl;
}


int print_myMonster(Animal& chick_obj, const char* base)
{
	std::string baseName = base;/*"알에서막부화한병아리";*/ // 파일들의 공통 부분
	std::string extension = ".txt"; // 파일 확장자
	int startNumber = 1;
	int endNumber = 2;

	//std::string filename = "알에서막부화한병아리.txt"; // 입력받을 파일 이름


	for (int i = startNumber; i <= endNumber; i++)
	{
		system("cls");
		std::string filename = baseName + std::to_string(i) + extension; // 입력받을 파일 이름

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
		chick_obj.printInfo();

		Sleep(500);

		// 파일 닫기
		file.close();
	}



	//// 파일 열기
	//std::ifstream file(filename);
	//if (!file.is_open())
	//{
	//    std::cout << "파일을 열 수 없습니다." << std::endl;
	//    return 1;
	//}

	//// 파일 내용 출력

	//
	//    std::string line;
	//
	//    while (std::getline(file, line))
	//    {
	//        std::cout << line << std::endl;
	//    }
	//
	//    // 파일 닫기
	//   file.close();

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
	int now_level;

	//const char* baseName = "알에서막부화한병아리";
	while (1)
	{
		now_level = myAnimal.getlevel();
		// 여기서 스위치 (알 -> 병아리 -> 닭 -> 불사조)
		// 스위치 후 프린트
		//system("cls");
		switch (now_level)
		{
		case 0:
		case 1:
			print_myMonster(myAnimal, "알");
			break;
		case 2:
		case 3:
			print_myMonster(myAnimal, "알에서막부화한병아리");
			break;

		}
		//print_myMonster(myAnimal, "알에서막부화한병아리");
		//myAnimal.printInfo();
		myAnimal.playMonster();
		//Sleep(500);
		//if (now_level >= 2) {
		  //  break;
	   // }
	}
	return 0;
}