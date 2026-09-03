#include <iostream>
#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>

#include "gameMain.h"

float DetectLinuxScale()
{
	const char* gdkScale = getenv("GDK_SCALE");
	if (gdkScale) return (float)atof(gdkScale);

	const char* qtScale = getenv("QT_SCALE_FACTOR");
	if (qtScale) return (float)atof(qtScale);

	return 1.0f; // fall back to no scaling
}

int main(void)
{
	#if PRODUCTION_BUILD == 1
		SetTraceLogLevel(LOG_NONE); // Disable logging in production builds
	#endif

	// FLAG_WINDOW_HIGHDPI tells the OS window backend this app is DPI-aware
	SetConfigFlags(FLAG_WINDOW_HIGHDPI |FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
	InitWindow(1920, 1080, "window name");
	SetExitKey(KEY_NULL); // Disable the default exit key (ESC) to prevent accidental closure
	SetTargetFPS(240); // Set a high target FPS for smooth rendering

	float dpiScale = DetectLinuxScale();
	float widgetScale = 3.0f; // Scale ImGui widgets to be larger on high-DPI displays

	// Load the font at a size multiplied by the DPI scale
	const int baseFontSize = 40;
	const int scaledFontSize = (int)(baseFontSize * dpiScale);

	Font roboto = LoadFontEx("resources/Roboto-Regular.ttf", scaledFontSize, nullptr, 0);
	SetTextureFilter(roboto.texture, TEXTURE_FILTER_BILINEAR);

#pragma region imgui	
	rlImGuiSetup(true);
	
	ImGuiIO& io = ImGui::GetIO();
	// io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable keyboard controls
	// io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable gamepad controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable docking
	io.FontGlobalScale = widgetScale; // Scale ImGui's own font rendering to match the display's DPI

	// ImGui::StyleColorsDark();
	// ImGui::StyleColorsLight();
	ImGui::StyleColorsClassic();
#pragma endregion
	
	// Scale all ImGui widget sizes, padding, borders, etc. to match the display's DPI
	ImGuiStyle& style = ImGui::GetStyle();
	style.ScaleAllSizes(widgetScale);

	if (!initGame())
	{
		return 0;
	}

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

	#pragma region imgui
		rlImGuiBegin();

		// docking stuff
		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);
	#pragma endregion

		if (!updateGame(roboto, scaledFontSize))
		{
			CloseWindow();
		}

	#pragma region imgui
		rlImGuiEnd();
	#pragma endregion
		
		EndDrawing();
	}

	CloseWindow();
	UnloadFont(roboto);
	closeGame();

#pragma region imgui
	rlImGuiShutdown();
#pragma endregion

	return 0;
}