#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "cds_error.h"
#include "cds_internal_common.h"
#include "cds_linkedlist.h"

typedef struct {
  void *next;
} node_md;

typedef struct {
  char is_init;
  unsigned int size;
  size_t elem_size;
  size_t elem_align;
  size_t data_offset;
  node_md *head;
  node_md *tail;
} linkedlist;

_Static_assert(sizeof(linkedlist) <= sizeof(cds_linkedlist), "cds_linkedlist must be large enough to contain linkedlist");
_Static_assert(_Alignof(linkedlist) <= _Alignof(cds_linkedlist), "linkedlist alignment must be smaller than cds_linkedlist");

typedef struct {
  linkedlist *ll;
  node_md *curr;
} linkedlist_iterator;

_Static_assert(sizeof(linkedlist_iterator) <= sizeof(cds_linkedlist_iterator), "cds_linkedlist_iterator must be large enough to contain linkedlist_iterator");
_Static_assert(_Alignof(linkedlist_iterator) <= _Alignof(cds_linkedlist_iterator), "linkedlist_iterator alignment must be smaller than cds_linkedlist_iterator");

// Idea. User passes in data, not node. Lib inserts meta data at top of data and uses as a node. Need to think about mallocs.

// Private functions

cds_err alloc_node(linkedlist *ll, node_md **ret_node) {
  void *node;
  size_t size;
  if (ll->elem_align <= sizeof(max_align_t)) {
    size = ll->data_offset + ll->elem_size;
    node = malloc(size);
  } else {
    size = align_up(ll->data_offset + ll->elem_size, ll->elem_align);
    node = aligned_alloc(ll->elem_align, size);
  }
  if (node == NULL) {
    return (errno == EINVAL) ? CDS_ERROR_BAD_ALLOC_INVALID_ALIGN : CDS_ERROR_BAD_ALLOC;
  }
  memset(node, 0, size);
  *ret_node = node;
  return CDS_SUCCESS;
}

static inline void *node_data(linkedlist *ll, node_md *node) {
  return (char *)node + ll->data_offset;
}

static inline void node_set_data(linkedlist *ll, node_md *node, void *src) {
  memcpy(node_data(ll, node), src, ll->elem_size);
}

static inline void node_cpy_data(linkedlist *ll, node_md *node, void *dest) {
  memcpy(dest, node_data(ll, node), ll->elem_size);
}

static inline node_md *node_get_at_index(linkedlist *ll, unsigned int index) {
  unsigned int idx = 0;
  node_md *node = ll->head;
  while (idx++ != index) {
    node = node->next;
  }
  return node;
}

// Public LinkedList functions

cds_err cds_linkedlist_init(cds_linkedlist *ds, size_t elem_size, size_t elem_align) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  ll->elem_size = elem_size;
  ll->elem_align = (alignof(node_md) > elem_align) ? alignof(node_md) : elem_align;
  ll->data_offset = align_up(sizeof(node_md), ll->elem_align);
  ll->size = 0;
  ll->head = NULL;
  ll->tail = NULL;
  ll->is_init = 1;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_free(cds_linkedlist *ds) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  for (node_md *curr = ll->head; curr->next != NULL;) {
    void *next = curr->next;
    free(curr);
    curr = next;
  }
  free(ll->tail);
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_get_iterator(cds_linkedlist *ds, cds_linkedlist_iterator *it) {
  linkedlist *ll = (linkedlist *)ds;
  linkedlist_iterator *llit = (linkedlist_iterator *)it;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  RETURN_IF_DS_NULL(llit);
  llit->curr = ll->head;
  llit->ll = ll;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_insert_tail(cds_linkedlist *ds, void *element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  node_md *node;
  cds_err ret = alloc_node(ll, &node);
  if (ret != CDS_SUCCESS) {
    return ret;
  }
  node_set_data(ll, node, element);
  ll->tail->next = node;
  ll->tail = node;
  ll->size++;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_insert_head(cds_linkedlist *ds, void *element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  node_md *node;
  cds_err ret = alloc_node(ll, &node);
  if (ret != CDS_SUCCESS) {
    return ret;
  }
  node_set_data(ll, node, element);
  node->next = ll->head;
  ll->head = node;
  ll->size++;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_insert_index(cds_linkedlist *ds, unsigned int index, void *element) {
  if (index == 0) {
    return cds_linkedlist_insert_head(ds, element);
  }
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  RETURN_IF_INDEX_OOB(ll, index);
  node_md *prev_node = node_get_at_index(ll, index - 1);
  node_md *node;
  cds_err ret = alloc_node(ll, &node);
  if (ret != CDS_SUCCESS) {
    return ret;
  }
  node_set_data(ll, node, element);
  node->next = prev_node->next;
  prev_node->next = node;
  ll->size++;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_get_head(cds_linkedlist *ds, void **element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  *element = node_data(ll, ll->head);
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_get_tail(cds_linkedlist *ds, void **element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  *element = node_data(ll, ll->tail);
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_get_index(cds_linkedlist *ds, unsigned int index, void **element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  RETURN_IF_INDEX_OOB(ll, index);
  node_md *node = node_get_at_index(ll, index);
  *element = node_data(ll, node);
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_read_head(cds_linkedlist *ds, const void **element) {
  return cds_linkedlist_get_head(ds, element);
}

cds_err cds_linkedlist_read_tail(cds_linkedlist *ds, const void **element) {
  return cds_linkedlist_get_tail(ds, element);
}

cds_err cds_linkedlist_read_index(cds_linkedlist *ds, unsigned int index, const void **element) {
  return cds_linkedlist_get_index(ds, index, element);
}

cds_err cds_linkedlist_set_head(cds_linkedlist *ds, const void *element) {
  const cds_linkedlist_get_head(ds, );
}

cds_err cds_linkedlist_set_tail(cds_linkedlist *ds, const void *element);

cds_err cds_linkedlist_set_index(cds_linkedlist *ds, unsigned int index, const void *element);
