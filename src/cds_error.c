#include "cds_error.h"

const char *cds_error_to_string(cds_err_t err) {
  switch (err) {
  case CDS_SUCCESS:
    return "Success";
  case CDS_ERROR_BAD_ALLOC:
    return "Failed to allocate memory";
  default:
    return "Unknown CDS error";
  }
}
