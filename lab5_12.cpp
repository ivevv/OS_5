//Иванчук Евгения. 9894

#include <iostream>
#include <fstream>
#include <pthread.h>
#include <unistd.h>
#include <cstdlib>
#include <semaphore.h>
#include <string.h>
#include <fcntl.h>

using namespace std;

sem_t sem;
bool flag = true;

void *th(void *arg)
{
	int n = 3;
	int val = 2;
	ofstream res;
	res.open("lab5.txt", ios::app);
	//cout << "begun thread" << endl; //trying to see at which point the program is freezing
	while (flag == 1)
	{
		sem_wait(&sem);
		//cout << "opened semaphore" << endl;
		if (res.is_open())
		{
			//cout << "opened file" << endl;
			for (int i = 0; i < n; i++)
			{
				if (flag != 1)
				break;
				res << val << flush;
				cout << val << " ";
				cout.flush();
				sleep(1);
			}
		}
		else
		{
			cout << "Cant open file" << endl;
		}
		sem_post(&sem);
		sleep(1);
	}
	res.close();
	return NULL;
}

int main()
{
	sem_open("/sem", O_CREAT, 0644, 1);
	pthread_t th1;
	pthread_create(&th1, NULL, th, NULL);
	//cout << "created thread" << endl;
	getchar();
	flag = false;
	pthread_join(th1, NULL);
	//cout << "joined thread" << endl;
	sem_close(&sem);
	sem_unlink("/sem");
	return 0;
}
