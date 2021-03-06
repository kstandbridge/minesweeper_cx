#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' ""version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

#include <windows.h>

#include "resource.h"
#include "windows_proc.h"


int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
    // Register the window class.
    wchar_t CLASS_NAME[]  = L"Minesweeper_cx";
    
    WNDCLASS wc = {0};
    
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.lpszMenuName  = MAKEINTRESOURCE(IDR_MENU);
    
    RegisterClass(&wc);
    
    // Create the window.
    
    HWND hwnd = CreateWindowEx(
                               0,                    // Optional window styles.
                               CLASS_NAME,           // Window class
                               L"Minesweeper",       // Window text
                               WS_OVERLAPPEDWINDOW,  // Window style
                               
                               // Size and position
                               CW_USEDEFAULT, CW_USEDEFAULT, 480, 640,
                               
                               NULL,       // Parent window    
                               NULL,       // Menu
                               hInstance,  // Instance handle
                               NULL        // Additional application data
                               );
    
    if (hwnd == NULL)
    {
        return 0;
    }
    
    ShowWindow(hwnd, nCmdShow);
    
    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return msg.wParam;
}