#include "main.h"

int main(void) {
  init();
  while (Ctx.flags & RUNNING) {
    update();
    draw();
  }
  return quit(0);
}

void init(void) {
  Ctx.screen = (struct screen) { 640, 480 };
  Ctx.flags = RUNNING;
  InitWindow(Ctx.screen.width, Ctx.screen.height, PROGRAM_NAME);
}

void update(void) {
  if (WindowShouldClose())
    Ctx.flags &= ~RUNNING;
}

void draw(void) {
  BeginDrawing(); {
    ClearBackground(RAYWHITE);
    DrawText("Congrats! You created your first window!",
             Ctx.screen.width/2 - 210, Ctx.screen.height/2 - 10, 20, LIGHTGRAY);
  } EndDrawing();
}

int quit(int exitcode) {
  CloseWindow();
  return exitcode;
}
