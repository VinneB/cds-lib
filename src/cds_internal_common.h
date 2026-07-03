#ifndef CDS_INTERNAL_COMMON_H 
#define CDS_INTERNAL_COMMON_H
#include <stddef.h>
#include "cds_config.h"

// Guard clauses
#if CDS_USE_DS_VALIDATION
#define RETURN_IF_DS_NULL(ds)                  \
  do {                                         \
    if ((ds) == NULL) {                        \
      return CDS_ERROR_DATA_STRUCTURE_IS_NULL; \
    }                                          \
  } while (0)
#else   
#define RETURN_IF_DS_NULL(ds)
#endif

#if CDS_USE_DS_VALIDATION
#define RETURN_IF_DS_NOT_INIT(ds) \
  do {                            \
    if ((ds)->is_init != 1) {     \
      return CDS_ERROR_NOT_INIT;  \
    }                             \
  } while (0)
#else
#define RETURN_IF_DS_NOT_INIT(ds)
#endif

#if CDS_USE_DS_VALIDATION
#define RETURN_IF_INDEX_OOB(ds, index) \
  do {                                 \
    if (index > ds->size) {            \
      return CDS_ERROR_INDEX_OOB;      \
    }                                  \
  } while (0)
#else
#define RETURN_IF_INDEX_OOB(ds, index)
#endif

// Alignment

static inline size_t align_up(size_t size, size_t alignment) {
  return (size + alignment - 1) & ~(a - 1);
}

#endif // !CDS_INTERNAL_COMMON_H
