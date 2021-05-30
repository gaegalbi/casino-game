#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

/*

int blackjackServer() {

	SOCKET s ,cs; // 서버와 클라이언트의 소켓 핸들 구조체
	WSADATA wasData; // 원속정보를 담을 구조체 
	SOCKADDR_IN sin, cli_addr; //서버와 클라이언트의 소켓주소 정보를 담을 구조체

	if (WSAStartup(WINSOCK_VERSION, &wasData) != 0) { //성공이 wasData에 원속정보값을 채워준다, Ws2_32.dill 을 불러와 메모리에 적재시켜준다
		printf("WSAStartup() 실패 에러코드 : %d\n", WasGetLastError());//에러시 0을 반환
		return -1;
	}

	//소켓생성 ,socket(사용할 주소치계(IPv4),
	//소켓타입(연결지향형/소켓이 연결된 클라이언트와만 데이터송수신
	//데이터 전송방식(TCP))
	s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (s == INVALID_SOCKET) {
		printf("소켓생성 실패 에러코드 : %d\n", WasGetLastError()); //socket 함수로 생성 실패시 INVALID_SOCKET 반환
		WASClenup(); //WAS소켓 반납
		return -1;
	}
	
	// 소켓생성시 소켓 주소 정보채워줌
	sin.sin_family = AF_INET;
	sin.sin_port = htons(5000); //서버포트 설정
	sin.sin_addr.S_un.S_addr = htonl(ADDR_ANY);
	
	//bind
	if (bind(s, (SOCKADDR*)&sin, sizeof(sin)) == SOCKET_ERROR) {
		printf("bind() 실패 에러코드 : %d\n", WasGetLastError()); //socket 함수로 생성 실패시 INVALID_SOCKET 반환
		closesocket(s); //생성한 소켓 제거
		WASClenup(); //WAS소켓 반납
		return -1;
		}
	
	//Listen
	if (listen(s, 1) != 0){ //1명의 접속 인원을 받음, 요청을 Queue 에 저장.
		printf("listen 모드 설정 실패, 에러코드 : %d", WasGetLastError());
		closesocket(s); //생성한 소켓 제거
		WASClenup(); //WAS소켓 반납
		return -1;

	}

	printf("서버가동\n");
	printf("클라이언트의 접속을 기다리는중입니다.\n");


	//Accept
	int cli_size = sizeof(cli_addr); //accpet함수에 cli_dddr의 크기를 주소로 넘겨주기위한 변수

	//클라이언트 연결, 접속이 있을때 까지 무한대기, 
	//연결후 클라이언트 소켓핸들 cs 에 클라이언트 정보를 가지고있는다.
	//accpet 함수는 listen이 만들어논 Queue에서 접속 시도한 클라이언트의 연결을 처리한다. 없으면 무한대기
	//accpet(서버소켓, 클라이언트소켓정보객체, 클라이언트 소켓정보객체 크기)
	cs = accpet(s, (SOCKADDR*)&cli_addr, &cli_size);
	if (cs == INVALID_SOCKET) {
		printf("접속승인 실패, 에러코드 : %d", WasGetLastError());
		closesocket(s); //생성한 소켓 제거
		WASClenup(); //WAS소켓 반납
		return -1;
	}

	//송수신


	return 0;
}

*/

void ErrorHandling(char* message);



int test1(int argc, char* argv[])

{

	WSADATA wsaData;

	SOCKET hServSock, hClntSock;

	SOCKADDR_IN servAddr, clntAddr;



	int szClntAddr;

	char message[] = "Hello World!";

	if (argc != 2)

	{

		printf("Usage:%s <port>\n", argv[0]);

		exit(1);

	}



	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) //소켓 라이브러리 초기화

		ErrorHandling("WSAStartup() error!");



	hServSock = socket(PF_INET, SOCK_STREAM, 0); //소켓생성

	if (hServSock == INVALID_SOCKET)

		ErrorHandling("socket() error");



	memset(&servAddr, 0, sizeof(servAddr));

	servAddr.sin_family = AF_INET;

	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	servAddr.sin_port = htons(atoi(argv[1]));



	if (bind(hServSock, (SOCKADDR*)&servAddr, sizeof(servAddr)) == SOCKET_ERROR) //소켓에 IP주소와 PORT 번호 할당

		ErrorHandling("bind() error");



	if (listen(hServSock, 5) == SOCKET_ERROR) //listen 함수호출을 통해서 생성한 소켓을 서버 소켓으로 완성

		ErrorHandling("listen() error");



	szClntAddr = sizeof(clntAddr);

	hClntSock = accept(hServSock, (SOCKADDR*)&clntAddr, &szClntAddr); //클라이언트 연결요청 수락하기 위해 accept함수 호출

	if (hClntSock == INVALID_SOCKET)

		ErrorHandling("accept() error");



	send(hClntSock, message, sizeof(message), 0); //send함수 호출을 통해서 연결된 클라이언트에 데이터를 전송

	closesocket(hClntSock);

	closesocket(hServSock);

	WSACleanup(); //프로그램 종료 전에 초기화한 소켓 라이브러리 해제

	return 0;

}



void ErrorHandling(char* message)

{

	fputs(message, stderr);

	fputc('\n', stderr);

	exit(1);

}




