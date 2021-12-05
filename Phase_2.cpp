#include<bits/stdc++.h>

// variable declaration 
char buff[40];
char M[300][4];
char IR[4];
char R[4];
int PTR,IC,SI,PI,TI;
int ranum[30] ;
int C;

struct PCB{
    int TLL;
    int TTL;
    int LLC;
    int TTC;
    int JID;
};

FILE *inputfile,*outputfile;
void MOS();
struct PCB *pcb;

//declaring all functions
void LOAD();
void INIT();
void INIT_PCB();
int ALLOCATE();
void START();
void START_EXE();
int ADMAP(int va);
void MOS();
void READ();
void WRITE();
void TERMINATE(int em);


//Start of the program
int main()
{    
  fflush(stdin);
	// printf("inside main\n");
	fflush(stdin);
    inputfile = fopen("inputfile.txt","r");
    outputfile = fopen("outputfile.txt","w");
    fflush(stdin);
    LOAD();
    return(0);
}

void LOAD()
{
	puts("\nInside load\n");

    int i,k;
    char temp;
    while(getc(inputfile)!=EOF)
    {
        printf("Inital PTR:%d\n",PTR );

        fseek(inputfile,-1,SEEK_CUR);
        memset(buff,0,40);
		fgets(buff,42,inputfile);
		printf("\nBuffer array contains :\n");
		for(i=0;i<40;i++)
		{
			printf("%c",buff[i]);
    	}
        printf("\nPTR:%d\n",PTR );
		printf("\n");

        if(buff[0] == '$' && buff[1] == 'A' && buff[2] =='M' && buff[3] == 'J')
        {
            printf("\nPROCESS STARTED\n");
            INIT();
            PTR = ALLOCATE();
            PTR = 10*PTR;
            k=PTR;
            printf("PTR = %d\n",PTR);
        }
        else if(buff[0] == '$' && buff[1] == 'D' && buff[2] =='T' && buff[3] == 'A')
        {
            // printf("\n\n");
            START();
        }

        else if(buff[0] == '$' && buff[1] == 'E' && buff[2] =='N' && buff[3] == 'D')
        {
            printf("\nPROCESS ENDED.\n\n");
            continue;
        }

        else
        {
        	// printf("\nINSIDE else condition\n");
          	int index = ALLOCATE();
          	printf("index=%d\n",index);
          
		  	int j = index/10;
          	j=j+'0';
          	M[k][0]= j;
          	j = index%10;
          	j=j+'0';
          	M[k][1]= j;
          
		  	index = index*10;
          	// int sh=index;
          	j=0;
		  	printf("\n");
		  	while(j<40 && buff[j]!='\n')
			{
			    printf("M[%d]: ",index);
			    for(i=0;i<4&&buff[j]!='\n';i++)
			    {
					M[index][i]=buff[j++];
				    printf("%c",M[index][i]);
			    }
			    index++;
			    printf("\n");
		    }
          	k++;
        }
    }
    fclose(inputfile);
    fclose(outputfile);
}

//Initalize memory 
void INIT()
{
	printf("Initializing\n");
    INIT_PCB();
    int i, j;
    for(i=0;i<300;i++)
    {
        for(j=0;j<4;j++)
        {
            M[i][j]='\0';
        }
    }
    for(i=0;i<4;i++)
    {
        IR[i]=R[i]='\0';
    }
    PTR = 0;
    IC = 0;
    SI = 0;
    PI = 0;
    TI = 0;
    for(i=0;i<30;i++){
    	ranum[i]=0;
    }
}

//Initalize PCB structure
void INIT_PCB()
{
	// printf("\nInside INIT_PCB\n");
    pcb = (struct PCB*)malloc(sizeof(struct PCB));
    pcb->LLC = 0;
    pcb->TTC = 0;
    pcb->JID=((int)buff[4]-48)*1000+((int)buff[5]-48)*100+((int)buff[6]-48)*10+((int)buff[7]-48);
    printf("\npcb->JID : %d\n",pcb->JID);
    pcb->TTL=((int)buff[8]-48)*1000+((int)buff[9]-48)*100+((int)buff[10]-48)*10+((int)buff[11]-48);
    printf("pcb->TTL : %d\n",pcb->TTL);
    pcb->TLL=((int)buff[12]-48)*1000+((int)buff[13]-48)*100+((int)buff[14]-48)*10+((int)buff[15]-48);
    printf("pcb->TLL : %d\n",pcb->TLL);
}

//Random memory allocation
int ALLOCATE()
{
	// printf("inside ALLOCATE\n");
    int n;
    n = rand()%30;
    while(ranum[n]==1){
        n = (rand()%30);
    }
	printf("\nn = %d \n",n);
    ranum[n]=1;

    return n;
}

