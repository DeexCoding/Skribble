#pragma once

#include "Skribble.h"

class GameLayer : public Skribble::Layer
{
public:
	GameLayer();
	virtual ~GameLayer() = default;

	void Update() override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

	void OnEvent(Skribble::Event& _event) override;
};