#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <string.h>


#define Page_Size getpagesize();

struct mainNode{
    struct mainNode *prev;
    struct mainNode *next;
    int Index_number;
    size_t requested_size;  
    size_t availablesize;
    struct node *ChildHead;
    void* start_Addr;
};
struct mainNode* MainNodeHead;

void* phy_addr[200];
void* virt_addr[200];


struct node{
    void* startAddr;
    struct node *prev;
    struct node *next;
    int Number;
    int functioning;   
    struct mainNode *Parent;
    size_t size;

};

void mems_init(){
    size_t PAGE_SIZE=getpagesize();
    MainNodeHead=(struct mainNode*)mmap(NULL, sizeof(struct mainNode), PROT_READ | PROT_WRITE, MAP_PRIVATE |  MAP_ANONYMOUS, -1, 0);
    MainNodeHead->prev=NULL;
    MainNodeHead->availablesize=PAGE_SIZE;
    MainNodeHead->Index_number=0;
    MainNodeHead->requested_size;   
}



void* virtual_addr(void* phy_addr){
    struct mainNode* tempnode=MainNodeHead->next;
    unsigned space_unused=0;
    struct mainNode* tempnode1=MainNodeHead->next;
    unsigned arr[10];
    int count=0;
    while(tempnode!=NULL){
        void *startPhy_addr=tempnode->start_Addr;
        void* start_addr=(void*)1000+(tempnode->Index_number-1)*4096;
        void* end_addr=(void*)1000+(tempnode->Index_number)*4096 - 1;
        void* start_addr1=start_addr;
        struct node* tempsubnode=tempnode->ChildHead;
        struct node* tempsubnode1=tempnode->ChildHead;
        while(tempsubnode!=NULL){
            unsigned lsize=tempsubnode->size;
            void*  end_addr1=((void*)start_addr1+lsize);
            if((tempsubnode->startAddr)==phy_addr){
                return start_addr1;
            }
            start_addr1=end_addr1;
            tempsubnode1=tempsubnode;
            tempsubnode=tempsubnode->next;
        }
        arr[count]=tempsubnode1->Number+2;
        count++;

        space_unused=space_unused+(end_addr-start_addr1);
        tempnode1=tempnode;
        tempnode=tempnode->next;
    }
}

void mems_print_stats(){
    struct mainNode* tempnode=MainNodeHead->next;
    struct mainNode* tempnode1=MainNodeHead->next;
    printf("\n\n--------------------Printing stats--------------------\n\n");
    if(tempnode!=NULL){
        unsigned space_unused=0;
        while(tempnode!=NULL){
        //struct node* tempsubnode=tempnode->ChildHead;
            
        unsigned offset=(unsigned int)1000;
        unsigned start_addr=1000+(tempnode->Index_number-1)*4096;
        unsigned end_addr=1000+(tempnode->Index_number)*4096 - 1;
        void* phy_addr=tempnode->start_Addr;
        unsigned int start_addr1=0;
        printf("Main%d[%u:%u]",tempnode->Index_number,start_addr,end_addr);
        struct node* tempsubnode=tempnode->ChildHead;
        struct node* tempsubnode1=tempnode->ChildHead;
        while(tempsubnode1!=NULL){
            tempsubnode1=tempsubnode1->next;
            unsigned difference=(unsigned long int)tempsubnode->startAddr-(unsigned long int)phy_addr;
            char a='P';
            if(tempsubnode->functioning==0){
            a='H';
            space_unused=space_unused+tempsubnode->size;
            }
            start_addr1=(unsigned int)start_addr+difference+tempsubnode->size-1;
            if(start_addr1>end_addr){
                printf(" ");

            }
            else if(start_addr1==end_addr){
              printf("->%c[%u:%u]",a,(unsigned int)start_addr+difference-1,end_addr);
;
            }
            else{
            printf("->%c[%u:%lu]",a,(unsigned int)start_addr+difference,(unsigned int)start_addr+difference+tempsubnode->size-1);
            }
            tempsubnode=tempsubnode->next;
        }
        if(start_addr1>=end_addr){
            printf("\n");
        }
        else{
        printf("->H[%u:%u]\n",start_addr1,end_addr);}
        space_unused=space_unused+(end_addr-start_addr1);
        tempnode1=tempnode;
        tempnode=tempnode->next;
        //printf("vv");
        
    }

    printf("Pages used :%d\n",tempnode1->Index_number);
    printf("Space Unused :%d\n",space_unused);
    printf("Main chain length :%d\n",tempnode1->Index_number);

}else{
    printf("\nFree list is empty\n\n");
    printf("--------------------------------------------\n\n");
}
        }






