#include <iostream>


#include "Engine.h"
#include "Scene.h"
#include "Actor.h"




#include <iostream>
#include <cstdlib>
#include <vector>





int main(int argc, char* argv[])
{
	g_engine.Initialize();


	while (!g_engine.IsQuit())
	{

		//____INPUT____

		g_engine.Update();


		//____DRAW____


		//	// clear screen
		g_engine.GetRenderer().SetColor(0, 0, 0, 0);
		g_engine.GetRenderer().BeginFrame();

		//g_engine.GetPS().Draw(g_engine.GetRenderer());

		g_engine.GetRenderer().EndFrame();



	}

	g_engine.Shutdown();

	return 0;
}