# 프로젝트 이름 : 야매고치 

<br/><br/>

## 제작 기간 : 2023.05.26 ~ 2023.06.12

<br/>

## 게임 목적 : C++의 클래스 상속을 통해 여러가지 동식물을 키우는 휴대용 게임 기기 다마고치를 구현

<br/>

## 개발 환경 : C, C++ Ubuntu, Github

<br/>

## Git hub : https://github.com/KOGH-44/Yamegotchi

<br/>

## 작 성 자 : 김근환 , 박민혁 , 정혜원 , 최종일 

<br/>

![계획표](https://github.com/KOGH-44/Yamegotchi/assets/129154514/9b42e754-b46a-438f-8424-8e8ea48db858)





## 1) 구현 방안

공용 부분(hp , exp ,먹기등등 )을 가지고 있는 animal 클래스를 만든후 

클래스를 상속받아 새로운 클래스가 가진 개인의 특성(상호작용)을 더해 몬스터를 생성하여

객체 지향을 유지하며 상황에 따른 케어를 통해 몬스터를 성장시키는 게임

<br/>

## 2) 구조 (레벨업 조건, 게임종료 조건)

![제목 없는 다이어그램 drawio](https://github.com/KOGH-44/Yamegotchi/assets/129154514/b527841f-649e-4f86-bbc3-980c40e00080)![제목 없는 다이어그램 drawio (1)](https://github.com/KOGH-44/Yamegotchi/assets/129154514/4b90dbca-1377-466d-957c-e52bd638ad38)

<br/>

## 3) 구현 목록


스레드 함수를 통해 실시간으로 키보드 입력받기 및 다양한 상황(놀아주기, 밥주기, 죽음 등) 연출

animal class : 모든 생물이 공통적으로 가지고 있는 변수와 상황을 함수로 구현

bird class :  애니멀을 상속 받은후 조류만의 특징을 가진 객체 지향적인 클래스를 만들어줌

plant class : 애니멀을 상속 받은후 식물만의 특징을 가진 객체 지향적인 클래스를 만들어줌

진화 시스템 - 시간에 따른 몬스터의 변화를 구현


<br/>

## 4) 게임 플레이 방법

  1.git clone https://github.com/KOGH-44/Yamegotchi 을 통해 파일을 복사.
  
  2.vs code를 이용하여 main.cpp을 윈도우 환경에서 실행.
  
  3.안내 메시지에 따라 1번(새) 혹은 2번(식물)을 입력.
  
  4.몬스터의 이름을 입력.(영어)
  
  5.상황에 따라 q,w,e,r 을 통해 몬스터를 케어
  
  6.새는 t버튼, 식물은 p버튼을 통해 몬스터와 상호작용
  
  이쁘고 멋진 몬스터를 키워봅시다.
  
<br/>  
  
## 5) 개선 사항

몬스터의 이름을 영어로만 입력 받을수 있다. 한글 입력 구현이 요망된다.

bird, plant 외에도 더 다양한 클래스를 추후에 추가하여 다양성을 더 늘리면 재미가 증가할 것 같다.

몬스터와 좀 더 상호작용하거나 미니게임을 추가하면 좋을것 같다.


<br/>

### 게임 플레이 예시 1 (성장기 - 성숙기 - 완전체 - 궁극체)

![성장기](https://github.com/KOGH-44/Yamegotchi/assets/76278512/8a5da8ea-8102-4b59-afb0-f48d1823291f)  ![성숙기](https://github.com/KOGH-44/Yamegotchi/assets/76278512/240b4673-6237-43c2-9e9e-1a6b3aeb7ad7)  ![완전체(조류)](https://github.com/KOGH-44/Yamegotchi/assets/76278512/1116519c-877a-437d-94d6-de1f7861f926)  ![궁극체](https://github.com/KOGH-44/Yamegotchi/assets/76278512/88f89677-ed9a-4180-9a8e-6f93476b6b35)
<br/><br/><br/>
### 게임 플레이 예시 2 (진화 장면)

![진화파트](https://github.com/KOGH-44/Yamegotchi/assets/76278512/48fc14dd-4a79-4e0b-973f-f9f2ca61236f)
<br/><br/><br/>
### 게임 플레이 예시 3 (게임 오버)

![게임오버](https://github.com/KOGH-44/Yamegotchi/assets/76278512/421f6daf-d2e5-4ca8-9a46-8c9f4d7b7ae9)

