#include "framework.h"
#include "lslmaker.h"
#include <lsl_cpp.h>
#include <string>
#include <vector>

#define MAX_LOADSTRING 100

// Global variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The text of the title bar
WCHAR szWindowClass[MAX_LOADSTRING];            // the name of the main window class

// Controls
std::vector<HWND> eventEdits;  // Event input fields
std::vector<HWND> eventButtons;  // Buttons for sending events
lsl::stream_outlet* outlet = nullptr;  // LSL stream for sending markers

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Function to create an LSL stream
void CreateLSLStream() {
    lsl::stream_info info("LSLMakerEvent", "Markers", 1, 0, lsl::cf_int32, "myuidw43536");
    outlet = new lsl::stream_outlet(info);
}

// Function to send an event
void SendEvent(int eventIndex) {
    char buffer[256];
    GetWindowTextA(eventEdits[eventIndex], buffer, 256);
    std::string eventText(buffer);

    if (!eventText.empty()) {
        outlet->push_sample(&eventIndex, 1);  // Send the marker
        OutputDebugStringA(("Event '" + eventText + "' sent with marker " + std::to_string(eventIndex + 1) + "\n").c_str());
    }
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LSLMAKER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LSLMAKER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // Release resources
    delete outlet;

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_LSLMAKER));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_LSLMAKER);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves the instance handle and creates the main window
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Save instance handle in a global variable

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // Create controls
        for (int i = 0; i < 5; ++i) {
            // Label for the event
            CreateWindowW(L"STATIC", (L"Event " + std::to_wstring(i + 1) + L":").c_str(),
                WS_VISIBLE | WS_CHILD, 10, 10 + i * 50, 100, 20, hWnd, nullptr, hInst, nullptr);

            // Input field for the event
            HWND hEdit = CreateWindowW(L"EDIT", L"",
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                120, 10 + i * 50, 200, 20, hWnd, nullptr, hInst, nullptr);
            eventEdits.push_back(hEdit);

            // Button for sending the event
            HWND hButton = CreateWindowW(L"BUTTON", L"Send",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                330, 10 + i * 50, 100, 20, hWnd, (HMENU)(100 + i), hInst, nullptr);
            eventButtons.push_back(hButton);
        }

        // Exit button
        CreateWindowW(L"BUTTON", L"Exit",
            WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            120, 260, 100, 30, hWnd, (HMENU)200, hInst, nullptr);

        // Create the LSL stream
        CreateLSLStream();
    }
    break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Handle button clicks
        if (wmId >= 100 && wmId < 105) {
            SendEvent(wmId - 100);  // Send the event
        }
        else if (wmId == 200) {
            // Exit
            DestroyWindow(hWnd);
        }
    }
    break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for the "About" window.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}