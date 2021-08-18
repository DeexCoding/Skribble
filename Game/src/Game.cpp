#include <Skribble.h>
#include <Skribble/Core/Entry.h>

#include "TestingLayer.h"

class Game : public Skribble::Application
{
public:
	Game()
	{
		PushLayer(new TestingLayer());
	}

	~Game()
	{

	}
};

Skribble::Application* Skribble::CreateApplication()
{
	return new Game();
}