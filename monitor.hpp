//Dorota Wojciechowicz
#ifndef __monitor_h
#define __monitor_h
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

class Monitor
{
private:
    int bufor;
    int max;
    pthread_mutex_t mtx;
    pthread_cond_t full;
    pthread_cond_t empty;
   // FILE *buffer;
public:
    Monitor(int m) : bufor(0), max(m)
    {
        pthread_mutex_init(&mtx,NULL);
        pthread_cond_init(&full,NULL);
        pthread_cond_init(&empty,NULL);
    //    buffer = fopen("buffer.txt", "w");
    }
    ~Monitor()
    {
        pthread_mutex_destroy(&mtx);
        pthread_cond_destroy(&full);
        pthread_cond_destroy(&empty);
      //  fclose(buffer);
    }
    void insert(int i)
    {
        pthread_mutex_lock(&mtx);
        while(bufor+i>max)
        {
            pthread_cond_wait(&full, &mtx);
        }
        bufor=bufor+i;
        std::cout<<" Insert stan bufora: "<<bufor<<std::endl;
        if(bufor>max/2)
        pthread_cond_signal(&empty);
        else
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mtx);
    }
    void remove(int i)
    {
        pthread_mutex_lock(&mtx);
        while(bufor-i<0)
        {
            pthread_cond_wait(&empty, &mtx);
        }
        bufor=bufor-i;
        std::cout<<"Remove stan bufora: "<<bufor<<std::endl;
        if(bufor<max/2)
        pthread_cond_signal(&full);
        else
        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mtx);
    }
};
#endif
