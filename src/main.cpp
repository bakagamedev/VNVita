#include "common.h"

int main(int argc, char *argv[]) 
{
  GameMain game;
  if(game.StatusCode != ErrorType::OK)
    return -1;

  game.GameTick();
}