extern "C" {
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
}

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <iostream>

#include "proto.h"

using namespace std;

ssize_t send_line(int connfd, const string &input)
{
	return send(connfd, input.c_str(), input.size(), 0);
}

int connect_to_server(const char *ip, uint16_t port)
{
	int bool_true = 1;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd == -1) {
		return -1;
	}
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR,
		&bool_true, sizeof(bool_true));

	struct sockaddr_in addr {
		.sin_family = AF_INET,
		.sin_port = htons(port),
		.sin_addr = {},
		.sin_zero = {}
	};
	// returns 1 on success, 0 on failure
	if (!inet_pton(AF_INET, ip, &addr.sin_addr)) {
		close(sockfd);
		return -1;
	}

	if (connect(sockfd, reinterpret_cast<struct sockaddr *>(&addr),
		sizeof(addr))) {
		close(sockfd);
		return -1;
	}

	return sockfd;
}

int main()
{
	const string ip{"127.0.0.1"};
	constexpr uint16_t port = 1234;

	int connfd = connect_to_server(ip.c_str(), port);
	if (connfd == -1) {
		return EXIT_FAILURE;
	}

	string input;
	getline(cin, input);
	send_line(connfd, input);

	close(connfd);

	return EXIT_SUCCESS;
}
