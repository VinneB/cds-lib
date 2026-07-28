#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cds_error.h"
#include "cds_internal_common.h"
#include "cds_linkedlist.h"

typedef struct node_md node_md;

// next needs to be the first element in node_md to ensure the iterator casting link to node logic works
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
  node_md **link;
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
  memset(ll, 0, sizeof(linkedlist));
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_get_iterator(cds_linkedlist *ds, cds_linkedlist_iterator *it) {
  linkedlist *ll = (linkedlist *)ds;
  linkedlist_iterator *llit = (linkedlist_iterator *)it;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  RETURN_IF_DS_NULL(llit);
  llit->link = &ll->head;
  llit->ll = ll;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_insert_tail(cds_linkedlist *ds, void *element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  // alloc & set node
  node_md *node;
  cds_err ret = alloc_node(ll, &node);
  if (ret != CDS_SUCCESS) {
    return ret;
  }
  node_set_data(ll, node, element);
  // update tail and update head if applicable
  if (ll->head == NULL) {
    ll->head = node;
    ll->tail = node;
  } else {
    ll->tail->next = node;
    ll->tail = node;
  }
  ll->size++;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_insert_head(cds_linkedlist *ds, void *element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  // alloc & set node
  node_md *node;
  cds_err ret = alloc_node(ll, &node);
  if (ret != CDS_SUCCESS) {
    return ret;
  }
  node_set_data(ll, node, element);
  // update head
  node->next = ll->head;
  ll->head = node;
  // update tail if applicable
  if (ll->tail == NULL) {
    ll->tail = node;
  }
  ll->size++;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_insert_index(cds_linkedlist *ds, unsigned int index, void *element) {
  linkedlist *ll = (linkedlist *)ds;
  if (index == 0) {
    return cds_linkedlist_insert_head(ds, element);
  } else if (index == ll->size) {
    return cds_linkedlist_insert_tail(ds, element);
  }
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
  return cds_linkedlist_get_head(ds, (void **)element);
}

cds_err cds_linkedlist_read_tail(cds_linkedlist *ds, const void **element) {
  return cds_linkedlist_get_tail(ds, (void **)element);
}

cds_err cds_linkedlist_read_index(cds_linkedlist *ds, unsigned int index, const void **element) {
  return cds_linkedlist_get_index(ds, index, (void **)element);
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
  // unlink head
  node_md *del_node = ll->head;
  ll->head = ll->head->next;
  // update tail if applicable
  if (del_node == ll->tail) {
    ll->tail = NULL;
  }
  free(del_node);
  ll->size--;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_delete_tail(cds_linkedlist *ds) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  if (ll->head == ll->tail) {
    free(ll->head);
    ll->head = ll->tail = NULL;
    ll->size--;
    return CDS_SUCCESS;
  }
  // get node before tail
  node_md **link = &ll->head;
  while ((*link)->next != NULL) {
    link = &(*link)->next;
  }
  ll->tail = (node_md *)link;
  free(*link);
  *link = NULL;
  ll->size--;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_delete_index(cds_linkedlist *ds, unsigned int index) {
  linkedlist *ll = (linkedlist *)ds;
  if (index == 0) {
    return cds_linkedlist_delete_head(ds);
  } else if (index == ll->size - 1) {
    return cds_linkedlist_delete_tail(ds);
  }
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  RETURN_IF_INDEX_OOB(ll, index);
  node_md *node = node_get_at_index(ll, index - 1);
  node_md *rem_node = node->next;
  node->next = rem_node->next;
  free(rem_node);
  ll->size--;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_extract_head(cds_linkedlist *ds, void *element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  // extract value
  memcpy(element, node_data(ll, ll->head), ll->elem_size);
  // unlink head
  node_md *del_node = ll->head;
  ll->head = ll->head->next;
  // update tail if applicable
  if (del_node == ll->tail) {
    ll->tail = NULL;
  }
  free(del_node);
  ll->size--;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_extract_tail(cds_linkedlist *ds, void *element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  // extract value
  memcpy(element, node_data(ll, ll->tail), ll->elem_size);
  // if only one elem
  if (ll->head == ll->tail) {
    free(ll->head);
    ll->head = ll->tail = NULL;
    ll->size--;
    return CDS_SUCCESS;
  }
  // get node before tail
  node_md **link = &ll->head;
  while ((*link)->next != NULL) {
    link = &(*link)->next;
  }
  // unlink tail
  ll->tail = (node_md *)link;
  free(*link);
  *link = NULL;
  ll->size--;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_extract_index(cds_linkedlist *ds, unsigned int index, void *element) {
  linkedlist *ll = (linkedlist *)ds;
  if (index == 0) {
    return cds_linkedlist_extract_head(ds, element);
  } else if (index == ll->size - 1) {
    return cds_linkedlist_extract_tail(ds, element);
  }
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  RETURN_IF_INDEX_OOB(ll, index);
  node_md *node = node_get_at_index(ll, index - 1);
  node_md *rem_node = node->next;
  memcpy(element, node_data(ll, rem_node), ll->elem_size);
  node->next = rem_node->next;
  free(rem_node);
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
  RETURN_IF_END_LINK_ITERATOR(lli);
  lli->link = &((*lli->link)->next);
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_iterator_get_curr(cds_linkedlist_iterator *ds, void **element) {
  linkedlist_iterator *lli = (linkedlist_iterator *)ds;
  RETURN_IF_DS_NULL(lli);
  RETURN_IF_DS_NULL(lli->ll);
  RETURN_IF_DS_NOT_INIT(lli->ll);
  RETURN_IF_END_LINK_ITERATOR(lli);
  *element = node_data(lli->ll, *lli->link);
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_iterator_set_curr(cds_linkedlist_iterator *ds, void *element) {
  linkedlist_iterator *lli = (linkedlist_iterator *)ds;
  RETURN_IF_DS_NULL(lli);
  RETURN_IF_DS_NULL(lli->ll);
  RETURN_IF_DS_NOT_INIT(lli->ll);
  RETURN_IF_END_LINK_ITERATOR(lli);
  memcpy(node_data(lli->ll, *lli->link), element, lli->ll->elem_size);
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_iterator_read_curr(cds_linkedlist_iterator *ds, const void **element) {
  return cds_linkedlist_iterator_get_curr(ds, (void **)element);
}

cds_err cds_linkedlist_iterator_cpy_curr(cds_linkedlist_iterator *ds, void *element) {
  linkedlist_iterator *lli = (linkedlist_iterator *)ds;
  RETURN_IF_DS_NULL(lli);
  RETURN_IF_DS_NULL(lli->ll);
  RETURN_IF_DS_NOT_INIT(lli->ll);
  RETURN_IF_END_LINK_ITERATOR(lli);
  memcpy(element, node_data(lli->ll, *lli->link), lli->ll->elem_size);
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_iterator_extract_curr(cds_linkedlist_iterator *ds, void *element) {
  linkedlist_iterator *lli = (linkedlist_iterator *)ds;
  RETURN_IF_DS_NULL(lli);
  RETURN_IF_DS_NULL(lli->ll);
  RETURN_IF_DS_NOT_INIT(lli->ll);
  RETURN_IF_END_LINK_ITERATOR(lli);
  node_md *node = *lli->link;
  memcpy(element, node_data(lli->ll, node), lli->ll->elem_size);
  *lli->link = node->next;
  if (node == lli->ll->tail) {
    if (lli->link == &lli->ll->head) {
      lli->ll->tail = NULL;
    } else {
      lli->ll->tail = (node_md *)lli->link;
    }
  }
  free(node);
  lli->ll->size--;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_iterator_delete_curr(cds_linkedlist_iterator *ds) {
  linkedlist_iterator *lli = (linkedlist_iterator *)ds;
  RETURN_IF_DS_NULL(lli);
  RETURN_IF_DS_NULL(lli->ll);
  RETURN_IF_DS_NOT_INIT(lli->ll);
  RETURN_IF_END_LINK_ITERATOR(lli);
  node_md *node = *lli->link;
  *lli->link = node->next;
  if (node == lli->ll->tail) {
    if (lli->link == &lli->ll->head) {
      lli->ll->tail = NULL;
    } else {
      lli->ll->tail = (node_md *)lli->link;
    }
  }
  free(node);
  lli->ll->size--;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_iterator_insert(cds_linkedlist_iterator *ds, void *element) {
  linkedlist_iterator *lli = (linkedlist_iterator *)ds;
  RETURN_IF_DS_NULL(lli);
  RETURN_IF_DS_NULL(lli->ll);
  RETURN_IF_DS_NOT_INIT(lli->ll);
  node_md *node;
  cds_err ret = alloc_node(lli->ll, &node);
  if (ret != CDS_SUCCESS) {
    return ret;
  }
  node_set_data(lli->ll, node, element);
  if ((node_md *)lli->link == lli->ll->tail) {
    lli->ll->tail = node;
  }
  node->next = *lli->link;
  *lli->link = node;
  lli->ll->size++;
  return CDS_SUCCESS;
}

cds_err cds_linkedlist_iterator_is_at_end(cds_linkedlist_iterator *ds) {
  linkedlist_iterator *lli = (linkedlist_iterator *)ds;
  RETURN_IF_DS_NULL(lli);
  RETURN_IF_DS_NULL(lli->ll);
  RETURN_IF_DS_NOT_INIT(lli->ll);
  return (*lli->link == NULL) ? CDS_ERROR_ITER_END : CDS_SUCCESS;
}
