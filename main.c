// A software developed by AnmolTheDeveloper
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
typedef struct
{
    int card_number;
    char cust_name[20];
    int balance;
    char pass[20];
}customer;

typedef enum {cust,admin}who;
void clrscr(void);
void admin_panel(void);
void cust_panel(int cardNum);
void create_customer(void);
void show_customer(who whom, int cardNum);
void show_all_customer(void);
void update_customer(void);
void delete_customer(void);
void checkFile(FILE *fp);
void updateCustName(char name[],int card);
void updateCustCardNum(int cardNum,int card);
void updateCustPass(char pass[],int card);
int updateCustBalance(int balance,int card,who whom);
int authenticate_User(int cardNum, char pass[20]);
void depositCash(int cardNum);
void withdrawCash(int cardNum);
int checkId(int cardNum);
who whom;
void clrscr()
{
	system("cls");
}
int main()
{
    int card_num=0;
    top:
    clrscr();
    printf("A software developed by AnmolTheDeveloper\nfb.com\\anmolthedeveloper\nAdmin card number : 3131\nThis copy is only for testing purpose\n\n");
    printf("Enter card number : ");
    scanf("%d",&card_num);
    if(card_num==3131)
        admin_panel();
    else
        cust_panel(card_num);
    getch();
    goto top;
    return 0;
}

// Administrator Panel
void admin_panel()
{
    int choice;
    top:
    clrscr();
    printf("Welcome Admin\n");
    printf("[1]Create new customer\n[2]Show customer\n[3]Show all customer\n[4]Update customer\n[5]Delete customer\n[6]Main menu\n[7]Exit\nYour choice : ");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            create_customer();
            break;
        case 2:
            show_customer(whom=admin,0);
            break;
        case 3:
            show_all_customer();
            break;
        case 4:
            update_customer();
            break;
        case 5:
            delete_customer();
            break;
        case 6:
            main();
            break;
        case 7:
            exit(0);
            break;
        default:
            printf("Wrong choice try again");
            getch();
            goto top;
    }
    goto top;
}

// Customer panel
void cust_panel(int cardNum)
{
    customer c1;
    FILE *fp_cust_panel;
    int choice=0;
    fp_cust_panel=fopen("data.dat","rb");
    checkFile(fp_cust_panel);
    while(fread(&c1,sizeof(c1),1,fp_cust_panel)>0)
    {

        if(c1.card_number==cardNum)
        {
            fclose(fp_cust_panel);
            top:
            clrscr();
            printf("\nWelcome %s\n",c1.cust_name);
            printf("[1]Cash withdraw\n[2]Cash deposit\n[3]Balance\n[4]Main Menu\n[5]Exit\nYour choice : ");
            scanf("%d",&choice);
            switch(choice)
            {
                case 1:
                    withdrawCash(cardNum);
                    break;
                case 2:
                    depositCash(cardNum);
                    break;
                case 3:
                    show_customer(cust,cardNum);
                    break;
                case 4:
                    main();
                    break;
                case 5:
                    exit(0);
                    break;
                default:
                    goto top;
            }
            goto top;
        }
        else
        {
            printf("\nWe don't recognize you try again...");
            fclose(fp_cust_panel);
        }
    }
}

void create_customer()
{
    FILE *fp;
    customer c1,c2;
    fp = fopen("data.dat","ab+");
    checkFile(fp);
    printf("\n\nEnter customer name : ");
    fflush(stdin);
    gets(c1.cust_name);
    printf("\nEnter card number : ");
    scanf("%d",&c1.card_number);
    while(fread(&c2,sizeof(c2),1,fp)>0)
    {
        if(c2.card_number==c1.card_number)
        {
            printf("\n\nCan not create new user with existing card number...");
            goto end;
        }
    }
    printf("Enter password for customer : ");
    fflush(stdin);
    gets(c1.pass);
    printf("Enter balance : ");
    scanf("%d",&c1.balance);
    fwrite(&c1,sizeof(c1),1,fp);
    printf("\n\nData Saved Successfully...");
    end:
    getch();
    fclose(fp);
}

