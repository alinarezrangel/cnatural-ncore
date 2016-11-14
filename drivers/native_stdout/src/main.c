#include "ipcapi.h"
#include "dynapi.h"

const NCoreMetadata_t ndriver_metadata;

NCORE_DYP_EXPORT NCoreError_t ndriver_init(NCoreDriverContext_t*);
NCORE_DYP_EXPORT NCoreError_t ndriver_deinit(NCoreDriverContext_t*);

NCORE_DYP_EXPORT NCoreError_t ndriver_signal(
	NCoreDriverContext_t*,
	NCoreDriverSignal_t*
);

NCORE_DYP_EXPORT NCoreError_t ndriver_
