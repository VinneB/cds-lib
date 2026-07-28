#include "cds_error.h"
#include "cds_linkedlist.h"
#include "ecassert.h"
#include "stddef.h"
#include <stdalign.h>
#include <stddef.h>

typedef struct {
  max_align_t a;
  max_align_t b;
} big_type;

typedef struct {
  alignas(max_align_t) int a;
  const char *str;
} max_aligned_type;

typedef struct {
  alignas(big_type) int a;
} big_aligned_type;

eca_status cds_test_linkedlist_init() {
  eca_register_to_string(eca_tostring_element_hex);
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));
  return ECA_PASS;
}

eca_status cds_test_linkedlist_free() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_head(&ll1, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_head(&ll2, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_head(&ll3, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_free(&ll1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_free(&ll2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_free(&ll3));

  ECA_ASSERT_INT(CDS_ERROR_NOT_INIT, cds_linkedlist_free(&ll3));

  return ECA_PASS;
}

eca_status cds_test_linkedlist_get_iterator() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  cds_linkedlist_iterator it1;
  cds_linkedlist_iterator it2;
  cds_linkedlist_iterator it3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_head(&ll1, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_head(&ll2, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_head(&ll3, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll1, &it1))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll2, &it2))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll3, &it3))

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_free(&ll1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_free(&ll2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_free(&ll3));

  return ECA_PASS;
}

eca_status cds_test_linkedlist_insert_tail() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  cds_linkedlist_iterator it1;
  cds_linkedlist_iterator it2;
  cds_linkedlist_iterator it3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  int elem_get_1;
  max_aligned_type elem_get_2;
  big_aligned_type elem_get_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_tail(&ll1, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_tail(&ll2, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_tail(&ll3, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_tail(&ll1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_tail(&ll2, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_tail(&ll3, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_tail(&ll1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_tail(&ll2, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_tail(&ll3, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll1, &elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll2, &elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll3, &elem_get_3));

  ECA_ASSERT(&elem_1, &elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_2, &elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_3, &elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll1, &elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll2, &elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll3, &elem_get_3));

  ECA_ASSERT(&elem_12, &elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_22, &elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_32, &elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll1, &elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll2, &elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll3, &elem_get_3));

  ECA_ASSERT(&elem_13, &elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_23, &elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_33, &elem_get_3, sizeof(elem_3));
  return ECA_PASS;
}

eca_status cds_test_linkedlist_insert_head() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  int elem_get_1;
  max_aligned_type elem_get_2;
  big_aligned_type elem_get_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_head(&ll1, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_head(&ll2, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_head(&ll3, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_head(&ll1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_head(&ll2, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_head(&ll3, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_head(&ll1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_head(&ll2, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_head(&ll3, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_tail(&ll1, &elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_tail(&ll2, &elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_tail(&ll3, &elem_get_3));

  ECA_ASSERT(&elem_1, &elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_2, &elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_3, &elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_tail(&ll1, &elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_tail(&ll2, &elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_tail(&ll3, &elem_get_3));

  ECA_ASSERT(&elem_12, &elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_22, &elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_32, &elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_tail(&ll1, &elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_tail(&ll2, &elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_tail(&ll3, &elem_get_3));

  ECA_ASSERT(&elem_13, &elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_23, &elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_33, &elem_get_3, sizeof(elem_3));
  return ECA_PASS;
}

eca_status cds_test_linkedlist_insert_index() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  int elem_get_1;
  max_aligned_type elem_get_2;
  big_aligned_type elem_get_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_ERROR_INDEX_OOB, cds_linkedlist_insert_index(&ll1, -1, &elem_1));
  ECA_ASSERT_INT(CDS_ERROR_INDEX_OOB, cds_linkedlist_insert_index(&ll1, 1, &elem_1));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll1, &elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll2, &elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll3, &elem_get_3));

  ECA_ASSERT(&elem_1, &elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_2, &elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_3, &elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll1, &elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll2, &elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll3, &elem_get_3));

  ECA_ASSERT(&elem_13, &elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_23, &elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_33, &elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll1, &elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll2, &elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll3, &elem_get_3));

  ECA_ASSERT(&elem_12, &elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_22, &elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_32, &elem_get_3, sizeof(elem_3));

  return ECA_PASS;
}

eca_status cds_test_linkedlist_get_head() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_ERROR_INDEX_OOB, cds_linkedlist_insert_index(&ll1, -1, &elem_1));
  ECA_ASSERT_INT(CDS_ERROR_INDEX_OOB, cds_linkedlist_insert_index(&ll1, 1, &elem_1));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll1, (void **)&elem_get_1))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll2, (void **)&elem_get_2))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll3, (void **)&elem_get_3))

  ECA_ASSERT(&elem_1, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_2, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_3, elem_get_3, sizeof(elem_3));

  *elem_get_1 = 9;
  elem_get_2->a = 9;
  elem_get_3->a = 9;

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll1, (void **)&elem_get_1))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll2, (void **)&elem_get_2))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll3, (void **)&elem_get_3))

  ECA_ASSERT_INT(9, *elem_get_1);
  ECA_ASSERT_INT(9, elem_get_2->a);
  ECA_ASSERT_INT(9, elem_get_3->a);
  return ECA_PASS;
}

