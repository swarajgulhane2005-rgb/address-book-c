#include "contact.h"
#include <string.h>
#include "populate.h"
#include <stdio.h>
#include "file.h"

int isValidName(char name[])
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if (name[i] == ' ') 
            continue;

        if (!((name[i] >= 'a' && name[i] <= 'z') ||
      (name[i] >= 'A' && name[i] <= 'Z') ||
       name[i] == ' '))
        return 0;
    }
    return 1;
}

int isValidPhone(char phone[])
{
    int count = 0;

    for (int i = 0; phone[i] != '\0'; i++)
    {

        if (phone[i] == ' ') 
            continue;
            
        if (phone[i] < '0' || phone[i] > '9')
            return 0;
        count++;
    }

    if (count != 10)
        return 0;

    return 1;
}

int isValidEmail(char email[])
{
    int i = 0 ;
    while(email[i] == ' ')
        i++; 

    char *at = strchr(email, '@');

    if(at == NULL)
        return 0;

    if(strstr(email, ".com") || strstr(email, ".in"))
        return 1;

    return 0;
}


void sort_name(AddressBook *addressBook){
    Contact temp;

    for(int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for(int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if(strcmp(addressBook->contacts[j].name, addressBook->contacts[j+1].name) > 0)
            {
            temp = addressBook->contacts[j];
            addressBook->contacts[j] = addressBook->contacts[j+1];
            addressBook->contacts[j+1] = temp ;
            }
        }
    }
}

void sort_phone(AddressBook *addressBook){
    Contact temp;

    for(int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for(int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if(strcmp(addressBook->contacts[j].phone, addressBook->contacts[j+1].phone) > 0)
            {
            temp = addressBook->contacts[j];
            addressBook->contacts[j] = addressBook->contacts[j+1];
            addressBook->contacts[j+1] = temp ;
            }
        }
    }
}

void sort_email(AddressBook *addressBook){
    Contact temp;

    for(int i = 0; i < addressBook->contactCount - 1; i++)
    {
        for(int j = 0; j < addressBook->contactCount - i - 1; j++)
        {
            if(strcmp(addressBook->contacts[j].email, addressBook->contacts[j+1].email) > 0)
            {
            temp = addressBook->contacts[j];
            addressBook->contacts[j] = addressBook->contacts[j+1];
            addressBook->contacts[j+1] = temp ;
            }
        }
    }
}

void initialize (AddressBook *ptr){
    ptr->contactCount = 0;

   // populateAddressBook(ptr);
   printf("Loading contacts...\n");
   loading();

   load_data_from_file(ptr);
}

