#include <stdio.h>  
#include <stdlib.h>  
#include <time.h>
#include <math.h> 
#include <string.h>

#define OK 1  
#define ERROR 0  
#define TRUE 1  
#define FALSE 0  
 
typedef int Status;  
typedef struct Event{   //�¼�����  
    float OccurTime;  //�¼�����ʱ��  
    int NType;      //�¼����ͣ�0��ʾ�����¼���������ֵ��ʾ��Ӧ���ڵ��뿪�¼�  
    struct Event *next;  
}Event,ElemType;  
  
typedef struct{ //��������ṹ  
    ElemType *head;//ͷָ��  
    ElemType *tail;//βָ��  
    int len;    //����  
}LinkList;  
  
typedef LinkList EventList; //�¼�����  
  
typedef struct QElemType{ //����Ԫ��  
    float ArrivalTime;//����ʱ��  
    float Duration;//����ҵ������ʱ��  
    struct QElemType *next;  
}QElemType;  
  
typedef struct{//���нṹ  
    QElemType *head;//ͷָ��  
    QElemType *tail;//βָ��  
}LinkQueue;   

//��������  
Event NewEvent(float occurT,int nType);  
    //����OccurTime��NTypeֵ������һ�����¼�������  
Status InitList(LinkList *L);  
    //��ʼ���¼�����  
Status InitQueue(LinkQueue *Q);  
    //��ʼ������Q  
Status OrderInsert(LinkList *L,Event e);  
    //���¼�e������ʱ��˳�������������L��  
Status IsEmptyList(LinkList *L);  
    //�ж�����L�Ƿ�Ϊ�գ�Ϊ�շ���TRUE�����򷵻�FALSE  
Status DelFirst(LinkList *L,ElemType *e);  
    //����L��Ϊ�գ�ɾ�����׽�㣬��e���أ�������OK�����򷵻�ERROR  
Status ListTraverse(LinkList *L);  
    //�����¼�����  
Status IsEmptyQueue(LinkQueue *Q);  
    //������QΪ�գ�����TRUE�����򷵻�FALSE  
Status DelQueue(LinkQueue *Q,QElemType *e);  
    //������Q��Ϊ�գ��׽����ӣ���e���أ�������OK�����򷵻�ERROR  
Status EnQueue(LinkQueue *Q,QElemType e);  
    //���e���Q 
Status GetHead(LinkQueue *Q,QElemType *e);  
    //������Q��Ϊ�գ���e�������׽�㣬������OK,���򷵻�ERROR  
Status QueueTraverse(LinkQueue *Q);  
    //��������Q   
//------------------//  
int MIN(float *a); 
	//���س���ΪWinNum����������СԪ�ص��±� 
int ShortestQueue();  
    //��ȡ��̶��еı��  
int ShortestWait();
    //��ȡ��̵ȴ����еı��   
int QueueLength(LinkQueue Q);  
    //���ض���Q�ĳ��ȣ���Ԫ�ظ���  
void OpenForDay();  
    //��ʼ������  
void CustomerArrived1();  
    //���1�µĹ˿ʹﵽ�¼�  
void CustomerArrived2(); 
	//���2�µĹ˿͵����¼� 
void CustomerDepature();  
    //�˿��뿪�¼�  
void Bank_Simulation();  
    //�����Ŷ�ģ��  
void PrintEventList();  
    //����¼�����  
void PrintQueue();  
    //��ӡ��ǰ����  
float  ArriveTime();
	//�����˿͵���ʱ�� 
float  ServeTime();  
    //�����˿ͷ���ʱ��
float WaitInQuene(LinkQueue Q);
	//���㵱ǰ����ĵȴ�ʱ�� 
	 
//----ȫ�ֱ���-----//  

