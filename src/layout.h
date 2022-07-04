#ifndef LAYOUT_H
#define LAYOUT_H

#define LAY_LENGTH(ARR) sizeof(ARR) / sizeof(ARR[0])

typedef unsigned int lay_id;
#define LAY_INVALID (lay_id)-1

enum lay_parent {
  LAY_ROW        = 0x02,
  LAY_COLUMN     = 0x03,
  LAY_LAYOUT     = 0x00,
  LAY_FLEX       = 0x02,
  LAY_NOWRAP     = 0x00,
  LAY_WRAP       = 0x04,
  LAY_START      = 0x08,
  LAY_MIDDLE     = 0x00,
  LAY_END        = 0x10,
  LAY_BETWEEN    = 0x18
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
  LAY_BREAK     = 0x200
};

enum lay_flags {
  LAY_PARENTMASK = 0x001f,
  LAY_CHILDMASK  = 0x03e0,
  LAY_HFIXED     = 0x0800,
  LAY_VFIXED     = 0x1000,
  LAY_INSERTED   = 0x0400
};

struct lay_item {
  enum lay_flags flags;
  lay_id firstchild;
  lay_id nextsibling;
  int margins[4];
  int size[2];
};

struct lay_context {
  struct lay_item *items;
  int (*rects)[4];
  lay_id capacity;
  lay_id count;
};

void lay_init(struct lay_context *ctx);
void lay_reserve(struct lay_context *ctx, lay_id count);
lay_id lay_createitem(struct lay_context *ctx);
void lay_setsize(struct lay_context *ctx, lay_id item, int width, int height);
void lay_getsize(struct lay_context *ctx, lay_id item, int *widthp, int *heightp);
void lay_insert(struct lay_context *ctx, lay_id parent, lay_id child);
void lay_append(struct lay_context *ctx, lay_id sibling, lay_id later);
void lay_setparentflags(struct lay_context *ctx, lay_id item, enum lay_parent flags);
void lay_setchildflags(struct lay_context *ctx, lay_id item, enum lay_child flags);
void lay_run(struct lay_context *ctx);
void lay_runitem(struct lay_context *ctx, lay_id item);

#endif /* LAYOUT_H */
