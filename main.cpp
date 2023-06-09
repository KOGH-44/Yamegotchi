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
#include <conio.h>
using namespace std;
int type_input;
int cases = 999;
bool is_alive = true;
bool keyboardInput = false;
bool evo_flag = true;
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
	void levelUp();
	void startHPDecrease();
	void decreaseHP();
	//void decreaseHP(int amount);
	void decreaseHP_(int amount);
	void increaseEXP(int amount);
	void restoreHP(int amount);
	void checkStatus();
	void printInfo();
	void playMonster();
	int getlevel();
	void randomSituations();
	void randomSituationStart(); // 배고픈 상황, 병 걸린 상황, 놀고싶은 상황, 슬픈 상황을 게임이 시작함과 동시에 스레드로 돌리는 함수
};

class Bird : public Animal {
	/*
	Animal 클래스에서 상속받고 fly 함수를 추가로 구현
	*/
public:
	void fly();
};

class Plant : public Animal {
	/*
	Animal 클래스에서 상속받고 blossom 함수를 추가로 구현
	*/
public:
	void blossom();
};

bool checkKeyPressedWithinTime(int seconds, Animal& ani_obj/*, int cases*/) {
	/*
	시간안에 키를 입력하도록 요구하는 함수
	만약 키입력 못할 경우 HP감소하도록 구현
	*/
	time_t start = time(nullptr); // 현재 시간 가져오기
	time_t end = start + seconds; // 종료 시간 설정
	//cout << "키를 입력하세요!" << endl;
	if (cases == 0)
	{
		while (time(nullptr) < end) {

			if (_kbhit()) { // 키 입력 여부 확인
				char key = _getch(); // 입력한 키 가져오기
				if (key == 'q' || key == 'Q') {

					ani_obj.restoreHP(5);
					cases = 999;
					return true; // 'q' 키가 눌렸으면 true 반환
				}
			}
		}
	}
	else if (cases == 1) {
		while (time(nullptr) < end) {

			if (_kbhit()) { // 키 입력 여부 확인
				char key = _getch(); // 입력한 키 가져오기
				if (key == 'w' || key == 'W') {

					ani_obj.restoreHP(5);
					cases = 999;
					return true; // 'q' 키가 눌렸으면 true 반환
				}
			}
		}
	}
	else if (cases == 2) {
		while (time(nullptr) < end) {

			if (_kbhit()) { // 키 입력 여부 확인
				char key = _getch(); // 입력한 키 가져오기
				if (key == 'e' || key == 'E') {

					ani_obj.restoreHP(5);
					cases = 999;
					return true; // 'q' 키가 눌렸으면 true 반환
				}
			}
		}
	}
	else if (cases == 3) {
		while (time(nullptr) < end) {

			if (_kbhit()) { // 키 입력 여부 확인
				char key = _getch(); // 입력한 키 가져오기
				if (key == 'r' || key == 'R') {
					ani_obj.increaseEXP((ani_obj.getlevel() + 1) * 50);
					cases = 999;
					return true; // 'q' 키가 눌렸으면 true 반환
				}
			}
		}
	}
	cases = 999;
	ani_obj.decreaseHP_(70);
	return false;
}

int Animal::getlevel() {
	//Animal의 레벨 구하는 함수
	return level;
}
char* Animal::getName() {
	//Animal의 이름 구하는 함수
	return name;
}

void Animal::setName(const char* animalName) {
	//Animal의 이름 설정하는 함수
	if (name != nullptr) {
		delete[] name;
	}
	name = new char[strlen(animalName) + 1];
	strcpy(name, animalName);
}

void Animal::startHPDecrease() {
	//Anima이 시간이 지남에 따라 HP감소 구현.
	//해당함수는 독립적으로 작동해야하기 때문에 스레드함수로 구현함.
	thread t(&Animal::decreaseHP, this);
	t.detach();
}

