#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "cds_error.h"
#include "cds_internal_common.h"
#include "cds_linkedlist.h"

typedef struct node_md node_md;

struct node_md {
  node_md *next;
};

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
  unsigned char is_on_curr;
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
  llit->is_on_curr = 1;
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
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  void *data = node_data(ll, ll->head);
  memcpy(data, element, ll->elem_size);
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_set_tail(cds_linkedlist *ds, const void *element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  void *data = node_data(ll, ll->tail);
  memcpy(data, element, ll->elem_size);
  return CDS_SUCCESS;
}
cds_err cds_linkedlist_set_index(cds_linkedlist *ds, unsigned int index, const void *element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  RETURN_IF_INDEX_OOB(ll, index);
  node_md *node = node_get_at_index(ll, index);
  void *data = node_data(ll, node);
  memcpy(data, element, ll->elem_size);
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_cpy_head(cds_linkedlist *ds, void *element_cpy) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  memcpy(element_cpy, node_data(ll, ll->head), ll->elem_size);
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_cpy_tail(cds_linkedlist *ds, void *element_cpy) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  memcpy(element_cpy, node_data(ll, ll->tail), ll->elem_size);
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_cpy_index(cds_linkedlist *ds, unsigned int index, void *element_cpy) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  node_md *node = node_get_at_index(ll, index);
  memcpy(element_cpy, node_data(ll, node), ll->elem_size);
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_delete_head(cds_linkedlist *ds) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  node_md *del_node = ll->head;
  ll->head = ll->head->next;
  free(del_node);
  ll->size--;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_delete_tail(cds_linkedlist *ds) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  node_md *node = ll->head;
  while (node->next->next != NULL) {
    node = node->next;
  }
  ll->tail = node->next;
  free(node->next);
  node->next = NULL;
  ll->size--;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_delete_index(cds_linkedlist *ds, unsigned int index) {
  if (index == 0) {
    return cds_linkedlist_delete_head(ds);
  }
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  RETURN_IF_INDEX_OOB(ll, index);
  node_md *node = ll->head;
  unsigned int idx = 0;
  while (idx++ != index - 1) {
    node = node->next;
  }
  node_md *next_node = node->next->next;
  free(node->next);
  node->next = next_node;
  ll->size--;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_extract_head(cds_linkedlist *ds, void *element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  memcpy(element, node_data(ll, ll->head), ll->elem_size);
  node_md *node = ll->head;
  ll->head = ll->head->next;
  free(node);
  ll->size--;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_extract_tail(cds_linkedlist *ds, void *element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  node_md *node = ll->head;
  while (node->next->next != NULL) {
    node = node->next;
  }
  ll->tail = node->next;
  memcpy(element, node_data(ll, node->next), ll->elem_size);
  free(node->next);
  node->next = NULL;
  ll->size--;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_extract_index(cds_linkedlist *ds, unsigned int index, void *element) {
  if (index == 0) {
    return cds_linkedlist_extract_head(ds, element);
  }
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  RETURN_IF_INDEX_OOB(ll, index);
  node_md *node = ll->head;
  unsigned int idx = 0;
  while (idx++ != index - 1) {
    node = node->next;
  }
  node_md *next_node = node->next->next;
  memcpy(element, node->next, ll->elem_size);
  free(node->next);
  node->next = next_node;
  ll->size--;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_size(cds_linkedlist *ds, unsigned int *return_size) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  *return_size = ll->size;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_iterator_next(cds_linkedlist_iterator *ds) {
  linkedlist_iterator *lli = (linkedlist_iterator *)ds;
  RETURN_IF_DS_NULL(lli);
  RETURN_IF_DS_NULL(lli->ll);
  RETURN_IF_DS_NOT_INIT(lli->ll);
  if (lli->is_on_curr) {
    lli->is_on_curr = 0;
  } else if (lli->curr->next == NULL || lli->curr->next->next == NULL) {
    return CDS_ERROR_END_OF_LIST;
  } else {
    lli->curr = lli->curr->next;
  }
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_iterator_get_curr(cds_linkedlist_iterator *ds, void **element) {
  linkedlist_iterator *lli = (linkedlist_iterator *)ds;
  RETURN_IF_DS_NULL(lli);
  RETURN_IF_DS_NULL(lli->ll);
  RETURN_IF_DS_NOT_INIT(lli->ll);
  node_md *node = (lli->is_on_curr) ? lli->curr : lli->curr->next;
  *element = node_data(lli->ll, node);
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_iterator_set_curr(cds_linkedlist_iterator *ds, void *element) {
  linkedlist_iterator *lli = (linkedlist_iterator *)ds;
  RETURN_IF_DS_NULL(lli);
  RETURN_IF_DS_NULL(lli->ll);
  RETURN_IF_DS_NOT_INIT(lli->ll);
  node_md *node = (lli->is_on_curr == 0) ? lli->curr->next : lli->curr;
  memcpy(node_data(lli->ll, node), element, lli->ll->elem_size);
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_iterator_read_curr(cds_linkedlist_iterator *ds, const void **element) {
  return cds_linkedlist_iterator_get_curr(ds, element);
}

cds_err cds_linkedlist_iterator_cpy_curr(cds_linkedlist_iterator *ds, void *element) {
  linkedlist_iterator *lli = (linkedlist_iterator *)ds;
  RETURN_IF_DS_NULL(lli);
  RETURN_IF_DS_NULL(lli->ll);
  RETURN_IF_DS_NOT_INIT(lli->ll);
  node_md *node = (lli->is_on_curr) ? lli->curr : lli->curr->next;
  memcpy(element, node_data(lli->ll, node), lli->ll->elem_size);
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_iterator_extract_curr(cds_linkedlist_iterator *ds, void *element) {
  linkedlist_iterator *lli = (linkedlist_iterator *)ds;
  RETURN_IF_DS_NULL(lli);
  RETURN_IF_DS_NULL(lli->ll);
  RETURN_IF_DS_NOT_INIT(lli->ll);
}

cds_err cds_linkedlist_iterator_delete_curr(cds_linkedlist_iterator *ds) {
  linkedlist_iterator *lli = (linkedlist_iterator *)ds;
  RETURN_IF_DS_NULL(lli);
  RETURN_IF_DS_NULL(lli->ll);
  RETURN_IF_DS_NOT_INIT(lli->ll);
  if () {
    return
  }
}

cds_err cds_linkedlist_iterator_insert_after(cds_linkedlist_iterator *ds, void *data);
