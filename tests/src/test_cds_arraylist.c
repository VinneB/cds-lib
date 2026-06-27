#include "test_cds_arraylist.h"
#include "cds_arraylist.h"
#include "cds_error.h"
#include "ecassert.h"
#include "stdio.h"

struct shape {
  const char *name;
  unsigned int vertex_count;
};

void shape_struct_tostring(void *element, size_t element_size, char *str);

eca_status cds_test_arraylist_1() {
  cds_arraylist arr;
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
  cds_arraylist arr;
  cds_arraylist_init(&arr, 1, sizeof(short));
  short i = 0;
  for (i = 0; i < 8; i++) {
    cds_arraylist_add_to_end(&arr, &i);
  }
  short val = 10;
  short removed_val = 0;
  short expected_arr[8] = {0, 1, 2, 3, 10, 5, 6, 7};
  cds_arraylist_set(&arr, &val, 4, &removed_val);
  ECA_ASSERT_SHORT(4, removed_val);
  ECA_ASSERT_ARR_SHORT(expected_arr, 8, arr.data, 8);
  return ECA_PASS;
}

eca_status cds_test_arraylist_3() {
  cds_arraylist arr;
  cds_arraylist_init(&arr, 1, sizeof(long));
  long i = 0;
  for (i = 0; i < 8; i++) {
    cds_arraylist_add_to_end(&arr, &i);
  }
  for (i = 10; i < 20; i++) {
    cds_arraylist_add(&arr, &i, i - 5);
  }
  long expected_arr[18] = {0, 1, 2, 3, 4, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 5, 6, 7};
  ECA_ASSERT_ARR_LONG(expected_arr, 18, arr.data, 18);
  return ECA_PASS;
}

eca_status cds_test_arraylist_4() {
  cds_arraylist arr;
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

eca_status cds_test_arraylist_5() {
  cds_arraylist arr;
  cds_arraylist_init(&arr, 5, sizeof(int));
  int i = 0;
  for (i = 0; i < 8; i++) {
    cds_arraylist_add_to_end(&arr, &i);
  }
  unsigned int get_val;
  cds_arraylist_get(&arr, 0, &get_val);
  ECA_ASSERT_INT(0, get_val)
  cds_arraylist_get(&arr, 7, &get_val);
  ECA_ASSERT_INT(7, get_val)
  return ECA_PASS;
}

eca_status cds_test_arraylist_6() {
  eca_register_to_string(shape_struct_tostring);
  cds_arraylist arr;
  const char *name[4] = {"po", "li", "tr", "sq"};
  cds_arraylist_init(&arr, 2, sizeof(struct shape));
  for (int i = 1; i < 5; i++) {
    struct shape curr_shape = {name[i - 1], i};
    cds_arraylist_add_to_end(&arr, &curr_shape);
  }
  ECA_ASSERT_INT(4, arr.capacity);
  struct shape test_shape = {"li", 2};
  struct shape get_shape;
  cds_arraylist_get(&arr, 1, &get_shape);
  ECA_ASSERT(&test_shape, (void *)&get_shape, sizeof(get_shape));
  return ECA_PASS;
}

eca_status cds_test_arraylist_7() {
  cds_arraylist arr;
  ECA_ASSERT_INT(cds_arraylist_init(&arr, 5, sizeof(int)), CDS_SUCCESS);
  int i = 0;
  for (i = 0; i < 8; i++) {
    ECA_ASSERT_INT(cds_arraylist_add_to_end(&arr, &i), CDS_SUCCESS);
  }
  int rem_element;
  int expected_arr[7] = {0, 1, 3, 4, 5, 6, 7};
  ECA_ASSERT_INT(cds_arraylist_remove(&arr, 2, &rem_element), CDS_SUCCESS);
  ECA_ASSERT_INT(2, rem_element);
  ECA_ASSERT_ARR_INT(expected_arr, 7, arr.data, arr.size);
  return ECA_PASS;
}

eca_status cds_test_arraylist_8() {
  eca_register_to_string(shape_struct_tostring);
  cds_arraylist arr;
  const char *name[4] = {"po", "li", "tr", "sq"};
  ECA_ASSERT_INT(cds_arraylist_init(&arr, 5, sizeof(struct shape)), CDS_SUCCESS);
  struct shape shape_to_remove;
  unsigned int removal_index;
  struct shape expected_arr[3];
  for (int i = 0; i < 4; i++) {
    struct shape curr_shape = {name[i], i + 2};
    ECA_ASSERT_INT(CDS_SUCCESS, cds_arraylist_add_to_end(&arr, &curr_shape));
    if (i != 0) {
      expected_arr[i - 1] = curr_shape;
    }
  }
  ECA_ASSERT_INT(CDS_SUCCESS, cds_arraylist_get(&arr, 0, &shape_to_remove));
  ECA_ASSERT_INT(CDS_SUCCESS, cds_arraylist_remove_element(&arr, &shape_to_remove, &removal_index));
  ECA_ASSERT_INT(0, removal_index);
  ECA_ASSERT_ARR(expected_arr, 3, arr.data, arr.size, sizeof(struct shape));
  return ECA_PASS;
}

void shape_struct_tostring(void *element, size_t element_size, char *str) {
  snprintf(str, element_size, "{%s, %u}", ((struct shape *)element)->name, ((struct shape *)element)->vertex_count);
}
