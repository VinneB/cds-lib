#ifndef CDS_DLINKEDLIST_H
#define CDS_DLINKEDLIST_H
#include <stddef.h>
#include <stdalign.h>
#include "cds_error.h"

#define CDS_DLINKEDLIST_BYTE_SZ 48 
#define CDS_DLINKEDLIST_ITERATOR_BYTE_SZ 16

typedef struct {
  alignas(max_align_t) char internal[CDS_DLINKEDLIST_BYTE_SZ];
} cds_dlinkedlist;

typedef struct {
  alignas(max_align_t) char internal[CDS_DLINKEDLIST_ITERATOR_BYTE_SZ];
} cds_dlinkedlist_iterator;

// dlinkedlist functionS

cds_err cds_dlinkedlist_init(cds_dlinkedlist *ds, size_t elem_size, size_t elem_align);

cds_err cds_dlinkedlist_free(cds_dlinkedlist *ds);

cds_err cds_dlinkedlist_get_iterator(cds_dlinkedlist *ds, cds_dlinkedlist_iterator *it);

cds_err cds_dlinkedlist_insert_tail(cds_dlinkedlist *ds, void *element);

cds_err cds_dlinkedlist_insert_head(cds_dlinkedlist *ds, void *element);

cds_err cds_dlinkedlist_insert_index(cds_dlinkedlist *ds, unsigned int index, void *element);

cds_err cds_dlinkedlist_get_head(cds_dlinkedlist *ds, void **element);

cds_err cds_dlinkedlist_get_tail(cds_dlinkedlist *ds, void **element);

cds_err cds_dlinkedlist_get_index(cds_dlinkedlist *ds, unsigned int index, void **element);

cds_err cds_dlinkedlist_read_head(cds_dlinkedlist *ds, const void **element);

cds_err cds_dlinkedlist_read_tail(cds_dlinkedlist *ds, const void **element);

cds_err cds_dlinkedlist_read_index(cds_dlinkedlist *ds, unsigned int index, const void **element);

cds_err cds_dlinkedlist_set_head(cds_dlinkedlist *ds, const void *element);

cds_err cds_dlinkedlist_set_tail(cds_dlinkedlist *ds, const void *element);

cds_err cds_dlinkedlist_set_index(cds_dlinkedlist *ds, unsigned int index, const void *element);

cds_err cds_dlinkedlist_cpy_head(cds_dlinkedlist *ds, void *element_cpy);

cds_err cds_dlinkedlist_cpy_tail(cds_dlinkedlist *ds, void *element_cpy);

cds_err cds_dlinkedlist_cpy_index(cds_dlinkedlist *ds, unsigned int index, void *element_cpy);

cds_err cds_dlinkedlist_delete_head(cds_dlinkedlist *ds);

cds_err cds_dlinkedlist_delete_tail(cds_dlinkedlist *ds);

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


#endif // !CDS_DLINKEDLIST_H
