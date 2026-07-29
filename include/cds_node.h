#ifndef CDS_NODE_H
#define CDS_NODE_H
#include <stddef.h>
#include <stdalign.h>

typedef struct cds_node cds_node;

typedef struct {
  void *next;
} cds_node_md;

typedef struct {
  void *next;
  void *prev;
} cds_node_md_2;

struct cds_node_pointer {
  cds_node *next;
  void *data;
};

#endif // !CDS_NODE_H
