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
typedef struct Event{   //事件类型  
    float OccurTime;  //事件发生时刻  
    int NType;      //事件类型，0表示到达事件，正整数值表示对应窗口的离开事件  
    struct Event *next;  
}Event,ElemType;  
  
typedef struct{ //单向链表结构  
    ElemType *head;//头指针  
    ElemType *tail;//尾指针  
    int len;    //长度  
}LinkList;  
  
typedef LinkList EventList; //事件链表  
  
typedef struct QElemType{ //队列元素  
    float ArrivalTime;//到达时间  
    float Duration;//办理业务所需时间  
    struct QElemType *next;  
}QElemType;  
  
typedef struct{//队列结构  
    QElemType *head;//头指针  
    QElemType *tail;//尾指针  
}LinkQueue;   

//函数定义  
Event NewEvent(float occurT,int nType);  
    //根据OccurTime和NType值，创建一个新事件并返回  
Status InitList(LinkList *L);  
    //初始化事件链表  
Status InitQueue(LinkQueue *Q);  
    //初始化队列Q  
Status OrderInsert(LinkList *L,Event e);  
    //将事件e按发生时间顺序插入有序链表L中  
Status IsEmptyList(LinkList *L);  
    //判断链表L是否为空，为空返回TRUE，否则返回FALSE  
Status DelFirst(LinkList *L,ElemType *e);  
    //链表L不为空，删除其首结点，用e返回，并返回OK；否则返回ERROR  
Status ListTraverse(LinkList *L);  
    //遍历事件链表  
Status IsEmptyQueue(LinkQueue *Q);  
    //若队列Q为空，返回TRUE，否则返回FALSE  
Status DelQueue(LinkQueue *Q,QElemType *e);  
    //若队列Q不为空，首结点出队，用e返回，并返回OK；否则返回ERROR  
Status EnQueue(LinkQueue *Q,QElemType e);  
    //结点e入队Q 
Status GetHead(LinkQueue *Q,QElemType *e);  
    //若队列Q不为空，用e返回其首结点，并返回OK,否则返回ERROR  
Status QueueTraverse(LinkQueue *Q);  
    //遍历队列Q   
//------------------//  
int MIN(float *a); 
	//返回长度为WinNum的数组中最小元素的下标 
int ShortestQueue();  
    //获取最短队列的编号  
int ShortestWait();
    //获取最短等待队列的编号   
int QueueLength(LinkQueue Q);  
    //返回队列Q的长度，即元素个数  
void OpenForDay();  
    //初始化操作  
void CustomerArrived1();  
    //情况1下的顾客达到事件  
void CustomerArrived2(); 
	//情况2下的顾客到达事件 
void CustomerDepature();  
    //顾客离开事件  
void Bank_Simulation();  
    //银行排队模拟  
void PrintEventList();  
    //输出事件队列  
void PrintQueue();  
    //打印当前队列  
float  ArriveTime();
	//产生顾客到达时间 
float  ServeTime();  
    //产生顾客服务时间
float WaitInQuene(LinkQueue Q);
	//计算当前队伍的等待时间 
	 
//----全局变量-----//  

EventList ev;  
Event en;   
LinkQueue* q;
QElemType customer;  
int CustomerNum=0;  
float TotalTime=0; 
float Timeinqueue=0; 
int CloseTime,WinNum;//关闭时间，即营业时间长度;银行窗口数目 
int Chose;//用于辨别排队方式  
FILE *fp; 
float Lamda,Mu;//用于模拟的参数 
int   Length=0;//用于输出平均队长 
int   Qlength=0;
float t;
//--------------main()------------------//  
int main(void){  

	printf("M/M/S排队模型的蒙特卡洛模拟\n") ;
	printf("*************************************************\n"); 
	printf("请输入系统关闭时间(单位为分钟)：			//输入一正整数值\n");
	scanf("%d",&CloseTime);  
	printf("请输入顾客到达时间的参数Lamda:"); 
	scanf("%f",&Lamda);
	printf("请输入顾客服务时间的参数Mu:"); 
	scanf("%f",&Mu);
	printf("输入服务的窗口数(正整数)：");
	scanf("%d",&WinNum);
	q=(LinkQueue*)malloc(sizeof(LinkQueue)*(WinNum+1));   
	printf("请输入1或2选择排队的方式:\n(1.(叫号模型)加入到最短等待的窗口队列中;\n"
	"2.(传统排队模型)加入到人数最少的窗口队列中.)\n");
	printf("注：这里假设到达后一定会完成服务，不会中途离开\n"); 
	scanf("%d",&Chose);
	if(Chose!=1&&Chose!=2){
		printf("输入有误！程序终止！"); 
		exit(ERROR);
	} 
	
	char filename[32];
	printf("输入保存数据的文件名(加上.txt的后缀)\n"); 
	scanf("%s",filename);
	fp=fopen(filename,"w+");
    srand((unsigned)time(NULL));
    fprintf(fp,"100次模拟平均等待时间输出\n");
    
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
	
	fprintf(fp,"平均等待时间W：%f\n",mean_waittime);
	fprintf(fp,"平均队长L：%f\n",mean_length);
	fprintf(fp,"平均等待时间Wq：%f\n",mean_queuetime);
	fprintf(fp,"平均队长Lq：%f\n",mean_qlength);
  	
    fclose(fp);
    system("pause"); 
    
    return 0;  
    
}   
//--------------模拟排队----------------//  
void OpenForDay(){  
    //初始化操作  
    int i;  
    TotalTime=0;    CustomerNum=0;  
    InitList(&ev);//初始化事件队列  
    en.OccurTime=0;  
    en.NType=0;  
    OrderInsert(&ev,en);  
    for(i=1;i<=WinNum;i++)  
        InitQueue(&q[i]);//初始化四个窗口队列  
        
}//OpenForDay  
  
