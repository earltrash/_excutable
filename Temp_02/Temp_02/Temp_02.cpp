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

	// 로케일 설정
	//std::locale::global(std::locale(".UTF8"));
	//std::wcout.imbue(std::locale());

	// 콘솔 출력을 UTF-8로
	SetConsoleOutputCP(CP_UTF8); 

	//예외처리 
	ObjectRegister(); //assert로 시켜도 됨 일단 factory에 obj 등록 
	SceneFactory::Get().SceneRegister();

	M_Core core;
	core.Init();

	core.Run();
	core.End();

	_CrtDumpMemoryLeaks();
	return 0;
}