EventList ev;  
Event en;   
LinkQueue* q;
QElemType customer;  
int CustomerNum=0;  
float TotalTime=0; 
float Timeinqueue=0; 
int CloseTime,WinNum;//�ر�ʱ�䣬��Ӫҵʱ�䳤��;���д�����Ŀ 
int Chose;//���ڱ���Ŷӷ�ʽ  
FILE *fp; 
float Lamda,Mu;//����ģ��Ĳ��� 
int   Length=0;//�������ƽ���ӳ� 
int   Qlength=0;
float t;
//--------------main()------------------//  
int main(void){  

	printf("M/M/S�Ŷ�ģ�͵����ؿ���ģ��\n") ;
	printf("*************************************************\n"); 
	printf("������ϵͳ�ر�ʱ��(��λΪ����)��			//����һ������ֵ\n");
	scanf("%d",&CloseTime);  
	printf("������˿͵���ʱ��Ĳ���Lamda:"); 
	scanf("%f",&Lamda);
	printf("������˿ͷ���ʱ��Ĳ���Mu:"); 
	scanf("%f",&Mu);
	printf("�������Ĵ�����(������)��");
	scanf("%d",&WinNum);
	q=(LinkQueue*)malloc(sizeof(LinkQueue)*(WinNum+1));   
	printf("������1��2ѡ���Ŷӵķ�ʽ:\n(1.(�к�ģ��)���뵽��̵ȴ��Ĵ��ڶ�����;\n"
	"2.(��ͳ�Ŷ�ģ��)���뵽�������ٵĴ��ڶ�����.)\n");
	printf("ע��������赽���һ������ɷ��񣬲�����;�뿪\n"); 
	scanf("%d",&Chose);
	if(Chose!=1&&Chose!=2){
		printf("�������󣡳�����ֹ��"); 
		exit(ERROR);
	} 
	
	char filename[32];
	printf("���뱣�����ݵ��ļ���(����.txt�ĺ�׺)\n"); 
	scanf("%s",filename);
	fp=fopen(filename,"w+");
    srand((unsigned)time(NULL));
    fprintf(fp,"100��ģ��ƽ���ȴ�ʱ�����\n");
    
	float result[100];
	float length[100];
	float queueT[100];
	float qlength[100];
	
	for(int i=0;i<100;i++){
		Bank_Simulation();  
		result[i]=(float)TotalTime/CustomerNum;
		length[i]=(float)Length/CustomerNum;
		queueT[i]=(float)Timeinqueue/CustomerNum;
		qlength[i]=(float)Qlength/CustomerNum;
		
		fprintf(fp,"%f	%f	%f	%f\n",(float)TotalTime/CustomerNum,(float)Length/CustomerNum,(float)Timeinqueue/CustomerNum,(float)Qlength/CustomerNum);
		//fprintf(fp,"Total time:%d		Total cousumers:%d		Mean time:%f\n",TotalTime,CustomerNum,(float)TotalTime/CustomerNum);
		TotalTime=0;
		CustomerNum=0;
		Length=0; 
		Timeinqueue=0;
		Qlength=0;
		
	}
	
	float mean_waittime=0;
	float mean_length=0;
	float mean_queuetime=0;
	float mean_qlength=0;
	for(int i=0;i<100;i++){
		mean_waittime+=result[i];
		mean_length+=length[i];
		mean_queuetime+=queueT[i];
		mean_qlength+=qlength[i];
	}
	
		
	mean_waittime=mean_waittime/100;
	mean_length=mean_length/100;
	mean_queuetime=mean_queuetime/100;
	mean_qlength=mean_qlength/100;
	
	fprintf(fp,"ƽ���ȴ�ʱ��W��%f\n",mean_waittime);
	fprintf(fp,"ƽ���ӳ�L��%f\n",mean_length);
	fprintf(fp,"ƽ���ȴ�ʱ��Wq��%f\n",mean_queuetime);
	fprintf(fp,"ƽ���ӳ�Lq��%f\n",mean_qlength);
  	
    fclose(fp);
    system("pause"); 
    
    return 0;  
    
}   
//--------------ģ���Ŷ�----------------//  
void OpenForDay(){  
    //��ʼ������  
    int i;  
    TotalTime=0;    CustomerNum=0;  
    InitList(&ev);//��ʼ���¼�����  
    en.OccurTime=0;  
    en.NType=0;  
    OrderInsert(&ev,en);  
    for(i=1;i<=WinNum;i++)  
        InitQueue(&q[i]);//��ʼ���ĸ����ڶ���  
        
}//OpenForDay  
  