void show_customer(who whom,int cardNum)
{
    FILE *fp;
    customer c1;
    char password[20];
    int cardinum=cardNum;
    fp = fopen("data.dat","rb");
    checkFile(fp);
    if(whom==cust)
    {
        printf("\nEnter password : ");
        fflush(stdin);
        gets(password);
        if(!authenticate_User(cardinum,password))
        {
            printf("\nWrong password try again...");
            getch();
            cust_panel(cardNum);
        }
    }
    else
    {
        printf("Enter customer card number : ");
        scanf("%d",&cardinum);
    }

    if(checkId(cardinum))
    {
        while(fread(&c1,sizeof(c1),1,fp)>0)
        {
            if(c1.card_number==cardinum && whom==admin)
            {
                printf("\nName: %s\tCard number: %d\tBalance: %d\n",c1.cust_name,c1.card_number,c1.balance);
            }

            else if(c1.card_number==cardinum)
            {
                printf("\nBalance : %d\n",c1.balance);
            }
        }
    }
    else
        printf("\nId doesn't exist!");
    fclose(fp);
    getch();
    if(whom==admin)
        admin_panel();
    else
        cust_panel(cardNum);
}

void show_all_customer()
{
    FILE *fp;
    customer c1;
    fp = fopen("data.dat","rb");
    checkFile(fp);
    while(fread(&c1,sizeof(c1),1,fp)>0)
        printf("Name: %s\tCard number: %d\tBalace: %d\n",c1.cust_name,c1.card_number,c1.balance);
    fclose(fp);
    getch();
    admin_panel();
}

void update_customer()
{
    customer c0;
    int cardNumber=0;
    int choice;
    top:
    printf("\n[1]Change name\n[2]Change card number\n[3]change password\n[4]Change balance\n[5]Back to admin panel\nYour choice : ");
    scanf("%d",&choice);
    if(!(choice==5))
    {
        printf("\nEnter card number : ");
        scanf("%d",&cardNumber);
    }
    switch(choice)
    {
	case 1:
		printf("\nEnter new name : ");
		fflush(stdin);
		gets(c0.cust_name);
		updateCustName(c0.cust_name,cardNumber);
		break;
	case 2:
	    printf("\nEnter old card number : ");
	    scanf("%d",&cardNumber);
		printf("\nEnter new card number : ");
		scanf("%d",&c0.card_number);
		updateCustCardNum(c0.card_number,cardNumber);
		break;
	case 3:
		printf("\nEnter new password : ");
		fflush(stdin);
		gets(c0.pass);
		updateCustPass(c0.pass,cardNumber);
		break;
	case 4:
		printf("\nEnter new balance : ");
		scanf("%d",&c0.balance);
		int amount=c0.balance;
		updateCustBalance(amount,cardNumber,admin);
		break;
	case 5:
		break;
	default:
		printf("Wrong choice try again...");
		goto top;
    }
}

//For Update Name
void updateCustName(char name[20],int card)
{
    customer c1;
    FILE *fp,*fp1;
    fp=fopen("data.dat","rb");
    fp1=fopen("tata.dat","wb");
    checkFile(fp);
    checkFile(fp1);
    if(checkId(card))
    {
        while(fread(&c1,sizeof(c1),1,fp)>0)
        {
            if(c1.card_number==card)
                strcpy(c1.cust_name,name);
            fwrite(&c1,sizeof(c1),1,fp1);
        }
        printf("\nUpdate Successful...");
    }
    else
        printf("\nId doesn't exist!");
    fclose(fp);
    fclose(fp1);
    remove("data.dat");
    rename("tata.dat","data.dat");
    getch();
    update_customer();

}
//For Update Card Number
void updateCustCardNum(int cardNum,int card)
{
    customer c1;
    FILE *fp,*fp1;
    fp=fopen("data.dat","rb");
    fp1=fopen("tata.dat","wb");
    checkFile(fp);
    checkFile(fp1);
    if(checkId(card))
    {
        while(fread(&c1,sizeof(c1),1,fp)>0)
        {
            if(c1.card_number==card)
                c1.card_number=cardNum;

            fwrite(&c1,sizeof(c1),1,fp1);
        }
        printf("\nUpdate Successful...");
    }
    else
        printf("\nId doesn't exist!");
    fclose(fp);
    fclose(fp1);
    remove("data.dat");
    rename("tata.dat","data.dat");

    getch();
    update_customer();
}
//For Update Password
void updateCustPass(char pass[20],int card)
{
    customer c1;
    FILE *fp,*fp1;
    fp=fopen("data.dat","rb");
    fp1=fopen("tata.dat","wb");
    checkFile(fp);
    checkFile(fp1);
    if(checkId(card))
    {
        while(fread(&c1,sizeof(c1),1,fp)>0)
        {
            if(c1.card_number==card)
                strcpy(c1.pass,pass);
            fwrite(&c1,sizeof(c1),1,fp1);
        }
         printf("\nUpdate Successful...");
    }
    else
        printf("\nId doesn't exist!");
    fclose(fp);
    fclose(fp1);
    remove("data.dat");
    rename("tata.dat","data.dat");
    getch();
    update_customer();
}