// Setting IC and executing instruction 1 by 1
void START()
{
	//printf("\nInside start\n");
    IC=0;
    START_EXE();
}

// GD PD LR SR instructions
void START_EXE()
{
	printf("inside START_EXE\n");
    int i;
    int ra = ADMAP(IC);
    if(PI==0)
	{
		IR[0]=M[ra][0];
		if(M[ra][1]!='\n'&&M[ra][1]!='$'&&IR[0]!='H')
		{
			IR[1]=M[ra][1];
			IR[2]=M[ra][2];
			IR[3]=M[ra][3];
			printf("\nIR=%s\n",IR);
			IC++;
			int m=(int)IR[3] -48;  // 48 ascii table '0'
			int n=(int)IR[2] -48;
			if(m<10 && n<10 && m>=0 && n>=0)
			{
				n=(n*10)+m;
				ra=ADMAP(n);
			}
			else{
                PI = 2;
			}
            if(PI==0)
            {
                if(IR[0]=='L'&&IR[1]=='R')
                {
                    printf("\nIn LR\n");
                    for(i=0;i<4;i++)
                    {
                        R[i]=M[ra][i];
                    }
                }
				else if(IR[0]=='S'&&IR[1]=='R')
                {
                    printf("\nIn SR\n");
                    for(i=0;i<4;i++){
                    	M[ra][i]=R[i];
                    }
				}
                else if(IR[0]=='C'&&IR[1]=='R')
                {
                    printf("\nIn CR\n");
                    int a;
					for(a=0;a<4;)
					{
						if(M[ra][a]==R[a]){
                           	a++;
						}
						else{
					    	break;
						}
					}
					if(a==4){
                        C=1;
					}
					else{
                        C=0;
					}
                }
                else if(IR[0]=='B'&&IR[1]=='T')
                {
                    printf("\nIn BT\n");
					if(C==1)
                        IC=((int)IR[2] -48)*10 + ((int)IR[3] -48);
                }
				else if(IR[0]=='G'&&IR[1]=='D')
				{
                    printf("\nIn GD\n");
                    SI = 1;
                }
				else if(IR[0]=='P'&&IR[1]=='D')
                {
                    printf("\nIn PD\n");
                    SI = 2;
                }
				else{
					PI=1;
				}
            }
		}
		else if(IR[0]=='H')
        {
            printf("\nIn H\n");
            IC++;
            SI=3;
        }
        else{
            PI = 1;
        }
    }
	pcb->TTC++;
	printf("pcb->TTC: %d\n",pcb->TTC);
    if(pcb->TTC >= pcb->TTL){
        TI=2;
    }
    if(TI!=0||PI!=0||SI!=0)
	{
		printf("going to mos function\n");
		MOS();
	}
	else{
		printf("NOT going to mos function instad going to START_EXE\n");
        START_EXE();
	}
}

// Address Map
int ADMAP(int va)
{
	// printf("inside admap\n");
	printf("PTR: %d va: %d\n",PTR,va );
    int j;
    int PTE = PTR + (va/10);
    printf("PTE: %d\n",PTE);
    char temp[4];
    for(j=0;j<4;j++)
		temp[j]=M[PTE][j];

    int ra=30;

    if(temp[0]=='0'||temp[0]=='1'||temp[0]=='2')
    {
        ra = ((int)temp[0] -48)*10 + ((int)temp[1] -48);
    }
    if(ra>=0&&ra<30)
	{
		ra = ra*10;
		ra = ra + (va)%10;
	}
	else
    {
        PI = 3;
    }
    printf("RA: %d\n",ra);
    printf("PI: %d\n",PI);
    return(ra);
}