void CustomerArrived1(){  
    //�˿ʹﵽ�¼�  
    float durtime,intertime,L;
	int i,j;   
	QElemType e;
    ++CustomerNum;  
    intertime=ArriveTime();//������ʱ��
    durtime=ServeTime();//����ʱ��
    t=en.OccurTime+intertime;  
    if(t<CloseTime){//δ�������ʱ��  
        printf("A new customer will arrive at:%f\n",t);//��һλ�˿ʹﵽʱ��  
        OrderInsert(&ev,NewEvent(t,0));  //������һ�������¼� 
        i=ShortestWait();//���ٵȴ� 
		//Length+=QueueLength(q[i]);//�����ܶӳ� 
		for(j=1;j<=WinNum;j++){
			
			L=QueueLength(q[j]);			
			Length+=L;//�����ܶӳ�
			if(L)
				Qlength+=L-1;	
		}
					
		//Timeinquene+=WaitInQuene(q[i]);//�����ܵĶ���ȴ�ʱ�� 
        e.ArrivalTime=en.OccurTime;  
        e.Duration=durtime;  
        EnQueue(&q[i],e);  
        if(QueueLength(q[i])==1)  
            OrderInsert(&ev,NewEvent(en.OccurTime+durtime,i));  //�����뿪�¼� 
    }  
    
}  

void CustomerArrived2(){  
    //�˿ʹﵽ�¼�  
    float durtime,intertime,L;
	int i;   
    QElemType e;  
    ++CustomerNum;   
    intertime=ArriveTime();//������ʱ��  
    durtime=ServeTime();//����ʱ��    
    t=en.OccurTime+intertime;  
    if(t<CloseTime){//δ�������ʱ��  
        printf("A new customer will arrive at:%f\n",t);//�����һλ�˿ʹﵽʱ��  
        OrderInsert(&ev,NewEvent(t,0));  //������һ�������¼� 
        i=ShortestQueue();//��̶���  
        L=QueueLength(q[i]);
        Length+=L;//�����ܶӳ� 
        if(L)
        	Qlength+=L-1;
			 
        //Timeinquene+=WaitInQuene(q[i]); //�����ܵĶ���ȴ�ʱ�� 
        e.ArrivalTime=en.OccurTime;  
        e.Duration=durtime;  
        EnQueue(&q[i],e);  
        if(QueueLength(q[i])==1)  
            OrderInsert(&ev,NewEvent(en.OccurTime+durtime,i)); //�����뿪�¼� 
    }  
    
}  
  
void CustomerDepature(){  
    //�˿��뿪�¼�  
    int i=en.NType;  
    DelQueue(&q[i],&customer);  
    printf("A customer leaves at:%f\n",en.OccurTime);//����˿��뿪ʱ��  
    TotalTime+=en.OccurTime-customer.ArrivalTime; 
	Timeinqueue+=en.OccurTime-customer.ArrivalTime-customer.Duration;
    if(!IsEmptyQueue(&q[i])){  
        GetHead(&q[i],&customer);  
        OrderInsert(&ev,NewEvent(en.OccurTime+customer.Duration,i));  //�����뿪�¼� 
    }  
    
}  
  
void Bank_Simulation(){  
    //�����Ŷ�ģ��  
    OpenForDay();   
    while(!IsEmptyList(&ev)){  
        DelFirst(&ev,&en);  
        if(en.NType==0){
        	switch(Chose){
        		case 1:CustomerArrived1();break;
        		case 2:CustomerArrived2();break;
        	}
        }              
        else  
            CustomerDepature();  
        PrintEventList(); 
        PrintQueue();  
    }  
    printf("\nTotal time is: %f minutes,",TotalTime);
	printf("Total customers are %d persons.\n",CustomerNum);
	printf("So the average time is: %f minutes.\n",(float)TotalTime/CustomerNum); 
	
}  
  
void PrintQueue(){  
    //��ӡ��ǰ����  
    int i;  
    for(i=1;i<=WinNum;i++){  
        printf("Queue %d have %d customer(s):",i,QueueLength(q[i]));  
        QueueTraverse(&q[i]);  
    }  
    printf("\n");  
    
}  
  
