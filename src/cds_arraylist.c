#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cds_arraylist.h"
#include "cds_error.h"

// INTERNAL MACROS
#define RETURN_IF_DS_NULL(ds)                  \
  do {                                         \
    if ((ds) == NULL) {                        \
      return CDS_ERROR_DATA_STRUCTURE_IS_NULL; \
    }                                          \
  } while (0)

#define RETURN_IF_DS_NOT_INIT(ds) \
  do {                            \
    if ((ds)->is_init != 1) {     \
      return CDS_ERROR_NOT_INIT;  \
    }                             \
  } while (0)

#define RETURN_IF_INDEX_OOB(ds, index) \
  do {                                 \
    if (index > ds->size) {            \
      return CDS_ERROR_INDEX_OOB;      \
    }                                  \
  } while (0)

// PRIVATE
static unsigned int realloc_data(cds_arraylist *ds, void **new_data, unsigned int new_capacity) {
  size_t old_size = ds->capacity * ds->element_size;
  size_t new_size = new_capacity * ds->element_size;
  void *temp = realloc(ds->data, new_size);
  if (temp == NULL) {
    return CDS_ERROR_BAD_ALLOC;
  }
  if (old_size < new_size) {
    void *new_mem_start = temp + old_size;
    memset(new_mem_start, 0, (new_size - old_size));
  }
  *new_data = temp;
  return CDS_SUCCESS;
}

static unsigned int dyn_resize(cds_arraylist *ds, unsigned int size_inc) {
  if ((ds->size + size_inc) <= ds->capacity) {
    return CDS_SUCCESS;
  }
  unsigned int new_capacity = ds->capacity + (ds->capacity >> 1);
  new_capacity = (new_capacity < ds->capacity + size_inc) ? ds->capacity + 1 : new_capacity;
  void *new_data = NULL;
  if (realloc_data(ds, &new_data, new_capacity) != CDS_SUCCESS) {
    return CDS_ERROR_BAD_ALLOC;
  }
  ds->data = new_data;
  ds->capacity = new_capacity;
  return CDS_SUCCESS;
}

static void shift_data_right(cds_arraylist *ds, unsigned int shift_from_index) {
  for (char *p = ((char *)ds->data) + (ds->size * ds->element_size); p >= ((char *)ds->data + (shift_from_index * ds->element_size)); p = p - ds->element_size) {
    memcpy(p, p - ds->element_size, ds->element_size);
  }
}

static void shift_data_left(cds_arraylist *ds, unsigned shift_to_index) {
  for (char *p = ((char *)ds->data) + (shift_to_index * ds->element_size); p < ((char *)ds->data + ((ds->size - 1) * ds->element_size)); p = p + ds->element_size) {
    memcpy(p, p + ds->element_size, ds->element_size);
  }
}

static inline void set(cds_arraylist *ds, int index, void *element) {
  memcpy(ds->data + (index * ds->element_size), element, ds->element_size);
}

static inline void cpy(cds_arraylist *ds, void *dst, int index) {
  memcpy(dst, ds->data + (index * ds->element_size), ds->element_size);
}

static inline unsigned char is_equal(void *a, void *b, size_t element_size) {
  char *ptr_a = (char *)a;
  char *ptr_b = (char *)b;
  for (; ptr_a < (char *)(a + element_size); ptr_a++, ptr_b++) {
    if (*ptr_a != *ptr_b) {
      return 0;
    }
  }
  return 1;
}

// PUBLIC

unsigned int cds_arraylist_init(cds_arraylist *ds, unsigned int initial_capacity, size_t element_size) {
  RETURN_IF_DS_NULL(ds);
  ds->capacity = DEFAULT_ARRAYLIST_CAPACITY;
  if (initial_capacity != 0) {
    ds->capacity = initial_capacity;
  }
  ds->size = 0;
  ds->element_size = element_size;
  ds->data = malloc(element_size * initial_capacity);
  if (ds->data == NULL) {
    return CDS_ERROR_BAD_ALLOC;
  }
  ds->is_init = 1;
  return CDS_SUCCESS;
}