eca_status cds_test_linkedlist_get_tail() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_ERROR_INDEX_OOB, cds_linkedlist_insert_index(&ll1, -1, &elem_1));
  ECA_ASSERT_INT(CDS_ERROR_INDEX_OOB, cds_linkedlist_insert_index(&ll1, 1, &elem_1));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_tail(&ll1, (void **)&elem_get_1))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_tail(&ll2, (void **)&elem_get_2))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_tail(&ll3, (void **)&elem_get_3))

  ECA_ASSERT(&elem_12, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_22, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_32, elem_get_3, sizeof(elem_3));

  *elem_get_1 = 9;
  elem_get_2->a = 9;
  elem_get_3->a = 9;

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_tail(&ll1, (void **)&elem_get_1))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_tail(&ll2, (void **)&elem_get_2))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_tail(&ll3, (void **)&elem_get_3))

  ECA_ASSERT_INT(9, *elem_get_1);
  ECA_ASSERT_INT(9, elem_get_2->a);
  ECA_ASSERT_INT(9, elem_get_3->a);
  return ECA_PASS;
}

eca_status cds_test_linkedlist_get_index() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_ERROR_INDEX_OOB, cds_linkedlist_insert_index(&ll1, -1, &elem_1));
  ECA_ASSERT_INT(CDS_ERROR_INDEX_OOB, cds_linkedlist_insert_index(&ll1, 1, &elem_1));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll1, 1, (void **)&elem_get_1))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll2, 1, (void **)&elem_get_2))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll3, 1, (void **)&elem_get_3))

  ECA_ASSERT(&elem_13, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_23, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_33, elem_get_3, sizeof(elem_3));

  *elem_get_1 = 9;
  elem_get_2->a = 9;
  elem_get_3->a = 9;

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll1, 1, (void **)&elem_get_1))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll2, 1, (void **)&elem_get_2))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll3, 1, (void **)&elem_get_3))

  ECA_ASSERT_INT(9, *elem_get_1);
  ECA_ASSERT_INT(9, elem_get_2->a);
  ECA_ASSERT_INT(9, elem_get_3->a);
  return ECA_PASS;
}

eca_status cds_test_linkedlist_read_head() {
  return ECA_PASS;
}

eca_status cds_test_linkedlist_read_tail() {
  return ECA_PASS;
}

eca_status cds_test_linkedlist_read_index() {
  return ECA_PASS;
}

eca_status cds_test_linkedlist_set_head() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_set_head(&ll1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_set_head(&ll2, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_set_head(&ll3, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll2, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll3, (void **)&elem_get_3));

  ECA_ASSERT(&elem_12, elem_get_1, sizeof(elem_12));
  ECA_ASSERT(&elem_22, elem_get_2, sizeof(elem_22));
  ECA_ASSERT(&elem_32, elem_get_3, sizeof(elem_32));
  return ECA_PASS;
}

eca_status cds_test_linkedlist_set_tail() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_set_tail(&ll1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_set_tail(&ll2, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_set_tail(&ll3, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll2, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll3, (void **)&elem_get_3));

  ECA_ASSERT(&elem_12, elem_get_1, sizeof(elem_12));
  ECA_ASSERT(&elem_22, elem_get_2, sizeof(elem_22));
  ECA_ASSERT(&elem_32, elem_get_3, sizeof(elem_32));
  return ECA_PASS;
}

