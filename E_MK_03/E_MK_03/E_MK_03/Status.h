#pragma once

struct TotalStatus //2�� �������ͽ��� �ձ��� �빮�ڷ� ǥ�� , �÷��̾ ������ �� ����ü�� ->
{
	int Strength;
	int Magic_Power;
	int Health;
	int Knowledge;
	int Charm;
};

struct fundamentalStatus //��� �� ���� �ҹ��ڷ� ǥ�� , �������� ������ �� ����ü��
{
	int power;
	int agile;
	int intelligence;
	int luck;
};



enum class Status_Total
{
	Strength,
	Magic_Power,
	Health,
	Knowledge,
	Charm
};


enum class Status_fundamental //�������� ���� �ִ� ����
{
	power,
	agile,
	intelligence,
	luck,

	Unknown
};


enum class Wearable_part //-> Wearable �з�
{
	Weapon,
	Shoes,
	EarRing,
	Neckless,
	Glove,
	Under,
	Upper,
	Helmet,
	Cape,
	UnKnown
};

enum class Need_Moment //-> ���� �ʿ��ϳ�?
{
	Gen_2, //2���� 
	Gen_3, //3����
	Gen_4, //4���� �⺻
	//�ڿ������� ����� �ֵ� 

	//����ؼ� ����� �ֵ� 

	Syn, //�ռ� ��,
	Adv, //���� ��,

	//�� 
	Fam3, //2���� ���� ��, �� ��ġ�� ���� 3����� ���� �ֵ� 
	Fam4, //Ư�� �� ��ġ �޼� ��,
	UnKnown
};