void PrintEventList(){  
    //����¼�����  
    printf("Current Eventlist are��\n");  
    ListTraverse(&ev);  
    
}  
  
int ShortestQueue(){  
    //��ȡ��̶��еı��  
    int i; 
	float *a=(float*)malloc(sizeof(float)*(WinNum+1)); 
    for(i=1;i<=WinNum;i++){  
        a[i]=QueueLength(q[i]);  
        //printf("��%d�ĳ���Ϊ%d\n",i,QueueLength(q[i]));  
    }  
    return MIN(a);//���д�1��ʼ���  
    
}  

int ShortestWait(){
	//��ȡ��̵ȴ����б�ţ�
	float *a=(float*)malloc(sizeof(float)*(WinNum+1));
	for(int i=1;i<=WinNum;i++) a[i]=0;//��ʼ��Ϊ0 
	QElemType *s;
	for(int i=1;i<=WinNum;i++){//����ÿ�����еĵȴ�ʱ�� 
		s=(&q[i])->head->next;
		while(s){
			a[i]+=s->Duration;			
			s=s->next;
		}
		s=(&q[i])->head->next;
		if(s) a[i]+=s->ArrivalTime-en.OccurTime;
	}
    int result=MIN(a); 
	return result;	 
	
} 

int MIN(float *a){
	//���س���ΪWinNum+1��������СԪ�ص��±� 
	int min=1; 
	float minnum=a[1];
	for(int i=1;i<=WinNum;i++){
		if(a[i]<minnum){
			minnum=a[i];
			min=i;
		}
	}
	
	return min;
	
}
  
//-----------�Ӻ��������--------------//  
Event NewEvent(float occurT,int nType){  
    //����OccurTime��NTypeֵ���������¼�  
    Event e;  
    e.OccurTime=occurT;  
    e.NType=nType;  
    return e;  
    
}  
  
Status InitList(LinkList *L){  
    //��ʼ���¼�����  
    L->head=(ElemType *)malloc(sizeof(ElemType)); 
	L->tail=(ElemType *)malloc(sizeof(ElemType));  
    if(!L->head||!L->tail){  
        printf("Apply for memory error.LinkList initialize failed.\n");  
        exit(0);  
    }  
    L->head=L->tail;
    L->head->next=NULL;  //��Ϊ�ж������Ƿ�Ϊ�յ�����֮һ 
    return OK;  
    
}  


Status OrderInsert(LinkList *L,Event e){  
	//���¼�e������ʱ��˳�������������L��  
    ElemType *p,*q,*newptr;  
    newptr=(ElemType *)malloc(sizeof(ElemType));  
    if(!newptr){  
        printf("Apply for memory error��new node can't insert into the Eventlist.\n");  
        exit(0);  
    }  
    *newptr=e;  
    if(IsEmptyList(L)){//����Ϊ��  
       L->head->next=newptr;  
       L->tail=newptr;  
       L->tail->next=NULL;  
       return OK;  
    }  
    else{
    q=L->head;	
    p=L->head->next;  
    while(p){//���������������¼�˳�����  
        if(p->OccurTime>=newptr->OccurTime)  
            break;  
        q=p;  
        p=p->next;  
    }  
    q->next=newptr;  
    newptr->next=p;  
    if(!p){//����λ��Ϊ����β��  
        q->next=newptr;
		L->tail=newptr;
		L->tail->next=NULL; 
        } 
	return OK;  
	}
	
}  
  
Status IsEmptyList(LinkList *L){  
    //�ж�����L�Ƿ�Ϊ�գ�Ϊ�շ���TRUE�����򷵻�FALSE  
    if((L->head==L->tail)&&(L->head->next==NULL))
        return TRUE;  
    else  
        return FALSE;  
        
}  
  
Status DelFirst(LinkList *L,ElemType *e){  
    //����L��Ϊ�գ�ɾ�����׽�㣬��e���أ�������OK�����򷵻�ERROR  
    ElemType *p=L->head->next;  
    if(!p)  
        return ERROR;  
    L->head->next=p->next;  
    *e=*p;  
    free(p);  
    if(L->head->next==NULL)  
        L->tail=L->head;  
    return OK;  
    
}  
  