eca_status cds_test_linkedlist_set_index() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  int elem_14 = 0xCCCC;
  max_aligned_type elem_24 = {0, "dd"};
  big_aligned_type elem_34 = {0xDDDD};
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_ERROR_INDEX_OOB, cds_linkedlist_insert_index(&ll1, -1, &elem_1));
  ECA_ASSERT_INT(CDS_ERROR_INDEX_OOB, cds_linkedlist_insert_index(&ll1, 1, &elem_1));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_set_index(&ll1, 1, &elem_14));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_set_index(&ll2, 1, &elem_24));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_set_index(&ll3, 1, &elem_34));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll1, 1, (void **)&elem_get_1))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll2, 1, (void **)&elem_get_2))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll3, 1, (void **)&elem_get_3))

  ECA_ASSERT(&elem_14, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_24, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_34, elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_set_index(&ll1, 0, &elem_14));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_set_index(&ll2, 0, &elem_24));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_set_index(&ll3, 0, &elem_34));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll1, 0, (void **)&elem_get_1))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll2, 0, (void **)&elem_get_2))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll3, 0, (void **)&elem_get_3))

  ECA_ASSERT(&elem_14, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_24, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_34, elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_set_index(&ll1, 2, &elem_14));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_set_index(&ll2, 2, &elem_24));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_set_index(&ll3, 2, &elem_34));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll1, 2, (void **)&elem_get_1))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll2, 2, (void **)&elem_get_2))
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll3, 2, (void **)&elem_get_3))

  ECA_ASSERT(&elem_14, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_24, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_34, elem_get_3, sizeof(elem_3));
  return ECA_PASS;
}

eca_status cds_test_linkedlist_cpy_head() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_cpy_1;
  max_aligned_type elem_cpy_2;
  big_aligned_type elem_cpy_3;
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_cpy_head(&ll1, &elem_cpy_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_cpy_head(&ll2, &elem_cpy_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_cpy_head(&ll3, &elem_cpy_3));

  ECA_ASSERT(&elem_1, &elem_cpy_1, sizeof(elem_1));
  ECA_ASSERT(&elem_2, &elem_cpy_2, sizeof(elem_2));
  ECA_ASSERT(&elem_3, &elem_cpy_3, sizeof(elem_3));

  elem_cpy_1 = 9;
  elem_cpy_2.a = 9;
  elem_cpy_3.a = 9;

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll2, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll3, (void **)&elem_get_3));

  ECA_ASSERT(&elem_1, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_2, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_3, elem_get_3, sizeof(elem_3));

  return ECA_PASS;
}

eca_status cds_test_linkedlist_cpy_tail() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_cpy_1;
  max_aligned_type elem_cpy_2;
  big_aligned_type elem_cpy_3;
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_cpy_tail(&ll1, &elem_cpy_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_cpy_tail(&ll2, &elem_cpy_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_cpy_tail(&ll3, &elem_cpy_3));

  ECA_ASSERT(&elem_1, &elem_cpy_1, sizeof(elem_1));
  ECA_ASSERT(&elem_2, &elem_cpy_2, sizeof(elem_2));
  ECA_ASSERT(&elem_3, &elem_cpy_3, sizeof(elem_3));

  elem_cpy_1 = 9;
  elem_cpy_2.a = 9;
  elem_cpy_3.a = 9;

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll2, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll3, (void **)&elem_get_3));

  ECA_ASSERT(&elem_1, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_2, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_3, elem_get_3, sizeof(elem_3));

  return ECA_PASS;
}

eca_status cds_test_linkedlist_cpy_index() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  int elem_cpy_1;
  max_aligned_type elem_cpy_2;
  big_aligned_type elem_cpy_3;
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_cpy_index(&ll1, 1, &elem_cpy_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_cpy_index(&ll2, 1, &elem_cpy_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_cpy_index(&ll3, 1, &elem_cpy_3));

  ECA_ASSERT(&elem_13, &elem_cpy_1, sizeof(elem_1));
  ECA_ASSERT(&elem_23, &elem_cpy_2, sizeof(elem_2));
  ECA_ASSERT(&elem_33, &elem_cpy_3, sizeof(elem_3));

  elem_cpy_1 = 9;
  elem_cpy_2.a = 9;
  elem_cpy_3.a = 9;

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll1, 1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll2, 1, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll3, 1, (void **)&elem_get_3));

  ECA_ASSERT(&elem_13, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_23, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_33, elem_get_3, sizeof(elem_3));

  return ECA_PASS;
}

