 #include<stdio.h>
 #include<stdlib.h>
 #include<time.h>
 #include<string.h>

 #define GOTOXY(x,y) printf("\330[%d;%df",y,x)

 void delay(int time)
 {

     int milli = 1000 * time ;
     clock();
     while(clock()<milli);
 }

 void input();
 void writefile();
 void search();
 void output();

 struct date{
	   int month;
	   int day;
	   int year;
	   };
  struct account {
	int number;
	char name[100];
	int acct_no;
	float mobile_no;
	char street[100];
	char city[100];
	char acct_type;
	float oldbalance;
	float newbalance;
	float payment;
	struct date lastpayment;
  }customer;
  int tl,sl,ts;
 void main()
{
	  int i,n;
	  char ch;
	  system("clear");
	  printf("   CUSTOMER BILLING SYSTEM:\n\n");
	  printf("===============================\n\n");
	  printf("1:    Add account on list\n");
	  printf("2:    Search customer account\n");
	  printf("3:    Exit\n");
	  printf("================================\n");
	  do
        {
	       printf("\n select what do you want to do?\n");
	       ch=getchar();
	  }while(ch<='0' || ch>'3');
	  switch(ch)
	  {
		case '1':
			system("clear");
			printf("\n how many customer accounts?");
			scanf("%d",&n);
			getchar();
			for(i=0;i<n;i++)
                {
				input();
				if(customer.payment>0.0)
					customer.acct_type=(customer.payment < customer.oldbalance)? 'O': 'D';
				else
customer.acct_type=(customer.oldbalance>0)?'D' : 'C';
				customer.newbalance=customer.oldbalance - customer.payment;
				writefile();
			}
			main();
		case '2':
			system("clear");
			printf("search by what?\n\n");
			printf("1: ------ search by customer number\n");
			printf("2: ------ search by customer name\n");
			search();
			ch=getchar();
			main();
		case '3':
			system("clear");
			delay(500);
			GOTOXY(10,25);
			printf(" A PROJECT BY I AM LEARNING & OTHER TUTO HHH");
			delay(1500);
			exit(1);
}
 }


   void input()
	{
	  FILE *fp=fopen("file.txt","ab+");
	  fseek (fp,0,SEEK_END);
	  tl=ftell(fp);
	  sl=sizeof(customer);
	  ts=tl/sl;
	  fseek(fp,(ts-1)*sl,SEEK_SET);
	  fread(&customer,sizeof(customer),1,fp);
	  printf("\ncustomer no:%d\n",++customer.number);
	  fclose(fp);
	  printf("         Account number:");
	  scanf("%d",&customer.acct_no);
	  getchar();
	  printf("\n       Name:");
	  scanf("%s",customer.name);
	  getchar();
	  printf("\n       mobile no:");
	  scanf("%f",&customer.mobile_no);
	  getchar();
	  printf("\n         Street:");
	  scanf("%s",customer.street);
	  getchar();
	  printf("\n         City:");
	  scanf("%s",customer.city);
	  getchar();
	  printf("\n         Previous balance:");
	  scanf("%f",&customer.oldbalance);
	  getchar();
	  printf("\n         Current payment:");
	  scanf("%f",&customer.payment);
	  getchar();
	  printf("         Payment date(mm/dd/yyyy):");
	  scanf("%d/%d/%d",&customer.lastpayment.month,&customer.lastpayment.day,&customer.lastpayment.year);
	  getchar();

	}
	   void writefile()
   {
	  FILE *fp;
	  fp=fopen("file.txt","ab+");
	  fwrite(&customer,sizeof(customer),1,fp);
	  fclose(fp);
	  return;
   }
   void search()
   {
	 char ch;
	 char nam[100];
	 int n,i,m=1;
	 FILE *fp;
	 fp=fopen("file.txt","r+");
	 do
        {
		printf("\n enter your choice:");
		ch=getchar();
	 }while(ch!='1' && ch!='2');
	 switch(ch)
	 {
	     case '1':
	         fseek(fp,0,SEEK_END);
		     tl=ftell(fp);
		     sl=sizeof(customer);
		     ts=tl/sl;
		     do
		     {
		         printf("\n choose customer number:");
			     scanf("%d",&n);
			     if(n<=0 || n>ts)
			     printf("\nenter correct\n");
			     else
			     {
			         fseek(fp,(n-1)*sl,SEEK_SET);
			         fread(&customer,sl,1,fp);
			         output();
			}
			printf("\n\n again?(y/n)");
			ch=getchar();
		    }while(ch=='y');
		    fclose(fp);
		    break;
	      case '2':
	          fseek(fp,0,SEEK_END);
		    tl=ftell(fp);
		    sl=sizeof(customer);
		    ts=tl/sl;
		    fseek(fp,(ts-1)*sl,SEEK_SET);
		    fread(&customer,sizeof(customer),1,fp);
		    n=customer.number;

		    do
                {
                    printf("\nenter the name:");
			        scanf("%s",nam);
			        fseek(fp,0,SEEK_SET);
			        for(i=1;i<=n;i++)
			{
			     fread(&customer,sizeof(customer),1,fp);
			          if(strcmp(customer.name,nam)==0)
			     {
				output();
				m=0;
				break;
			     }
			}
			if(m!=0)
			printf("\n\n doesn't exist\n");
			printf("\n another?(y/n)");
			ch=getchar();
		    }while(ch=='y');
		    fclose(fp);
	      }
	      return;
	 }

void output()
	 {
	   printf("\n\n    Customer no    :%d \n",customer.number);
	   printf("    Name 	   :%s \n",customer.name);
	   printf("    Mobile no      :%.f \n",customer.mobile_no);
	   printf("    Account number :%d \n",customer.acct_no);
	   printf("    Street         :%s \n",customer.street);
	   printf("    City           :%s \n",customer.city);
	   printf("    Old balance    :%.2f \n",customer.oldbalance);
	   printf("    Current payment:%.2f \n",customer.payment);
	   printf("    New balance    :%.2f \n",customer.newbalance);
	   printf("    Payment date   :%d/%d/%d\n\n",customer.lastpayment.month,customer.lastpayment.day,customer.lastpayment.year);
	   printf("    Account status :");
	   switch(customer.acct_type)
	      {
	      case 'C':
		 printf("CURRENT\n\n");
		 break;
	      case 'O':
		 printf("OVERDUE\n\n");
		 break;
	      case 'D':
		 printf("DELINQUENT\n\n");
		 break;
	      default:
		 printf("ERROR\\n\n");
	      }
	      return;
	   }







Output:
          CUSTOMER BILLING SYSTEM :



1: ADD account on list

2: SEARCH customer account

3: EXIT







SOURCE:

1.  It can hold any number of accounts and account can be added to the program at any time.
     2.The programming of simple calculations such as calculation of due amount, balance etc. have been embed in the code of project.
          3. The Customer Billing System project in C gives you the facility of searching the account by two ways, either by name of the customer or by the number of customer.
          4. If you have nothing to do with the program, you can directly exit from the main menu.