void* mems_get(void* ptr){
    //int count=0;
    unsigned long int ptr2=((unsigned long int)ptr-1000)/4096;
       //printf("%lu",ptr2);
    struct mainNode* mainNode= MainNodeHead->next;
    while(mainNode!=NULL ){
        if(mainNode->Index_number==ptr2 +1){
        ptr2=1000+ptr2*4096;
        unsigned long int a= (unsigned long int)ptr-ptr2;
        return mainNode->start_Addr+a;
    }mainNode=mainNode->next;
    }}
    
    
int count1=0;

void* mems_malloc(size_t requested_size){
    struct mainNode* currentnode=MainNodeHead->next;
    
    while(currentnode!=NULL){
        void* temp22 ;
        if(currentnode->ChildHead!=NULL){ 
        if((currentnode->availablesize)>=requested_size){
            struct node* tempnode1=currentnode->ChildHead;
            struct node* tempnode=tempnode1;                
                while(tempnode1!=NULL){
                    if(tempnode1->functioning==0 && tempnode1->size>=requested_size){
                        tempnode1->functioning=1;
                        if(tempnode1->size-requested_size>0){
                            struct node* Node=(struct node*)mmap(NULL, sizeof(struct node), PROT_READ | PROT_WRITE, MAP_PRIVATE |  MAP_ANONYMOUS, -1, 0);
                            
                            Node->size=tempnode1->size - requested_size;
                            tempnode1->size=requested_size;
                            Node->prev=tempnode1;
                            Node->next=tempnode1->next;
                            tempnode1->next=Node;
                            Node->Parent=currentnode;
                            currentnode->availablesize=currentnode->availablesize-requested_size;
                            Node->Number=tempnode->Number + 1;
                            Node->functioning=0;
                            Node->startAddr=tempnode1->startAddr+tempnode1->size;
                            temp22 =virtual_addr(tempnode1->startAddr);
                            phy_addr[count1]=Node->startAddr;
                            virt_addr[count1]=virtual_addr(tempnode1->startAddr)+tempnode1->size;
                            count1++;
                            return temp22;}
                        else{
                            currentnode->availablesize=currentnode->availablesize-requested_size;
                            return virtual_addr(tempnode1->startAddr);
                        }
                    }
                    tempnode=tempnode1;
                    tempnode1=tempnode1->next;
                }
                
                struct node* Node=(struct node*)mmap(NULL, sizeof(struct node), PROT_READ | PROT_WRITE, MAP_PRIVATE |  MAP_ANONYMOUS, -1, 0);
                tempnode->next=Node;
                Node->size=requested_size;
                Node->prev=tempnode;
                Node->next=NULL;
                Node->Parent=currentnode;
                Node->Number=tempnode->Number + 1;
                Node->functioning=1;
                Node->startAddr=tempnode->startAddr+tempnode->size;
                currentnode->requested_size=currentnode->requested_size+requested_size;
                currentnode->availablesize=currentnode->availablesize-requested_size;

                phy_addr[count1]=(Node->startAddr);
                
                temp22 =virtual_addr(Node->startAddr);
                virt_addr[count1]=temp22;
                count1++;
                return temp22 ;


                }}
                currentnode=currentnode->next;}
    
    struct mainNode* mainNode=(struct mainNode*)mmap(NULL, sizeof(struct mainNode), PROT_READ | PROT_WRITE, MAP_PRIVATE |  MAP_ANONYMOUS, -1, 0);
    currentnode = MainNodeHead;
    
    while(currentnode->next!=NULL){
        currentnode=currentnode->next;
    }
    
    mainNode->prev=currentnode;
    currentnode->next=mainNode;
    mainNode->Index_number=currentnode->Index_number +1;
    void* allocatedaddr = mmap(NULL, getpagesize() , PROT_READ | PROT_WRITE, MAP_PRIVATE |  MAP_ANONYMOUS, -1, 0);
    mainNode->start_Addr=allocatedaddr;
    if (allocatedaddr == MAP_FAILED) {
        perror("mmap failed malloc");
        exit(1);
    }
    else{
    struct node* Node=mmap(NULL, sizeof(struct node), PROT_READ | PROT_WRITE, MAP_PRIVATE |  MAP_ANONYMOUS, -1, 0);
    mainNode->availablesize=getpagesize()-requested_size;
    Node->functioning=1;
    
    Node->Parent=mainNode;
    Node->startAddr=allocatedaddr;
    Node->size=requested_size;
    mainNode->requested_size=requested_size;
    mainNode->ChildHead=Node;
    Node->Number=0;
    
    struct node* Node1=mmap(NULL, sizeof(struct node), PROT_READ | PROT_WRITE, MAP_PRIVATE |  MAP_ANONYMOUS, -1, 0);
    Node1->functioning=0;
    Node1->next=NULL;
    Node1->Parent=mainNode;
    Node1->startAddr=allocatedaddr+requested_size;
    Node1->size=mainNode->availablesize;
    
    Node1->Number=1;
    Node->next=Node1;
    phy_addr[count1]=allocatedaddr;
    void* temp22 =virtual_addr(Node->startAddr);
    virt_addr[count1]=temp22;
    count1++;

    phy_addr[count1]=Node1->startAddr;
    void* temp21=virtual_addr(Node1->startAddr);
    virt_addr[count1]=temp21;
    count1++;


    return temp22;}

}


