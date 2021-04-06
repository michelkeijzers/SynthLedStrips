// Window.cpp
// Only for Windows.

#ifdef _WINDOWS


#include <cmath>
#include <string>
#include <math.h>

#include "Resource.h"
#include "Time.h"
#include "framework.h"
#include "ClassNames.h"
#include HEADER_FILE(MIDI_CLASS)
#include "MidiInjection.h"
#include "SynthLedStrips.h"
#include "FastLedStub.h"

using namespace std;

constexpr auto MAX_LOADSTRING = 100;
constexpr auto PAR_DISTANCE_X = 100;
constexpr auto PAR_DISTANCE_Y = 180;
#define PAR_DIAMETER	     (PAR_DISTANCE_X - 3)
#define PAR_RADIUS			 (PAR_DIAMETER / 2)
#define LED_DIAMETER		 (PAR_DIAMETER / 4 - 12)
#define LED_RADIUS			 (LED_DIAMETER / 2)
constexpr auto TEXT_OFFSET_X = -30;
constexpr auto TEXT_OFFSET_Y = -100;
constexpr auto FIXTURE_OFFSET_X = -10;
constexpr auto FIXTURE_OFFSET_Y = -80;
constexpr auto RGB_DISTANCE = 0.4;
constexpr auto WHITE_DISTANCE = 0.15;

#define FONT_SIZE             11

#define PI_F                   3.14159265358979f

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

int _refreshCounter;
bool _backgroundPainted = false;
bool _backgroundFixturePaint = false;

// Forward declarations of functions included in this code module:
void ArduinoAppSetup();
void ArduinoAppLoop(MSG& msg);

void CalcCenter(int degrees, int centerX, int centerY, int distance, int* outputX, int* outputY);

ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	_refreshCounter = 0;

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SYNTHLEDSTRIPS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SYNTHLEDSTRIPS));

	MSG msg;

	ArduinoAppSetup();

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			ArduinoAppLoop(msg);
		}
	}

	return int(msg.wParam);
}


//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style          = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SYNTHLEDSTRIPS));
	wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground  = HBRUSH(COLOR_WINDOW+1);
	wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SYNTHLEDSTRIPS);
	wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}


//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		50, 50, 1200, 700, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return INT_PTR(TRUE);

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return INT_PTR(TRUE);
		}
		break;
	}
	return INT_PTR(FALSE);
}


//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_COMMAND:
	{
		int wmId = LOWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	}

	case WM_PAINT:
	{
		PAINTSTRUCT ps;
		HDC hdc = BeginPaint(hWnd, &ps);

		if (CFastLED::IsShowEnabled())
		{
			int nrOfLedStrips = CFastLED::GetNrOfLedStrips();

			SetDCBrushColor(hdc, 0);
			int ledHeight = 50;

			for (int ledStrip = 0; ledStrip < nrOfLedStrips; ledStrip++)
			{
				int nrOfUsedLeds = CFastLED::GetNrOfUsedLeds(ledStrip);
				int ledWidth = 1100 / nrOfUsedLeds;
				for (int led = 0; led < nrOfUsedLeds; led++)
				{
					struct FastLedCRGB rgb = CFastLED::GetData(ledStrip)[led];
					DWORD color = (rgb.blue << 16) + (rgb.green << 8) + rgb.red;
					COLORREF oldcr = SetBkColor(hdc, color);
					int x1 = 50 +  led      * ledWidth;
					int y1 = 50 +  ledStrip * ledHeight;
					int x2 = 50 + (led + 1) * ledWidth;
					int y2 = 50 + (ledStrip + 1) * ledHeight;

					RECT rect = { x1, y1, x2, y2 };
					ExtTextOut(hdc, 0, 0, ETO_OPAQUE, &rect, LPCWSTR(NULL), 0, 0);
				}
			}
		}

		if (_backgroundFixturePaint)
		{
			_backgroundPainted = true;
		}

		EndPaint(hWnd, &ps);
		break;
	}

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	case WM_MOUSEMOVE:
	case WM_NCMOUSEMOVE:
	case WM_SETCURSOR:
	case WM_NCHITTEST:
	case WM_MOUSELEAVE:
	case WM_NCMOUSELEAVE:
		// Ignore
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}


void CalcCenter(int degrees, int centerX, int centerY, int distance, int* outputX, int* outputY)
{
	*outputX = centerX + int(sin(degrees / 180.0f * PI_F) * distance);
	*outputY = centerY + int(cos(degrees / 180.0f * PI_F) * distance);
}


MidiInjection _midiInjection;


void ArduinoAppSetup()
{
	SynthLedStrips::Setup();

	_midiInjection.Add(1000, midiB, midi::MidiType::NoteOn, 50, 127);
	_midiInjection.Add(1000, midiB, midi::MidiType::NoteOn, 55, 127);
	_midiInjection.Add(5000, midiB, midi::MidiType::NoteOff, 50, 127);
	_midiInjection.Add(5000, midiB, midi::MidiType::NoteOff, 55, 127);
}


void ArduinoAppLoop(MSG& msg)
{
	_midiInjection.Inject(_refreshCounter);
	SynthLedStrips::Loop();
	_refreshCounter++;

	// Handle
	InvalidateRect(msg.hwnd, nullptr, FALSE);
}

#endif // _WINDOWS