void Animal::randomSituations() {
	// 랜덤한 시간마다 랜덤한 상황을 벌이고 처리(HP회복 및 EXP획득 / HP타격) 하는 함수
	int SituationCase = 0;
	int RandomDelayTime = 0;
	while (1) {
		
		RandomDelayTime = rand() % 50 + 10; //100~199까지 하나의 시간을 골라서 일이 벌어진다.
		Sleep(RandomDelayTime * 300);
		SituationCase = rand() % 4;
		switch (SituationCase)
		{
			bool bool_var;
		case 0: // 배고픈 상황
			cases = 0;
			bool_var = checkKeyPressedWithinTime(5, *this);
			break;

		case 1://병 걸린 상황
			cases = 1;
			bool_var = checkKeyPressedWithinTime(5, *this);
			break;

		case 2:// 슬픈 상황
			cases = 2;
			bool_var = checkKeyPressedWithinTime(5, *this);
			break;

		case 3:// 놀고 싶은 상황
			cases = 3;
			bool_var = checkKeyPressedWithinTime(5, *this);
			break;


		}

	}
}

void Animal::randomSituationStart() {
	// randomSituations 함수를 스레드로 작동하기 위해 구현된 함수
	thread rt(&Animal::randomSituations, this);
	rt.detach();
}



void Animal::decreaseHP() {
	/*
	시간이 지남에 따라 HP감소하는 함수, 만약 HP가 0이되면 게임오버 파일을 출력하는 함수
	*/
	//int totalSeconds = 30;
	int decreaseAmount = 1; // HP 감소량

	while (hp >= 0) {
		std::this_thread::sleep_for(std::chrono::seconds(10));
		//totalSeconds--;
		hp -= decreaseAmount;
		checkStatus();
		if (hp <= 0) {
			is_alive = false;
			system("cls");

			//////////////////////////////////////////////////////////////////////////////
			std::string gameoverfilename = "게임오버(1).txt"; // 입력받을 파일 이름

			// 파일 열기
			std::ifstream file(gameoverfilename);


			// 파일 내용 출력
			std::string line;
			while (std::getline(file, line))
			{
				std::cout << line << std::endl;
			}
			//Sleep(500);

			// 파일 닫기
			file.close();
			//////////////////////////////////////////////////////////////////////////////

			std::cout << "게임 오버! " << name << "의 체력이 0이 되었습니다." << std::endl;
			exit(0); // 프로그램 종료
		}
	}


}

//void Animal::decreaseHP(int amount) {
//	hp -= amount;
//	checkStatus();
//	if (hp <= 0) {
//		std::cout << "게임 오버! " << name << "의 체력이 0이 되었습니다." << std::endl;
//
//		exit(0); // 프로그램 종료
//	}
//}

void Animal::decreaseHP_(int amount) {
	/*
	함수 checkKeyPressedWithinTime 에서 요구사항에 만족하지 못할경우 실행됨.
	불이익 수치(amount)만큼 HP가 감소. 만약 HP가 0 이하가 되면 게임오버 화면을 출력함.
	*/
	hp -= amount;
	checkStatus();
	if (hp <= 0) {
		is_alive = false;
		system("cls");

		//////////////////////////////////////////////////////////////////////////////
		std::string gameoverfilename = "게임오버(1).txt"; // 입력받을 파일 이름

		// 파일 열기
		std::ifstream file(gameoverfilename);


		// 파일 내용 출력
		std::string line;
		while (std::getline(file, line))
		{
			std::cout << line << std::endl;
		}
		//Sleep(500);

		// 파일 닫기
		file.close();
		//////////////////////////////////////////////////////////////////////////////

		std::cout << "게임 오버! " << name << "의 체력이 0이 되었습니다." << std::endl;

		exit(0); // 프로그램 종료
	}
}


void Animal::increaseEXP(int amount) {
	/*
	exp 증가하는 함수, 만약 level_cnt보다 넘게되면 레벨업 하도록 구현.
	*/
	exp += amount;
	static int level_cnt = 100;
	if (exp >= level_cnt)
	{
		Animal::levelUp();
		level_cnt = level_cnt * 2;
	}

}

