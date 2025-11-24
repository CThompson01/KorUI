#include <stdio.h>
#include "raylib.h"
#include "../korui/korui.h"

#define NORMAL_UI_NUM 4

int g_closeGame = 0;
int g_test_score = 0;
int g_paused = 0;
int g_event_changeScrollSelector = 0;

int defaultCallback() {
	printf("Hello World!\n");
	return 0;
}

int incrementScoreCallback() {
	g_test_score++;
	return 0;
}

int changeScrollSelectorCallback() {
	g_event_changeScrollSelector = 1;
	return 0;
}

int pauseCallback() {
	g_paused = 1;
	return 0;
}

int resumeCallback() {
	g_paused = 0;
	return 0;
}

int exitCallback() {
	g_closeGame = 1;
	return 0;
}

int main() {
	// Window Setup
	SetConfigFlags(FLAG_VSYNC_HINT);
	InitWindow(854, 480, "KorUI Test Environment");
	SetTargetFPS(60);
	SetExitKey(KEY_P);

	// UI Setup
	Font defaultFont = LoadFontEx("resources/fonts/arial.ttf", 96, 0, 0);

	// Regular Display
	UIElement scoreDisplay;
	UIElement scoreIncrementer;
	UIElement pauseButton;
	UIElement randomScrollSelector;
	InitializeNumberLabelElement(&scoreDisplay, "score_display", "Score: ", &g_test_score, 0, 0, 200, 25);
	InitializeButtonElement(&scoreIncrementer, "scoreincrement_button", "Increment Score", 0, 30, 200, 25,
		&incrementScoreCallback);
	InitializeButtonElement(&pauseButton, "pause_button", "Pause", 0, 60, 100, 25, &pauseCallback);
	char *randomSelectorOptions[] = {"Test 1", "Test 2", "Test 3", "Test 4", "Test 5"};
	char *randomSelectorAltOptions[] = {"Alt 1", "Alt 2", "Alt 3", "Alt 4", "Alt 5", "Alt 6"};
	InitializeScrollSelectorElement(&randomScrollSelector, "random_scrollselector", "Random Test Selector",
		randomSelectorOptions, 5, 100, 90);
	UIElement *normalUI[NORMAL_UI_NUM] = {
		&scoreDisplay,
		&scoreIncrementer,
		&pauseButton,
		&randomScrollSelector
	};
	// AutoLayout(normalUI, NORMAL_UI_NUM,
	// 	(LayoutStyle) {CENTERED, CENTERED, VERTICAL},
	// 	(LayoutDetails) {0, 0, 854, 480}, 5);

	// Pause Menu
	UIElement resumeButton;
	InitializeButtonElement(&resumeButton, "resume_button", "Resume", 0, 0, 100, 25, &resumeCallback);
	UIElement optionsButton;
	InitializeButtonElement(&optionsButton, "options_button", "Options", 0, 0, 100, 25, &changeScrollSelectorCallback);
	UIElement exitButton;
	InitializeButtonElement(&exitButton, "exit_button", "Exit", 0, 0, 100, 25, &exitCallback);
	UIElement *pauseMenu[3] = {
		&resumeButton,
		&optionsButton,
		&exitButton
	};
	AutoLayout(pauseMenu, 3,
		(LayoutStyle) {CENTERED, CENTERED, VERTICAL},
		(LayoutDetails) {0, 0, 854, 480}, 5);

	// Start main game loop
	while (!WindowShouldClose() && !g_closeGame) {
		// Input
		int mx = GetMouseX();
		int my = GetMouseY();
		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			printf("Mouse Button Pressed\n");
			if (g_paused) {
				for (int i = 0; i < 3; i++) {
					CheckUIElementPressed(pauseMenu[i], mx, my);
				}
			} else {
				for (int i = 0; i < NORMAL_UI_NUM; i++) {
					CheckUIElementPressed(normalUI[i], mx, my);
				}
			}
		} else if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
			printf("Mouse Button Released\n");
			if (g_paused) {
				for (int i = 0; i < 3; i++) {
					CheckUIElementReleased(pauseMenu[i], mx, my);
				}
			} else {
				for (int i = 0; i < NORMAL_UI_NUM; i++) {
					CheckUIElementReleased(normalUI[i], mx, my);
				}
			}
		}

		// Update
		if (g_event_changeScrollSelector) {
			randomScrollSelector.element.scrollSelector = ChangeScrollSelectorOptions((randomScrollSelector.element.scrollSelector), randomSelectorAltOptions, 6);
			g_event_changeScrollSelector = 0;
		}

		// Render
		BeginDrawing();
		ClearBackground(DARKBLUE);

		for (int i = 0; i < NORMAL_UI_NUM; i++) {
			DrawUIElement(*normalUI[i], defaultFont);
		}

		if (g_paused) {
			for (int i = 0; i < 3; i++) {
				DrawUIElement(*pauseMenu[i], defaultFont);
			}
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}