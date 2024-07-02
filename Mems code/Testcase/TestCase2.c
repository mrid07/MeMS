// include other header files as needed
#include"mems.h"


int main(int argc, char const *argv[])
{mems_init();
    void* ptr[10];
    //void* d;//=(void*)mems_malloc(sizeof(int)*250);
    mems_print_stats();
    /*void* c=(void*)mems_malloc(sizeof(int)*1024);
    printf("Virtual address %lu\n",(unsigned long)c);*/
    for(int i=0;i<10;i++){
        ptr[i]=(void*)mems_malloc(sizeof(int)*250);
        //printf("%lu%lu",);
        printf("Virtual address %lu\t\t",(unsigned long)ptr[i]);
        printf("Physical address %lu\n",(unsigned long)mems_get(ptr[i]));
    }
    mems_print_stats();
    printf("Completed successfully");
    void * a1=mems_get(ptr[0]);
    printf("Virtual address %lu\n",(unsigned long)a1);
    mems_free(ptr[0]);

    mems_free(ptr[3]);
    mems_free(ptr[4]);
    /*mems_free(ptr[2]);
    mems_free(ptr[5]);*/
    /*for(int i=0;i<10;i++){
        //printf("%lu%lu",);
        printf("Physical address %lu\n",(unsigned long)mems_get(ptr[i]));
    }*/


    mems_print_stats();
    void* a=(void*)mems_malloc(sizeof(int)*24);
    void* b=(void*)mems_malloc(sizeof(int)*250);
    void* c=(void*)mems_malloc(sizeof(int)*250);
    void* d=(void*)mems_malloc(sizeof(int)*250);
    void* e=(void*)mems_malloc(sizeof(int)*250);
    mems_print_stats();
    printf("Virtual address :%lu",(unsigned long)a);
    printf("Virtual address :%lu",(unsigned long)b);
    printf("Virtual address :%lu",(unsigned long)c);
    printf("Virtual address :%lu",(unsigned long)d);
    printf("Virtual address :%lu",(unsigned long)e);
    printf("Virtual address :%lu",(unsigned long)mems_malloc(sizeof(int)*24));

    mems_print_stats();
    a1=mems_get(ptr[0]);
    printf("Virtual address %lu\n",(unsigned long)a1);
    mems_finish();
    mems_print_stats();
    return 0;
}