eca_status cds_test_linkedlist_delete_head() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_delete_head(&ll1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_delete_head(&ll2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_delete_head(&ll3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll2, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll3, (void **)&elem_get_3));

  ECA_ASSERT(&elem_13, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_23, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_33, elem_get_3, sizeof(elem_3));
  return ECA_PASS;
}

eca_status cds_test_linkedlist_delete_tail() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_delete_tail(&ll1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_delete_tail(&ll2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_delete_tail(&ll3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_tail(&ll1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_tail(&ll2, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_tail(&ll3, (void **)&elem_get_3));

  ECA_ASSERT(&elem_13, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_23, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_33, elem_get_3, sizeof(elem_3));
  return ECA_PASS;
}

eca_status cds_test_linkedlist_delete_index() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_delete_index(&ll1, 1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_delete_index(&ll2, 1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_delete_index(&ll3, 1));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll1, 1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll2, 1, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll3, 1, (void **)&elem_get_3));

  ECA_ASSERT(&elem_12, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_22, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_32, elem_get_3, sizeof(elem_3));
  return ECA_PASS;
}

eca_status cds_test_linkedlist_extract_head() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  int elem_cpy_1;
  max_aligned_type elem_cpy_2;
  big_aligned_type elem_cpy_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll1, &elem_cpy_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll2, &elem_cpy_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_head(&ll3, &elem_cpy_3));

  ECA_ASSERT(&elem_1, &elem_cpy_1, sizeof(elem_1));
  ECA_ASSERT(&elem_2, &elem_cpy_2, sizeof(elem_2));
  ECA_ASSERT(&elem_3, &elem_cpy_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll2, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_head(&ll3, (void **)&elem_get_3));

  ECA_ASSERT(&elem_13, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_23, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_33, elem_get_3, sizeof(elem_3));
  return ECA_PASS;
}

eca_status cds_test_linkedlist_extract_tail() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  int elem_cpy_1;
  max_aligned_type elem_cpy_2;
  big_aligned_type elem_cpy_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_tail(&ll1, &elem_cpy_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_tail(&ll2, &elem_cpy_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_tail(&ll3, &elem_cpy_3));

  ECA_ASSERT(&elem_12, &elem_cpy_1, sizeof(elem_1));
  ECA_ASSERT(&elem_22, &elem_cpy_2, sizeof(elem_2));
  ECA_ASSERT(&elem_32, &elem_cpy_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_tail(&ll1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_tail(&ll2, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_tail(&ll3, (void **)&elem_get_3));

  ECA_ASSERT(&elem_13, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_23, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_33, elem_get_3, sizeof(elem_3));
  return ECA_PASS;
}

eca_status cds_test_linkedlist_extract_index() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  int elem_cpy_1;
  max_aligned_type elem_cpy_2;
  big_aligned_type elem_cpy_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_index(&ll1, 1, &elem_cpy_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_index(&ll2, 1, &elem_cpy_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_index(&ll3, 1, &elem_cpy_3));

  ECA_ASSERT(&elem_13, &elem_cpy_1, sizeof(elem_1));
  ECA_ASSERT(&elem_23, &elem_cpy_2, sizeof(elem_2));
  ECA_ASSERT(&elem_33, &elem_cpy_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll1, 1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll2, 1, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll3, 1, (void **)&elem_get_3));

  ECA_ASSERT(&elem_12, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_22, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_32, elem_get_3, sizeof(elem_3));
  return ECA_PASS;
}

eca_status cds_test_linkedlist_size() {
  cds_linkedlist ll1;
  int elem_1 = 0xFFFF;
  int elem_cpy_1;
  unsigned int size;
  cds_linkedlist_iterator it;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_size(&ll1, &size));
  ECA_ASSERT_INT(0, size);

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_size(&ll1, &size));
  ECA_ASSERT_INT(1, size);

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_1));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_size(&ll1, &size));
  ECA_ASSERT_INT(2, size);

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_1));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_size(&ll1, &size));
  ECA_ASSERT_INT(3, size);

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_extract_tail(&ll1, &elem_cpy_1));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_size(&ll1, &size));
  ECA_ASSERT_INT(2, size);

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_delete_index(&ll1, 1));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_size(&ll1, &size));
  ECA_ASSERT_INT(1, size);

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll1, &it));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_insert(&it, &elem_1));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_size(&ll1, &size));
  ECA_ASSERT_INT(2, size);

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_delete_curr(&it));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_size(&ll1, &size));
  ECA_ASSERT_INT(1, size);

  return ECA_PASS;
}