void CustomerArrived1(){  
    //顾客达到事件  
    float durtime,intertime,L;
	int i,j;   
	QElemType e;
    ++CustomerNum;  
    intertime=ArriveTime();//到达间隔时间
    durtime=ServeTime();//服务时间
    t=en.OccurTime+intertime;  
    if(t<CloseTime){//未到达结束时间  
        printf("A new customer will arrive at:%f\n",t);//下一位顾客达到时间  
        OrderInsert(&ev,NewEvent(t,0));  //插入下一个到达事件 
        i=ShortestWait();//最少等待 
		//Length+=QueueLength(q[i]);//更新总队长 
		for(j=1;j<=WinNum;j++){
			
			L=QueueLength(q[j]);			
			Length+=L;//更新总队长
			if(L)
				Qlength+=L-1;	
		}
					
		//Timeinquene+=WaitInQuene(q[i]);//更新总的队伍等待时间 
        e.ArrivalTime=en.OccurTime;  
        e.Duration=durtime;  
        EnQueue(&q[i],e);  
        if(QueueLength(q[i])==1)  
            OrderInsert(&ev,NewEvent(en.OccurTime+durtime,i));  //插入离开事件 
    }  
    
}  

void CustomerArrived2(){  
    //顾客达到事件  
    float durtime,intertime,L;
	int i;   
    QElemType e;  
    ++CustomerNum;   
    intertime=ArriveTime();//到达间隔时间  
    durtime=ServeTime();//服务时间    
    t=en.OccurTime+intertime;  
    if(t<CloseTime){//未到达结束时间  
        printf("A new customer will arrive at:%f\n",t);//输出下一位顾客达到时间  
        OrderInsert(&ev,NewEvent(t,0));  //插入下一个到达事件 
        i=ShortestQueue();//最短队列  
        L=QueueLength(q[i]);
        Length+=L;//更新总队长 
        if(L)
        	Qlength+=L-1;
			 
        //Timeinquene+=WaitInQuene(q[i]); //更新总的队伍等待时间 
        e.ArrivalTime=en.OccurTime;  
        e.Duration=durtime;  
        EnQueue(&q[i],e);  
        if(QueueLength(q[i])==1)  
            OrderInsert(&ev,NewEvent(en.OccurTime+durtime,i)); //插入离开事件 
    }  
    
}  
  
void CustomerDepature(){  
    //顾客离开事件  
    int i=en.NType;  
    DelQueue(&q[i],&customer);  
    printf("A customer leaves at:%f\n",en.OccurTime);//输出顾客离开时间  
    TotalTime+=en.OccurTime-customer.ArrivalTime; 
	Timeinqueue+=en.OccurTime-customer.ArrivalTime-customer.Duration;
    if(!IsEmptyQueue(&q[i])){  
        GetHead(&q[i],&customer);  
        OrderInsert(&ev,NewEvent(en.OccurTime+customer.Duration,i));  //插入离开事件 
    }  
    
}  
  
void Bank_Simulation(){  
    //银行排队模拟  
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
    //打印当前队列  
    int i;  
    for(i=1;i<=WinNum;i++){  
        printf("Queue %d have %d customer(s):",i,QueueLength(q[i]));  
        QueueTraverse(&q[i]);  
    }  
    printf("\n");  
    
}  
  
void PrintEventList(){  
    //输出事件队列  
    printf("Current Eventlist are：\n");  
    ListTraverse(&ev);  
    
}  
  
int ShortestQueue(){  
    //获取最短队列的编号  
    int i; 
	float *a=(float*)malloc(sizeof(float)*(WinNum+1)); 
    for(i=1;i<=WinNum;i++){  
        a[i]=QueueLength(q[i]);  
        //printf("队%d的长度为%d\n",i,QueueLength(q[i]));  
    }  
    return MIN(a);//队列从1开始编号  
    
}  

