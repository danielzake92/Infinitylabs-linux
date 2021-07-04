#include <iostream> // printing
#include "thread_safe_que.hpp"

using namespace ilrd_rd100;
using namespace std;
/*****************************************************************************/
const size_t NUM_OF_THREADS = 4;
pthread_t thread_id[NUM_OF_THREADS] = {0};

TSQueue< size_t, PriorityQueue<size_t> >queue1;
/*****************************************************************************/
void *PopingThread(void *arg)
{
    (void)arg;
    queue1.Pop();

    return NULL;
}

void *PushingThread(void *arg)
{
    queue1.Push((size_t)arg);
    queue1.Push((size_t)arg + 1);

    return NULL;
}
/********************************** driver ***********************************/
int main()
{   
    size_t i = 0;
    for (i = 0; (NUM_OF_THREADS / 2) > i; ++i)
    {
        pthread_create((&thread_id[i]), NULL, PopingThread, NULL);
    }
    for (; NUM_OF_THREADS > i; ++i)
    {
        pthread_create((&thread_id[i]), NULL, PushingThread, (void *)(i));
    }

    for (i = 0; NUM_OF_THREADS > i; ++i)
    {
        pthread_join(thread_id[i], NULL);
    }
    
    //cout << "front: " << queue1.Front() << endl;
    //cout << "back: " <<queue1.Back() << endl;
    cout << "size: " << queue1.Size() << endl;
    cout << "is empty: " <<queue1.Empty() << endl;
    
    return 0;
}
/*****************************************************************************/