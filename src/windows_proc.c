#include "windows_proc.h"

#include <windowsx.h>
#include <CommCtrl.h>

#include "resource.h"

const int ID_BUTTON = 9000;

void MainWindow_OnClose(HWND hwnd)
{
    DestroyWindow(hwnd);
}

void MainWindow_OnDestroy(HWND hwnd)
{
    PostQuitMessage(0);
}

void MainWindow_OnCommand_Exit(HWND hwnd)
{
    PostQuitMessage(0);
}

void MainWindow_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
    switch(id)
    {
        case IDM_FILE_EXIT:
        {
            MainWindow_OnCommand_Exit(hwnd);
        } break;
    }
}

BOOL MainWindow_InitalizeGrid(HWND hwnd, int cols, int rows)
{
    RECT rect;
    if(!GetClientRect(hwnd, &rect))
    {
        MessageBox(hwnd, L"Failed to get window Rect!", L"Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }
    
    HFONT hFont = CreateFont(24,0,0,0, FW_DONTCARE, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                             CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, NULL);
    
    if(hFont == NULL)
    {
        MessageBox(hwnd, L"Failed to create font!", L"Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }
    
    for(int x = 0; x < cols; x++)
        for(int y = 0; y < rows; y++)
    {
        int button_id = ID_BUTTON + (y * cols  + x);
        
        HWND button_hwnd = CreateWindow(L"BUTTON", L"", 
                                        WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                                        (1+x)*32, (1+y)*32, 32, 32,
                                        hwnd, (HMENU)button_id, (HINSTANCE)GetWindowLongPtr(hwnd, GWLP_HINSTANCE), NULL);
        
        if(button_hwnd == NULL)
        {
            MessageBox(hwnd, L"Failed to create button!", L"Error", MB_OK | MB_ICONERROR);
            return FALSE;
        }
    }
    
    return TRUE;
}

BOOL MainWindow_OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
    HWND hStatus = CreateWindowEx(0, STATUSCLASSNAME, L"",
                                  SBARS_SIZEGRIP | WS_CHILD | WS_VISIBLE,
                                  0, 0, 0, 0,
                                  hwnd, (HMENU)IDC_STATUS, GetModuleHandle(NULL), NULL);
    
    if(hStatus == NULL)
    {
        MessageBox(hwnd, L"Failed to create status bar!", L"Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }
    
    int status_width[] = { 100, -1 };
    SendMessage(hStatus, SB_SETPARTS, sizeof(status_width)/sizeof(int), (LPARAM)status_width);
    
    SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)L"left text here");
    SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM)L"right text here");
    
    BOOL result = MainWindow_InitalizeGrid(hwnd, 10, 15);
    if(!result)
    {
        MessageBox(hwnd, L"Failed to initalize grid!", L"Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }
    
    return TRUE;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hwnd, WM_CLOSE, MainWindow_OnClose);
        HANDLE_MSG(hwnd, WM_DESTROY, MainWindow_OnDestroy);
        HANDLE_MSG(hwnd, WM_COMMAND, MainWindow_OnCommand);
        HANDLE_MSG(hwnd, WM_CREATE, MainWindow_OnCreate);
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}