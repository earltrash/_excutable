#pragma once
#include "pch.h"
#include "Status.h"


//�̰� �� �����ϰ� �� �ٵ� 07_28_����
class PlayerStatus
{

public:
	PlayerStatus() = default;
	~PlayerStatus() = default;

public:
	//��� ���� ��, Item->GameManager->Player�� ����
	//�� �����غ��� ������ ���ذ����� ������Ѿ� �ڴ�. Total�� GET�̶� DEBUG ���̰� SET ��ü�� �����ؾ��ҵ�
	void SetStatus(Status_fundamental which_status, int much);

	void Update_fStatus(Status_fundamental which_status, int much); //�̰͵� �� �� ������ �� ���ʿ��� ������ �� �� ���Ƽ�. 

	void Update_TStatus(); // fstatus ��� ��ġ�� �����ͼ� ���������� Tstatus�� ���� ��ȭ ��Ű��. //f���� �������� �Ŵϱ� 
	//�̰Ŵ� ���θ� �� �� �ؾ��� �� 

	int GetStatus(Status_Total which_status);

	void StatDebug(); //������ 

private:
	TotalStatus m_playerstatus{}; //�ʹ� ���� �� 0;
	fundamentalStatus m_fplayerstatus{};
};

