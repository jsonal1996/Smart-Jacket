#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main()
{
      FILE *code,*sym,*op,*reg,*bin;
      char st[20];
      int line=0,i,j,symj,regj,opj,stlen=0;
      char opcode[30][2][20];
      char regis[8][2][20];
      char label[8][2][20];
      code = fopen("code.txt","r");
      sym = fopen("sym.txt","w");
     // int counter=0;  //holds the address of the machine code instruction
      
      //making symbol table
      // A label is a symbol which mark a location in a program.
      
     //---------------------------------------------------FIRST PASS OF 2 PASS ASSEMBLER---------------------------------------------------------------------------- 
      
      code = fopen("code.txt","r");
      sym = fopen("sym.txt","w");
      fgets(st,20,code);
      do   
      {
         int len;
         len=strlen(st);                         
         for(i=0;i<len;i++)                      //loop for finding colon(label identifier) in the string
         {
            if(st[i]==':')  
            {                   //and then writing in symbol table file its corresponding line number.
                st[i]='\0';
                fprintf(sym,"%s %d\n",st,line+1);
            }
         }
         line++;
         fgets(st,20,code);
     }while( !feof(code) );
     fclose(code);
     fclose(sym);
   
   //--------------------------------------------------------------------------------------------------------------------------------------------------------------
   
     code = fopen("code.txt","r");
     sym = fopen("sym.txt","r");
     op = fopen("Instruction.txt","r");
     reg = fopen("Register.txt","r");
     bin = fopen("bin.txt","w");
 
    //-----------------------reading opcodes and their binary representation and writing them in array--------------------------
     i=0,j=0;
     do    
     {                                       
        fscanf(op,"%s",st);
        if(i==0)    
        {
            strcpy(opcode[j][i],st);
            i++;
        }
        else    
        {
            strcpy(opcode[j][i],st);
            j++;
            i--;
        }
    }while( !feof(op) );                        
     opj=j;                        //opj represents no. of lines in opcode file
     
     
    
   //------------------------reading registers and their binary representation and writing them in array--------------------------- 
     i=0,j=0;
     do 
     {                                     
        fscanf(reg,"%s",st);
        if(i==0)    
        {
            strcpy(regis[j][i],st);
             i++;
        }
        else    
        {
            strcpy(regis[j][i],st);
            j++;
            i--;
        }
    }while( !feof(reg) );
    regj=j;                //regj represents no. of lines in Registers file
    
    
    
   //------------------------reading labels and their line values from symbol table file-------------------
    i=0,j=0;
    do  
    {                                       
        fscanf(sym,"%s",st);
        if(i==0)    {
            strcpy(label[j][i],st);
            i++;
        }
        else    {
            strcpy(label[j][i],st);
            j++;
            i--;
        }
    }while( !feof(sym) );
    symj=j;                //symj represents no. of lines in Symbol table file
    
    
  //--------------------------------------SECOND PASS OF ASSEMBLER-----------------------------------------------------------------------------------------  
   //----------------------------------------Changing one by one each assembly instruction into binary code-------------------------------------
   
    fscanf(code,"%s",st);
    do  
    {                                      
        char temp1[3];
        int val,temp,len,fl=0;
        len=strlen(st);
        if(st[len-1]==':')  {                   //skip if label instruction.(leaving label line blank in binary file)
            //fprintf(bin,"\n");
            stlen=0;
        }
        else    
	{
            for(j=0;j<opj;j++)     
	     {              //comparing string from file and opcode array and then writing binary form in file
                if(strcmp(st,opcode[j][0])==0)  
		{
		  //  printf("%s\n",opcode[j][0]);
                    fprintf(bin,"%s",opcode[j][1]);         //writing the binary format of opcode in binary file
                    fl=1;                                   // keeping track if matches 
                    stlen+=strlen(opcode[j][1]);            //stlen shows the length of binary instruction decoded till now
                    break;
                }
	    }
            if(fl==0)   {
                for(j=0;j<regj;j++) { 
		//printf("%s\n",regis[j][0]);
		//printf("%s\n",st);              //comparing string from file and register array and then writing binary form in file
                    if(strcmp(st,regis[j][0])==0)   {
			//printf("%s\n",regis[j][0]);
                        fprintf(bin,"%s",regis[j][1]);    //writing the binary formatof register in binary file
                        fl=1;
                        stlen+=strlen(regis[j][1]);
                        break;
                    }
                }
            }
            if(fl==0)   {
                for(j=0;j<symj;j++) {               //reading line number from symbol table file and converting it to binary and then writing in binary file
                    if(strcmp(st,label[j][0])==0)   {           //only when jump instructions are used
                        val=atoi(label[j][1]);                  //since int is stored as string it converts it back 
                        strcpy(temp1,"000");
                        j=2;
                        while(val>0)    {               //storing in temp1 the binary representation of line no.
                            temp=val%2;
                            val/=2;
                            temp1[j]=temp+'0';
                            j--;
                        }
                        fprintf(bin,"%s",temp1);            //writing binary representaion finally to the binary file
                        fl=1;
                        break;
                    }
                }
            }
                  
            if(fl==0 && strcmp(st,";")!=0)  {       //when immediate values are encountered in assembly code
                temp=8-stlen;
                if(temp==3) {                       //for 3 bit immediate values(used in 2 address instructions)
                    
                    val=atoi(st);                    // converting immediate value to int
                    strcpy(temp1,"000");       //initializing temp1
                    j=2;                        
                    while(val>0)    {               //converts immediate number into its binary representation
                        temp=val%2;
                        val/=2;
                        temp1[j]=temp+'0';
                        j--;
                    }
                            
                    fprintf(bin,"%s",temp1);            //writing binary representaion finally to the binary file 
                }
            }
            if(strcmp(st,";")==0){                  //checking for end of instruction
                fprintf(bin,"\n");
                stlen=0;
            }
        }
        fscanf(code,"%s",st);
    }while( !feof(code) );
    fclose(code);
    fclose(sym);
    fclose(bin);
    fclose(op);
    fclose(reg);
    return 0;
}
        
     