unsigned int cds_arraylist_free(cds_arraylist *ds) {
  RETURN_IF_DS_NULL(ds);
  RETURN_IF_DS_NOT_INIT(ds);

  free(ds->data);
  memset(ds, 0, sizeof(*ds));
  return CDS_SUCCESS;
}

unsigned int cds_arraylist_ensure_capacity(cds_arraylist *ds, unsigned int new_capacity) {
  RETURN_IF_DS_NULL(ds);
  RETURN_IF_DS_NOT_INIT(ds);
  if (new_capacity <= ds->capacity) {
    return CDS_ERROR_BAD_NEW_CAPACITY;
  }
  void *new_data = NULL;
  if (realloc_data(ds, &new_data, new_capacity) != CDS_SUCCESS) {
    return CDS_ERROR_BAD_ALLOC;
  }
  ds->data = new_data;
  ds->capacity = new_capacity;
  return CDS_SUCCESS;
}

unsigned int cds_arraylist_trim_to_size(cds_arraylist *ds) {
  RETURN_IF_DS_NULL(ds);
  RETURN_IF_DS_NOT_INIT(ds);
  void *new_data = NULL;
  if (realloc_data(ds, &new_data, ds->size * ds->element_size) != CDS_SUCCESS) {
    return CDS_ERROR_BAD_ALLOC;
  }
  ds->data = new_data;
  ds->capacity = ds->size;
  return CDS_SUCCESS;
}

unsigned int cds_arraylist_size(cds_arraylist *ds) { return ds->size; }

unsigned int cds_arraylist_add(cds_arraylist *ds, void *element, unsigned int index) {
  RETURN_IF_DS_NULL(ds);
  RETURN_IF_DS_NOT_INIT(ds);
  RETURN_IF_INDEX_OOB(ds, index);
  dyn_resize(ds, 1);
  shift_data_right(ds, index);
  set(ds, index, element);
  ds->size++;
  return CDS_SUCCESS;
}

unsigned int cds_arraylist_add_to_end(cds_arraylist *ds, void *element) {
  RETURN_IF_DS_NULL(ds);
  RETURN_IF_DS_NOT_INIT(ds);
  dyn_resize(ds, 1);
  set(ds, ds->size, element);
  ds->size++;
  return CDS_SUCCESS;
}

unsigned int cds_arraylist_get(cds_arraylist *ds, unsigned int index, void *value) {
  RETURN_IF_DS_NULL(ds);
  RETURN_IF_DS_NOT_INIT(ds);
  RETURN_IF_INDEX_OOB(ds, index);
  cpy(ds, value, index);
  return CDS_SUCCESS;
}

unsigned int cds_arraylist_remove(cds_arraylist *ds, unsigned int index, void *removed_element) {
  RETURN_IF_DS_NULL(ds);
  RETURN_IF_DS_NOT_INIT(ds);
  RETURN_IF_INDEX_OOB(ds, index);
  cpy(ds, removed_element, index);
  shift_data_left(ds, index);
  ds->size--;
  return CDS_SUCCESS;
}

unsigned int cds_arraylist_remove_element(cds_arraylist *ds, void *element, unsigned int *removed_index) {
  RETURN_IF_DS_NULL(ds);
  RETURN_IF_DS_NOT_INIT(ds);
  for (char *p = (char *)ds->data; p < ((char *)ds->data + (ds->size * ds->element_size)); p = p + ds->element_size) {
    if (is_equal(p, element, ds->element_size)) {
      *removed_index = (unsigned int)((p - (char *)ds->data) / ds->element_size);
      shift_data_left(ds, *removed_index);
      ds->size--;
      return CDS_SUCCESS;
    }
  }
  return CDS_ERROR_ELEMENT_NOT_FOUND;
}

unsigned int cds_arraylist_set(cds_arraylist *ds, void *element, unsigned int index, void *removed_element) {
  RETURN_IF_DS_NULL(ds);
  RETURN_IF_DS_NOT_INIT(ds);
  RETURN_IF_INDEX_OOB(ds, index);
  cpy(ds, removed_element, index);
  set(ds, index, element);
  return CDS_SUCCESS;
}
