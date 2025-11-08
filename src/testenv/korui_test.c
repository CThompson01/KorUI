#include "raylib.h"
#include "../korui/korui.h"

int main() {
	// Window Setup
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(854, 480, "KorUI Test Environment");
	SetTargetFPS(60);
	SetExitKey(KEY_P);

	Font defaultFont = LoadFontEx("resources/fonts/arial.ttf", 96, 0, 0);
	UIElement resumeButton = CreateButtonElement("resume_button", "Resume", 0, 0, 100, 25);
	UIElement optionsButton = CreateButtonElement("options_button", "Options", 0, 0, 100, 25);
	UIElement exitButton = CreateButtonElement("exit_button", "Exit", 0, 0, 100, 25);
	UIElement* pauseMenu[3] = {
		&resumeButton,
		&optionsButton,
		&exitButton
	};
	AutoLayout(pauseMenu, 3,
		(LayoutStyle) {CENTERED, CENTERED, VERTICAL},
		(LayoutDetails) {0, 0, 854, 480}, 5);


	// Start main game loop
	while (!WindowShouldClose()) {
		// Input
		// for (int i = 0; i < 3; i++) {
		// }

		// Update

		// Render
		BeginDrawing();
		ClearBackground(DARKBLUE);

		for (int i = 0; i < 3; i++) {
			DrawUIElement(*pauseMenu[i], defaultFont);
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}