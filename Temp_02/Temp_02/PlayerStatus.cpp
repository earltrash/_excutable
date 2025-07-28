#include "PlayerStatus.h"

void PlayerStatus::SetStatus(Status_fundamental which_status, int much)
{
	switch (which_status)
	{
	case Status_fundamental::power:
		m_fplayerstatus.power = much;
		break;
	case Status_fundamental::agile:
		m_fplayerstatus.agile = much;
		break;
	case Status_fundamental::intelligence:
		m_fplayerstatus.intelligence = much;
		break;
	case Status_fundamental::luck:
		m_fplayerstatus.luck = much;
		break;
	default:
		std::cout << "¿ì¸®´Â ±×·± °Å ¾ø´Âµª¼î" << std::endl;
		break;
	}
}

void PlayerStatus::Update_fStatus(Status_fundamental which_status, int much)
{
	switch (which_status)
	{
	case Status_fundamental::power:
		m_fplayerstatus.power = m_fplayerstatus.power+ much;
		break;
	case Status_fundamental::agile:
		m_fplayerstatus.agile = m_fplayerstatus.agile + much;
		break;
	case Status_fundamental::intelligence:
		m_fplayerstatus.intelligence = m_fplayerstatus.intelligence + much;
		break;
	case Status_fundamental::luck:
		m_fplayerstatus.luck = m_fplayerstatus.luck + much;
		break;
	default:
		std::cout << "¿ì¸®´Â ±×·± °Å ¾ø´Âµª¼î" << std::endl;
		break;
	}





}





int PlayerStatus::GetStatus(Status_Total which_status)
{
	switch (which_status)
	{
	case Status_Total::Strength:
		return m_playerstatus.Strength;
	case Status_Total::Magic_Power:
		return m_playerstatus.Magic_Power;
	case Status_Total::Health:
		return m_playerstatus.Health;
	case Status_Total::Knowledge:
		return m_playerstatus.Knowledge;
	case Status_Total::Charm:
		return m_playerstatus.Charm;
	default:
		std::cout << "¿ì¸®´Â ±×·± °Å ¾ø´Âµª¼î" << std::endl;
		break;
	}
}

void PlayerStatus::StatDebug()
{
	std::cout << "Strength:" << m_playerstatus.Strength << std::endl;
	std::cout << "Magic_Power:" << m_playerstatus.Magic_Power << std::endl;
	std::cout << "Health:" << m_playerstatus.Health << std::endl;
	std::cout << "Knowledge:" << m_playerstatus.Knowledge << std::endl;
	std::cout << "Charm:" << m_playerstatus.Charm << std::endl;

}
