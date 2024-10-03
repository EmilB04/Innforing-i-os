#include <stdio.h>
#include <pthread.h>

int count = 0;
pthread_mutex_t m_lock;

void *increase()
{ 
   int i; 
   for(i = 0; i < 1e8; ++i){
      pthread_mutex_lock(&m_lock); // Låser mutex før økning
      count ++;
      pthread_mutex_unlock(&m_lock); // Låser opp mutex etter økning
   }
}

void *decrease()
{  
   int i;
   for(i = 0; i < 1e8; ++i){
      pthread_mutex_lock(&m_lock);  // Låser mutex før reduksjon
      count--; 
      pthread_mutex_unlock(&m_lock);  // Låser opp mutex etter reduksjon
   }
}

int main()
{ 
   pthread_t thread1, thread2;

   pthread_mutex_init(&m_lock, NULL);

   pthread_create(&thread1, NULL, increase, NULL);
   pthread_create(&thread2, NULL, decrease, NULL);
   
   pthread_join(thread1, NULL); 
   pthread_join(thread2, NULL);

   pthread_mutex_destroy(&m_lock);
   
   printf("count = %d\n", count);
}
