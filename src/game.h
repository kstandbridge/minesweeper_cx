extern int g_gridColumns;
extern int g_gridRows;
extern int g_numMines;
extern int g_tilesToCheck;

typedef enum
{
    UNCHECKED = -1,
    
    CLEAR = 0,
    
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,
    SIX = 6,
    SEVEN = 7,
    EIGHT = 8,
    NINE = 9,
    
    MINE = 10,
    EXPLODE = 11,
    FLAGGED_CORRECT = 12,
    FLAGGED_INCORRECT = 13
} TILE_STATE;

void InitGame();
void CleanUp();

TILE_STATE CheckTileState(int x, int y);
TILE_STATE GetTileState(int x, int y);

