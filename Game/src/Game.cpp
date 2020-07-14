#include <Skribble.h>

class Game : public Skribble::Application
{
public:
	Game()
	{

	}

	~Game()
	{

	}
};

Skribble::Application* Skribble::CreateApplication()
{
	return new Game();
}