// Iterator functions

eca_status cds_test_linkedlist_iterator_next() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  cds_linkedlist_iterator it1;
  cds_linkedlist_iterator it2;
  cds_linkedlist_iterator it3;
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  int elem_cpy_1;
  max_aligned_type elem_cpy_2;
  big_aligned_type elem_cpy_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll1, &it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll2, &it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll3, &it3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it2, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it3, (void **)&elem_get_3));

  ECA_ASSERT(&elem_1, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_2, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_3, elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it2, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it3, (void **)&elem_get_3));

  ECA_ASSERT(&elem_13, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_23, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_33, elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it2, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it3, (void **)&elem_get_3));

  ECA_ASSERT(&elem_12, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_22, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_32, elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it3));

  ECA_ASSERT_INT(CDS_ERROR_ITER_END, cds_linkedlist_iterator_get_curr(&it1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_ERROR_ITER_END, cds_linkedlist_iterator_get_curr(&it2, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_ERROR_ITER_END, cds_linkedlist_iterator_get_curr(&it3, (void **)&elem_get_3));

  ECA_ASSERT_INT(CDS_ERROR_ITER_END, cds_linkedlist_iterator_next(&it1));
  ECA_ASSERT_INT(CDS_ERROR_ITER_END, cds_linkedlist_iterator_next(&it2));
  ECA_ASSERT_INT(CDS_ERROR_ITER_END, cds_linkedlist_iterator_next(&it3));

  ECA_ASSERT_INT(CDS_ERROR_ITER_END, cds_linkedlist_iterator_is_at_end(&it1));
  ECA_ASSERT_INT(CDS_ERROR_ITER_END, cds_linkedlist_iterator_is_at_end(&it2));
  ECA_ASSERT_INT(CDS_ERROR_ITER_END, cds_linkedlist_iterator_is_at_end(&it3));

  return ECA_PASS;
}

eca_status cds_test_linkedlist_iterator_get_curr() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  cds_linkedlist_iterator it1;
  cds_linkedlist_iterator it2;
  cds_linkedlist_iterator it3;
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll1, &it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll2, &it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll3, &it3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it2, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it3, (void **)&elem_get_3));

  ECA_ASSERT(&elem_1, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_2, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_3, elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it2, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it3, (void **)&elem_get_3));

  ECA_ASSERT(&elem_13, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_23, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_33, elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it2, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it3, (void **)&elem_get_3));

  ECA_ASSERT(&elem_12, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_22, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_32, elem_get_3, sizeof(elem_3));

  return ECA_PASS;
}

