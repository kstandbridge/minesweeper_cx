#include "game.h"

#include <windows.h>

int g_gridColumns = 10;
int g_gridRows = 15;
int g_numMines = 10;
int g_tilesToCheck = 0;
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

void InitGame()
{
    CleanUp();
    
    g_tiles = GlobalAlloc(GPTR, sizeof(int) * g_gridRows * g_gridColumns);
    
    InitMines(0, 0);
    g_tilesToCheck = g_gridColumns * g_gridRows - g_numMines;
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
    
    g_tilesToCheck--;
    
    TILE_STATE result = g_tiles[y * g_gridColumns + x];
    if(result == MINE)
    {
        g_tiles[y * g_gridColumns + x] = EXPLODE;
        return EXPLODE;
    }
    
    int mines = 0;
    for(int i = -1; i < 2; i++)
    {
        for(int j = -1; j < 2; j++)
        {
            if(x + i >= 0 && x + i < g_gridColumns && y + j >= 0 && y + j < g_gridRows)
            {
                if(g_tiles[(y + j) * g_gridColumns + (x + i)] == MINE)
                {
                    mines++;
                }
            }
        }
    }
    if(mines == 0)
    {
        g_tiles[y * g_gridColumns + x] = CLEAR;
        return CLEAR;
    }
    if(mines > 0 && mines < 10)
    {
        g_tiles[y * g_gridColumns + x] = mines;
        return mines;
    }
    else
    {
        MessageBox(NULL, L"Strange we hit this", L"Error", MB_OK);
    }
    
    return UNCHECKED;
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