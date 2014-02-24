/*
 * ClaimsServer.cpp
 *
 *  Created on: Feb 20, 2014
 *      Author: volt
 */

#include "ClaimsServer.h"

#include <malloc.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstdio>
#include "../Catalog/Catalog.h"
#include "../Daemon/Daemon.h"

ClaimsServer::ClaimsServer(int port) {

	m_num = 0;
	m_clientFds = new int[MAXCONN];
	for (int i = 0; i < MAXCONN; ++i) {
		m_clientFds[i] = -1;
	}
	m_fd = -1;
	m_port = port;
}

ClaimsServer::~ClaimsServer() {

	delete m_clientFds;
}

int ClaimsServer::addClient(const int fd) {

	if (m_num == MAXCONN) {

		perror("Server has the maximum connection");
		return -1;
	}

	for (int i = 0; i < MAXCONN; ++i) {
		if (m_clientFds[i] < 0) {
			m_clientFds[i] = fd;
			++m_num;
			break;
		}
	}
	return 0;
}

int ClaimsServer::removeClient(const int fd) {

	int ret = -1;
	for (int i = 0; i < MAXCONN; ++i) {
		if (m_clientFds[i] == fd) {
			m_clientFds[i] = -1;
			--m_num;
			ret = 0;
			break;
		}
	}
	return ret;
}

int ClaimsServer::receiveRequest(const int fd, const char *cmd) {

	remote_command rcmd;
	rcmd.socket_fd = fd;
	rcmd.cmd.append(cmd);

	Daemon::getInstance()->addRemoteCommand(rcmd);
	return 0;
}

/**
 * configure the socket parameter, bind to the specific ip/port
 * startup the send/receive threads
 */