Status ListTraverse(LinkList *L){  
    //��������  
    Event *p=L->head->next;  
    if(!p){  
        printf("List is empty.\n");  
        return ERROR;  
    }  
    while(p!=NULL){  
        printf("OccurTime:%f,Event Type:%d\n",p->OccurTime,p->NType);  
        p=p->next;  
    }  
    printf("\n");  	
    return OK;  
    
}  
  
Status InitQueue(LinkQueue *Q){  
    //��ʼ������Q  
    Q->head=(QElemType *)malloc(sizeof(QElemType));
	Q->tail=(QElemType *)malloc(sizeof(QElemType));  
	Q->head=Q->tail;
    if(!Q->head||!Q->tail){  
        printf("Apply for memory error.LinkQueue initialize failed.\n");  
        exit(0);  
    }  
    Q->head->next=NULL;  //��Ϊ�ж϶����Ƿ�Ϊ�յ�����֮һ 
    return OK;  
    
}  
  
Status IsEmptyQueue(LinkQueue *Q){  
    //������QΪ�գ�����TRUE�����򷵻�FALSE  
    if(Q->head==Q->tail&&Q->head->next==NULL)  
        return TRUE;  
    else  
        return FALSE;  
        
}  
  
Status DelQueue(LinkQueue *Q,QElemType *e){  
    //������Q��Ϊ�գ��׽����ӣ���e���أ�������OK�����򷵻�ERROR  
    QElemType *p=Q->head->next;  
    if(!p)  
        return ERROR;  
    *e=*p;  
    Q->head->next=p->next;//ɾȥ���ף�ָ������е���һ�� 
    free(p);  
    if(!Q->head->next)//ɾȥ���׺��Ϊ��  
        Q->tail=Q->head;  
    return OK;  
    
}  
  
Status EnQueue(LinkQueue *Q,QElemType e){  
    //���e���Q  
    QElemType *p=(QElemType *)malloc(sizeof(QElemType));  
    if(!p){  
        printf("Apply for memory error,new element can't enqueue.\n");  
        exit(0);  
    }  
    *p=e;  
    p->next=NULL;  
    Q->tail->next=p;//�����β  
    Q->tail=p;//�޸Ķ�βָ��  
    return OK;  
    
}  
  
int QueueLength(LinkQueue Q){  
    //���ض���Q�ĳ��ȣ���Ԫ�ظ���  
    int count=0;  
    QElemType *p=Q.head->next;  
    while(p){  
        p=p->next;  
        count++;  
    }  
    return count;  
    
}  
  
Status GetHead(LinkQueue *Q,QElemType *e){  
    //������Q��Ϊ�գ���e�������׽�㣬������OK,���򷵻�ERROR  
    if(IsEmptyQueue(Q))  
        return ERROR;  
    *e=*(Q->head->next);  
        return OK;  
        
}  
  
Status QueueTraverse(LinkQueue *Q){  
    //��������Q  
    QElemType *p=Q->head->next;  
    if(!p){  
        printf("--Is empty.\n");  
        return ERROR;  
    }  
    while(p){  
        printf("(%f,%f) ",p->ArrivalTime,p->Duration);  
        p=p->next;  
    }  
    printf("\n");  
    return OK;  
    
}  

float ArriveTime(){
	//����������ʱ�� 
	float Rand;
	
	Rand=rand()/(RAND_MAX+1.0);
	Rand=(-log(1-Rand))/Lamda;
	
	return Rand;
	
}
	 
float ServeTime(){
	//��������ʱ�� 
	float Rand;
	
	Rand=rand()/(RAND_MAX+1.0);
	Rand=(-log(1-Rand))/Mu;
	
	return Rand;
	
}
/*
float WaitInQuene(LinkQueue Q){
	//���ص�ǰ���еĵȴ�ʱ��  
    float time=0;  
    QElemType *p=Q.head->next;  
    
    if(p)
		time+=p->ArrivalTime;
	else 
		return (float)0;

    while(p){  
    	time+=p->Duration;
        p=p->next;  
    }  
    time=time-t;
    
    if(time<0) 
		return (float)0;
    else
    	return time;  
    
} 
*/
