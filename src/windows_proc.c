#include "windows_proc.h"

#include <windowsx.h>

void MainWindow_OnClose(HWND hwnd)
{
    DestroyWindow(hwnd);
}

void MainWindow_OnDestroy(HWND hwnd)
{
    PostQuitMessage(0);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch(uMsg)
    {
        HANDLE_MSG(hwnd, WM_CLOSE, MainWindow_OnClose);
        HANDLE_MSG(hwnd, WM_DESTROY, MainWindow_OnDestroy);
    }
    
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}