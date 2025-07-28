#pragma once
#include "pch.h"
#include "Status.h"


//이건 좀 공부하고 더 다듬어봄 07_28_범진
class PlayerStatus
{

public:
	PlayerStatus() = default;
	~PlayerStatus() = default;

public:
	//장비 착용 시, Item->GameManager->Player순 전달
	//아 생각해보니 아이템 기준값으로 변경시켜야 겠다. Total은 GET이랑 DEBUG 용이고 SET 자체는 변경해야할듯
	void SetStatus(Status_fundamental which_status, int much);

	void Update_fStatus(Status_fundamental which_status, int much); //이것도 좀 더 봐야할 듯 불필요한 연산을 할 거 같아서. 

	void Update_TStatus(); // fstatus 기반 수치를 가져와서 최종적으로 Tstatus의 값을 변화 시키는. //f값이 여러개일 거니깐 
	//이거는 공부를 좀 더 해야할 듯 

	int GetStatus(Status_Total which_status);

	void StatDebug(); //디버깅용 

private:
	TotalStatus m_playerstatus{}; //초반 값은 다 0;
	fundamentalStatus m_fplayerstatus{};
};

