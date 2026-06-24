#ifndef CDS_ERROR_H
#define CDS_ERROR_H

/**
 * @brief Error values
 */
typedef enum {
  CDS_SUCCESS = 0,
  CDS_ERROR_BAD_ALLOC,
  CDS_ERROR_DATA_STRUCTURE_IS_NULL,
  CDS_ERROR_NOT_INIT,
  CDS_ERROR_BAD_NEW_CAPACITY,
  CDS_ERROR_INDEX_OOB,
  CDS_ERROR_INTERNAL,
  CDS_ERROR_ELEMENT_NOT_FOUND
} cds_err_t;

/**
 * @brief Convert cds error value to string literal
 * @param err Cds error value
 * @return String literal describing error.
 */
const char* cds_error_to_string (cds_err_t err);

#endif // !CDS_ERROR_H
