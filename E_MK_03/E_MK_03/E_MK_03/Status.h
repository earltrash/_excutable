#pragma once

struct TotalStatus //2차 스테이터스임 앞글자 대문자로 표기 , 플레이어가 가져야 할 구조체임 
{
	int Strength;
	int Magic_Power;
	int Health;
	int Knowledge;
	int Charm;
};

struct fundamentalStatus //얘는 앞 글자 소문자로 표기 , 아이템이 가져야 할 구조체임
{
	int power;
	int agile;
	int intelligence;
	int luck;
};


enum class Status_fundamental //enum으로 둔 거는 구조체 멤버 식별용임. 수치적 기능을 하지 않음
{
	power,
	agile,
	intelligence,
	luck
};

enum class Status_Total
{
	Strength,
	Magic_Power,
	Health,
	Knowledge,
	Charm
};



//[1차 스테이터스]
//힘: 근력, 건강에 영향
//민첩 : 근력, 매력에 영향
//지력 : 지식, 마력에 영향
//행운 : 매력, 지식에 영향
