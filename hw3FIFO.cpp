#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <string>
#include <list>
#include <sstream>
#include <stack>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <algorithm> 
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <semaphore.h>

using namespace std;
using std::cout;
using std::endl;

string sendrequest(string request, char* ptr)
{
	int n = request.size();
	string nnn;
	for (int x = 0; x < n; x++)
	{
		ptr[x] = request[x];
		nnn += ptr[x];
	}

	return nnn;
}

int findindex(int a[], int size, int thing)
{

	for (int x = 0; x < size; x++)
	{
		if (a[x] == thing)
		{
			return x;
		}
	}


	return -1;
}

bool checkend(char* ptr)
{
	if (ptr[0] == 'e' && ptr[1] == 'n' && ptr[2] == 'd')
	{
		return true;
	}

	return false;
}

bool checkempty(char* ptr)
{
	for (int x = 0; x < 11; x++)
	{
		if (ptr[x] != '\0')
			return false;
	}
	return true;
}

string readrequest(char* ptr)
{
	string nnn;
	for (int x = 0; x < 11; x++)
	{
		nnn += ptr[x];
	}

	return nnn;
}

void clearrequest(char* ptr)
{
	for (int x = 0; x < 11; x++)
	{
		ptr[x] = '\0';
	}
}

string hextobin(string hex)
{
	string bin = "";

	for (int x = 0; x < hex.length(); x++)
	{
		char y = hex[x];

		switch (y)
		{
		case '0': bin += "0000";
			break;
		case '1': bin += "0001";
			break;
		case '2': bin += "0010";
			break;
		case '3': bin += "00011";
			break;
		case '4': bin += "0100";
			break;
		case '5': bin += "0101";
			break;
		case '6': bin += "0110";
			break;
		case '7': bin += "0111";
			break;
		case '8': bin += "1000";
			break;
		case '9': bin += "1001";
			break;
		case 'A': bin += "1010";
			break;
		case 'B': bin += "1011";
			break;
		case 'C': bin += "1100";
			break;
		case 'D': bin += "1101";
			break;
		case 'E': bin += "1110";
			break;
		case 'F': bin += "1111";
			break;
		default:
			break;
		}
	}
	return bin;
}

int bintodec(int bin)
{
	int dec = 0;
	int base = 1;
	int rem = 0;
	int num = bin;

	while (num > 0)
	{
		rem = num % 10;
		dec = dec + rem * base;
		base = base * 2;
		num = num / 10;
	}


	return dec;
}



