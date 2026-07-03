#ifndef CDS_LINKEDLIST_H
#define CDS_LINKEDLIST_H
#include <stddef.h>
#include <stdalign.h>
#include "cds_error.h"

#define CDS_LINKEDLIST_BYTE_SZ 48 
#define CDS_LINKEDLIST_ITERATOR_BYTE_SZ 16

typedef struct {
  alignas(max_align_t) char internal[CDS_LINKEDLIST_BYTE_SZ];
} cds_linkedlist;

typedef struct {
  alignas(max_align_t) char internal[CDS_LINKEDLIST_ITERATOR_BYTE_SZ];
} cds_linkedlist_iterator;

// LinkedList functionS

cds_err cds_linkedlist_init(cds_linkedlist *ds, size_t elem_size, size_t elem_align);

cds_err cds_linkedlist_free(cds_linkedlist *ds);

cds_err cds_linkedlist_get_iterator(cds_linkedlist *ds, cds_linkedlist_iterator *it);

cds_err cds_linkedlist_insert_tail(cds_linkedlist *ds, void *element);

cds_err cds_linkedlist_insert_head(cds_linkedlist *ds, void *element);

cds_err cds_linkedlist_insert_index(cds_linkedlist *ds, unsigned int index, void *element);

cds_err cds_linkedlist_get_head(cds_linkedlist *ds, void **element);

cds_err cds_linkedlist_get_tail(cds_linkedlist *ds, void **element);

cds_err cds_linkedlist_get_index(cds_linkedlist *ds, unsigned int index, void **element);

cds_err cds_linkedlist_read_head(cds_linkedlist *ds, const void **element);

cds_err cds_linkedlist_read_tail(cds_linkedlist *ds, const void **element);

cds_err cds_linkedlist_read_index(cds_linkedlist *ds, unsigned int index, const void **element);

cds_err cds_linkedlist_set_head(cds_linkedlist *ds, const void *element);

cds_err cds_linkedlist_set_tail(cds_linkedlist *ds, const void *element);

cds_err cds_linkedlist_set_index(cds_linkedlist *ds, unsigned int index, const void *element);

cds_err cds_linkedlist_cpy_head(cds_linkedlist *ds, void *element_cpy);

cds_err cds_linkedlist_cpy_tail(cds_linkedlist *ds, void *element_cpy);

cds_err cds_linkedlist_cpy_index(cds_linkedlist *ds, unsigned int index, void *element_cpy);

cds_err cds_linkedlist_delete_head(cds_linkedlist *ds);

cds_err cds_linkedlist_delete_tail(cds_linkedlist *ds);

cds_err cds_linkedlist_delete_index(cds_linkedlist *ds, unsigned int index);

cds_err cds_linkedlist_extract_head(cds_linkedlist *ds, void *element);

cds_err cds_linkedlist_extract_tail(cds_linkedlist *ds, void *element);

cds_err cds_linkedlist_extract_index(cds_linkedlist *ds, unsigned int index, void *element);

cds_err cds_linkedlist_size(cds_linkedlist *ds, unsigned int *return_size);

// Iterator functions

cds_err cds_linkedlist_iterator_next(cds_linkedlist_iterator *ds);

cds_err cds_linkedlist_iterator_get_curr(cds_linkedlist_iterator *ds, void *return_element);

cds_err cds_linkedlist_iterator_set_curr(cds_linkedlist_iterator *ds, void *return_element);

cds_err cds_linkedlist_iterator_read_curr(cds_linkedlist_iterator *ds, void *return_element);

cds_err cds_linkedlist_iterator_cpy_curr(cds_linkedlist_iterator *ds, void *return_element);

cds_err cds_linkedlist_iterator_extract_curr(cds_linkedlist_iterator *ds, void *return_element);

cds_err cds_linkedlist_iterator_delete_curr(cds_linkedlist_iterator *ds, void *return_element);

cds_err cds_linkedlist_iterator_insert_after(cds_linkedlist_iterator *ds, void *data);


#endif // !CDS_LINKED_H
