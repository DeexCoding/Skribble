#include <Skribble.h>
#include <Skribble/Entry.h>

#include "GameLayer.h"

class Game : public Skribble::Application
{
public:
	Game()
	{
		PushLayer(new GameLayer());
	}

	~Game()
	{

	}
};

Skribble::Application* Skribble::CreateApplication()
{
	return new Game();
}