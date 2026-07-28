#ifndef CDS_TEST_LINKEDLIST_H
#define CDS_TEST_LINKEDLIST_H

#include "ecassert.h" 
eca_status cds_test_linkedlist_init();

eca_status cds_test_linkedlist_free();

eca_status cds_test_linkedlist_get_iterator();

eca_status cds_test_linkedlist_insert_tail();

eca_status cds_test_linkedlist_insert_head();

eca_status cds_test_linkedlist_insert_index();

eca_status cds_test_linkedlist_get_head();

eca_status cds_test_linkedlist_get_tail();

eca_status cds_test_linkedlist_get_index();

eca_status cds_test_linkedlist_read_head();

eca_status cds_test_linkedlist_read_tail();

eca_status cds_test_linkedlist_read_index();

eca_status cds_test_linkedlist_set_head();

eca_status cds_test_linkedlist_set_tail();

eca_status cds_test_linkedlist_set_index();

eca_status cds_test_linkedlist_cpy_head();

eca_status cds_test_linkedlist_cpy_tail();

eca_status cds_test_linkedlist_cpy_index();

eca_status cds_test_linkedlist_delete_head();

eca_status cds_test_linkedlist_delete_tail();

eca_status cds_test_linkedlist_delete_index();

eca_status cds_test_linkedlist_extract_head();

eca_status cds_test_linkedlist_extract_tail();

eca_status cds_test_linkedlist_extract_index();

eca_status cds_test_linkedlist_size();

// Iterator functions

eca_status cds_test_linkedlist_iterator_next();

eca_status cds_test_linkedlist_iterator_get_curr();

eca_status cds_test_linkedlist_iterator_set_curr();

eca_status cds_test_linkedlist_iterator_read_curr();

eca_status cds_test_linkedlist_iterator_cpy_curr();

eca_status cds_test_linkedlist_iterator_extract_curr();

eca_status cds_test_linkedlist_iterator_delete_curr();

eca_status cds_test_linkedlist_iterator_insert();

eca_status cds_test_linkedlist_iterator_is_at_end();

#endif // !CDS_TEST_LINKEDLIST_H
