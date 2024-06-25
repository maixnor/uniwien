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

bool receive_and_eval(int connfd)
{
	char buf[4096];
	ssize_t received;

	while ((received = recv(connfd, buf, sizeof(buf), 0)) > 0) {
    
		cout << string(buf, received);
	}
	cout << endl;
}

int accept_and_send_challenge(int sockfd)
{
	int connfd;
	struct sockaddr_in conn_addr{};
	socklen_t addr_len = sizeof(conn_addr);

	connfd = accept(sockfd,
		reinterpret_cast<struct sockaddr *>(&conn_addr),
		&addr_len);
	if (connfd == -1) {
		return;
	}
}

int create_server_socket(uint16_t port)
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
		// binds to all interfaces
		.sin_addr = {.s_addr = INADDR_ANY},
		.sin_zero = {}
	};

	if (bind(sockfd, reinterpret_cast<struct sockaddr *>(&addr),
		sizeof(addr))) {
		close(sockfd);
		return -1;
	}

	if (listen(sockfd, 1)) {
		close(sockfd);
		return -1;
	}

	return sockfd;
}

int main()
{
	constexpr uint16_t port = 1234;

	int sockfd = create_server_socket(port);
	if (sockfd == -1) {
		return EXIT_FAILURE;
	}

	auto expected = accept_and_send_challenge(sockfd);
  // await result
  auto result = receive_and_eval();
  // check result

  // answer 
  
  // close connection / keep socket open

	close(sockfd);

	return EXIT_SUCCESS;
}
