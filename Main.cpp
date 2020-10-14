#define _CRTDBG_MAP_ALLOC  
#include <stdlib.h>  
#include <crtdbg.h>
#include <string>
#include "SceneManager.h"
#include "Debug.h"

  
int main(int argc, char* args[]) {

	std::string name = { "Graphics Game Engine" };
	Debug::DebugInit(name + "_Log");
	Debug::Info("Starting the GameSceneManager", __FILE__, __LINE__);
	
	SceneManager* gsm = new SceneManager();
	if (gsm->Initialize(name, 1280, 720) ==  true) { //1280, 720   1920, 1080
		gsm->Run();
	} 
	delete gsm;
	
	_CrtDumpMemoryLeaks();
	exit(0);

}