void Animal::restoreHP(int amount) {
	/*
	체력 회복하는 함수, 만약 체력이 100을 넘으면 100이되도록 구현
	*/
	hp += amount;
	if (hp > 100) {
		hp = 100;
	}
	checkStatus();
}

void Animal::checkStatus() {
	/*상태 이상을 출력하는 함수. 만약 HP가 30 미만일 경우 이상상태를 출력한다.
	*/
	if (hp < 30) {
		status = 2;

	}
	else {
		status = 1; // 정상
	}
}


void Animal::printInfo() {
	//화면에 Animal의 정보를 출력하는 함수
	std::cout << "이름: " << name << std::endl;
	std::cout << "레벨: " << level << std::endl;
	std::cout << "경험치: " << exp << std::endl;
	std::cout << "체력: " << hp << std::endl;
	/// 999 : 정상 |   0: 배고픔     |    1: 아픔     |       2: 슬픔      |  3: 즐거움
	if (cases == 999) {
		cout << "상태: 정상" << endl;
	}
	else if (cases == 0) {
		cout << "상태: 배고픔" << endl;
	}
	else if (cases == 1) {
		cout << "상태: 아픔" << endl;
	}
	else if (cases == 2) {
		cout << "상태: 슬픔" << endl;
	}
	else if (cases == 3) {
		cout << "상태: 심심함" << endl;
	}

	if (hp <= 30) {
		std::cout << "경고: " << name << "의 체력이 30 이하입니다!" << std::endl;
	}

	if (cases == 0) {
		cout << name << "에게 q(Q)를 눌러 밥을 주세요~" << endl;
	}
	else if (cases == 1) {
		cout << name << "에게 w(W)를 눌러 병을 치료해주세요~" << endl;
	}
	else if (cases == 2) {
		cout << name << "에게 e(E)를 눌러 위로를 해주세요~" << endl;
	}
	else if (cases == 3) {
		cout << name << "에게 r(R)을 눌러 놀아주세요~" << endl;
	}
	if (keyboardInput) {
		switch (type_input)
		{
		case 1://새
			if (level <= 2)//알
				cout << name << "(이) 가 부화 하려 합니다" << endl;

			else if (level <= 5)//알병아리
				cout << name << "(이) 가 머리를 흔듭니다" << endl;

			else if (level <= 7)//걷는병아리
				cout << name << "(이)가 걷고 있습니다" << endl;

			else if (level <= 9)//닭
				cout << name << "(이)가 인사를 합니다" << endl;

			else if (level >= 10)//주작
				cout << name << "(이)가 날개짓을  합니다" << endl;

			break;

		case 2://식물
			if (level <= 2)//씨앗
				cout << name << "(이) 흔들립니다" << endl;

			else if (level <= 5)//새싹
				cout << name << "(이) 가 자라고 있습니다" << endl;

			else if (level <= 7)//좀큰나무
				cout << name << "(이)가 더욱 더 자라고 있습니다" << endl;

			else if (level <= 9)//다큰나무
				cout << name << "(이)가 바람에 흔들립니다" << endl;

			else if (level >= 10)//밑동
				cout << name << "(이)가 슬퍼 보입니다." << endl;
			break;
		}

	}

}