int ShortestWait(){
	//获取最短等待队列编号；
	float *a=(float*)malloc(sizeof(float)*(WinNum+1));
	for(int i=1;i<=WinNum;i++) a[i]=0;//初始化为0 
	QElemType *s;
	for(int i=1;i<=WinNum;i++){//计算每个队列的等待时间 
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
	//返回长度为WinNum+1数组中最小元素的下标 
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
  
//-----------队和链表操作--------------//  
Event NewEvent(float occurT,int nType){  
    //根据OccurTime和NType值，创建新事件  
    Event e;  
    e.OccurTime=occurT;  
    e.NType=nType;  
    return e;  
    
}  
  
Status InitList(LinkList *L){  
    //初始化事件链表  
    L->head=(ElemType *)malloc(sizeof(ElemType)); 
	L->tail=(ElemType *)malloc(sizeof(ElemType));  
    if(!L->head||!L->tail){  
        printf("Apply for memory error.LinkList initialize failed.\n");  
        exit(0);  
    }  
    L->head=L->tail;
    L->head->next=NULL;  //作为判断链表是否为空的依据之一 
    return OK;  
    
}  


Status OrderInsert(LinkList *L,Event e){  
	//将事件e按发生时间顺序插入有序链表L中  
    ElemType *p,*q,*newptr;  
    newptr=(ElemType *)malloc(sizeof(ElemType));  
    if(!newptr){  
        printf("Apply for memory error，new node can't insert into the Eventlist.\n");  
        exit(0);  
    }  
    *newptr=e;  
    if(IsEmptyList(L)){//链表为空  
       L->head->next=newptr;  
       L->tail=newptr;  
       L->tail->next=NULL;  
       return OK;  
    }  
    else{
    q=L->head;	
    p=L->head->next;  
    while(p){//遍历整个链表，按事件顺序插入  
        if(p->OccurTime>=newptr->OccurTime)  
            break;  
        q=p;  
        p=p->next;  
    }  
    q->next=newptr;  
    newptr->next=p;  
    if(!p){//插入位置为链表尾部  
        q->next=newptr;
		L->tail=newptr;
		L->tail->next=NULL; 
        } 
	return OK;  
	}
	
}  
  
Status IsEmptyList(LinkList *L){  
    //判断链表L是否为空，为空返回TRUE，否则返回FALSE  
    if((L->head==L->tail)&&(L->head->next==NULL))
        return TRUE;  
    else  
        return FALSE;  
        
}  
  
Status DelFirst(LinkList *L,ElemType *e){  
    //链表L不为空，删除其首结点，用e返回，并返回OK；否则返回ERROR  
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
    //遍历链表  
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
    //初始化队列Q  
    Q->head=(QElemType *)malloc(sizeof(QElemType));
	Q->tail=(QElemType *)malloc(sizeof(QElemType));  
	Q->head=Q->tail;
    if(!Q->head||!Q->tail){  
        printf("Apply for memory error.LinkQueue initialize failed.\n");  
        exit(0);  
    }  
    Q->head->next=NULL;  //作为判断队列是否为空的依据之一 
    return OK;  
    
}  
  
Status IsEmptyQueue(LinkQueue *Q){  
    //若队列Q为空，返回TRUE，否则返回FALSE  
    if(Q->head==Q->tail&&Q->head->next==NULL)  
        return TRUE;  
    else  
        return FALSE;  
        
}  
  
Status DelQueue(LinkQueue *Q,QElemType *e){  
    //若队列Q不为空，首结点出队，用e返回，并返回OK；否则返回ERROR  
    QElemType *p=Q->head->next;  
    if(!p)  
        return ERROR;  
    *e=*p;  
    Q->head->next=p->next;//删去队首，指向队列中的下一个 
    free(p);  
    if(!Q->head->next)//删去队首后队为空  
        Q->tail=Q->head;  
    return OK;  
    
}  
  
Status EnQueue(LinkQueue *Q,QElemType e){  
    //结点e入队Q  
    QElemType *p=(QElemType *)malloc(sizeof(QElemType));  
    if(!p){  
        printf("Apply for memory error,new element can't enqueue.\n");  
        exit(0);  
    }  
    *p=e;  
    p->next=NULL;  
    Q->tail->next=p;//插入队尾  
    Q->tail=p;//修改队尾指针  
    return OK;  
    
}  
  
int QueueLength(LinkQueue Q){  
    //返回队列Q的长度，即元素个数  
    int count=0;  
    QElemType *p=Q.head->next;  
    while(p){  
        p=p->next;  
        count++;  
    }  
    return count;  
    
}  
  
Status GetHead(LinkQueue *Q,QElemType *e){  
    //若队列Q不为空，用e返回其首结点，并返回OK,否则返回ERROR  
    if(IsEmptyQueue(Q))  
        return ERROR;  
    *e=*(Q->head->next);  
        return OK;  
        
}  
  
Status QueueTraverse(LinkQueue *Q){  
    //遍历队列Q  
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
	//产生到达间隔时间 
	float Rand;
	
	Rand=rand()/(RAND_MAX+1.0);
	Rand=(-log(1-Rand))/Lamda;
	
	return Rand;
	
}
	 
float ServeTime(){
	//产生服务时间 
	float Rand;
	
	Rand=rand()/(RAND_MAX+1.0);
	Rand=(-log(1-Rand))/Mu;
	
	return Rand;
	
}
/*
float WaitInQuene(LinkQueue Q){
	//返回当前队列的等待时间  
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
