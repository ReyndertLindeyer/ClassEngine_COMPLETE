#include "Core/ClassEngine.h"
#include "../Game/GameOne.h"

int main(int argc, char* args[]) {
	ClassEngine::GetInstance()->SetGameInterface(new GameOne());
	////VERSION 1
	//if (!ClassEngine::GetInstance()->Initialize("GAM301 Engine", 800, 600)) {
	//	std::cout << "Engine failed to initialize" << std::endl;
	//	return 0;
	//}
	
	//VERSION 2
	ClassEngine::GetInstance()->Initialize("GAM301 Engine", 800, 600);
	
	ClassEngine::GetInstance()->Run();

	return 0;
}