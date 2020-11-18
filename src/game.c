#include "game.h"

#include <windows.h>

int* g_tiles;

void InitMines(int x, int y)
{
    int mines = g_numMines;
    
    while(mines > 0)
    {
        int rx = rand() % g_gridColumns;
        int ry = rand() % g_gridRows;
        
        if(g_tiles[ry * g_gridColumns + rx] == 0 && rx != x && ry != y)
        {
            g_tiles[ry * g_gridColumns + rx] = MINE;
            mines--;
        }
    }
}

void InitGame(int cols, int rows, int mines)
{
    g_gridColumns = cols;
    g_gridRows = rows;
    g_numMines = mines;
    
    CleanUp();
    
    g_tiles = GlobalAlloc(GPTR, sizeof(int) * g_gridRows * g_gridColumns);
    
    InitMines(0, 0);
}

void CleanUp()
{
    if(g_tiles)
    {
        GlobalFree(g_tiles);
    }
}

TILE_STATE CheckTileState(int x, int y)
{
    if(!g_tiles)
    {
        MessageBox(NULL, L"Board not initalized!", L"Error", MB_OK | MB_ICONERROR);
        return UNCHECKED;
    }
    
    TILE_STATE result = g_tiles[y * g_gridColumns + x];
    if(result == MINE)
    {
        g_tiles[y * g_gridColumns + x] = EXPLODE;
        return EXPLODE;
    }
    return CLEAR;
}

TILE_STATE GetTileState(int x, int y)
{
    if(!g_tiles)
    {
        MessageBox(NULL, L"Board not initalized!", L"Error", MB_OK | MB_ICONERROR);
        return UNCHECKED;
    }
    
    TILE_STATE result = g_tiles[y * g_gridColumns + x];
    return result;
}