//For Update Balance
int updateCustBalance(int balance,int cardNum,who whom)
{
    customer c1;
    FILE *fp,*fp1;
    fp=fopen("data.dat","rb");
    fp1=fopen("tata.dat","wb");
    checkFile(fp);
    checkFile(fp1);
    if(checkId(cardNum))
    {
        while(fread(&c1,sizeof(c1),1,fp)>0)
        {
            if(c1.card_number==cardNum)
            {
                if(whom==cust)
                    c1.balance+=balance;
                else
                    c1.balance=balance;
                printf("Updated balance : %d",c1.balance);
            }
            fwrite(&c1,sizeof(c1),1,fp1);
        }
        if(whom==cust)
            printf("\nDeposited Successfully...");
        else
            printf("\nUpdated successfully...");
    }
    else
        printf("\nId doesn't exist!");
    fclose(fp1);
    fclose(fp);
    remove("data.dat");
    rename("tata.dat","data.dat");
    if(whom==admin)
    {


        getch();
        return 0;
    }
    else
    {
        getch();
        return 0;
    }
}

void delete_customer()
{
    customer c1;
    int card=0;
    FILE *fp,*fp1;
    fp=fopen("data.dat","rb");
    fp1=fopen("tata.dat","wb");
    checkFile(fp);
    checkFile(fp1);
    printf("\nEnter new card number : ");
    scanf("%d",&card);
    if(checkId(card))
    {
        while(fread(&c1,sizeof(c1),1,fp)>0)
        {
            if(c1.card_number!=card)
                fwrite(&c1,sizeof(c1),1,fp1);
        }
         printf("\nDeleted Successfully...");
    }
    else
        printf("\nId doesn't exist!");
    fclose(fp);
    fclose(fp1);
    remove("data.dat");
    rename("tata.dat","data.dat");

    getch();

}

void checkFile(FILE *fp)
{
    if(fp==NULL)
    {
        printf("\nDATA FILE MISSING...");
        getch();
        exit(1);
    }
}

int authenticate_User(int cardNum,char pass[20])
{
    FILE *fp;
    customer c1;
    fp=fopen("data.dat","rb");
    while(fread(&c1,sizeof(c1),1,fp)>0)
    {
        if(c1.card_number==cardNum && strcmp(pass,c1.pass)==0)
        {
            fclose(fp);
            return 1;
        }
        else
        {
            fclose(fp);
            return 0;
        }
    }
}

void depositCash(int cardNum)
{
    int amount=0;
    char pass[20];
    printf("\nEnter password : ");
    fflush(stdin);
    gets(pass);
    if(!authenticate_User(cardNum,pass))
    {
        printf("\nWrong password try again!");
    }
    else
    {
        printf("\nEnter amount : ");
        scanf("%d",&amount);
        updateCustBalance(amount,cardNum,cust);
    }
}

void withdrawCash(int cardNum)
{
    FILE *fp,*fp1;
    customer c1;
    char pass[20];
    int amount=0;
    fp = fopen("data.dat","rb");
    fp1 = fopen("tata.dat","wb");
    checkFile(fp);
    checkFile(fp1);
    printf("\nEnter password : ");
    fflush(stdin);
    gets(pass);
    if(!authenticate_User(cardNum,pass))
    {
        printf("\nWrong password try again!");
        fclose(fp);
        fclose(fp1);
    }
    else
    {
        printf("\nEnter amount : ");
        scanf("%d",&amount);
        while(fread(&c1,sizeof(c1),1,fp)>0)
        {
            if(c1.card_number==cardNum)
            {
                if((c1.balance-amount)<0)
                    printf("\nInsufficient balance...");
                else
                {
                    c1.balance-=amount;
                    printf("\nCurrent balance : %d \nPlease take your cash...",c1.balance);
                }

            }
            fwrite(&c1,sizeof(c1),1,fp1);
        }
        fclose(fp);
        fclose(fp1);
        remove("data.dat");
        rename("tata.dat","data.dat");
    }
    getch();
}

int checkId(int cardNum)
{
    FILE *fp;
    int flag=0;
    customer c1;
    fp=fopen("data.dat","rb");
    checkFile(fp);
    while(fread(&c1,sizeof(c1),1,fp)>0)
    {
        if(c1.card_number==cardNum)
            flag++;
    }
    fclose(fp);
    if(flag==0)
        return 0;
    else
        return 1;
}
