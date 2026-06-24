#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stddef.h>

#define DEFAULT_ARRAYLIST_CAPACITY 64

/**
 * @brief ArrayList data structure
 */
typedef struct {
  char is_init;
  size_t element_size;
  unsigned int size;
  unsigned int capacity;
  void* data;
} arraylist_t;

/** 
 * @brief Creates an initialized arraylist
 * @param ds pointer to intialized arraylist_t struct
 * @param initial_capacity the capacity of the arraylist returned. If 0, then DEFAULT_ARRAYLIST_CAPACITY is used
 * @param element_size Number of bytes in an individual element 
 * @return Returns error value on error. Returns CDS_SUCCESS (0) on success.
 */
unsigned int cds_arraylist_init(arraylist_t *ds, unsigned int initial_capacity, size_t element_size);

/**
 * @brief Free the arraylist internal memory and clear struct. DOES NOT FREE STRUCT ITSELF.
 * @param ds pointer to intialized arraylist_t struct
 * @return Returns error value on error. Returns CDS_SUCCESS (0) on success.
 */
unsigned int cds_arraylist_free(arraylist_t *ds);

/** 
 * @brief Add element to arraylist at index. Amortized O(N)
 * Add element to arraylist at index. Index can be any value greater than or equal to zero and less than of equal to size.
 * @param ds pointer to intialized arraylist_t struct
 * @param element Element to add to arraylist. 
 * @param index Index in arraylist to put element. 0 <= index <= size.
 * @return Returns error value on error. Returns CDS_SUCCESS (0) on success.
 */
unsigned int cds_arraylist_add(arraylist_t *ds, void *element, unsigned int index);

/**
 * @brief Add element to end of arraylist. Amortized O(1)
 * @param ds pointer to intialized arraylist_t struct
 * @param element Element to add to arraylist. 
 * @return Returns error value on error. Returns CDS_SUCCESS (0) on success.
 */
unsigned int cds_arraylist_add_to_end(arraylist_t *ds, void *element);

/**
 * @brief Get element at index. O(1)
 * @param ds pointer to intialized arraylist_t struct
 * @param index Index of the element to get.
 * @param value The value found at index
 * @return Returns error value on error. Returns CDS_SUCCESS (0) on success.
 */
unsigned int cds_arraylist_get(arraylist_t *ds, unsigned int index, void *value);

/*
 * @brief Remove element from arraylist at given index and return it. O(N). DOES NOT FREE ELEMENT.
 * @param ds pointer to intialized arraylist_t struct
 * @param index Index to remove element from.
 * @param removed_element Element which was removed from list (not freed).
 * @return Returns error value on error. Returns CDS_SUCCESS (0) on success.
 */
unsigned int cds_arraylist_remove(arraylist_t *ds, unsigned int index, void *removed_element);

/*
 * @brief Removes the first instance of provided element from array. O(N). DOES NOT FREE ELEMENT.
 * @param ds pointer to intialized arraylist_t struct
 * @param element Element to remove from arraylist.
 * @param removed_index Index of removed element
 * @return Returns error value on error. Returns CDS_SUCCESS (0) on success.
 */
unsigned int cds_arraylist_remove_element(arraylist_t *ds, void *element, unsigned int *removed_index);

/*
 * @brief Put the provided element in array at provided index and return the element that was previously at that index. O(1). DOES NOT FREE ELEMENT.
 * @param ds pointer to intialized arraylist_t struct
 * @param element Element to put in arraylist.
 * @param index Index in arraylist to put element. Must be within 0 to size-1.
 * @param removed_element Element which was previously at index (not freed).
 * @return Returns error value on error. Returns CDS_SUCCESS (0) on success.
 */
unsigned int cds_arraylist_set(arraylist_t *ds, void *element, unsigned int index, void *removed_element);

/*
 * @brief Return the size of the arraylist.
 * @param ds pointer to intialized arraylist_t struct
 * @return Returns the size of the arraylist
 */
unsigned int cds_arraylist_size(arraylist_t *ds); 

/*
 * @brief Grow internal array to provided size.  
 * Grow internal array to provided size. The new size must be greater than current.
 * @param new_capacity The new size of internal array.
 * @param ds pointer to intialized arraylist_t struct
 * @return Returns error value on error. Returns CDS_SUCCESS (0) on success.
 */
unsigned int cds_arraylist_ensure_capacity(arraylist_t *ds, unsigned int new_capacity);

/*
 * @brief Reduce capacity down to size.
 * @param new_capacity The new size of internal array.
 * @return Returns error value on error. Returns CDS_SUCCESS (0) on success.
 */
unsigned int cds_arraylist_trim_to_size(arraylist_t *ds);

#endif