eca_status cds_test_linkedlist_iterator_set_curr() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  int elem_14 = 0xCCCC;
  max_aligned_type elem_24 = {0, "dd"};
  big_aligned_type elem_34 = {0xDDDD};
  cds_linkedlist_iterator it1;
  cds_linkedlist_iterator it2;
  cds_linkedlist_iterator it3;
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_14));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_24));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_34));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_14));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_24));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_34));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_14));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_24));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_34));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll1, &it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll2, &it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll3, &it3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_set_curr(&it1, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_set_curr(&it2, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_set_curr(&it3, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_set_curr(&it1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_set_curr(&it2, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_set_curr(&it3, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_set_curr(&it1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_set_curr(&it2, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_set_curr(&it3, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll1, 0, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll2, 0, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll3, 0, (void **)&elem_get_3));

  ECA_ASSERT(&elem_1, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_2, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_3, elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll1, 1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll2, 1, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll3, 1, (void **)&elem_get_3));

  ECA_ASSERT(&elem_12, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_22, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_32, elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll1, 2, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll2, 2, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll3, 2, (void **)&elem_get_3));

  ECA_ASSERT(&elem_13, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_23, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_33, elem_get_3, sizeof(elem_3));

  return ECA_PASS;
}

eca_status cds_test_linkedlist_iterator_read_curr() {
  return ECA_PASS;
}

eca_status cds_test_linkedlist_iterator_cpy_curr() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  cds_linkedlist_iterator it1;
  cds_linkedlist_iterator it2;
  cds_linkedlist_iterator it3;
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  int elem_cpy_1;
  max_aligned_type elem_cpy_2;
  big_aligned_type elem_cpy_3;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll1, &it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll2, &it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll3, &it3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_cpy_curr(&it1, &elem_cpy_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_cpy_curr(&it2, &elem_cpy_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_cpy_curr(&it3, &elem_cpy_3));

  ECA_ASSERT(&elem_1, &elem_cpy_1, sizeof(elem_1));
  ECA_ASSERT(&elem_2, &elem_cpy_2, sizeof(elem_2));
  ECA_ASSERT(&elem_3, &elem_cpy_3, sizeof(elem_3));

  elem_cpy_1 = 9;
  elem_cpy_2.a = 9;
  elem_cpy_3.a = 9;

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_cpy_curr(&it1, &elem_cpy_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_cpy_curr(&it2, &elem_cpy_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_cpy_curr(&it3, &elem_cpy_3));

  ECA_ASSERT(&elem_13, &elem_cpy_1, sizeof(elem_1));
  ECA_ASSERT(&elem_23, &elem_cpy_2, sizeof(elem_2));
  ECA_ASSERT(&elem_33, &elem_cpy_3, sizeof(elem_3));

  elem_cpy_1 = 9;
  elem_cpy_2.a = 9;
  elem_cpy_3.a = 9;

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_cpy_curr(&it1, &elem_cpy_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_cpy_curr(&it2, &elem_cpy_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_cpy_curr(&it3, &elem_cpy_3));

  ECA_ASSERT(&elem_12, &elem_cpy_1, sizeof(elem_1));
  ECA_ASSERT(&elem_22, &elem_cpy_2, sizeof(elem_2));
  ECA_ASSERT(&elem_32, &elem_cpy_3, sizeof(elem_3));

  elem_cpy_1 = 9;
  elem_cpy_2.a = 9;
  elem_cpy_3.a = 9;

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll1, 0, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll2, 0, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll3, 0, (void **)&elem_get_3));

  ECA_ASSERT(&elem_1, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_2, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_3, elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll1, 1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll2, 1, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll3, 1, (void **)&elem_get_3));

  ECA_ASSERT(&elem_13, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_23, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_33, elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll1, 2, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll2, 2, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_index(&ll3, 2, (void **)&elem_get_3));

  ECA_ASSERT(&elem_12, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_22, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_32, elem_get_3, sizeof(elem_3));

  return ECA_PASS;
}

eca_status cds_test_linkedlist_iterator_extract_curr() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  int elem_cpy_1;
  max_aligned_type elem_cpy_2;
  big_aligned_type elem_cpy_3;
  cds_linkedlist_iterator it1;
  cds_linkedlist_iterator it2;
  cds_linkedlist_iterator it3;
  cds_linkedlist_iterator it12;
  cds_linkedlist_iterator it22;
  cds_linkedlist_iterator it32;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll1, &it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll2, &it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll3, &it3));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll1, &it12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll2, &it22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll3, &it32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_extract_curr(&it1, &elem_cpy_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_extract_curr(&it2, &elem_cpy_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_extract_curr(&it3, &elem_cpy_3));

  ECA_ASSERT(&elem_cpy_1, &elem_13, sizeof(elem_1));
  ECA_ASSERT(&elem_cpy_2, &elem_23, sizeof(elem_2));
  ECA_ASSERT(&elem_cpy_3, &elem_33, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it12, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it22, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it32, (void **)&elem_get_3));

  ECA_ASSERT(elem_get_1, &elem_1, sizeof(elem_1));
  ECA_ASSERT(elem_get_2, &elem_2, sizeof(elem_2));
  ECA_ASSERT(elem_get_3, &elem_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it12, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it22, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it32, (void **)&elem_get_3));

  ECA_ASSERT(elem_get_1, &elem_12, sizeof(elem_1));
  ECA_ASSERT(elem_get_2, &elem_22, sizeof(elem_2));
  ECA_ASSERT(elem_get_3, &elem_32, sizeof(elem_3));

  return ECA_PASS;
}

