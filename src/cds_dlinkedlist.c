#include "cds_dlinkedlist.h"
#include "cds_error.h"
#include "cds_internal_common.h"
#include <errno.h>
#include <stdlib.h>
#include <string.h>

// data model

typedef struct node_md node_md;

// next needs to be the first element in node_md to ensure the iterator casting link to node logic works
struct node_md {
  node_md *next;
  node_md *prev;
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

_Static_assert(sizeof(linkedlist) <= sizeof(cds_dlinkedlist), "cds_linkedlist must be large enough to contain linkedlist");
_Static_assert(_Alignof(linkedlist) <= _Alignof(cds_dlinkedlist), "linkedlist alignment must be smaller than cds_linkedlist");

typedef struct {
  linkedlist *ll;
  node_md *node;
} linkedlist_iterator;

_Static_assert(sizeof(linkedlist_iterator) <= sizeof(cds_dlinkedlist_iterator), "cds_linkedlist_iterator must be large enough to contain linkedlist_iterator");
_Static_assert(_Alignof(linkedlist_iterator) <= _Alignof(cds_dlinkedlist_iterator), "linkedlist_iterator alignment must be smaller than cds_linkedlist_iterator");

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
  unsigned int idx;
  node_md *node;
  if (index < (ll->size / 2)) {
    node = ll->head;
    idx = 0;
    while (idx++ != index) {
      node = node->next;
    }
  } else {
    node = ll->tail;
    idx = ll->size - 1;
    while (idx-- != index) {
      node = node->next;
    }
  }
  return node;
}

// dlinkedlist functions

cds_err cds_dlinkedlist_init(cds_dlinkedlist *ds, size_t elem_size, size_t elem_align) {
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

cds_err cds_dlinkedlist_free(cds_dlinkedlist *ds) {
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

cds_err cds_dlinkedlist_get_iterator(cds_dlinkedlist *ds, cds_dlinkedlist_iterator *it) {
  linkedlist *ll = (linkedlist *)ds;
  linkedlist_iterator *llit = (linkedlist_iterator *)it;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  RETURN_IF_DS_NULL(llit);
  llit->node = ll->head;
  llit->ll = ll;
  return CDS_SUCCESS;
}

cds_err cds_dlinkedlist_insert_tail(cds_dlinkedlist *ds, void *element) {
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
    node->prev = ll->tail;
    ll->tail = node;
  }
  ll->size++;
  return CDS_SUCCESS;
}

cds_err cds_dlinkedlist_insert_head(cds_dlinkedlist *ds, void *element) {
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
  if (ll->head == NULL) {
    ll->head = node;
    ll->tail = node;
  } else {
    node->next = ll->head;
    ll->head->prev = node;
    ll->head = node;
  }
  ll->size++;
  return CDS_SUCCESS;
}

cds_err cds_dlinkedlist_insert_index(cds_dlinkedlist *ds, unsigned int index, void *element) {
  linkedlist *ll = (linkedlist *)ds;
  if (index == 0) {
    return cds_dlinkedlist_insert_head(ds, element);
  } else if (index == ll->size) {
    return cds_dlinkedlist_insert_tail(ds, element);
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

cds_err cds_dlinkedlist_get_head(cds_dlinkedlist *ds, void **element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  *element = node_data(ll, ll->head);
  return CDS_SUCCESS;
}

cds_err cds_dlinkedlist_get_tail(cds_dlinkedlist *ds, void **element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  *element = node_data(ll, ll->tail);
  return CDS_SUCCESS;
}

cds_err cds_dlinkedlist_get_index(cds_dlinkedlist *ds, unsigned int index, void **element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  RETURN_IF_INDEX_OOB(ll, index);
  node_md *node = node_get_at_index(ll, index);
  *element = node_data(ll, node);
  return CDS_SUCCESS;
}

cds_err cds_dlinkedlist_read_head(cds_dlinkedlist *ds, const void **element) {
  return cds_dlinkedlist_get_head(ds, (void **)element);
}

cds_err cds_dlinkedlist_read_tail(cds_dlinkedlist *ds, const void **element) {
  return cds_dlinkedlist_get_tail(ds, (void **)element);
}

cds_err cds_dlinkedlist_read_index(cds_dlinkedlist *ds, unsigned int index, const void **element) {
  return cds_dlinkedlist_get_index(ds, index, (void **)element);
}

cds_err cds_dlinkedlist_set_head(cds_dlinkedlist *ds, const void *element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  void *data = node_data(ll, ll->head);
  memcpy(data, element, ll->elem_size);
  return CDS_SUCCESS;
}

cds_err cds_dlinkedlist_set_tail(cds_dlinkedlist *ds, const void *element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  void *data = node_data(ll, ll->tail);
  memcpy(data, element, ll->elem_size);
  return CDS_SUCCESS;
}

cds_err cds_dlinkedlist_set_index(cds_dlinkedlist *ds, unsigned int index, const void *element) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  RETURN_IF_INDEX_OOB(ll, index);
  node_md *node = node_get_at_index(ll, index);
  void *data = node_data(ll, node);
  memcpy(data, element, ll->elem_size);
  return CDS_SUCCESS;
}

cds_err cds_dlinkedlist_cpy_head(cds_dlinkedlist *ds, void *element_cpy) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  memcpy(element_cpy, node_data(ll, ll->head), ll->elem_size);
  return CDS_SUCCESS;
}

cds_err cds_dlinkedlist_cpy_tail(cds_dlinkedlist *ds, void *element_cpy) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  memcpy(element_cpy, node_data(ll, ll->tail), ll->elem_size);
  return CDS_SUCCESS;
}

