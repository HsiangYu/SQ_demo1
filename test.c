#include <stdio.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>
#include <net/if.h>

int detect_network(void)
{
	int inet_sock;
	struct ifreq ifr;

	inet_sock = socket(AF_INET, SOCK_DGRAM, 0);
	strcpy(ifr.ifr_name, "ppp0"); 

	if (ioctl(inet_sock, SIOCGIFADDR, &ifr) < 0)
	{
		return 0;
	} else {
		return 1;
	}
}


int main()
{
	if(detect_network()==0)
		printf("not detect_network\n");
	else
		printf("detect_network\n");
	return 0;
}
