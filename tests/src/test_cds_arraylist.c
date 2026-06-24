#include "test_cds_arraylist.h"
#include "cds_arraylist.h"
#include "cds_error.h"
#include "ecassert.h"
#include "stdio.h"

eca_status cds_test_arraylist_1() {
  arraylist_t arr;
  ECA_ASSERT_INT(cds_arraylist_init(&arr, 8, sizeof(int)), ECA_PASS);
  int i = 0;
  for (i = 0; i < 8; i++) {
    ECA_ASSERT_INT(cds_arraylist_add_to_end(&arr, &i), ECA_PASS);
  }
  ECA_ASSERT_INT(8, arr.capacity);
  cds_arraylist_add_to_end(&arr, &i);
  ECA_ASSERT_INT(12, arr.capacity);
  return ECA_PASS;
}

eca_status cds_test_arraylist_2() {
  arraylist_t arr;
  cds_arraylist_init(&arr, 1, sizeof(int));
  int i = 0;
  for (i = 0; i < 8; i++) {
    cds_arraylist_add_to_end(&arr, &i);
  }
  int val = 10;
  int removed_val = 0;
  int expected_arr[8] = {0, 1, 2, 3, 10, 5, 6, 7};
  cds_arraylist_set(&arr, &val, 4, &removed_val);
  ECA_ASSERT_INT(4, removed_val);
  ECA_ASSERT_ARR_INT(expected_arr, 8, arr.data, 8);
  return ECA_PASS;
}

eca_status cds_test_arraylist_3() {
  arraylist_t arr;
  cds_arraylist_init(&arr, 1, sizeof(int));
  int i = 0;
  for (i = 0; i < 8; i++) {
    cds_arraylist_add_to_end(&arr, &i);
  }
  for (i = 10; i < 20; i++) {
    cds_arraylist_add(&arr, &i, i-5);
  }
  int expected_arr[18] = {0, 1, 2, 3, 4, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 5, 6, 7};
  ECA_ASSERT_ARR_INT(expected_arr, 18, arr.data, 18);
  return ECA_PASS;
}


eca_status cds_test_arraylist_4() {
  arraylist_t arr;
  cds_arraylist_init(&arr, 1, sizeof(int));
  int val = 5;
  int err = cds_arraylist_add(&arr, &val, 1);
  ECA_ASSERT_INT(CDS_ERROR_INDEX_OOB, err);
  err = cds_arraylist_add(&arr, &val, 1);
  ECA_ASSERT_INT(CDS_ERROR_INDEX_OOB, err);
  err = cds_arraylist_add(&arr, &val, 0);
  ECA_ASSERT_INT(CDS_SUCCESS, err);
  return ECA_PASS;
}
