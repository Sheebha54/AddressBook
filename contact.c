#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"
int unique_phone(char temp[],AddressBook *addressBook)        //check whether entered phone is unique or not
{
    int i;
    for(i =0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].phone,temp)==0)
        {
            printf("Enter a unique phone number,as already exists\n");
            return 1;
        }
    }
    return 0;
}
int unique_email(char temp[],AddressBook *addressBook)        //check whether entered phone is unique or not
{
    int i;
    for(i =0;i<addressBook->contactCount;i++)
    {
        if(strcmp(addressBook->contacts[i].email,temp)==0)
        {
            printf("Enter a unique email ,as already exists\n");
            return 1;
        }
    }
    return 0;
}
int unique_name(char temp[],AddressBook *addressBook)
{
    int i;
    for(i=0;i<addressBook->contactCount;i++){
        if(strcmp(addressBook->contacts[i].name,temp)==0){
            printf("Entered name already exists,Please enter a unique name\n");
            return 1;
        }
        
    }
    return 0;
}

int validate_name(char temp[])   //validate whether user is entering proper name or not
{
    int i=0;
    while(temp[i]!='\0')
    {
        if(temp[i] >= 'a' && temp[i]<='z' || temp[i] >= 'A' && temp[i]<='Z' || temp[i] == ' ')
        {
            i++;
        }
        else
        {
            printf("Invalid name entered\n");
            return 1;
        }
    }
    return 0;
}
int validate_mobile(char temp[])   //validate whether user is entering proper phone number or not
{
    int i=0;
    while(temp[i]!='\0')
    {
        if(temp[i] >= '0' && temp[i]<='9')
        {
            i++;
        }
        else
        {
            printf("Entered phone is invalid\n");
            return 1;
        }
    }
    if(i>10 || i<10)
    {
         printf("Entered phone is invalid\n");
         return 1;
    }
    else
         return 0;
}
int validate_email(char temp[])
{
    int i=0;
    char com[] = ".com";
    char target[]="@";
    if(strstr(temp,com)== NULL)
    {
        printf("Entered email is invalid, \".com\" is missing\n");
        return 1;
    }
    if(strstr(temp,target)== NULL)
    {
        printf("Entered email is invalid, \"@\" is missing\n");
        return 1;
    }
    return 0;
}

void listContacts(AddressBook *addressbook, int sortCriteria) 
{
    Contact dummy;
    int i,j;
    switch(sortCriteria)
    {
        case 1:
            printf("Sorted based on name\n");
            for(i=0;i<addressbook->contactCount;i++)
            {
                 for(j=0;j<addressbook->contactCount-1;j++)
                 {
                    if((strcmp(addressbook->contacts[j].name,addressbook->contacts[j+1].name))>0)
                    {
                        dummy = addressbook->contacts[j];
                        addressbook->contacts[j] = addressbook->contacts[j+1];
                        addressbook->contacts[j+1] = dummy;

                    }
                 }
            }
            
            break;
        case 2:
            printf("Sorted based on phone\n");
            printf("Sorted based on name\n");
            for(i=0;i<addressbook->contactCount;i++)
            {
                 for(j=0;j<addressbook->contactCount-1;j++)
                 {
                    if((strcmp(addressbook->contacts[j].phone,addressbook->contacts[j+1].phone))>0)
                    {
                        dummy = addressbook->contacts[j];
                        addressbook->contacts[j] = addressbook->contacts[j+1];
                        addressbook->contacts[j+1] = dummy;

                    }
                 }
            }
            
            break;
        case 3:
            printf("Sorted based on email\n");
            printf("Sorted based on name\n");
            for(i=0;i<addressbook->contactCount;i++)
            {
                 for(j=0;j<addressbook->contactCount-1;j++)
                 {
                    if((strcmp(addressbook->contacts[j].email,addressbook->contacts[j+1].email))>0)
                    {
                        dummy = addressbook->contacts[j];
                        addressbook->contacts[j] = addressbook->contacts[j+1];
                        addressbook->contacts[j+1] = dummy;

                    }
                 }
            }
            
            break;
        default:
            printf("Selection criteria is invalid\n");
            return;

    }
    printf("__________________________________________________>\n");
    printf("INDEX\tNAME\t\tMOBILE NUMBER\tEMAIL\n");
    printf("__________________________________________________>\n");
    for(i =0;i<addressbook->contactCount;i++)
    {
        printf("%d\t%s\t%s\t%s\n",i+1,addressbook->contacts[i].name,addressbook->contacts[i].phone,addressbook->contacts[i].email);
    }
    
}

