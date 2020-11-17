#include "windows_proc.h"

#include <windowsx.h>

#include "resource.h"

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

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hwnd, WM_CLOSE, MainWindow_OnClose);
        HANDLE_MSG(hwnd, WM_DESTROY, MainWindow_OnDestroy);
        HANDLE_MSG(hwnd, WM_COMMAND, MainWindow_OnCommand);
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}