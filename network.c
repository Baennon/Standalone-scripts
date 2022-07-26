#include <glib.h>
#include <libnm/NetworkManager.h>

int main(int argc, char const *argv[])
{
	NMClient *client;
	NMActiveConnection *active;
	const GPtrArray *connections;
	client = nm_client_new(NULL, NULL);
	active = nm_client_get_primary_connection(client);
	if (active != NULL)
	{
		char *activeId = nm_active_connection_get_id(active);
		printf("%s 直\n", activeId);
	}
	else
	{
		printf("Not connected 睊\n");
	}
	return 0;
}