int mem_defrag(struct mainNode* mainNode){
        struct node* tempnode=mainNode->ChildHead->next;
        struct node* tempnode1=mainNode->ChildHead;
        struct node* tempnode2=mainNode->ChildHead;
        while(tempnode!=NULL){
            if(tempnode1->functioning==0 && tempnode->functioning==0){
                tempnode1->size=tempnode1->size+tempnode->size;
                tempnode1->next=tempnode->next;
                //tempnode->next->prev=tempnode1;
            }
            tempnode1=tempnode;
            tempnode=tempnode->next;}
        

        if(tempnode1->functioning==0 && tempnode1->next!=NULL){
            unsigned a=(unsigned long int)1000+(mainNode->Index_number)*4096;

            tempnode1->size=a-(unsigned long)tempnode1->startAddr;
            tempnode2->next=NULL;
        }
    return 0;
}
void mems_free(void* ptr) {
    struct mainNode* currMain = MainNodeHead->next;
    while (currMain != NULL) {
        struct node* currSub = currMain->ChildHead;
        struct node* currSub1 = currMain->ChildHead;
        while (currSub != NULL) {
            int count=0;
            while(phy_addr[count]!=currSub->startAddr){
                count++;
            }
            void* vir_addr=virt_addr[count];
            if (vir_addr == ptr ) {
                if(currSub==currMain->ChildHead){
                    currSub->functioning=0;
                    currMain->availablesize=currMain->availablesize+currSub->size;
                }
                else{
                currSub->functioning = 0; 
                currMain->availablesize=currMain->availablesize+currSub->size;
                
                
            }}
            currSub1=currSub;
            currSub = currSub->next;
        }int a=mem_defrag(currMain);
        currMain = currMain->next;
    }
}


void mems_finish() {
    for(int i=0;i<200;i++){
        mems_free(virt_addr[i]);
    }

    struct mainNode* mainNode = MainNodeHead->next;
    while(mainNode!=NULL){
        munmap(mainNode->start_Addr,getpagesize());
        mainNode=mainNode->next;
    }
    MainNodeHead->next=NULL;
}
