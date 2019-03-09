//Dorota Wojciechowicz
#include <iostream>
#include <unistd.h>
#include "monitor.hpp"

//using namespace std;
//Monitor monit;
struct numbers
{
    int prodnum;
    int consnum;
    int sprodint;
    int bprodint;
    int sconsint;
    int bconsint;
    int m;
    Monitor* monit;
};
numbers n;

int random(int a, int b)
{
    int c=(rand()%(b-a))+a;
    return c;
}
void *producer(void *ptr)
{
    int i;
    while(true)
    {
        i=random(n.sprodint,n.bprodint);
        n.monit->insert(i);
        sleep(1);
    }
}
void *consumer(void *ptr)
{
    int i;
    while(true)
    {
        i=random(n.sconsint,n.bconsint);
        n.monit->remove(i);
        sleep(1);
    }
}
int main(int argc, char *argv[])
{
    if(argc<8)
    {
        std::cout << "Nieprawidlowa liczba argumentow" << std::endl;
        return 1;
    }
//   int prodnum;
//   int consnum;

    n.prodnum=atoi(argv[1]);
    n.consnum=atoi(argv[2]);
    /*   int sprodint;
       int bprodint;
       int sconsint;
       int bconsint;*/
    n.sprodint=atoi(argv[3]);
    n.bprodint=atoi(argv[4]);
    n.sconsint=atoi(argv[5]);
    n.bconsint=atoi(argv[6]);
//   int m;
    n.m=atoi(argv[7]);
    n.monit=new Monitor(n.m);
    pthread_t prod[n.prodnum];
    pthread_t cons[n.consnum];
    int i;
    for(i=0; i<n.prodnum; ++i)
    {
        pthread_create(&(prod[i]), NULL, producer, &n);
    }
    for(i=0; i<n.consnum; ++i)
    {
        pthread_create(&(cons[i]), NULL, consumer, &n);
    }
    for (i=0; i<n.prodnum; ++i)
    {
        pthread_join(prod[i], NULL);
    }
    for (i=0; i<n.consnum; ++i)
    {
        pthread_join(cons[i], NULL);
    }
    delete n.monit;
    return 0;
}
