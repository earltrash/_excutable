#pragma once

struct TotalStatus //2�� �������ͽ��� �ձ��� �빮�ڷ� ǥ�� , �÷��̾ ������ �� ����ü�� 
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


enum class Status_fundamental //enum���� �� �Ŵ� ����ü ��� �ĺ�����. ��ġ�� ����� ���� ����
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



//[1�� �������ͽ�]
//��: �ٷ�, �ǰ��� ����
//��ø : �ٷ�, �ŷ¿� ����
//���� : ����, ���¿� ����
//��� : �ŷ�, ���Ŀ� ����
