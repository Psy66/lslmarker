#include "framework.h"
#include "lslmaker.h"
#include <lsl_cpp.h>
#include <string>
#include <vector>

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна

// Элементы управления
std::vector<HWND> eventEdits;  // Поля ввода для событий
std::vector<HWND> eventButtons;  // Кнопки для отправки событий
lsl::stream_outlet* outlet = nullptr;  // LSL-поток для отправки маркеров

// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Функция для создания LSL-потока
void CreateLSLStream() {
    lsl::stream_info info("LSLMakerEvent", "Markers", 1, 0, lsl::cf_int32, "myuidw43536");
    outlet = new lsl::stream_outlet(info);
}

// Функция для отправки события
void SendEvent(int eventIndex) {
    char buffer[256];
    GetWindowTextA(eventEdits[eventIndex], buffer, 256);
    std::string eventText(buffer);

    if (!eventText.empty()) {
        outlet->push_sample(&eventIndex, 1);  // Отправка маркера
        OutputDebugStringA(("Событие '" + eventText + "' отправлено с маркером " + std::to_string(eventIndex + 1) + "\n").c_str());
    }
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_LSLMAKER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_LSLMAKER));

    MSG msg;

    // Цикл основного сообщения:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    // Освобождение ресурсов
    delete outlet;

    return (int)msg.wParam;
}

//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
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
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

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
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        // Создание элементов управления
        for (int i = 0; i < 5; ++i) {
            // Метка для события
            CreateWindowW(L"STATIC", (L"Событие " + std::to_wstring(i + 1) + L":").c_str(),
                WS_VISIBLE | WS_CHILD, 10, 10 + i * 50, 100, 20, hWnd, nullptr, hInst, nullptr);

            // Поле ввода для события
            HWND hEdit = CreateWindowW(L"EDIT", L"",
                WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
                120, 10 + i * 50, 200, 20, hWnd, nullptr, hInst, nullptr);
            eventEdits.push_back(hEdit);

            // Кнопка для отправки события
            HWND hButton = CreateWindowW(L"BUTTON", L"Отправить",
                WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                330, 10 + i * 50, 100, 20, hWnd, (HMENU)(100 + i), hInst, nullptr);
            eventButtons.push_back(hButton);
        }

        // Кнопка выхода
        CreateWindowW(L"BUTTON", L"Выход",
            WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
            120, 260, 100, 30, hWnd, (HMENU)200, hInst, nullptr);

        // Создание LSL-потока
        CreateLSLStream();
    }
    break;

    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Обработка нажатий на кнопки
        if (wmId >= 100 && wmId < 105) {
            SendEvent(wmId - 100);  // Отправка события
        }
        else if (wmId == 200) {
            // Выход
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

// Обработчик сообщений для окна "О программе".
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