void initialize(AddressBook *addressBook) 
{
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
 {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
    /*Define the logic to create a Contacts */
    char temp[50];
	printf("Menu -> Create Contact\n");
    printf("----------------------------------------------------->\n");
    do
    {
    printf("Enter the name:\n");
    scanf(" %[^\n]",temp);
    }while(validate_name(temp));
    strcpy(addressBook->contacts[addressBook->contactCount].name,temp);
    do
    {
    printf("Enter the phone:\n");
    scanf("%s",temp);
    }while(validate_mobile(temp)|unique_phone(temp,addressBook));   //  to  avoid short circuiting using bitwise or operator
    strcpy(addressBook->contacts[addressBook->contactCount].phone,temp);
    do
    {
    printf("Enter the email:\n");
    scanf("%s",temp);
    }while(validate_email(temp)|unique_email(temp,addressBook));        ////  to  avoid short circuiting using bitwise or operator
    strcpy(addressBook->contacts[addressBook->contactCount].email,temp);
    addressBook->contactCount++;
    printf("Creating contact successful\n");

}


int searchContact(AddressBook *addressBook) 
{
    /* Define the logic for search */
    int opt;
    int count=0;
    char temp[20];
    printf("Menu - Search contact");
    printf("\nPress 1 for search by name");
    printf("\nPress 2 for search by phone");
    printf("\nPress 3 for search by email\n");
    scanf("%d", &opt);
    getchar();
    switch(opt)
    {
        case 1:
          do{
            printf("Enter the name:\n");
            scanf("%[^\n]",temp);
            getchar();
            }while(validate_name(temp));
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcasestr(addressBook->contacts[i].name,temp)!=NULL)
                {
                    count++;
                    printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
                }
                
            }
            if(count == 0)
            {
                 printf("Contact not found\n");
                 return 0;
                    
            }
            break;
        case 2:
            printf("Enter the phone:\n");
            scanf("%[^\n]",temp);
            getchar();
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcasestr(addressBook->contacts[i].phone,temp)!=NULL)
                {
                    count++;
                    printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

                }
                
            }
            if(count == 0)
            {
                 printf("Contact not found\n");
                 return 0;  
            }
               break;
        case 3:
            printf("Enter the email:\n");
            scanf("%[^\n]",temp);
            getchar();
            for(int i=0;i<addressBook->contactCount;i++)
            {
                if(strcasestr(addressBook->contacts[i].email,temp)!=NULL)
                {
                    count++;
                    printf("%d\t%s\t%s\t%s\n",i+1,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);

                }
                
            }
            if(count == 0)
            {
                 printf("Contact not found\n");
                 return 0;
            }
               break;
        default:
               printf("\tEntered option is invalid\n");
    }
    return 1;
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */

    int index,opt;
    char var[50];
    printf("Menu ----Edit Contact\n");
    if(!searchContact(addressBook))
       return;
    printf("Enter the index to edit-----> ");
    scanf("%d",&index);
    getchar();
    if(index<0 || index>addressBook->contactCount)
    {
       printf("You have entered a invalid index\n");
       return; 
    }
    edit:
    printf("1. Edit Name\t 2.Edit Phone\t3.Edit Email\n");
    scanf("%d",&opt);
    switch(opt)
    {
         case 1:
            do{
                printf("Enter the name to edit:\n");
                scanf(" %[^\n]",var);
               // getchar();
            }while(validate_name(var)|unique_name(var,addressBook));
            strcpy(addressBook->contacts[index-1].name,var);
            printf("Name edited successfully\n");
            break;
        case 2:
            do{
                printf("Enter the phone to edit:\n");
                scanf("%s",var);
                getchar();
            }while(validate_mobile(var)|unique_phone(var,addressBook));
            strcpy(addressBook->contacts[index-1].phone,var);
            printf("Phone edited successfully\n");
            break;
        case 3:
            do{
               printf("Enter the email to edit:\n");
               scanf("%s",var);
            }while(validate_email(var)|unique_email(var,addressBook));
            strcpy(addressBook->contacts[index-1].email,var);
            printf("Email edited successfully\n");
            break;
        default:
            printf("Entered option is invalid\n");
            goto edit;
            
    }
    printf("Contact edited successfully\n");


}

    
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int index;
    printf("Menu-----Delete contact\n");
    if(!searchContact(addressBook))
    return;
    printf("Enter the index to edit------->");
    scanf("%d",&index);
    getchar();
    if(index<0 || index>addressBook->contactCount)
    {
        printf("You have entered a invalid index\n");
        return;
    }
    for(int i=index-1;i<addressBook->contactCount-1;i++)
    {
        addressBook->contacts[i]=addressBook->contacts[i+1];
        
    }
    addressBook->contactCount--;
    printf("Contact deleted sucessfully\n");
   
}
