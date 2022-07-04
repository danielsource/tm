#include <stdlib.h>
#include <string.h>

#include "layout.h"

static void lay_reallocitems(struct lay_context *ctx);
static void lay_appendp(struct lay_item *siblingp, lay_id child, struct lay_item *childp);
static void lay_calcsize(struct lay_context *ctx, lay_id item, int dim);
static void lay_arrange(struct lay_context *ctx, lay_id item, int dim);

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
  ctx->rects = (int (*)[4]) &ctx->items[ctx->capacity];
}

lay_id
lay_createitem(struct lay_context *ctx)
{
  enum { capinit = 32, capmult = 4 };
  lay_id item = ctx->count++;
  struct lay_item *itemp;
  if (item >= ctx->capacity) {
    ctx->capacity = ctx->capacity < 1 ? capinit : (ctx->capacity * capmult);
    lay_reallocitems(ctx);
  }
  itemp = &ctx->items[item];
  memset(itemp, 0, sizeof (struct lay_item));
  itemp->firstchild = LAY_INVALID;
  itemp->nextsibling = LAY_INVALID;
  memset(&ctx->rects[item], 0, sizeof (*ctx->rects));
  return item;
}

void
lay_setsize(struct lay_context *ctx, lay_id item, int width, int height)
{
  struct lay_item *itemp = &ctx->items[item];
  itemp->size[0] = width;
  itemp->size[1] = height;
  if (width == 0)
    itemp->flags &= ~LAY_HFIXED;
  else
    itemp->flags |= LAY_HFIXED;
  if (height == 0)
    itemp->flags &= ~LAY_VFIXED;
  else
    itemp->flags |= LAY_VFIXED;
}

void
lay_getsize(struct lay_context *ctx, lay_id item, int *widthp, int *heightp)
{
  struct lay_item *itemp = &ctx->items[item];
  *widthp = itemp->size[0];
  *heightp = itemp->size[1];
}

void
lay_insert(struct lay_context *ctx, lay_id parent, lay_id child)
{
  struct lay_item *parentp = &ctx->items[parent];
  struct lay_item *childp = &ctx->items[child];
  struct lay_item *siblingp;
  lay_id sibling;
  if (parentp->firstchild == LAY_INVALID) {
    parentp->firstchild = child;
    childp->flags |= LAY_INSERTED;
    return;
  }
  for (sibling = parentp->firstchild; sibling != LAY_INVALID;) {
    siblingp = &ctx->items[sibling];
    sibling = siblingp->nextsibling;
  }
  lay_appendp(siblingp, child, childp);
}

void
lay_appendp(struct lay_item *siblingp, lay_id child, struct lay_item *childp)
{
  childp->nextsibling = siblingp->nextsibling;
  childp->flags |= LAY_INSERTED;
  siblingp->nextsibling = child;
}

void
lay_append(struct lay_context *ctx, lay_id sibling, lay_id child)
{
  struct lay_item *siblingp = &ctx->items[sibling];
  struct lay_item *childp = &ctx->items[child];
  lay_appendp(siblingp, child, childp);
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

void
lay_run(struct lay_context *ctx)
{
  if (ctx->count > 0)
    lay_runitem(ctx, 0);
}

void
lay_runitem(struct lay_context *ctx, lay_id item)
{
  lay_calcsize(ctx, item, 0);
  lay_arrange(ctx, item, 0);
  lay_calcsize(ctx, item, 1);
  lay_arrange(ctx, item, 1);
}

void
lay_calcsize(struct lay_context *ctx, lay_id item, int dim)
{
  struct lay_item *itemp = &ctx->items[item];
  struct lay_item *childp;
  lay_id child;
  int sz;
  for (child = itemp->firstchild; child != LAY_INVALID;) {
    lay_calcsize(ctx, child, dim); /* NOTE: RECURSION */
    childp = &ctx->items[item];
    child = childp->nextsibling;
  }
  ctx->rects[item][dim] = itemp->margins[dim];
  if (itemp->size[dim] != 0) {
    ctx->rects[item][2 + dim] = itemp->size[dim];
    return;
  }
}

void
lay_arrange(struct lay_context *ctx, lay_id item, int dim)
{

}
