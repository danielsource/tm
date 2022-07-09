#include "layout.h"

struct lay_context *
lay_context(Rectangle root, int count) {
  struct lay_context *ctx = malloc(sizeof (struct lay_context));
  ctx->count = 0;
  ctx->capacity = count;
  ctx->root = root;
  ctx->items = malloc(ctx->capacity * sizeof (struct lay_item));
  return ctx;
}

void
lay_additem(struct lay_context *ctx, enum lay_type type, Rectangle rect, union lay_u this) {
  if (ctx->count >= ctx->capacity) {
    return;
  }
  struct lay_item *item = &ctx->items[ctx->count++];
  item->type = type;
  item->rect = rect;
  item->this = this;
  switch(item->type) {
  case lay_piano:
    item->draw = piano_draw;
    break;
  case lay_guitar:
    item->draw = guitar_draw;
    break;
  case lay_generic: break;
  }
}

void
lay_makelist(struct lay_context *ctx, int gap) {
  Rectangle root = ctx->root;
  int width = 0, height = 0;
  for (int i = 0; i < ctx->count; i++) {
    struct lay_item item = ctx->items[i];
    height += item.rect.height;
    width = MAX(width, item.rect.width);
  }
  height += gap * (ctx->count - 1);
  int x = (root.width / 2) - (width / 2),
    y = (root.height / 2) - (height / 2);
  for (int i = 0; i < ctx->count; i++) {
    struct lay_item *itemp = &ctx->items[i];
    if (!itemp->rect.x) {
      itemp->rect.x = x;
    }
    if (!itemp->rect.y) {
      itemp->rect.y = y;
      y += itemp->rect.height + gap;
    }
  }
}

void
lay_draw(struct lay_context *ctx) {
  for (int i = 0; i < ctx->count; i++) {
    struct lay_item item = ctx->items[i];
    if (item.draw)
      item.draw(&item);
  }
}

void
lay_destroy(struct lay_context *ctx) {
  struct lay_item *items = ctx->items;
  if (ctx)
    free(ctx);
  if (items)
    free(items);
}
