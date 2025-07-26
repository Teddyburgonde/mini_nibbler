#pragma once
#include "../includes/IGui.hpp"
#include <SDL.h>
#include "../core/GameState.hpp"
#include "GuiSDLDraw.hpp"

class GuiSDL : public IGui
{
	public:
		void	init(int width, int height) override;
		void	render(const GameState& state) override;
		Input	getInput() override;
		void	cleanup() override;
		~GuiSDL() override = default;
	private:
		void checkTerminalSize(int requiredWidth, int requiredHeight);
		void showVictory() override;
		void showGameOver() override;
		int	_screenWidth;
		int	_screenHeight;
};