void Animal::playMonster(void)
{	// 몬스터를 놀아주고 경험치를 획득하는 함수. 경험치는 Rand()함수를 사용하여 구현함.
	// 시드 설정
	//srand(static_cast<unsigned int>(time(nullptr)));
	const int default_EXP = 200;

	// 0부터 RAND_MAX 사이의 랜덤한 숫자 생성
	int randomNumber = rand();
	float random_case = randomNumber % 21;
	// 0, 1, 2 <= 0.3 곱해주기
	// 3, 4, 5, 6 <= 0.7곱해주기
	// 7, 8, 9, 10, 11, 12 <= 1 곱해주기
	// 13, 14, 15, 16, 17 <= 1.5 곱해주기
	// 18, 19, 20 <= 2.5 곱해주기 
	if (random_case >= 0 && random_case < 3) { random_case = 0.3; /*cout << "경험치를 " << random_case * default_EXP << "만큼 획득하였습니다." << endl;*/ }
	else if (random_case >= 3 && random_case < 7) {
		random_case = 0.7; /*cout << "경험치를 " << random_case * default_EXP << "만큼 획득하였습니다." << endl;*/
	}
	else if (random_case >= 7 && random_case < 13) {
		random_case = 1; /*cout << "경험치를 " << random_case * default_EXP << "만큼 획득하였습니다." << endl;*/
	}
	else if (random_case >= 13 && random_case < 18) {
		random_case = 1.5;  /*cout << "경험치를 " << random_case * default_EXP << "만큼 획득하였습니다." << endl;*/
	}
	else {
		random_case = 2.5; /*cout << "경험치를 " << random_case * default_EXP << "만큼 획득하였습니다." << endl;*/
	}


	Animal::increaseEXP(default_EXP * random_case * ((this->level) + 1));
}

void Animal::levelUp(void)
{ //레벨업 하는 함수, 레벨업시 HP를 100으로 초기화
	Animal::level++;
	Animal::hp = 100;
}

void text_screen() {
	std::cout << "START" << std::endl;
}

void Bird::fly() {
	
	 /*
	 스레드 독립, t or T 입력받으면 출력
	 1초동안 동작 이후 원래 상태로 복귀
	 */
	while (1)
	{	

		if (_kbhit())
		{ // 키 입력 여부 확인
			char key = _getch(); // 입력한 키 가져오기
			if (key == 't' || key == 'T')
			{

				keyboardInput = true;
				Sleep(1000);
				keyboardInput = false;
			}
		}
	}
}