void ClaimsServer::configure() {

	int &serverSockFd = m_fd;
	int clientSockFd;
	unsigned int nread;
	char *buf = new char[128];
	sockaddr_in serverSocket;
	sockaddr_in clientSocket;

	serverSocket.sin_family = AF_INET;
	serverSocket.sin_port = htons(8000);
	serverSocket.sin_addr.s_addr = INADDR_ANY;

	if ((serverSockFd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("socket error");
		return;
	}

	if (bind(serverSockFd, (sockaddr *) &serverSocket, sizeof(serverSocket))
			< 0) {
		perror("Server:: bind error!");
		return;
	}

	int backLog = MAXCONN - 1;
	if (listen(serverSockFd, backLog) == -1) {
		printf("Server::listen error!\n");
		return;
	} else {
		printf("Server::listen ok!\n");
	}

	pthread_t t_Receiver;
	pthread_t t_Sender;

	const int error1 = pthread_create(&t_Receiver, NULL, receiveHandler, this);
	if (error1 != 0) {
		std::cout << "cannot create receive thread!" << std::endl;
	}

	const int error2 = pthread_create(&t_Sender, NULL, sendHandler, this);
	if (error2 != 0) {
		std::cout << "cannot create send thread!" << std::endl;
	}

}

void* ClaimsServer::receiveHandler(void *para) {

	printf("-Init receive handler.\n");
	ClaimsServer *server = (ClaimsServer *) para;
	int &serverSockFd = server->m_fd;
	int clientSockFd;

	char *buf = new char[128];

	unsigned int sockLen;
	int nread;

	int nfds = serverSockFd + 1;
	fd_set watchFds;
	fd_set readFds;

	FD_ZERO(&watchFds);
	FD_SET(serverSockFd, &watchFds);

	bool stop = false;
	while (!stop) {

		readFds = watchFds;
		switch (select(nfds, &readFds, NULL, NULL, (timeval *) 0)) {
		case -1:
			break;
		case 0:
			break;
		default:

			if (FD_ISSET(serverSockFd, &readFds)) {
				//ADD Client
				sockaddr_in clientSocket;
				sockLen = sizeof(sockaddr_in);

				if (!server->isFull()) {
					if ((clientSockFd = accept(serverSockFd,
							(sockaddr *) &clientSocket, &sockLen)) >= 0) {

						printf("open communication with client, %d\n",
								clientSockFd);
//						server->m_clientFds[server->m_num++] = clientSockFd;
						server->addClient(clientSockFd);
						FD_SET(clientSockFd, &watchFds);
						nfds = (clientSockFd >= nfds ? clientSockFd + 1 : nfds);
					} else {
						printf("Accept Error!\n");
					}
				}
			}
			for (int i = 0; i < MAXCONN; ++i) {

				if (server->m_clientFds[i] < 0)
					continue;

				if (FD_ISSET(server->m_clientFds[i], &readFds)) {

					ioctl(server->m_clientFds[i], FIONREAD, &nread);"Client: message from server!\n"
					if (0 == nread) {
						//TODO does here means a client close the connection with server?
						printf("close connection on socket %d!\n", server->m_clientFds[i]);
						FD_CLR(server->m_clientFds[i], &watchFds);
						::close(server->m_clientFds[i]);
						server->removeClient(server->m_clientFds[i]);
						continue;
					}
					read(server->m_clientFds[i], buf, nread);

					int retCode = server->receiveRequest(server->m_clientFds[i], buf);
					if (1 == retCode) {
						printf("Successfully receive query from client %d.\n",
								server->m_clientFds[i]);
					}
//					else if (-1 == retCode) {
//						server->shutdown();
//						stop = true;
//						printf("Shut Down!\n");
//					} else {
//						printf("Failed query from client %d.\n",
//								server->m_clientFds[i]);
//					}
				}
			}
			break;
		} /*end of switch*/
	}
	FD_ZERO(&watchFds);
	FD_ZERO(&readFds);
	delete buf;

}

void *ClaimsServer::sendHandler(void *para) {

	printf("-Init send handler!\n");
	ClaimsServer *server = (ClaimsServer*) para;

	ClientResponse cliRes;
	while (true) {
		executed_result result = Daemon::getInstance()->getExecutedResult();
		if (result.status == 0) {
			//OK
			cliRes.setOk("Yes Ok");
			server->write(result.fd, cliRes);

			cliRes.setSchema(result.result->schema_);
			server->write(result.fd, cliRes);

			std::vector<std::string> list = result.result->column_header_list_;
			ColumnHeader header;
			for (int i = 0; i < list.size(); ++i) {
				header.add_header(list[i]);
			}
			cliRes.setAttributeName(header);
			server->write(result.fd, cliRes);


			ResultSet::Iterator it = result.result->createIterator();
			BlockStreamBase* block;

			while (block = (BlockStreamBase*) it.atomicNextBlock()) {
				cliRes.setDataBlock(*(Block*) block);
				server->write(result.fd, cliRes);
			}

			cliRes.setEnd("Yes Query finished!");
			server->write(result.fd, cliRes);

		} else {
			//ERROR
			cliRes.setError(result.error_info);
			server->write(result.fd, cliRes);
		}
	}
}

/**
 * Thread shut down the server when it receives "shut down" command from a client.
 */
//void ClaimsServer::run() {
//
//	int &serverSockFd = m_fd;
//	int clientSockFd;
//	unsigned int nread;
//	char *buf = new char[128];
//	sockaddr_in serverSocket;
//	sockaddr_in clientSocket;
//
//	serverSocket.sin_family = AF_INET;
//	serverSocket.sin_port = htons(8000);
//	serverSocket.sin_addr.s_addr = INADDR_ANY;
//
//	if ((serverSockFd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
//		printf("socket error");
//		return;
//	}
//
//	if (bind(serverSockFd, (sockaddr *) &serverSocket, sizeof(serverSocket))
//			< 0) {
//		perror("Server:: bind error!");
//		return;
//	}
//
//	int backLog = MAXCONN - 1;
//	if (listen(serverSockFd, backLog) == -1) {
//		printf("Server::listen error!\n");
//		return;
//	} else {
//		printf("Server::listen ok!\n");
//	}
//
//	int nfds = serverSockFd + 1;
//	unsigned int sockLen;
//	fd_set watchFds;
//	fd_set readFds;
//
//	FD_ZERO(&watchFds);
//	FD_SET(serverSockFd, &watchFds);
//
//	bool stop = false;
//	while (!stop) {
//
//		readFds = watchFds;
//		switch (select(nfds, &readFds, NULL, NULL, (timeval *) 0)) {
//		case -1:
//			break;
//		case 0:
//			break;
//		default:
//
//			if (FD_ISSET(serverSockFd, &readFds)) {
//				//ADD Client
//				sockLen = sizeof(sockaddr_in);
//
//				if (!isFull()) {
//					if ((clientSockFd = accept(serverSockFd,
//							(sockaddr *) &clientSocket, &sockLen)) >= 0) {
//
//						printf("open communication with client, %d\n",
//								clientSockFd);
//						m_clientFds[m_num++] = clientSockFd;
//						FD_SET(clientSockFd, &watchFds);
//						nfds = (clientSockFd >= nfds ? clientSockFd + 1 : nfds);
//					} else {
//						printf("Accept Error!\n");
//					}
//				}
//			}
//			for (int i = 0; i < MAXCONN; ++i) {
//
//				if (m_clientFds[i] < 0)
//					continue;
//
//				if (FD_ISSET(m_clientFds[i], &readFds)) {
//
//					ioctl(m_clientFds[i], FIONREAD, &nread);
//					if (0 == nread) {
//						//TODO does here means a client close the connection with server?
//						printf("retained!!!\n");
//						FD_CLR(m_clientFds[i], &watchFds);
////						::shutdown(m_clientFds[i], 2);
//						::close(m_clientFds[i]);
//
//						m_clientFds[i] = -1;
//						continue;
//					}
//					read(m_clientFds[i], buf, nread);
//
//					int retCode = answerRequest(m_clientFds[i], buf);
//					if (1 == retCode) {
//						printf("Successfully answer query from client %d.\n",
//								m_clientFds[i]);
//					} else if (-1 == retCode) {
//						shutdown();
//						stop = true;
//						printf("Shut Down!\n");
//					} else {
//						printf("Failed query from client %d.\n",
//								m_clientFds[i]);
//					}
//
//				}
//			}
//			break;
//		} /*end of switch*/
//	}
//	FD_ZERO(&watchFds);
//	FD_ZERO(&readFds);
//	delete buf;
//}

/**
 * shut down the server
 */
void ClaimsServer::shutdown() {

	for (int i = 0; i < MAXCONN; ++i) {
		if (m_clientFds[i] > 0)
			close(m_clientFds[i]);
	}
	close(m_fd);
}

int ClaimsServer::write(const int fd, const ClientResponse& res) const {

	int ret = 0;
	char *buffer;
	int length = res.serialize(buffer);
	ret = ::write(fd, buffer, length);
	printf("Server: %d bytes send!\n", ret);
	free(buffer);
	return ret;
}