//Master Mode
void MOS()
{
	// printf("inside mos\n");

	if(PI!=0)   //Cases(TI and PI)
	{
		if(TI==0)
		{
			if(PI==1)
				TERMINATE(4);
			else if(PI==2)
				TERMINATE(5);
			else if(PI==3)
			{
				if((IR[0]=='G'&& IR[1]=='D' ) ||  (IR[0]=='S'&& IR[1]=='R' ))
				{

					int ra=((int)IR[2] -48)*10 + ((int)IR[3] -48);
					int m= PTR + (ra/10);

					int t = ALLOCATE();
					printf("\nValid Page Fault Handled with Block No. - %d\n",t);
                    
					int j = t/10;
                    j=j+'0';
                    M[m][0]= j;
                    j = t%10;
                    j=j+'0';
                    M[m][1]= j;

					IC--;
					pcb->TTC--;
					PI=0;
					START_EXE();
				}
				else
					TERMINATE(6);   //invalid page fault
			}
		}
		else if(TI==2)
		{

			if(PI==1)
				TERMINATE(7);
			else if(PI==2)
				TERMINATE(8);
			else if(PI==3)
				TERMINATE(3);
		}
	}
	else   //if PI==0(cases of TI and SI)
	{
		if(TI==0)
		{
			if(SI==1)
				READ();
			else if(SI==2)
				WRITE();
			else if(SI==3)
				TERMINATE(0);
		}
		else if(TI==2)
		{
			if(SI==1)
				TERMINATE(3);
			else if(SI==2)
			{
				WRITE();
				TERMINATE(3);
			}
			else if(SI==3)
			{
				TERMINATE(0);
			}
			else if(SI==0)
			{
				TERMINATE(3);
			}
		}
	}
}

void READ()
{
	// printf("inside read\n");
    SI=0;
    IR[3]='0';
    char temp;
    int val=((int)IR[2] -48)*10 + ((int)IR[3] -48);
    int i,p=0,j;
    memset(buff,0,40);
	for(i=0;i<40&&getc(inputfile)!=EOF;i++)
	{
	    fseek(inputfile,-1,SEEK_CUR);
		temp = (char)(getc(inputfile));
		if(temp=='\n')
			break;
		buff[i]=temp;
		printf("%c",buff[i]);
	}
	printf("\n");
	if(buff[0]!='$')
	{
		int ra=ADMAP(val);
		int sh=ra;
		do{
			printf("M[%d]: ",ra);
			for(j=0;j<4&&buff[p]!='\n'&&buff[p]!=NULL;j++)
			{
				M[ra][j]=buff[p++];
				printf("%c",M[ra][j] );
			}
			printf("\n");
			ra++;
		}while(buff[p]!=NULL&&buff[p]!='\n');
		START_EXE();
	}
	else
	{
		TERMINATE(1);
	}
}

void WRITE()
{
	// printf("inside write\n");
    SI=0;
    IR[3]='0';
    int val=((int)IR[2] -48)*10 + ((int)IR[3] -48);
    pcb->LLC++;
	if(pcb->LLC > pcb->TLL)
		TERMINATE(2);
	else
	{
		int j=0,i=0;
		int ra=ADMAP(val);
		while(i<10)
		{
			if(M[ra][j]!='\n'&&M[ra][j]!=NULL&&M[ra][j]!='$'){
                fputc(M[ra][j],outputfile);
			}
			j++;
			if(j==4)
			{
				ra++;
                i++;
				j=0;
			}
		}
		fputc('\n',outputfile);
		if(TI==0){
            START_EXE();
		}
	}
}

void TERMINATE(int em)
{
	// printf("inside terminate\n");
	fputs("JOB ID 	:	",outputfile);
	fprintf(outputfile,"%d\n",pcb->JID);
    switch(em)
	{
		case 0:
		fputs("NO ERROR",outputfile);
		break;
		case 1:
		fputs("OUT OF DATA",outputfile);
		break;
		case 2:
		fputs("LINE LIMIT EXCEEDED",outputfile);
		break;
		case 3:
		fputs("TIME LIMIT EXCEEDED",outputfile);
		break;
		case 4:
		fputs("OPERATION CODE ERROR",outputfile);
		break;
		case 5:
		fputs("Operand Error",outputfile);
		break;
		case 6:
		fputs("INVALID PAGE FAULT",outputfile);
		break;
		case 7:
		fputs("TIME LIMIT EXCEEDED AND OPERATION CODE ERROR",outputfile);
		break;
		case 8:
		fputs("TIME LIMIT EXCEEDED AND OPERAND ERROR",outputfile);
		break;
	}
    
	fputs("\nIC 		:	",outputfile);
    fprintf(outputfile,"%d\n",IC);
    if(IR[0]=='H'){
    	fputs("IR 		:	",outputfile);
    	fprintf(outputfile,"%c\n",IR[0]);
    }
    else{
    	fputs("IR 		:	",outputfile);
    	fprintf(outputfile,"%s\n",IR);
    }

    fputs("TTC		:	",outputfile);
    fprintf(outputfile,"%d\n",pcb->TTC);
    fputs("LLC		:	",outputfile);
    fprintf(outputfile,"%d\n",pcb->LLC);
    fputs("TTL		:	",outputfile);
    fprintf(outputfile,"%d\n",pcb->TTL);
    fputs("TLL		:	",outputfile);
    fprintf(outputfile,"%d\n",pcb->TLL);
	
	fputs("\n \n",outputfile);

}