cds_err cds_dlinkedlist_cpy_index(cds_dlinkedlist *ds, unsigned int index, void *element_cpy) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  node_md *node = node_get_at_index(ll, index);
  memcpy(element_cpy, node_data(ll, node), ll->elem_size);
  return CDS_SUCCESS;
}

cds_err cds_dlinkedlist_delete_head(cds_dlinkedlist *ds) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  // unlink head
  node_md *del_node = ll->head;
  if (del_node == ll->tail) {
    ll->tail = ll->head = NULL;
  } else {
    ll->head = ll->head->next;
    ll->head->prev = NULL;
  }
  free(del_node);
  ll->size--;
  return CDS_SUCCESS;
}

cds_err cds_dlinkedlist_delete_tail(cds_dlinkedlist *ds) {
  linkedlist *ll = (linkedlist *)ds;
  RETURN_IF_DS_NULL(ll);
  RETURN_IF_DS_NOT_INIT(ll);
  node_md *del_node = ll->tail;
  if (del_node == ll->head) {
    ll->head = ll->tail = NULL;
  } else {
    ll->tail = ll->tail->prev;
    ll->tail->next = NULL;
  }
  free(del_node);
  ll->size--;
  return CDS_SUCCESS;
}

cds_err cds_dlinkedlist_delete_index(cds_dlinkedlist *ds, unsigned int index);

cds_err cds_dlinkedlist_extract_head(cds_dlinkedlist *ds, void *element);

cds_err cds_dlinkedlist_extract_tail(cds_dlinkedlist *ds, void *element);

cds_err cds_dlinkedlist_extract_index(cds_dlinkedlist *ds, unsigned int index, void *element);

cds_err cds_dlinkedlist_size(cds_dlinkedlist *ds, unsigned int *return_size);

// Iterator functions

cds_err cds_dlinkedlist_iterator_next(cds_dlinkedlist_iterator *ds);

cds_err cds_dlinkedlist_iterator_prev(cds_dlinkedlist_iterator *ds);

cds_err cds_dlinkedlist_iterator_get_curr(cds_dlinkedlist_iterator *ds, void **element);

cds_err cds_dlinkedlist_iterator_set_curr(cds_dlinkedlist_iterator *ds, void *element);

cds_err cds_dlinkedlist_iterator_read_curr(cds_dlinkedlist_iterator *ds, const void **element);

cds_err cds_dlinkedlist_iterator_cpy_curr(cds_dlinkedlist_iterator *ds, void *element);

cds_err cds_dlinkedlist_iterator_extract_curr(cds_dlinkedlist_iterator *ds, void *element);

cds_err cds_dlinkedlist_iterator_delete_curr(cds_dlinkedlist_iterator *ds);

cds_err cds_dlinkedlist_iterator_insert_before(cds_dlinkedlist_iterator *ds, void *element);

cds_err cds_dlinkedlist_iterator_insert_after(cds_dlinkedlist_iterator *ds, void *element);

cds_err cds_dlinkedlist_iterator_is_at_end(cds_dlinkedlist_iterator *ds);
