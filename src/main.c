/* ****************************************************
**************************
*** NCore Source Code. See the LICENSE.txt file for
*** more info.
*** **
*** **
*** **
*** **
*** **
**************************
**************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <ipcapi.h>

int main(int argc, char** argv)
{
	bool isServer = false;
	NCoreServerIPC_t* server = NULL;
	NCoreServerIPC_t* conn = NULL;
	char buffer[256];
	int ret = 0;

	if(argc <= 1)
	{
		fprintf(stderr, "Error in ncore executable: one argument is required\n");
		fprintf(stderr, "Usage:\n");
		fprintf(stderr, "    ncore (server|client)\n");
		fprintf(stderr, "E_NOARG: Error No Arguments\n");
		exit(EXIT_FAILURE);
	}

	isServer = !strcmp("server", argv[1]);

	if(isServer)
	{
		printf("Starting as server...\n");

		if(ncore_server_ipc_new(&server, NCORE_IS_SERVER, NCORE_DEFAULT_SERVER) < 0)
		{
			perror("Error connecting");
			exit(EXIT_FAILURE);
		}

		while(ncore_server_ipc_accept(server, &conn) >= 0)
		{
			do
			{
				ncore_server_ipc_wait_for_response(conn);

				if(ncore_server_ipc_receive_fix(conn, buffer, 255) >= 0)
				{
					perror("Error receiving the data");
					ncore_server_ipc_destroy(&conn);
					ncore_server_ipc_destroy(&server);
					exit(EXIT_FAILURE);
				}

				printf("R:%s\n", buffer);

				/* Echoed */

				if(ncore_server_ipc_send(conn, buffer, 255) < 0)
				{
					perror("Error echoing the data");
					ncore_server_ipc_destroy(&conn);
					ncore_server_ipc_destroy(&server);
					exit(EXIT_FAILURE);
				}
			} while(strcmp(".", buffer) != 0);

			ncore_server_ipc_destroy(&conn);
		}

		ncore_server_ipc_destroy(&server);
	}
	else
	{
		printf("Starting as server...\n");

		if(ncore_server_ipc_new(&server, NCORE_IS_CLIENT, NCORE_DEFAULT_SERVER) < 0)
		{
			perror("Error connecting");
			exit(EXIT_FAILURE);
		}

		do
		{
			memset(buffer, '\0', 255);
			scanf("%s", buffer);

			if(ncore_server_ipc_send(server, buffer, 255) < 0)
			{
				perror("Error echoing the data");
				ncore_server_ipc_destroy(&conn);
				ncore_server_ipc_destroy(&server);
				exit(EXIT_FAILURE);
			}

			ncore_server_ipc_wait_for_response(server);

			if(ncore_server_ipc_receive_fix(server, buffer, 255) >= 0)
			{
				perror("Error receiving the data");
				ncore_server_ipc_destroy(&conn);
				ncore_server_ipc_destroy(&server);
				exit(EXIT_FAILURE);
			}
			printf("R:%s\n", buffer);
		} while(strcmp(".", buffer) != 0);

		ncore_server_ipc_destroy(&server);
	}
}
