#include "ecassert.h"
#include "test_cds_arraylist.h"
#include <stdio.h>

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
  eca_run_tests();
  eca_cleanup();
  return 0;
}