void Plant::blossom() {
	/*
	 스레드 독립, p or P 입력받으면 출력
	 1초동안 동작 이후 원상태 복귀
	 */
	while (1) 
	{
		if (_kbhit()) 
		{ // 키 입력 여부 확인
			char key = _getch(); // 입력한 키 가져오기
			if (key == 'p' || key == 'P') 
			{

				keyboardInput = true;
				Sleep(1000);
				keyboardInput = false;
				
			}
		}
	}
}
int print_myMonster(Animal& chick_obj, string base, string type_)
{
	//몬스터에 대한 그림을 출력하는 함수
	std::string baseName = base;/*"알에서막부화한병아리";*/ // 파일들의 공통 부분
	std::string type = type_;
	std::string extension = ".txt"; // 파일 확장자

	int startNumber = 1;
	int endNumber = 2;

	//std::string filename = "알에서막부화한병아리.txt"; // 입력받을 파일 이름
	int levelCheck = chick_obj.getlevel();
	if (levelCheck < 3) {
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
	}
	else if ((levelCheck >= 3) && (levelCheck < 5) && evo_flag) { //진화파트
		for (int a = 0; a < 10; a++) {
			for (int i = startNumber; i <= endNumber; i++)
			{
				system("cls");
				std::string filename1 = baseName + std::to_string(i) + extension; // 입력받을 파일 이름
				filename1 = "알1.txt"; // 입력받을 파일 이름
				filename1 = "유년기(" + type + ")1" + extension;

				// 파일 열기
				std::ifstream file(filename1);
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

				Sleep(50);
				// 파일 닫기
				file.close();



				system("cls");
				std::string filename2 = baseName + std::to_string(i) + extension; // 입력받을 파일 이름
				filename2 = "알에서막부화한병아리1.txt"; // 입력받을 파일 이름
				filename2 = "성장기(" + type + ")1" + extension;
				// 파일 열기
				std::ifstream file2(filename2);
				if (!file2.is_open())
				{
					std::cout << "파일을 열 수 없습니다." << std::endl;
					return 1;
				}

				// 파일 내용 출력
				//std::string line;
				while (std::getline(file2, line))
				{
					std::cout << line << std::endl;
				}
				chick_obj.printInfo();

				Sleep(50);
				// 파일 닫기
				file2.close();
			}
		}
		evo_flag = false;
	}
	else if ((levelCheck >= 3) && (levelCheck < 6)) {
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
	}
	else if ((levelCheck >= 6) && (levelCheck < 8) && !evo_flag)
	{
		for (int a = 0; a < 10; a++) {
			for (int i = startNumber; i <= endNumber; i++)
			{
				system("cls");
				std::string filename1 = baseName + std::to_string(i) + extension; // 입력받을 파일 이름
				filename1 = "알에서막부화한병아리1.txt"; // 입력받을 파일 이름
				filename1 = "성장기(" + type + ")1" + extension;
				// 파일 열기
				std::ifstream file(filename1);
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

				Sleep(50);
				// 파일 닫기
				file.close();



				system("cls");
				std::string filename2 = baseName + std::to_string(i) + extension; // 입력받을 파일 이름
				filename2 = "걸어다니는병아리1.txt"; // 입력받을 파일 이름
				filename2 = "성숙기(" + type + ")1" + extension;
				// 파일 열기
				std::ifstream file2(filename2);
				if (!file2.is_open())
				{
					std::cout << "파일을 열 수 없습니다." << std::endl;
					return 1;
				}

				// 파일 내용 출력
				//std::string line;
				while (std::getline(file2, line))
				{
					std::cout << line << std::endl;
				}
				chick_obj.printInfo();

				Sleep(50);
				// 파일 닫기
				file2.close();
			}
		}
		evo_flag = true;
	}

	else if ((levelCheck >= 6) && (levelCheck < 8)) {
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
	}

	else if ((levelCheck >= 8) && (levelCheck < 10) && evo_flag)
	{
		for (int a = 0; a < 10; a++) {
			for (int i = startNumber; i <= endNumber; i++)
			{
				system("cls");
				std::string filename1 = baseName + std::to_string(i) + extension; // 입력받을 파일 이름
				filename1 = "걸어다니는병아리1.txt"; // 입력받을 파일 이름
				filename1 = "성숙기(" + type + ")1" + extension;
				// 파일 열기
				std::ifstream file(filename1);
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

				Sleep(50);
				// 파일 닫기
				file.close();



				system("cls");
				std::string filename2 = baseName + std::to_string(i) + extension; // 입력받을 파일 이름
				filename2 = "닭1.txt"; // 입력받을 파일 이름
				filename2 = "완전체(" + type + ")1" + extension;
				// 파일 열기
				std::ifstream file2(filename2);
				if (!file2.is_open())
				{
					std::cout << "파일을 열 수 없습니다." << std::endl;
					return 1;
				}

				// 파일 내용 출력
				//std::string line;
				while (std::getline(file2, line))
				{
					std::cout << line << std::endl;
				}
				chick_obj.printInfo();

				Sleep(50);
				// 파일 닫기
				file2.close();
			}
		}
		evo_flag = false;
	}

	else if ((levelCheck >= 8) && (levelCheck < 10)) {
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
	}

	else if ((levelCheck == 10) && !evo_flag)
	{
		for (int a = 0; a < 10; a++) {
			for (int i = startNumber; i <= endNumber; i++)
			{
				system("cls");
				std::string filename1 = baseName + std::to_string(i) + extension; // 입력받을 파일 이름
				filename1 = "닭1.txt"; // 입력받을 파일 이름
				filename1 = "완전체(" + type + ")1" + extension;
				// 파일 열기
				std::ifstream file(filename1);
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

				Sleep(50);
				// 파일 닫기
				file.close();



				system("cls");
				std::string filename2 = baseName + std::to_string(i) + extension; // 입력받을 파일 이름
				filename2 = "불사조1.txt"; // 입력받을 파일 이름
				filename2 = "궁극체(" + type + ")1" + extension;
				// 파일 열기
				std::ifstream file2(filename2);
				if (!file2.is_open())
				{
					std::cout << "파일을 열 수 없습니다." << std::endl;
					return 1;
				}

				// 파일 내용 출력
				//std::string line;
				while (std::getline(file2, line))
				{
					std::cout << line << std::endl;
				}
				chick_obj.printInfo();

				Sleep(50);
				// 파일 닫기
				file2.close();
			}
		}
		evo_flag = true;
	}
	else if (levelCheck >= 10)
	{
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

	}
}



