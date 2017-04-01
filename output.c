#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

//ALU signal generated in DEC, DIS,CRGE,TEMP

int flag[2]={0};
//	flag[0]=negative flag | flag[1]=zero flag

int password(int a)
{
    int pass=5;
    if(a==pass)
        return 1;
    else
        return 0;          
}
int music(int song)
{
	//favl[] is an array of favourite songs
	//n<=7
	int flagi=0;
	//printf("\nIn SONG %d",song);
	int i,favl[10];
	for(i=0;i<8;i++)
		favl[i]=i;
	for(i=0;i<8;i++)
	{
		if(favl[i]==song)
			flagi=1;
	       
	}
	return flagi;
}
int charge(int ch)
{
	int chrge=0,i;
	if(ch<=3)                //0->0-15 %charge,2->30-45 %charge
	{
		for(i=ch*15;i<=100;i++)
        		chrge++;
     
      		ch=7;
      		return 1;
    	}
  	else
    		return 0;
}
int connect(int call)
{

    int i,contactList[10],flagi=0;
    for(i=0;i<8;i++) 
    	contactList[i]=i;
    for(i=0;i<8;i++)
    {
       if(call==contactList[i])
          flagi=1;
       
    }
    return flagi;
}

int loss_Prevention()
{
    int n,i; 
    n=rand()%2;	//n for lost or not lost

    int dir; // 1-east,2-west,3-north,4-south
    
    int r=rand()%4+1;	//in any 1 to 4 direction
    if(n==0)
    {
        
            for(dir=1;dir<5;dir++)
            {
              if(dir==r)
                 return r;
            }
       
      }
     else
        return 0;     
      
}
int notify(int s)
{
    if(s==1) //s=1 then call and if s=0 then message
      return 1;
    else
       return 0;
}   

int distance(int src,int dest)
{
	//printf("\n%d %d",src,dest);
	int x[8]={100,200,300,400,500,600,700,800};	//a is cities array like a[0] city is at 100 position
	int y[8]={100,200,300,400,500,600,700,800};
	int dist;
	dist=sqrt(pow(x[src]-x[dest],2)+pow(y[src]-y[dest],2));
	    
	return dist;
    
}

int temp_func(int n,int s)
{    
           
  if(s==0)//feeling hot
  	n=n-4;
  
  else	//feeling cold
  	n=n+4;
  
  return n;
}

int bintoint(int a) {
    int temp,val=0,i=0;
    while(a>0)  {
        temp=a%10;
        val+=temp*pow(2,i);
        i++;
        a/=10;
    }
    return val;
}
  
