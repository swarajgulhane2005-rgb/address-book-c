#include <stdio.h>
#include "file.h"
#include <unistd.h>


void loading()
{
    for(int i = 1; i <= 100; i++)
    {
        printf("[Loading... %d%%]\r", i);
        fflush(stdout);
        usleep(20000);
    }
    printf("\n");
}

void saveContactsToFile(AddressBook *addressBook)
{
    printf("Saving contacts...\n");  
    loading();            

    FILE *fp = fopen("contacts.txt", "w");

    for(int i = 0; i < addressBook->contactCount; i++)
    {
         if(isValidName(addressBook->contacts[i].name) &&
           isValidPhone(addressBook->contacts[i].phone) &&
           isValidEmail(addressBook->contacts[i].email))
        {
        fprintf(fp, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);
    }
    else{
        printf("Enter valid contact for saving\n");
    }
}
    fclose(fp);
    printf("Data saved successfully\n");
}

void load_data_from_file(AddressBook *addressBook)
{
    FILE *fp = fopen("contacts.txt", "r");
    if(fp == NULL)
    {
        perror("file is not present\n");
        return ;
    }

    for(int i = 0;  ; i++)
    {
        if(addressBook->contactCount >= MAX_CONTACTS)
        {
        printf("Address Book Full\n");
        break;
        }
        int res = fscanf(fp, "%[^,],%[^,],%[^\n]\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email);

        if(res == 3)
        {
            if(isValidName(addressBook->contacts[i].name) &&
               isValidPhone(addressBook->contacts[i].phone) &&
               isValidEmail(addressBook->contacts[i].email))
            {
                addressBook->contactCount++;
            }
            else
            {
                printf("Data missing insert proper data");
            }
        }
        else
            break;
    }
    fclose(fp);
}