int main() {

	int tp;
	int sl;
	int ps;
	int r;
	int min;
	int max;
	int k;

	int val;

	ifstream  file1("hw3input.txt");

	string str2;

	getline(file1, str2);
	tp = atoi(str2.c_str());
	getline(file1, str2);
	sl = atoi(str2.c_str());
	getline(file1, str2);
	ps = atoi(str2.c_str());
	getline(file1, str2);
	r = atoi(str2.c_str());
	getline(file1, str2);
	min = atoi(str2.c_str());
	getline(file1, str2);
	max = atoi(str2.c_str());
	getline(file1, str2);
	k = atoi(str2.c_str());

	int pidk[k];
	int sizek[k];

	list<string> pidr;
	list<string> addrr;

	for (int x = 0; x < k; x++)
	{
		getline(file1, str2);
		str2 += ";";

		stringstream ss2(str2);
		string token;

		while (ss2.peek() != ';')
		{
			if (ss2.peek() == ' ')
			{
				ss2.ignore();
				pidk[x] = atoi(token.c_str());
				token = "";
			}
			else
			{
				token += ss2.peek();
				ss2.ignore();
			}
		}
		sizek[x] = atoi(token.c_str());
	}

	while (getline(file1, str2))
	{
		str2 += ";";

		stringstream ss2(str2);
		string token;

		while (ss2.peek() != ';')
		{
			if (ss2.peek() == ' ')
			{
				ss2.ignore();
				pidr.push_back(token);
				token = "";
			}
			else
			{
				token += ss2.peek();
				ss2.ignore();
			}
		}


		if (token.substr(0, 2) == "0x")
		{
			addrr.push_back(hextobin(token.substr(2)));
			val = hextobin(token.substr(2)).length();

		}
		else
		{
			addrr.push_back(token);
		}
	}
	file1.close();
	//shared memory for requests
	int shmid1;
	key_t key = 1238591;
	size_t size = sizeof(char) * (8 + 3);

	shmid1 = shmget(key, size, 0666 | IPC_CREAT);
	if (shmid1<0)
	{
		perror("shmget");
		exit(1);
	}
	char *request1 = (char *)shmat(shmid1, 0, 0);
	if (request1<0)
	{
		perror("shmat");
		exit(1);
	}

	int shmid2;
	key = 1238591 + 1;
	size = sizeof(char) * (8 + 3);

	shmid2 = shmget(key, size, 0666 | IPC_CREAT);
	if (shmid2<0)
	{
		perror("shmget");
		exit(1);
	}
	char *request2 = (char *)shmat(shmid2, 0, 0);
	if (request2<0)
	{
		perror("shmat");
		exit(1);
	}

	int shmid3;
	key = 1238591 + 2;
	size = sizeof(char) * (8 + 3);

	shmid3 = shmget(key, size, 0666 | IPC_CREAT);
	if (shmid3<0)
	{
		perror("shmget");
		exit(1);
	}
	char *request3 = (char *)shmat(shmid3, 0, 0);
	if (request3<0)
	{
		perror("shmat");
		exit(1);
	}
	// shared memory for sempahores
	int shmid4;
	key = 1238591 + 3;
	size = sizeof(sem_t);

	shmid4 = shmget(key, size, 0666 | IPC_CREAT);
	if (shmid4<0)
	{
		perror("shmget");
		exit(1);
	}
	sem_t *sema1 = (sem_t *)shmat(shmid4, 0, 0);
	if (sema1<0)
	{
		perror("shmat");
		exit(1);
	}

	int shmid5;
	key = 1238591 + 4;

	shmid5 = shmget(key, size, 0666 | IPC_CREAT);
	if (shmid5<0)
	{
		perror("shmget");
		exit(1);
	}
	sem_t *sema2 = (sem_t *)shmat(shmid5, 0, 0);
	if (sema2<0)
	{
		perror("shmat");
		exit(1);
	}

	int shmid6;
	key = 1238591 + 5;

	shmid6 = shmget(key, size, 0666 | IPC_CREAT);
	if (shmid6<0)
	{
		perror("shmget");
		exit(1);
	}
	sem_t *sema3 = (sem_t *)shmat(shmid6, 0, 0);
	if (sema3<0)
	{
		perror("shmat");
		exit(1);
	}
	int shmid7;
	key = 1238591 + 6;
	size = sizeof(sem_t);

	shmid7 = shmget(key, size, 0666 | IPC_CREAT);
	if (shmid7<0)
	{
		perror("shmget");
		exit(1);
	}
	sem_t *sema4 = (sem_t *)shmat(shmid7, 0, 0);
	if (sema4<0)
	{
		perror("shmat");
		exit(1);
	}

	int shmid8;
	key = 1238591 + 7;

	shmid8 = shmget(key, size, 0666 | IPC_CREAT);
	if (shmid8<0)
	{
		perror("shmget");
		exit(1);
	}
	sem_t *sema5 = (sem_t *)shmat(shmid8, 0, 0);
	if (sema5<0)
	{
		perror("shmat");
		exit(1);
	}

	int shmid9;
	key = 1238591 + 8;

	shmid9 = shmget(key, size, 0666 | IPC_CREAT);
	if (shmid9<0)
	{
		perror("shmget");
		exit(1);
	}
	sem_t *sema6 = (sem_t *)shmat(shmid9, 0, 0);
	if (sema6<0)
	{
		perror("shmat");
		exit(1);
	}

	//initialize sema
	if (sem_init(sema1, 1, 0) < 0) {
		perror("sem_init");
		exit(1);
	}
	if (sem_init(sema2, 1, 0) < 0) {
		perror("sem_init");
		exit(1);
	}
	if (sem_init(sema3, 1, 0) < 0) {
		perror("sem_init");
		exit(1);
	}
	if (sem_init(sema4, 1, 0) < 0) {
		perror("sem_init");
		exit(1);
	}
	if (sem_init(sema5, 1, 0) < 0) {
		perror("sem_init");
		exit(1);
	}
	if (sem_init(sema6, 1, 0) < 0) {
		perror("sem_init");
		exit(1);
	}

	int segmentnumber = (log(sl) / log(2));
	int pagenumber = val - ((segmentnumber + log(ps) / log(2)));
	int pl = pow(pagenumber, 2);

	int pid;
	pid = fork();

	if (pid == 0)
	{
		string frames[tp][ps];
		int segmenttable[k][sl];
		int pagetable[k][sl][pl];
		list<string> fifo[k];
		int pf[k];
		list<int> framesavailable;

		for (int x = 0; x < k; x++)
		{
			pf[x] = 0;
			for (int y = 0; y < sl; y++)
			{
				for (int z = 0; z < pl; z++)
				{
					pagetable[x][y][z] = -1;
				}
			}
		}

		for (int x = 0; x < tp; x++)
		{
			framesavailable.push_back(x);
		}

		//page management process
		while (true)
		{
			//cout << "page management starts waiting semaphore 4, main" << endl;
			if (sem_wait(sema4) < 0) {
				perror("sem_wait");
			}
			//	cout << "page management finished waiting semaphore 4, main" << endl;

			if (checkend(request1))
			{
			//	cout << "endpm" << endl;
				sendrequest("end", request2);
				clearrequest(request1);
				//	cout << "page management signals semaphore 5, disk driver" << endl;
				if (sem_post(sema5) < 0) {
					perror("sem_post");
				}


				for (int x = 0; x < k; x++)
				{
					cout << "page fault: "<<pidk[x] <<" "<<pf[x]<< endl;
				}
				break;
			}


			cout << "request: " + readrequest(request1) << endl;
			string request = readrequest(request1);
		//	sendrequest(readrequest(request1), request2);
			clearrequest(request1);
			//check requested addr in frames

			string pid = request.substr(0, 3);
			string addr = request.substr(3);

			int pi = findindex(pidk, k, atoi(pid.c_str()));

			if (addr.substr(0,2)=="-1")
			{
				//cout << addr << endl;
				for (int x = 0; x < sl; x++)
				{
					for (int y = 0; y < pl; y++)
					{
						if (pagetable[pi][x][y] != -1)
						{
							framesavailable.push_back(pagetable[pi][x][y]);
							pagetable[pi][x][y] = -1;
						//	cout << "g" << endl;
						}
					}
				}
				if (sem_post(sema1) < 0) {
					perror("sem_post");
				}
				continue;
			}

			
			int segi = bintodec(atoi(addr.substr(0, segmentnumber).c_str()));
			int pagi = bintodec(atoi(addr.substr(segmentnumber, pagenumber).c_str()));
			string offset = addr.substr(segmentnumber + pagenumber);

			bool inframes = false;
			if (pagetable[pi][segi][pagi] != -1)
			{
				inframes = true;
			}
			//check free frames
			if (!inframes)
			{
				//cout << "pf" << endl;

				//count page fault
				pf[pi] +=1;

				if (fifo[pi].size()<r)
				{
					//has free
				//	cout << "hf" << endl;
					fifo[pi].push_back(addr.substr(0, segmentnumber + pagenumber));

			//		cout << addr.substr(0, segmentnumber + pagenumber) << endl;

					int frameindex = framesavailable.front();

					framesavailable.pop_front();

					pagetable[pi][segi][pagi] = frameindex;

			//		cout << pagetable[pi][segi][pagi] << endl;

					//read request
					sendrequest("read", request2);
					//	cout << "page management signals semaphore 5, disk driver" << endl;
					if (sem_post(sema5) < 0) {
						perror("sem_post");
					}


					//		cout << "page management starts waiting semaphore 2, disk driver" << endl;
					if (sem_wait(sema2) < 0) {
						perror("sem_wait");
					}
					//		cout << "page management finished waiting semaphore 2, disk driver" << endl;



					//		cout << "page management signals semaphore 1, main" << endl;
					if (sem_post(sema1) < 0) {
						perror("sem_post");
					}
				}
				else
				{
					//page replacement
				//	cout << "pr" << endl;
					//		cout << "page replacement" << endl;
					int segi2 = bintodec(atoi(fifo[pi].front().substr(0, segmentnumber).c_str()));
					int pagi2 = bintodec(atoi(fifo[pi].front().substr(segmentnumber, pagenumber).c_str()));
					fifo[pi].pop_front();

					int framereplace = pagetable[pi][segi2][pagi2];

					pagetable[pi][segi2][pagi2] = -1;

					//write request
					sendrequest("write", request2);
					//	cout << "page management signals semaphore 5, disk driver" << endl;
					if (sem_post(sema5) < 0) {
						perror("sem_post");
					}


					//	cout << "page management starts waiting semaphore 2, disk driver" << endl;
					if (sem_wait(sema2) < 0) {
						perror("sem_wait");
					}
					//cout << "page management finished waiting semaphore 2, disk driver" << endl;


					fifo[pi].push_back(addr.substr(0, segmentnumber + pagenumber));

				//	cout << addr.substr(0, segmentnumber + pagenumber) << endl;
					pagetable[pi][segi][pagi] = framereplace;



					//read request
					sendrequest("read", request2);
					//	cout << "page management signals semaphore 5, disk driver" << endl;
					if (sem_post(sema5) < 0) {
						perror("sem_post");
					}


					//	cout << "page management starts waiting semaphore 2, disk driver" << endl;
					if (sem_wait(sema2) < 0) {
						perror("sem_wait");
					}
					//	cout << "page management finished waiting semaphore 2, disk driver" << endl;



					//	cout << "page management signals semaphore 1, main" << endl;
					if (sem_post(sema1) < 0) {
						perror("sem_post");
					}
				}
			}
			else
			{
			//	cout << "in frame" << endl;
				//	cout << "page management signals semaphore 1, main" << endl;

				if (sem_post(sema1) < 0) {
					perror("sem_post");
				}
			}

		}

		if (shmdt(request1) == -1)
		{
			perror("shmdt");
			exit(1);
		}
		if (shmdt(request2) == -1)
		{
			perror("shmdt");
			exit(1);
		}
		if (shmdt(request3) == -1)
		{
			perror("shmdt");
			exit(1);
		}
		if (shmdt(sema1) == -1)
		{
			perror("shmdt");
			exit(1);
		}
		if (shmdt(sema2) == -1)
		{
			perror("shmdt");
			exit(1);
		}
		if (shmdt(sema3) == -1)
		{
			perror("shmdt");
			exit(1);
		}
		if (shmdt(sema4) == -1)
		{
			perror("shmdt");
			exit(1);
		}
		if (shmdt(sema5) == -1)
		{
			perror("shmdt");
			exit(1);
		}
		if (shmdt(sema6) == -1)
		{
			perror("shmdt");
			exit(1);
		}

	}
	else
	{
		pid = fork();

		if (pid == 0)
		{
			//disk driver process
			while (true)
			{
				//	cout << "disk driver starts waiting semaphore 5, page management" << endl;
				if (sem_wait(sema5) < 0) {
					perror("sem_wait");
				}
				//	cout << "disk finished waiting semaphore 5, page management" << endl;
				if (checkend(request2))
				{
				//	cout << "enddd" << endl;
					sendrequest("end", request3);
					clearrequest(request2);
					//		cout << "disk driver signals semaphore 6, disk" << endl;
					if (sem_post(sema6) < 0) {
						perror("sem_post");
					}
					break;
				}

				//do disk driver request
			//	cout << readrequest(request2) << endl;
				sendrequest(readrequest(request2), request3);
				clearrequest(request2);


				//	cout << "disk driver signals semaphore 6, disk" << endl;
				if (sem_post(sema6) < 0) {
					perror("sem_post");
				}

				//	cout << "disk driver starts waiting semaphore 3, disk driver" << endl;
				if (sem_wait(sema3) < 0) {
					perror("sem_wait");
				}
				//cout << "disk finished waiting semaphore 3, disk driver" << endl;


				//	cout << "disk driver signals semaphore 2, page management" << endl;
				if (sem_post(sema2) < 0) {
					perror("sem_post");
				}
			}

			if (shmdt(request1) == -1)
			{
				perror("shmdt");
				exit(1);
			}
			if (shmdt(request2) == -1)
			{
				perror("shmdt");
				exit(1);
			}
			if (shmdt(request3) == -1)
			{
				perror("shmdt");
				exit(1);
			}
			if (shmdt(sema1) == -1)
			{
				perror("shmdt");
				exit(1);
			}
			if (shmdt(sema2) == -1)
			{
				perror("shmdt");
				exit(1);
			}
			if (shmdt(sema3) == -1)
			{
				perror("shmdt");
				exit(1);
			}
			if (shmdt(sema4) == -1)
			{
				perror("shmdt");
				exit(1);
			}
			if (shmdt(sema5) == -1)
			{
				perror("shmdt");
				exit(1);
			}
			if (shmdt(sema6) == -1)
			{
				perror("shmdt");
				exit(1);
			}
		}
		else
		{
			pid = fork();

			if (pid == 0)
			{
				//disk process


				while (true)
				{
					//	cout << "disk starts waiting semaphore 6, disk driver" << endl;
					if (sem_wait(sema6) < 0) {
						perror("sem_wait");
					}
					//	cout << "disk finished waiting semaphore 6, disk driver" << endl;
					if (checkend(request3))
					{
				//		cout << "endd" << endl;
						clearrequest(request3);
						break;
					}

					//do disk request
				//	cout << readrequest(request3) << endl;
					string request = readrequest(request3);

					if (request.substr(0,4)=="read")
					{
					//	cout << request <<"rrrrr"<< endl;
						//sleep(1);
					}
					else
					{
					//	cout << request << endl;
						//sleep(2);
					}

					clearrequest(request3);

					//cout << "disk signals semaphore 3, disk driver" << endl;
					if (sem_post(sema3) < 0) {
						perror("sem_post");
					}
				}

				if (shmdt(request1) == -1)
				{
					perror("shmdt");
					exit(1);
				}
				if (shmdt(request2) == -1)
				{
					perror("shmdt");
					exit(1);
				}
				if (shmdt(request3) == -1)
				{
					perror("shmdt");
					exit(1);
				}
				if (shmdt(sema1) == -1)
				{
					perror("shmdt");
					exit(1);
				}
				if (shmdt(sema2) == -1)
				{
					perror("shmdt");
					exit(1);
				}
				if (shmdt(sema3) == -1)
				{
					perror("shmdt");
					exit(1);
				}
				if (shmdt(sema4) == -1)
				{
					perror("shmdt");
					exit(1);
				}
				if (shmdt(sema5) == -1)
				{
					perror("shmdt");
					exit(1);
				}
				if (shmdt(sema6) == -1)
				{
					perror("shmdt");
					exit(1);
				}
			}
			else
			{
				//main process
				sleep(1);
				int s = pidr.size();
				for (int x = 0; x < s; x++)
				{
					sendrequest(pidr.front() + addrr.front(), request1);
					//	cout << "main signals semaphore 4, page management" << endl;
					if (sem_post(sema4) < 0) {
						perror("sem_post");
					}


					//	cout << "main starts waiting semaphore 1, page management" << endl;
					if (sem_wait(sema1) < 0) {
						perror("sem_wait");
					}
					//cout << "main finished waiting semaphore 1, page management" << endl;
					pidr.pop_front();
					addrr.pop_front();
				}
				sendrequest("end", request1);
				//cout << "main signals semaphore 4, page management" << endl;
				if (sem_post(sema4) < 0) {
					perror("sem_post");
				}
			}
		}
	}
	if (pid != 0)
	{
		wait(NULL);
		wait(NULL);
		wait(NULL);

		if (shmdt(request1) == -1)
		{
			perror("shmdt");
			exit(1);
		}
		if (shmdt(request2) == -1)
		{
			perror("shmdt");
			exit(1);
		}
		if (shmdt(request3) == -1)
		{
			perror("shmdt");
			exit(1);
		}
		if (shmdt(sema1) == -1)
		{
			perror("shmdt");
			exit(1);
		}
		if (shmdt(sema2) == -1)
		{
			perror("shmdt");
			exit(1);
		}
		if (shmdt(sema3) == -1)
		{
			perror("shmdt");
			exit(1);
		}
		if (shmdt(sema4) == -1)
		{
			perror("shmdt");
			exit(1);
		}
		if (shmdt(sema5) == -1)
		{
			perror("shmdt");
			exit(1);
		}
		if (shmdt(sema6) == -1)
		{
			perror("shmdt");
			exit(1);
		}

		if (shmctl(shmid1, IPC_RMID, 0) == -1)
		{
			perror("shmctl");
			exit(1);
		}
		if (shmctl(shmid2, IPC_RMID, 0) == -1)
		{
			perror("shmctl");
			exit(1);
		}
		if (shmctl(shmid3, IPC_RMID, 0) == -1)
		{
			perror("shmctl");
			exit(1);
		}
		if (shmctl(shmid4, IPC_RMID, 0) == -1)
		{
			perror("shmctl");
			exit(1);
		}
		if (shmctl(shmid5, IPC_RMID, 0) == -1)
		{
			perror("shmctl");
			exit(1);
		}
		if (shmctl(shmid6, IPC_RMID, 0) == -1)
		{
			perror("shmctl");
			exit(1);
		}
		if (shmctl(shmid7, IPC_RMID, 0) == -1)
		{
			perror("shmctl");
			exit(1);
		}
		if (shmctl(shmid8, IPC_RMID, 0) == -1)
		{
			perror("shmctl");
			exit(1);
		}
		if (shmctl(shmid9, IPC_RMID, 0) == -1)
		{
			perror("shmctl");
			exit(1);
		}
	}

}