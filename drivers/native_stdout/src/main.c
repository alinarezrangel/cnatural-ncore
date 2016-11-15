#include "ipcapi.h"
#include "dynapi.h"

const NCoreDriverMetadata_t ndriver_metadata =
{
	"driver", "native_stdout",
	"namespace", "sys.ncore.drivers.native.stdout",
	"version", "0.0.1",
	"date", "2016-11-10",
	"license", "Imported from NCore",
	"devices.0", "natural/ipc/server/stdout",
	"devices.1", "natural/ipc/server/nstdout",
	"description", "Binds /dev/stdout with ncore stdout and nstdout",
	"author.name", "Alejandro Linarez Rangel",
	"author.team-or-group", "NCore Developers Team",
	NULL, NULL
};

NCORE_DYP_EXPORT NCoreError_t ndriver_init(NCoreDriverContext_t*);
NCORE_DYP_EXPORT NCoreError_t ndriver_loop(NCoreDriverContext_t*);
NCORE_DYP_EXPORT NCoreError_t ndriver_deinit(NCoreDriverContext_t*);

NCORE_DYP_EXPORT NCoreError_t ndriver_get_metadata(
	NCoreDriverContext_t*,
	NCoreDriverMetadata_t**
);

NCORE_DYP_EXPORT NCoreError_t ndriver_signal_recv(
	NCoreDriverContext_t*,
	NCoreDriverSignal_t*
);

NCORE_DYP_EXPORT NCoreError_t ndriver_message_recv(
	NCoreDriverContext_t*,
	NCoreDriverMessage_t*
);

NCORE_DYP_EXPORT NCoreError_t ndriver_signal_send(
	NCoreDriverContext_t*,
	NCoreDriverSignal_t**,
	NCoreNProcessID_t*
);

NCORE_DYP_EXPORT NCoreError_t ndriver_message_send(
	NCoreDriverContext_t*,
	NCoreDriverMessage_t**,
	NCoreNProcessID_t*
);
