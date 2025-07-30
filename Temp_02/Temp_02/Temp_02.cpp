#include "Core.h"
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW

#include "Factory.h"
#include "SceneFactory.h"



int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// ������ ����
	//std::locale::global(std::locale(".UTF8"));
	//std::wcout.imbue(std::locale());

	// �ܼ� ����� UTF-8��
	SetConsoleOutputCP(CP_UTF8); 

	//����ó�� 
	ObjectRegister(); //assert�� ���ѵ� �� �ϴ� factory�� obj ��� 
	SceneFactory::Get().SceneRegister();

	M_Core core;
	core.Init();

	core.Run();
	core.End();

	_CrtDumpMemoryLeaks();
	return 0;
}

