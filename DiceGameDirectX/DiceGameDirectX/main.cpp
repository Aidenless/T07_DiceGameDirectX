#include <windows.h>
#include <string>
#include <cassert>
#include <d3d11.h>
#include <vector>

#include "WindowUtils.h"
#include "game.h"


using namespace std;
using namespace DirectX;
using namespace DirectX::SimpleMath;





//if ALT+ENTER or resize or drag window we might want do
//something like pause the game perhaps, but we definitely
//need to let D3D know what's happened (OnResize_Default).
void OnResize(int screenWidth, int screenHeight, MyD3D& d3d)
{
	d3d.OnResize_Default(screenWidth, screenHeight);
}

//messages come from windows all the time, should we respond to any specific ones?
LRESULT CALLBACK MainWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	//do something game specific here
	switch (msg)
	{
		// Respond to a keyboard event.
	case WM_CHAR:
		switch (wParam)
		{
		case 0x01:
			PostQuitMessage(0);
			break;

		case 0x0D:
			Game::Get().enterPressed = true;
			break;

		default:
			if (wParam == '\b') {
				if (Game::Get().playerInput.size() > 0) {
					Game::Get().playerInput.erase(Game::Get().playerInput.size() - 1, 1);
					Game::Get().gameInfo.erase(Game::Get().gameInfo.size() - 1, 1);
				}
			}
			else {
				Game::Get().input = wParam;
				Game::Get().playerInput += wParam;
			}
		}
	}

	//default message handling (resize window, full screen, etc)
	return WinUtil::DefaultMssgHandler(hwnd, msg, wParam, lParam);
}

//main entry point for the game
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{

	int w(1280), h(720);
	//int defaults[] = { 640,480, 800,600, 1024,768, 1280,1024 };
	//	WinUtil::ChooseRes(w, h, defaults, 4);
	if (!WinUtil::Get().InitMainWindow(w, h, hInstance, "Dice Game", MainWndProc, true))
		assert(false);

	MyD3D d3d;
	if (!d3d.InitDirect3D(OnResize))
		assert(false);
	WinUtil::Get().SetD3D(d3d);
	d3d.GetCache().SetAssetPath("data/");
	Game game(d3d);

	bool canUpdateRender;
	float dTime = 0;


	while (WinUtil::Get().BeginLoop(canUpdateRender))
	{
		if (canUpdateRender && dTime>0)
		{
			game.Update(dTime);
			game.Render(dTime);
		}
		dTime = WinUtil::Get().EndLoop(canUpdateRender);
	}

	game.Release();
	d3d.ReleaseD3D(true);	
	return 0;
}