eca_status cds_test_linkedlist_iterator_delete_curr() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {0, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {0, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  cds_linkedlist_iterator it1;
  cds_linkedlist_iterator it2;
  cds_linkedlist_iterator it3;
  cds_linkedlist_iterator it12;
  cds_linkedlist_iterator it22;
  cds_linkedlist_iterator it32;
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(max_aligned_type), alignof(max_aligned_type)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(big_aligned_type), alignof(big_aligned_type)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll1, &it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll2, &it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll3, &it3));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll1, &it12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll2, &it22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll3, &it32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 0, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 0, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 0, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll1, 1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll2, 1, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_insert_index(&ll3, 1, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_delete_curr(&it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_delete_curr(&it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_delete_curr(&it3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it12, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it22, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it32, (void **)&elem_get_3));

  ECA_ASSERT(elem_get_1, &elem_1, sizeof(elem_1));
  ECA_ASSERT(elem_get_2, &elem_2, sizeof(elem_2));
  ECA_ASSERT(elem_get_3, &elem_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it12, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it22, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it32, (void **)&elem_get_3));

  ECA_ASSERT(elem_get_1, &elem_12, sizeof(elem_1));
  ECA_ASSERT(elem_get_2, &elem_22, sizeof(elem_2));
  ECA_ASSERT(elem_get_3, &elem_32, sizeof(elem_3));

  return ECA_PASS;
}

eca_status cds_test_linkedlist_iterator_insert() {
  cds_linkedlist ll1;
  cds_linkedlist ll2;
  cds_linkedlist ll3;
  int elem_1 = 0xFFFF;
  max_aligned_type elem_2 = {1, "aa"};
  big_aligned_type elem_3 = {0xAAAA};
  int elem_12 = 0xEEEE;
  max_aligned_type elem_22 = {0, "bb"};
  big_aligned_type elem_32 = {0xBBBB};
  int elem_13 = 0xDDDD;
  max_aligned_type elem_23 = {12, "cc"};
  big_aligned_type elem_33 = {0xCCCC};
  int elem_14 = 0xDDDD;
  max_aligned_type elem_24 = {12, "cc"};
  big_aligned_type elem_34 = {0xCCCC};
  int *elem_get_1;
  max_aligned_type *elem_get_2;
  big_aligned_type *elem_get_3;
  cds_linkedlist_iterator it1;
  cds_linkedlist_iterator it2;
  cds_linkedlist_iterator it3;
  cds_linkedlist_iterator it12;
  cds_linkedlist_iterator it22;
  cds_linkedlist_iterator it32;

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll1, sizeof(unsigned int), alignof(unsigned int)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll2, sizeof(elem_2), alignof(elem_2)));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_init(&ll3, sizeof(elem_3), alignof(elem_3)));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll1, &it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll2, &it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll3, &it3));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll1, &it12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll2, &it22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_get_iterator(&ll3, &it32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_insert(&it1, &elem_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_insert(&it2, &elem_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_insert(&it3, &elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_insert(&it1, &elem_12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_insert(&it2, &elem_22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_insert(&it3, &elem_32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_insert(&it1, &elem_13));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_insert(&it2, &elem_23));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_insert(&it3, &elem_33));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it12, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it22, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it32, (void **)&elem_get_3));

  max_aligned_type *tst_elem_get_1;
  max_aligned_type *tst_elem_get_2;
  max_aligned_type *tst_elem_get_3;

  cds_linkedlist_get_index(&ll2, 0, (void **)&tst_elem_get_1);
  cds_linkedlist_get_index(&ll2, 1, (void **)&tst_elem_get_2);
  cds_linkedlist_get_index(&ll2, 2, (void **)&tst_elem_get_3);

  ECA_ASSERT(&elem_13, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_23, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_33, elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it12, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it22, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it32, (void **)&elem_get_3));

  ECA_ASSERT(&elem_12, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_22, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_32, elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it12, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it22, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it32, (void **)&elem_get_3));

  ECA_ASSERT(&elem_1, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_2, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_3, elem_get_3, sizeof(elem_3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it12));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it22));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it32));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_insert(&it12, &elem_14));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_insert(&it22, &elem_24));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_insert(&it32, &elem_34));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_next(&it3));

  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it1, (void **)&elem_get_1));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it2, (void **)&elem_get_2));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_linkedlist_iterator_get_curr(&it3, (void **)&elem_get_3));

  ECA_ASSERT(&elem_14, elem_get_1, sizeof(elem_1));
  ECA_ASSERT(&elem_24, elem_get_2, sizeof(elem_2));
  ECA_ASSERT(&elem_34, elem_get_3, sizeof(elem_3));

  return ECA_PASS;
}

eca_status cds_test_linkedlist_iterator_is_at_end() {
  return ECA_PASS;
}
