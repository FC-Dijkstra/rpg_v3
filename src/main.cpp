#include <glad/glad.h>
#include "Engine/Engine.h"
#include "Engine/IGame.h"
#include "Game/TestGame.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "time.h"
#include "Personnage.h"
#include "Entity.h"

using namespace std;
int main(){
    cout << "hello world \n";
    Personnage p(100);
    cout << "personnage pv : " << p.getPv();
int main(void)
{
	bool vsync = true;
	Game* g = new TestGame();
	Engine* e = new Engine("test openGL", 800, 600, vsync, g);
	e->run();

    return 0;
}
