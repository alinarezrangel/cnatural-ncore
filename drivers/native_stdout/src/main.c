#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"

#include "ipcapi.h"
#include "dynapi.h"

/* CONTANTS */
enum {
	NDRIVER_STATUS_IDLE,
	NDRIVER_STATUS_READ_READY
};

NCoreIPCConnection_t* native_stdout = NULL;
NCoreIPCConnection_t* native_nstdout = NULL;

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

size_t ndriver_safe_strlen(const NCoreString_t str, size_t maxlen)
{
	size_t i = 0;

	for(i = 0; i < maxlen; i++)
	{
		if(str[i] == '\0')
			return i;
	}

	return maxlen;
}

NCoreError_t ndriver_read_and_print(NCoreDriverContext_t* ctx)
{
	NCoreChar_t buffer[NCORE_IOFCN_READ_BLOCK_SIZE + 1];
	size_t len = NCORE_IOFCN_READ_BLOCK_SIZE;

	memset(buffer, '\0', sizeof(NCoreChar_t) * NCORE_IOFCN_READ_BLOCK_SIZE);

	NCORE_TRY(ncore_ipc_connection_receive(native_stdout, buffer))
		NCORE_CATCH_ALL_EXCEPT(NCORE_ERROR_IOBUFF)
			return ncore_errno;

	if(buffer[NCORE_IOFCN_READ_BLOCK_SIZE] == '\0')
	{
		len = strlen(buffer);
	}

	fwrite(stdout, buffer, len);
}

NCORE_DYNLIB_EXPORT NCoreError_t ndriver_init(NCoreDriverContext_t* ctx)
{
	NCORE_TRY(ncore_ipc_connection_new(&native_stdout))
		return ncore_errno;
	NCORE_TRY(ncore_ipc_connection_new(&native_nstdout))
		return ncore_errno;

	NCORE_TRY(ncore_ipc_connection_create(native_stdout, NCORE_STR("natural/ipc/server/stdout")))
		return ncore_errno;
	NCORE_TRY(ncore_ipc_connection_create(native_nstdout, NCORE_STR("natural/ipc/server/nstdout")))
	{
		NCORE_TRY(ncore_ipc_connection_close(native_stdout))
			return ncore_errno;
		NCORE_TRY(ncore_ipc_connection_destroy(&native_stdout))
			return ncore_errno;

		return ncore_errno;
	}

	NCORE_TRY(ncore_driver_context_reserve_devices(ctx, 2))
		return ncore_errno;

	NCORE_TRY(ncore_driver_context_set_device(ctx, 0, native_stdout))
		return ncore_errno;
	NCORE_TRY(ncore_driver_context_set_device(ctx, 1, native_nstdout))
		return ncore_errno;

	return NCORE_NO_ERROR;
}

NCORE_DYNLIB_EXPORT NCoreError_t ndriver_loop(NCoreDriverContext_t* ctx)
{
	int status = NDRIVER_STATUS_IDLE;

	NCORE_TRY(ncore_driver_context_get_status(ctx, &status))
		return ncore_errno;

	switch(status)
	{
		case NDRIVER_STATUS_READ_READY:
			return ndriver_read_and_print(ctx);
		case NDRIVER_STATUS_IDLE:
			break;
	}

	return NCORE_NO_ERROR;
}

NCORE_DYNLIB_EXPORT NCoreError_t ndriver_deinit(NCoreDriverContext_t* ctx)
{
	NCORE_TRY(ncore_ipc_connection_close(native_stdout))
		return ncore_errno;
	NCORE_TRY(ncore_ipc_connection_close(native_nstdout))
		return ncore_errno;
	NCORE_TRY(ncore_ipc_connection_destroy(&native_stdout))
		return ncore_errno;
	NCORE_TRY(ncore_ipc_connection_destroy(&native_nstdout))
		return ncore_errno;

	NCORE_TRY(ncore_driver_context_set_device(ctx, 0, NULL))
		return ncore_errno;
	NCORE_TRY(ncore_driver_context_set_device(ctx, 1, NULL))
		return ncore_errno;

	return NCORE_NO_ERROR;
}

NCORE_DYNLIB_EXPORT NCoreError_t ndriver_get_metadata(
	NCoreDriverContext_t* ctx,
	NCoreDriverMetadata_t* meta
)
{
	meta = &ndriver_metadata;

	return NCORE_NO_ERROR;
}

NCORE_DYNLIB_EXPORT NCoreError_t ndriver_signal_recv(
	NCoreDriverContext_t* ctx,
	NCoreDriverSignal_t* signal
)
{
	if(signal->type == NCORE_SIGNAL_IOREADY)
	{
		NCORE_TRY(ncore_driver_context_set_status(ctx, NDRIVER_STATUS_READ_READY))
			return ncore_errno;
	}

	return NCORE_NO_ERROR;
}

NCORE_DYNLIB_EXPORT NCoreError_t ndriver_message_recv(
	NCoreDriverContext_t* ctx,
	NCoreDriverMessage_t* msg
)
{
	return NCORE_NO_ERROR;
}

NCORE_DYNLIB_EXPORT NCoreError_t ndriver_signal_send(
	NCoreDriverContext_t* ctx,
	NCoreDriverSignal_t** signal,
	NCoreNProcessID_t* to
)
{
	return NCORE_NO_ERROR;
}

NCORE_DYNLIB_EXPORT NCoreError_t ndriver_message_send(
	NCoreDriverContext_t* ctx,
	NCoreDriverMessage_t** msg,
	NCoreNProcessID_t* to
)
{
	return NCORE_NO_ERROR;
}
