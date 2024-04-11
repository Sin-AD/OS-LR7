#include <pthread.h>
#include <stdio.h>
char Ibuk[ ]="abcdefghijklmnoprstv";
pthread_t tid1, tid2, tid3;

#define ERROR_CREATE_THREAD -11
#define ERROR_JOIN_THREAD -12
void procthread13(void *arg)
{
  // запрещаем отмену (нельзя будет отменить из главного потока)
  // причем снять запрет можно только из этого потока, В не в внешнего 
  pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL); 
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);

  // собственно получаем переданный аргуммент
  int flag = (int)arg;
  
  int k, j;
  for (k=0; k<20; k++)
    {
    // процедура общая, потоки разные, действия разные 
    if(flag == 1) {
    
        printf("\033[%d;20H\033[1; 34m", k+1);
        // выводим символ N-нити * 2 раз
            for (j=0;j<(int)arg*2; j++)
                printf("%c",Ibuk[k]);
            printf("\n");
            usleep(1011000);
        }
    else {
        // на 12 шаге снова разрешаем отмену
        if (k == 12)
            pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
         if (k == 15 || k == 16)
            // просматриваем очередь поступивших запросов на отмену, если они есть, отменяем нить. pthread_testcancel();
            printf("\033[%d;60H\033[31m",k+1);
            for (j=0; j<(int)arg*2; j++)
                printf("%c",Ibuk[k]);
            printf("\n");
            usleep(1031000);
        }
    }
}

void procthread2 (void *arg)
{
    int k, j;
    for (k=0; k<20; k++)
    {
        printf("\033[%d;40H\033[1;32m",k+1); 
        for (j=0; j<(int)arg*2; j++)
            printf("%c",Ibuk[k]);
        printf("\n");
        usleep(1021000);    
    }
}
void main()
{
    int k;
    int rc;
    printf("\033[2]\n");
    rc=pthread_create(&tid1, NULL, (void*) procthread13, (void*)1); 
    rc=pthread_create(&tid2, NULL, (void*) procthread2, (void*)2); 
    rc-pthread_create(&tid3, NULL, (void*) procthread13, (void*)3); 
    for (k=0; k<20; k++)
    {
        printf("\033[%d;1H\033[37m",k+1); 
        printf("%c: \n",Ibuk[k]);
        // пытается отменить нити 1 и 3
        if (k==5)
        {
            pthread_cancel(tid1);
            printf("\033[25;1H");
            printf("\033[25;1H\033[38mAttempt to cancel thread1\n");
}
        if (k == 10)
{
            pthread_cancel(tid3);
            printf("\033[25;1H");
            printf("\033[25;1H\033[38mAttempt to cancel thread3\n");
}
            usleep(1000000);
}
printf("\033[25;1H");
    printf("\033[25; 1H\033[34mPress any key...\n");
getchar();
printf("\033[0m"); 
}