//Start of main
int main()  {
    //  Declaring File pointers. 
    FILE *bin,*op,*reg,*insflag,*symb;
    
    char opcode[50][2][40];
    char regval[50][2][40];
    char symval[50][2][40];
    char alu_status[3]="000"; //001 for add,010 for subtract
    char ch;
        
    int i,j,regj,opj,symj,line=1;
    int regist[4]={0},linepointer[100];
   

    //  opening different files used in the program
    op = fopen("Instruction.txt","r");
    reg = fopen("Register.txt","r");
    bin = fopen("bin.txt","r");
    insflag = fopen("flow_of_control.txt","w");
    symb=fopen("sym.txt","r");

    /*
        Storing line pointers in 1D array in linepointer
    */
    do{
           char st[100];
           fgets(st,100,bin);
	 // printf("\n line %d pointer %ld\n",line,ftell(bin));
           linepointer[line]=ftell(bin);
		//printf("\nline %d",linepointer[line]);
           line++;
        }while( !feof(bin) );
       
    fclose(bin);
    bin = fopen("bin.txt","r"); 
    
    /*
        Reading opcode and their binary code from instructions.txt file and 
        storing it in 3-D array named opcode
    */
	line=1;
    i=0,j=0;
    do  {
        char st[200];
        fscanf(op,"%s",st);
        if(i==0)    {
            strcpy(opcode[j][i],st);
            i++;
        }
        else    {
            strcpy(opcode[j][i],st);
            j++;
            i--;
        }
    }while( !feof(op) );
    opj=j;
    /*
        Storing only binary codes of registors in regval[] line by line
    */
    
    i=0,j=0;
    do  {
        char st[100];
        fscanf(reg,"%s",st);
        if(i==0){
		strcpy(regval[j][i],st) ;
		   i=1;
	}
        else    {
            strcpy(regval[j][i],st);
            j++;
            i--;
        }
    }while( !feof(reg) );
    regj=j;
    
  
    /*
        Storing only label codes of labels in symval[] line by line
    */
    
    i=0,j=0;
    do  {
        char st[100];
        fscanf(symb,"%s",st);
        if(i==0){
		strcpy(symval[j][i],st) ;
		   i=1;
	}
        else    {
            strcpy(symval[j][i],st);
            j++;
            i--;
        }
    }while( !feof(symb) );
    symj=j;
   

	/*for(j=0;j<opj;j++)  {
		printf("\n %s",opcode[j][0]);
	}

	for(j=0;j<symj;j++)  {
		printf("\n %d %s",symj,symval[j][0]);
	}*/
	
    do  
   {
	char st[100],opc[10],regc[10],imme[10],Label[10];
        int k,m,n,a,b,fl=0;
        
        //  extracting a word from file (8 bit)
        fscanf(bin,"%s",st);
        
         //FOR 2-ADDRESS INSTRUCTION
        //  extracting first 2 bits from string of opcode
        for(i=0;i<2;i++)
            opc[i]=st[i];
        opc[i]='\0';
        
        
       
        for(j=0;j<opj;j++)  {
            
            //finding equivalent opcode
            if(strcmp(opc,opcode[j][1])==0) {
                  fl=1;			//found opcode
	//	printf("\ntwo addresable");
       
                   
            if(strcmp(opcode[j][0],"MOV")==0)  
            {
			//printf("Yes");
                    for(i=2,n=0;i<5;n++,i++)//register one
                        regc[n]=st[i]; 
                        regc[n]='\0';
		    for(m=0;m<regj;m++)
                    {
                             if(strcmp(regc,regval[m][1])==0) 
                              break;
                    }
                    for(i=5,n=0;i<8;n++,i++)//immediate one
                        imme[n]=st[i];
                        imme[n]='\0';
                    
			
                    b=atoi(regval[m][1]);
                    b=bintoint(b);
                    a=atoi(imme);
                    a=bintoint(a);
                    fprintf(insflag,"\nIntruction Register IR: %s %s %d ;",opcode[j][0],regval[m][0],a);
                    regist[b]=a;
		//printf("\n%d %d %d",a,b,regist[b]);
            }
            //printf("\n%d %d %d",a,b,regist[1]);



           else if(strcmp(opcode[j][0],"DIS")==0)
            {
                     
                    for(i=2,n=0;i<5;n++,i++)
                            regc[n]=st[i]; 
                        regc[n]='\0';
		    for(m=0;m<regj;m++)
                    {
                             if(strcmp(regc,regval[m][1])==0) 
                              break;
                    }
	           char first[10];
		   strcpy(first,regval[m][0]);
                   a=atoi(regval[m][1]);
                    for(i=5,n=0;i<8;n++,i++)
                        regc[n]=st[i]; 
                        regc[n]='\0';
		    for(m=0;m<regj;m++)
                    {
                             if(strcmp(regc,regval[m][1])==0) 
                              break;
                    }
			int p,q;
			printf("\nEnter source and destination you want to know distance between: ");
			scanf("%d",&p);
			scanf("%d",&q);
		   char second[10];
		   strcpy(second,regval[m][0]);
		   fprintf(insflag,"\nIntruction Register IR: %s %s %s ;",opcode[j][0],first,second);	
                   b=atoi(regval[m][1]);
                   a=bintoint(a);
                   b=bintoint(b);
		   regist[a]=p;regist[b]=q;
                   int dis=distance(p,q);
                   fprintf(insflag,"\nThe distance between source and destination is:%d",dis);
                   strcpy(alu_status,"010 and 001"); //because subtract opertion is performed
            }
            else if(strcmp(opcode[j][0],"JMP")==0)
             {
                  int temp1,temp2=0;
                  for(i=2,n=0;i<5;n++,i++)
                                regc[n]=st[i];
                                 regc[n]='\0';
		   //fprintf(insflag,"\n%s %s %s ;",regc,regval[0][1],regval[0][0]); 
                    for(k=0;k<regj;k++)
                        if(strcmp(regc,regval[k][1])==0) 
                        break;       
                        
                    for(i=5,n=0;i<8;n++,i++)
                                Label[n]=st[i];
                                 Label[n]='\0';
		   a=atoi(Label);
                    a=bintoint(a);  
	           // fprintf(insflag,"\n%d %s %s ;",a,symval[0][1],symval[0][0]); 
		    for(i=0;i<symj;i++)
		    {
			int chng=atoi(symval[i][1]);
			//if(strcmp(Label,symval[i][1])==0)
			if(chng==a)
				break;

		    }
			
		    //fprintf(insflag,"\n%s ;",Label);
                    
		     
		    fprintf(insflag,"\n%s %s %s ;",opcode[j][0],regval[k][0],symval[i][0]);  
		    
                       
                    b=atoi(regval[k][1]);
                    b=bintoint(b);
                    temp1=regist[b];  
                    if(temp1>temp2)
                    {
                         flag[0]=0;
                         flag[1]=0;
                    }  
                    else if(temp1==temp2)    
                    {	
                         flag[0]=0;
                         flag[1]=1;
                    }
                    else if(temp1<temp2)    
                    {
                          flag[0]=1;
                          flag[1]=0;
                     } 
                      
                     if(flag[0]==0 && flag[1]==0){
			//line=a-1;   
                         fseek(bin,linepointer[a-1],SEEK_SET);//SEEK_SET points to beginning of file upto to linepointer[lineno]
			}
			
         	}
            }
	}
        //regist[1]=b;
	//printf("\n%d",regist[1]);
	
     //FOR 1-ADDRESS INSTRUCTION
        //  extracting first 5 bits from string  
        if(fl!=1)   
        { 
            for(i=0;i<5;i++)
                opc[i]=st[i];
            opc[i]='\0';   
            
            for(j=0;j<opj;j++) 
            {
                //finding equivalent opcode
		//printf("\n%s",opc);
                if(strcmp(opc,opcode[j][1])==0) 
                {
                      fl=1;
			//printf("\nOne Addresable");
                      if(strcmp(opcode[j][0],"CRGE")==0)  {
                                
                                //Take input
                                for(i=5,n=0;i<8;n++,i++)
                                    regc[n]=st[i];
                                     regc[n]='\0';
                                for(k=0;k<regj;k++)
                                  if(strcmp(regc,regval[k][1])==0) 
                                   break; 
                                
                                b=atoi(regval[k][1]);
				b=bintoint(b); 
				int p=rand()%8;
				regist[b]=p;
				fprintf(insflag,"\nIntruction Register IR: %s %s ;",opcode[j][0],regval[k][0]);
                                int ans=charge(regist[b]);
                                if(ans==1)
                                   {
                                    fprintf(insflag,"\nYour mobile is less than 45 percent charge hence its charging");
                                    fprintf(insflag,"\nNow its charged");
                                   }
                                 else
                                  {
                                    fprintf(insflag,"\nYour mobile is greater than 45 percent charge hence no charging required!");
                                  }
                                  strcpy(alu_status,"001"); //because addition opertion is performed
                            }
                         else if(strcmp(opcode[j][0],"MUSI")==0)  {
                                for(i=5,n=0;i<8;n++,i++)
                                    regc[n]=st[i];
                                     regc[n]='\0';
                                for(k=0;k<regj;k++)
                                  if(strcmp(regc,regval[k][1])==0) 
                                   break;  
				fprintf(insflag,"\nIntruction Register IR: %s %s ;",opcode[j][0],regval[k][0]);
                               a=atoi(regval[k][1]);
				
                               a=bintoint(a); 
				printf("Enter id of music you want to play (0-7)\n");
                                int p;
                                scanf("%d",&p); 
                               int ans=music(p);
				regist[a]=p;
                                if(ans==1)
                                 {
                                    fprintf(insflag,"\nSong is found and it is about to play");
                                    
                                 }
                                 else
                                 {
                                      fprintf(insflag,"\nSong not found in favorite list");   
                                 }
                                    
                         }
                         else if(strcmp(opcode[j][0],"CONN")==0)  {
                                for(i=5,n=0;i<8;n++,i++)
                                    regc[n]=st[i];
                                     regc[n]='\0';
                                for(k=0;k<regj;k++)
                                  if(strcmp(regc,regval[k][1])==0) 
                                   break;  
				fprintf(insflag,"\nIntruction Register IR: %s %s ;",opcode[j][0],regval[k][0]);
                               a=atoi(regval[k][1]);
				
                               a=bintoint(a); 
				printf("\nEnter the caller id(0-7): ");
                                int p;
                                scanf("%d",&p); 
                                int ans=connect(p);
				regist[a]=p;
                                if(ans==1)
                                 {
                                    fprintf(insflag,"\ncontact is found in favourite contact list\n");
                                    
                                 }
                                 else
                                 {
                                      fprintf(insflag,"\ncontact is not found in contact list");   
                                 }
                                    
                         }
                         else if(strcmp(opcode[j][0],"TEMP")==0)
                         {
                                 for(i=5,n=0;i<8;n++,i++)
                                    regc[n]=st[i];
                                     regc[n]='\0';
                                for(k=0;k<regj;k++)
                                  if(strcmp(regc,regval[k][1])==0) 
                                   break;  
				fprintf(insflag,"\nIntruction Register IR: %s %s ;",opcode[j][0],regval[k][0]);
                               a=atoi(regval[k][1]);
				
                               a=bintoint(a); 
				printf("\nEnter feeling hot or cold (0-hot 1-cold): ");
                                int p;
                                scanf("%d",&p); 
				regist[a]=p;
				int currtemp;
				if(a==0)
                                 	 currtemp=rand()%100+35;
				else	
					currtemp=rand()%35+0;
                                 
                                 int newtemp=temp_func(currtemp,a);
                                 if(currtemp>newtemp)
                                 {
                                     strcpy(alu_status,"010");
                                     fprintf(insflag,"\nThe temp is decreased from %d to the new temperature is:%d",currtemp,newtemp);
                                 }
                                 else if(currtemp<newtemp)
                                 {
                                     strcpy(alu_status,"001");
                                     fprintf(insflag,"\nThe temp is increased from %d to  the new temperature is:%d",currtemp,newtemp);
                                 }
                         
                         
                         }
                         else if(strcmp(opcode[j][0],"NOTI")==0)
                         {
                                for(i=5,n=0;i<8;n++,i++)
                                    imme[n]=st[i];
                                    imme[n]='\0';
				
                                    b=atoi(imme);
                                    b=bintoint(b);
					fprintf(insflag,"\nIntruction Register IR: %s %d ;",opcode[j][0],b);
                                    int s=notify(b);
                                    if(s==1)
                                       fprintf(insflag,"\nSee Call notification"); 
                                     else
                                        fprintf(insflag,"\nSee SMS notification");  
                         }  
                         else if(strcmp(opcode[j][0],"PASS")==0)
                         {
				//printf("IN PASS");
                             for(i=5,n=0;i<8;n++,i++)
					regc[n]=st[i];
                                    regc[n]='\0';
				//printf("\n%s",regc);
				printf("Enter the password\n");
                                int p;
                                scanf("%d",&p);
                                for(k=0;k<regj;k++)
                                   if(strcmp(regc,regval[k][1])==0) 
                                       break;  
                                    a=atoi(regval[k][1]);
                                a=bintoint(a); 
                                 regist[a]=p;
					fprintf(insflag,"\nIntruction Register IR: %s %s ;",opcode[j][0],regval[k][0]);
                                    int s=password(p);
					//printf("\n%d",s);
                                    if(s==1)
                                       fprintf(insflag,"\nCorrect password ...Jacket unlocked"); 
                                     else
                                        fprintf(insflag,"\nWrong password");    
                         } 
                         else if(strcmp(opcode[j][0],"DEC")==0)
                             {
				//printf("\n In Decreasing ");
                                for(i=5,n=0;i<8;n++,i++)
                                    regc[n]=st[i];
                                    regc[n]='\0';
				//printf("\n%s",regc);
				
                                for(k=0;k<regj;k++)
                                   if(strcmp(regc,regval[k][1])==0) 
                                       break;  
				fprintf(insflag,"\nIntruction Register IR: %s %s ;",opcode[j][0],regval[k][0]);
				//printf("\n%s",regval[k][1]);
                                a=atoi(regval[k][1]);
                                a=bintoint(a);     
                                regist[a]=regist[a]-1;
				//printf("\n%d %d",a,regist[a]);
                                strcpy(alu_status,"010");
                            }
                       
		}
	}
	} 
 
                                
          //FOR 0-ADDRESS INSTRUCTION
        //  extracting first 8 bits from string  
           if(fl!=1)    
           {
                            for(i=0;i<8;i++)
                                opc[i]=st[i];
                            opc[i]='\0';
                            
                            for(j=0;j<opj;j++)  {
                                if(strcmp(opc,opcode[j][1])==0) {
                                    fl=1;

                                    if(strcmp(opcode[j][0],"SLE")==0)   {
                                        
                                        fprintf(insflag,"\nIntruction Register IR: %s ;",opcode[j][0]);
                                        fprintf(insflag,"\nTake rest\n");
                                    }
                                    else if(strcmp(opcode[j][0],"HALT")==0)  {
                                        
                                        //exit
					
                                        return 0;
                                    }
                                    
                                    else if(strcmp(opcode[j][0],"LOSS")==0){ 
					fprintf(insflag,"\nIntruction Register IR: %s ;",opcode[j][0]);
                                    	int n=loss_Prevention();
                                    	if(n==0)
                                        	fprintf(insflag,"\nphone not lost\n");
					
		                            else
		                            {
		                              if(n==1)
		                                  fprintf(insflag,"\nphone is found in east\n");
		                              else if(n==2)
		                                  fprintf(insflag,"\nphone is found in west\n");
		                              else if(n==3)
		                                  fprintf(insflag,"\nphone is found in north\n");
		                              else if(n==4)
		                                  fprintf(insflag,"\nphone is found in south\n");
		                            }
					}

                             }
                           }
                         }
                       
                    //Printing in flow_of_control file the various register values
		
                
		fprintf(insflag,"\nStatus of General Purpose Registers is:\n");     
	        for(i=0;i<4;i++)   
		      fprintf(insflag,"\tR0%d=%d ",i,regist[i]);
                fprintf(insflag,"\n");
		fprintf(insflag,"\nStatus of Special Purpose Registers is:"); 
                fprintf(insflag,"\n\tNegative Flag: %d\n",flag[0]);
                fprintf(insflag,"\tZero Flag: %d\n",flag[1]);
			
                
                fprintf(insflag,"\tProgram Counter: %ld\n",((ftell(bin))/8)+1);
                
		//printf("\tProgram Counter: %ld %ld\n",ftell(bin),(ftell(bin)/8)+1);

                //printf("\tProgram Counter:%ld \n",ftell(bin));
		
                	
	
                if(strcmp(alu_status,"000")!=0)   
                    fprintf(insflag,"\tALU Signal: %s",alu_status);
                fprintf(insflag,"\n\n");
                strcpy(alu_status,"000");
		flag[0]=0;flag[1]=0;
		line++;
		fprintf(insflag,"-----------------------------------------------------------------------------------------------------------------------");
	}while( !feof(bin) );
		
        
          fclose(bin);
          fclose(op);
          fclose(insflag);
          fclose(reg);
	  fclose(symb);  
       
          return 0;
}