void listContacts(AddressBook *addressBook){
    int choice ;
    printf("List based on: \n1. Name\n2. Phone\n3. Email\n");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
        sort_name(addressBook);
        break;

        case 2:
        sort_phone(addressBook);
        break;

        case 3:
        sort_email(addressBook);
        break;

        default:
        printf("Enter correct input\n");
        break;
    }
        
    for (int i = 0; i < addressBook->contactCount; i++){
        printf("%20s %15s %30s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
}

void createContact(AddressBook *addressBook){
    if(addressBook->contactCount >= MAX_CONTACTS){
        printf("List is full\n");
    }
    else{
   Contact new;
   printf("Enter name: ");
   scanf(" %[^\n]", new.name);

    if (!isValidName(new.name))
    {
        printf("Invalid name\n");
        return;
    }

    printf("Enter phone number: ");
    scanf(" %[^\n]", new.phone);

    if (!isValidPhone(new.phone))
    {
        printf("Invalid phone\n");
        return;
    }

    printf("Enter email: ");
    scanf(" %[^\n]", new.email);

    if (!isValidEmail(new.email))
    {
        printf("Invalid email\n");
        return;
    }


   addressBook->contacts[addressBook->contactCount] = new ;
   addressBook->contactCount++ ;

   printf("Contact added successfully\n");
    }
}


void searchContact(AddressBook *addressBook){
    char buffer[50];
    int choice, found = 0;
    printf("How you want to search :\n");
    printf("1. Name\n2. Phone\n3. Email\n");
    scanf("%d", &choice);
   
    switch (choice)
    {
        case 1:
        printf("Enter the name you want to search :");
        scanf(" %[^\n]", buffer);
        if (!isValidName(buffer))
        {
        printf("Invalid name number\n");
        return;
        }

        for(int i = 0; i < addressBook-> contactCount; i++){
            if(strcasestr(addressBook->contacts[i].name, buffer)){
            printf("Contact found\n");
            printf("%20s%15s%35s\n",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            found = 1;
        }
        }
        if(found == 0){
        printf("contact not found\n");
        }
        break;
    
        case 2:
        printf("Enter the number of person you want to search :");
        scanf(" %[^\n]", buffer);
        if (!isValidPhone(buffer))
        {
        printf("Invalid phone number\n");
        return;
        }  
    

        for(int i = 0; i < addressBook-> contactCount; i++){
            if(strcasestr(addressBook->contacts[i].phone, buffer)){
            printf("Contact found\n");
            printf("%20s%15s%35s\n",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            found = 1;
        }
        }
        if(found == 0){
            printf("contact not found\n");
        }
        break;
    
        case 3:
        printf("Enter the email of person you want to search :");
        scanf(" %[^\n]", buffer);
        if (!isValidEmail(buffer))
        {
        printf("Invalid email number\n");
        return;
        }


        for(int i = 0; i < addressBook-> contactCount; i++){
            if(strcasestr(addressBook->contacts[i].email, buffer)){
            printf("Contact found\n");
            printf("%20s%15s%35s\n",addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
            found = 1 ;
        }
        }
        if(found == 0){
            printf("contact not found\n");
        }
        break;
    
        default:
        printf("Enter correct input\n");
        break;
    }
}


void editContact(AddressBook *addressBook){
    char buffer[50];
    printf("Enter the contact you want to edit : ");
    scanf(" %[^\n]", buffer);
    
    for(int i = 0; i<addressBook->contactCount; i++)
    {
        if(strcasestr(addressBook->contacts[i].name, buffer))
        {
            printf("Enter contact : %s\n", buffer);
            printf("Enter new name : ");
            scanf(" %[^\n]", addressBook->contacts[i].name);
            if (!isValidName(addressBook->contacts[i].name))
            {
            printf("Invalid name\n");
            return;
            }
    
            printf("Enter new phone number : ");
            scanf(" %[^\n]", addressBook->contacts[i].phone);
            if (!isValidPhone(addressBook->contacts[i].phone))
            {
            printf("Invalid phone number\n");
            return;
            }

            printf("Enter new email : ");
            scanf(" %[^\n]", addressBook->contacts[i].email);
            if (!isValidEmail(addressBook->contacts[i].email))
            {
            printf("Invalid email\n");
            return;
            }

            printf("contact successfully edited\n");
            return ;
        }
    }
    printf("contact does not found\n");
}

void deleteContact(AddressBook *addressBook){
    char buffer[50];
    printf("Enter the contact you want to delete : ");
    scanf(" %[^\n]", buffer);

    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].name, buffer) == 0){
        for(int j = i; j < addressBook->contactCount - 1; j++)
        {
        
            addressBook->contacts[j] = addressBook->contacts[j+1];
        }
        addressBook->contactCount-- ;
        printf("contact delete successfully\n");
        return ;
    }
    }

     for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, buffer)==0){
        for(int j = i; j < addressBook->contactCount - 1; j++)
        {
        
            addressBook->contacts[j] = addressBook->contacts[j+1];
        }
        addressBook->contactCount-- ;
        printf("contact delete successfully\n");
        return ;
    }
    }

     for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].email, buffer) == 0){
       for(int j = i; j < addressBook->contactCount - 1; j++)
        {
        
            addressBook->contacts[j] = addressBook->contacts[j+1];
        }
        addressBook->contactCount-- ;
        printf("contact delete successfully\n");
        return ;
    }
    }
printf("contact does not found\n");
}




