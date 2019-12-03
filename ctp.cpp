#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#include <algorithm>
#include <random>

int TABLE_H = 3;
int TABLE_W = 3;
int TABLE_SIZE = TABLE_W * TABLE_H;
int cell_size = 100;
int n_checks = 2;
int rest_checks = n_checks;
char* table;
char* next_table;


struct ctp : public olc::PixelGameEngine
{
  bool OnUserCreate() override;
  bool OnUserDestroy() override;
  void PuzzleStep();
  bool OnUserUpdate(float fElapsedTime) override;
  bool UpdateGraphics() override;

  bool update_graphics = true;

  void DrawField()
  {
    Clear(olc::BLACK);

    for (int i = 0; i < TABLE_H; ++i)
    {
      for (int j = 0; j < TABLE_W; ++j)
      {
        int y = cell_size * i;
        int x = cell_size * j;
        if (table[j * TABLE_H + i] == 'x')
        {
          DrawLine(x + 5, y + 5, x + cell_size - 5, y + cell_size - 5, olc::RED);
          DrawLine(x + 5, y + 6, x + cell_size - 5, y + cell_size - 4, olc::RED);
          DrawLine(x + cell_size - 5, y + 5, x + 5, y + cell_size - 5, olc::RED);
          DrawLine(x + cell_size - 5, y + 6, x + 5, y + cell_size - 4, olc::RED);
        }
      }
    }
  }

  void Restart()
  {
    for (short i = 0; i < TABLE_SIZE; ++i)
    {
      table[i] = 'x';
    }
  }

  bool Solved()
  {
    if (rest_checks != n_checks)
      return false;
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
      if ('x' == table[i])
      {
        return false;
      }
    }
    return true;
  }

  enum State
  {
    WIN,
    PLAY,
    START
  };

  State state = START;
};

bool ctp::OnUserCreate()
{
  DrawField();
  return true;
}

bool ctp::OnUserDestroy()
{
  return true;
}

void ctp::PuzzleStep()
{
  update_graphics = false;
  if (rest_checks > 0) {
    if (GetMouse(0).bReleased)
    {
      int my = GetMouseX() / cell_size;
      int mx = GetMouseY() / cell_size;
      int mpos = my * TABLE_H + mx;
      if (table[mpos] == 'x')
      {
        table[mpos] = ' ';
        DrawField();
        --rest_checks;
        update_graphics = true;
      }
      for (short i = 0; i < TABLE_SIZE; ++i)
      {
        printf("%c ", table[i] == 'x' ? 'x' : 'o');
      }
      printf("%i ", rest_checks);
      puts("\n");
    }
  }
  else {
    update_graphics = true;
    rest_checks = n_checks;
    for (int k = 0; k < TABLE_SIZE; ++k)
      next_table[k] = ' ';
    for (int i = 0; i < TABLE_H; ++i)
      for (int j = 0; j < TABLE_W; ++j)
      {
        int ind = j * TABLE_H + i;
        if (table[ind] == 'x')
        {
          if (j > 0)
          {
            int up = (j - 1) * TABLE_H + i;
            next_table[up] = 'x';
          }
          if (j + 1 < TABLE_W)
          {
            int down = (j + 1) * TABLE_H + i;
            next_table[down] = 'x';
          }
          if (i > 0)
          {
            int left = j * TABLE_H + (i - 1);
            next_table[left] = 'x';
          }
          if (i + 1 < TABLE_H)
          {
            int right = j * TABLE_H + (i + 1);
            next_table[right] = 'x';
          }
        }
      }
    for (int i = 0; i < TABLE_SIZE; ++i)
      table[i] = next_table[i];
    DrawField();
  }
}

bool ctp::OnUserUpdate(float fElapsedTime)
{
    update_graphics = false;
    if (GetKey(olc::ESCAPE).bReleased)
        return false;
    switch (state)
    {
    case START:
        update_graphics = true;
        state = PLAY;
        break;
    case PLAY:
        PuzzleStep();
        if (Solved())
        {
            state = WIN;
            DrawString(0, 0, "YOU WIN!", {0,180,0}, 3);
            DrawString(2, 2, "YOU WIN!", {0,230,0}, 3);
            update_graphics = true;
        }
        break;
    case WIN:
        if (GetMouse(0).bReleased)
        {
            Restart();
            DrawField();
            state = START;
        }
        break;
    default:
        return false;
    }
    return true;
}

bool ctp::UpdateGraphics()
{
    return update_graphics;
}


int main(int args, char ** argv)
{
  printf("%d\n", args);
  if(args != 1)
  {
    TABLE_W = atoi(argv[1]);
    TABLE_H = atoi(argv[2]);
    n_checks = atoi(argv[3]);

    printf("%s %s %s\n", argv[1], argv[2], argv[3]);
    printf("%d %d %d\n", atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
  }

  printf("%d %d %d\n", TABLE_W, TABLE_H, n_checks);
  TABLE_SIZE = TABLE_W * TABLE_H;
  rest_checks = n_checks;
  table = (char*)malloc(TABLE_SIZE);
  next_table = (char*)malloc(TABLE_SIZE);

  ctp game;
  game.Restart();
  game.Construct(cell_size * TABLE_W, cell_size * TABLE_H + 100, 1, 1, false);
  game.Start();

  free(table);
  free(next_table);

  return 0;
}
