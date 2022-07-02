#include <string.h>

typedef unsigned int lay_id;

enum lay_parent {
  /* Direction */
  LAY_ROW        = 0x02,
  LAY_COLUMN     = 0x03,
  /* Model */
  LAY_LAYOUT     = 0x00,
  LAY_FLEX       = 0x02,
  /* Wrap */
  LAY_NOWRAP     = 0x00,
  LAY_WRAP       = 0x04,
  /* Justify */
  LAY_START      = 0x08,
  LAY_MIDDLE     = 0x00,
  LAY_END        = 0x10,
  LAY_BETWEEN    = 0x18,
  /* Mask */
  LAY_PARENTMASK = 0x1f
};

enum lay_child {
  LAY_LEFT      = 0x020,
  LAY_TOP       = 0x040,
  LAY_RIGHT     = 0x080,
  LAY_BOTTOM    = 0x100,
  LAY_HFILL     = 0x0a0,
  LAY_VFILL     = 0x140,
  LAY_HCENTER   = 0x000,
  LAY_VCENTER   = 0x000,
  LAY_CENTER    = 0x000,
  LAY_FILL      = 0x1e0,
  LAY_BREAK     = 0x200,
  LAY_CHILDMASK = 0x3e0
};

struct lay_item {
  enum lay_parent flags;
  lay_id firstchild;
  lay_id nextsibling;
  float margintop;
  float marginright;
  float marginbottom;
  float marginleft;
  float width;
  float height;
};

struct lay_context {
  struct lay_item *items;
  float (*rects)[4];
  lay_id capacity;
  lay_id count;
};

void lay_init(struct lay_context *ctx);
void lay_reserve(struct lay_context *ctx, lay_id count);
void lay_reallocitems(struct lay_context *ctx);
lay_id lay_createitem(struct lay_context *ctx);
void lay_setsize(struct lay_context *ctx, lay_id item, float width, float height);
void lay_getsize(struct lay_context *ctx, lay_id item, float *widthp, float *heightp);
void lay_insert(struct lay_context *ctx, lay_id parent, lay_id child);
void lay_setparentflags(struct lay_context *ctx, lay_id item, enum lay_parent flags);
void lay_setchildflags(struct lay_context *ctx, lay_id item, enum lay_child flags);

void
lay_init(struct lay_context *ctx)
{
  ctx->items = NULL;
  ctx->rects = NULL;
  ctx->capacity = 0;
  ctx->count = 0;
}

void
lay_reserve(struct lay_context *ctx, lay_id count)
{
  if (count >= ctx->capacity) {
    ctx->capacity = count;
    lay_reallocitems(ctx);
  }
}

void
lay_reallocitems(struct lay_context *ctx)
{
  ctx->items = (struct lay_item *)
    realloc(ctx->items, ctx->capacity * (sizeof (struct lay_item) +
                                         sizeof (*ctx->rects)));
  ctx->rects = (float (*)[4]) ctx->items + ctx->capacity;
}

lay_id
lay_createitem(struct lay_context *ctx)
{
  enum { capinit = 32, capmult = 4 };
  lay_id idx = ctx->count++;
  struct lay_item *itemp;
  if (idx >= ctx->capacity) {
    ctx->capacity = ctx->capacity < 1 ? capinit : (ctx->capacity * capmult);
    lay_reallocitems(ctx);
  }
  itemp = &ctx->items[idx];
  memset(itemp, 0, sizeof (struct lay_item));
  itemp->firstchild = -1;        /* TODO: Check if uint max == -1 */
  itemp->nextsibling = -1;
  memset(&ctx->rects[idx], 0, sizeof (*ctx->rects));
  return idx;
}

void
lay_setsize(struct lay_context *ctx, lay_id item, float width, float height)
{
  struct lay_item *itemp = &ctx->items[item];
  itemp->width = width;
  itemp->height = height;
}

void
lay_getsize(struct lay_context *ctx, lay_id item, float *widthp, float *heightp)
{
  struct lay_item *itemp = &ctx->items[item];
  *widthp = itemp->width;
  *heightp = itemp->height;
}

void
lay_insert(struct lay_context *ctx, lay_id parent, lay_id child)
{

}

void
lay_setparentflags(struct lay_context *ctx, lay_id item, enum lay_parent flags)
{
  struct lay_item *itemp = &ctx->items[item];
  itemp->flags = (itemp->flags & ~LAY_PARENTMASK) | flags;
}

void
lay_setchildflags(struct lay_context *ctx, lay_id item, enum lay_child flags)
{
  struct lay_item *itemp = &ctx->items[item];
  itemp->flags = (itemp->flags & ~LAY_CHILDMASK) | flags;
}
