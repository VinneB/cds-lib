#include "ecassert.h"
#include "test_cds_arraylist.h"
#include "test_cds_linkedlist.h"

int main() {
  // int a_val = 1;
  // int b_val = 2;
  // int return_val = cds_test_test_assert_primitive(&a_val, &b_val, sizeof(int), 1);
  // printf("return val = %d\n", return_val);
  //
  // byte a[] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
  // byte b[] = {0xFF, 0xFF, 3, 4, 5, 6, 7, 8, 9, 10, 11};
  // return_val = cds_test_test_assert_array(a, 11, b, 11, sizeof(byte), 1);
  // printf("return val = %d\n", return_val);
  eca_setup();
  eca_register_test("arraylist", "simple capacity test", cds_test_arraylist_1);
  eca_register_test("arraylist", "set value test", cds_test_arraylist_2);
  eca_register_test("arraylist", "add to middle test", cds_test_arraylist_3);
  eca_register_test("arraylist", "OOB error test", cds_test_arraylist_4);
  eca_register_test("arraylist", "get test", cds_test_arraylist_5);
  eca_register_test("arraylist", "struct test", cds_test_arraylist_6);
  eca_register_test("arraylist", "remove test", cds_test_arraylist_7);
  eca_register_test("arraylist", "remove element test", cds_test_arraylist_8);
  eca_register_test("linkedlist", "eca_test_linkedlist_init", cds_test_linkedlist_init);
  eca_register_test("linkedlist", "eca_test_linkedlist_free", cds_test_linkedlist_free);
  eca_register_test("linkedlist", "eca_test_linkedlist_get_iterator", cds_test_linkedlist_get_iterator);
  eca_register_test("linkedlist", "eca_test_linkedlist_insert_tail", cds_test_linkedlist_insert_tail);
  eca_register_test("linkedlist", "eca_test_linkedlist_insert_head", cds_test_linkedlist_insert_head);
  eca_register_test("linkedlist", "eca_test_linkedlist_insert_index", cds_test_linkedlist_insert_index);
  eca_register_test("linkedlist", "eca_test_linkedlist_get_head", cds_test_linkedlist_get_head);
  eca_register_test("linkedlist", "eca_test_linkedlist_get_tail", cds_test_linkedlist_get_tail);
  eca_register_test("linkedlist", "eca_test_linkedlist_get_index", cds_test_linkedlist_get_index);
  eca_register_test("linkedlist", "eca_test_linkedlist_read_head", cds_test_linkedlist_read_head);
  eca_register_test("linkedlist", "eca_test_linkedlist_read_tail", cds_test_linkedlist_read_tail);
  eca_register_test("linkedlist", "eca_test_linkedlist_read_index", cds_test_linkedlist_read_index);
  eca_register_test("linkedlist", "eca_test_linkedlist_set_head", cds_test_linkedlist_set_head);
  eca_register_test("linkedlist", "eca_test_linkedlist_set_tail", cds_test_linkedlist_set_tail);
  eca_register_test("linkedlist", "eca_test_linkedlist_set_index", cds_test_linkedlist_set_index);
  eca_register_test("linkedlist", "eca_test_linkedlist_cpy_head", cds_test_linkedlist_cpy_head);
  eca_register_test("linkedlist", "eca_test_linkedlist_cpy_tail", cds_test_linkedlist_cpy_tail);
  eca_register_test("linkedlist", "eca_test_linkedlist_cpy_index", cds_test_linkedlist_cpy_index);
  eca_register_test("linkedlist", "eca_test_linkedlist_delete_head", cds_test_linkedlist_delete_head);
  eca_register_test("linkedlist", "eca_test_linkedlist_delete_tail", cds_test_linkedlist_delete_tail);
  eca_register_test("linkedlist", "eca_test_linkedlist_delete_index", cds_test_linkedlist_delete_index);
  eca_register_test("linkedlist", "eca_test_linkedlist_extract_head", cds_test_linkedlist_extract_head);
  eca_register_test("linkedlist", "eca_test_linkedlist_extract_tail", cds_test_linkedlist_extract_tail);
  eca_register_test("linkedlist", "eca_test_linkedlist_extract_index", cds_test_linkedlist_extract_index);
  eca_register_test("linkedlist", "eca_test_linkedlist_size", cds_test_linkedlist_size);
  eca_register_test("linkedlist", "eca_test_linkedlist_iterator_next", cds_test_linkedlist_iterator_next);
  eca_register_test("linkedlist", "eca_test_linkedlist_iterator_get_curr", cds_test_linkedlist_iterator_get_curr);
  eca_register_test("linkedlist", "eca_test_linkedlist_iterator_set_curr", cds_test_linkedlist_iterator_set_curr);
  eca_register_test("linkedlist", "eca_test_linkedlist_iterator_read_curr", cds_test_linkedlist_iterator_read_curr);
  eca_register_test("linkedlist", "eca_test_linkedlist_iterator_cpy_curr", cds_test_linkedlist_iterator_cpy_curr);
  eca_register_test("linkedlist", "eca_test_linkedlist_iterator_extract_curr", cds_test_linkedlist_iterator_extract_curr);
  eca_register_test("linkedlist", "eca_test_linkedlist_iterator_delete_curr", cds_test_linkedlist_iterator_delete_curr);
  eca_register_test("linkedlist", "eca_test_linkedlist_iterator_insert", cds_test_linkedlist_iterator_insert);
  eca_register_test("linkedlist", "eca_test_linkedlist_iterator_is_at_end", cds_test_linkedlist_iterator_is_at_end);
  eca_run_tests();
  eca_cleanup();
  return 0;
}