void gamestart() {
	//게임 시작하는 함수
	srand(static_cast<unsigned int>(time(nullptr)));
	cout << "타입을 정하시오: 1(새), 2(식물)" << endl;
	cin >> type_input;
	char* char_name = NULL;
	std::cout << "캐릭터의 이름을 입력하세요: ";
	std::string name;
	cin >> name;
	std::string filename;
	std::string type_name;
	if (type_input == 1) {
		type_name = "조류";

		Bird myAnimal;

		/*std::getline(std::cin, name);
		myAnimal.setName(name.c_str());*/

		myAnimal.setName(name.c_str());
		//std::thread t(&Bird::fly, &myAnimal);
		//t.detach();
		// 게임 시작
		myAnimal.startHPDecrease();
		myAnimal.randomSituationStart(); // 랜덤 상황 함수도 같이 돌려준다.
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
				if (is_alive) {
			case 0:
			case 1:
			case 2:
				filename = "유년기(";
				filename += type_name + ")";

				print_myMonster(myAnimal, filename, type_name);
				break;
			case 3:
			case 4:
			case 5:
				filename = "성장기(";
				filename += type_name + ")";

				print_myMonster(myAnimal, filename, type_name);
				break;
			case 6:
			case 7:

				filename = "성숙기(";
				filename += type_name + ")";
				print_myMonster(myAnimal, filename, type_name);
				break;
			case 8:
			case 9:

				filename = "완전체(";
				filename += type_name + ")";
				print_myMonster(myAnimal, filename, type_name);
				break;
			default:

				filename = "궁극체(";
				filename += type_name + ")";
				print_myMonster(myAnimal, filename, type_name);
				break;
				}
			}
			//print_myMonster(myAnimal, "알에서막부화한병아리");
			//myAnimal.printInfo();
			myAnimal.playMonster();
			//Sleep(500);
			//if (now_level >= 2) {
			  //  break;
		   // }
		}
	}

	else if (type_input == 2)
	{

		Plant myAnimal;
		type_name = "식물";
		/*std::getline(std::cin, name);
		myAnimal.setName(name.c_str());*/
		//std::thread t(&Plant::blossom, &myAnimal);
		//t.detach();
		myAnimal.setName(name.c_str());

		// 게임 시작
		myAnimal.startHPDecrease();
		myAnimal.randomSituationStart(); // 랜덤 상황 함수도 같이 돌려준다.
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
				if (is_alive)
				{
			case 0:
			case 1:
			case 2:
				//print_myMonster(myAnimal, "알");
				filename = "유년기(";
				filename += type_name + ")";
				print_myMonster(myAnimal, filename, type_name);
				break;
			case 3:
			case 4:
			case 5:
				filename = "성장기(";
				filename += type_name + ")";
				//print_myMonster(myAnimal, "알에서막부화한병아리");
				print_myMonster(myAnimal, filename, type_name);
				break;
			case 6:
			case 7:
				filename = "성숙기(";
				filename += type_name + ")";
				//print_myMonster(myAnimal, "걸어다니는병아리");
				print_myMonster(myAnimal, filename, type_name);
				break;
			case 8:
			case 9:
				//print_myMonster(myAnimal, "닭");'
				filename = "완전체(";
				filename += type_name + ")";
				print_myMonster(myAnimal, filename, type_name);
				break;
			default:
				//print_myMonster(myAnimal, "불사조");
				filename = "궁극체(";
				filename += type_name + ")";
				print_myMonster(myAnimal, filename, type_name);
				break;
				}
			}
			//print_myMonster(myAnimal, "알에서막부화한병아리");
			//myAnimal.printInfo();
			myAnimal.playMonster();
		}
	}
	
}


int main()
{
	gamestart();
}