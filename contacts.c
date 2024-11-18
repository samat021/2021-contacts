#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "contacts.h"

// This is the (somewhat famous) djb2 hash
unsigned hash(const char *str) {
    unsigned hash_val = 5381;
    int i = 0;
    while (str[i] != '\0') {
        hash_val = ((hash_val << 5) + hash_val) + str[i];
        i++;
    }
    return hash_val % NUM_BUCKETS;
}
//

// Create a new contacts log instance
// log_name: The name of the contacts log
// Returns: Pointer to a contacts_log_t representing an empty log
//          or NULL if an error occurs
contacts_log_t *create_contacts_log(const char *log_name) {


    contacts_log_t *new_log = malloc(sizeof(contacts_log_t));
    if (new_log == NULL) {
        return NULL;
    }

//copies strings
    strcpy(new_log->log_name, log_name); 
    // strcpy(destination, source)
    //initalizing 
    for (int i = 0; i < NUM_BUCKETS; i++) {
        new_log->buckets[i] = NULL;
    }
    new_log->size = 0;

    return new_log;

}

// Returns a pointer to the contacts log name
// log: A pointer to a log to get the name of
// Returns: Pointer to log's name (not to be modified) 
const char *get_contacts_log_name(const contacts_log_t *log) {
    // TODO Not yet implemented
    // node_t *ptr = log
    // create_contacts_log(ptr)
    //checks if log is null
    if (log == NULL) {
        printf("Error: You must create or load a contacts log first\n");
        return NULL;
    }

    //returns log name
    return log->log_name;
}


// Add a new contact to the log (insert into hash table)
// log: A pointer to a contacts log to add the contact to
// name: Contact's name 
// phone_number: Contact's phone number
// zip_code: Contact's zip code
// Returns: 0 if the contact was successfully added
//          or -1 if the contact could not be added
int add_contact(contacts_log_t *log, const char *name, unsigned long phone_number, unsigned zip_code) {
    // TODO Not yet implemented

    

    // you have to do a Malloc for this one
    //creation and adding is when you call Malloc, use free() to take off
    //check if null
    if (log == NULL) {
        //printf("log is NULL!!\n");
        return -1;     
    }

    //hash(name) - this is index 

    //checks if phonenumber and zipcode are within bounds
    if ( phone_number <= 999999999 || phone_number > 9999999999 ) { // checks if within range of 10 digits dont worry bout zero in beginning
        return -1;
    }
    if (zip_code <= 9999 || zip_code > 99999){ //if bad do OR

        return -1;
    }

    node_t *node = malloc(sizeof(node_t));

    //check if node is null
    if (node == NULL) {
        //printf("Node is NULL!!\n");
        return -1;     
    }

    //copies name, number, etc.
    strncpy(node->name, name, MAX_NAME_LEN - 1); 
    node->name[MAX_NAME_LEN - 1] = '\0';
    node->zip_code = zip_code;
    node->phone_number = phone_number;
    node->next = NULL;

    //add nodes, needs for loop
    if (log->buckets[hash(name)] == NULL) {
        log->buckets[hash(name)] = node;
    } else {
        node_t *current = log->buckets[hash(name)];
        while(current->next != NULL){
            current = current->next;
    }
    current->next = node;
    }

    log->size++; //the log gets bigger cause now addded!

    return 0;
}


// Search for a specific contact's phone number in the contacts log
// log: A pointer to a log to search for the phone number in
// name: Contact's name to search for
// Returns: The contact's phone number if found
//          or -1 if no matching contact name is found
long find_phone_number(const contacts_log_t *log, const char *name) {
    // TODO Not yet implemented 
   
    // node->name[MAX_NAME_LEN - 1] = '\0'; ??
    //while loop,
    //strcpy ->
    // strncpy first arg is a character string, takes one string and copy it to the other string. 
   
    // No Malloc-ing needed!!!

    //get the hash value of name //hash(name)
    //use that to find the index of the number in the array
    //use a while loop to traverse the link list
    //while using string compareTo find the name 
    //and return the phone number

    if (log == NULL) { //checks log is null
        printf("log is NULL!!\n");
        return -1;     
    }

    //printf("Here %lu, %s\n", node->phone_number, node->name);
    //no unsigned val is neede

    node_t *node = log->buckets[hash(name)];

    //goes into while loop
    if(log->buckets[hash(name)] != NULL) {

        
        while(node != NULL){
            if (strcmp(node->name, name) == 0){
                //printf("Name is: %s\n", node->name);
                return node->phone_number;
            }
            node = node->next;
            
        }
    }
    return -1;

}


// Print out all contacts in the contacts log
// log: A pointer to the log containing the contacts to print
void print_contacts_log(const contacts_log_t *log) {
    // TODO Not yet implemented
    // no mallocng??


    //gets hold, goes into for loop to print
    node_t *head;
    for(int i = 0; i < NUM_BUCKETS; i++){
        head = log->buckets[i];

        while (head != NULL){
        
        printf("Name: %s, Phone Number: %lu, Zip Code: %u\n", head->name, head->phone_number, head->zip_code);
        head = head->next;
        } 


    }


}

// Frees all memory used to store the contents of the contacts log
// log: A pointer to the contacts log to free
void free_contacts_log(contacts_log_t *log) {
    // TODO Not yet implemented
    node_t *head;
    node_t *temp = NULL;
    //loops through hash, and frees,
    //sets to null so it can earse the mallocing
    for(int i = 0; i < NUM_BUCKETS; i++){
        head = log->buckets[i];
        while(head != NULL){
            temp = head;
            head = head->next;
            free(temp);
        }
        log->buckets[i] = NULL;
    }
    free(log); //log is free!
}

int write_contacts_log_to_text(const contacts_log_t *log) {
    char file_name[MAX_NAME_LEN + strlen(".txt")];
    strcpy(file_name, log->log_name);
    strcat(file_name, ".txt");
    FILE *f = fopen(file_name, "w");
    if (f == NULL) {
        return -1;
    }

    fprintf(f, "%u\n", log->size); //writes size? and thten loops
    for (int i = 0; i < NUM_BUCKETS; i++) {
        node_t *current = log->buckets[i];
        while (current != NULL) {
            fprintf(f, "%s %lu %u\n", current->name, current->phone_number, current->zip_code);
            current = current->next;
        }
    }
    fclose(f);
    return 0;
}

contacts_log_t *read_contacts_log_from_text(const char *file_name) {
    // TODO Not yet implemented


    //you do not need to do the same as write!
    // char file_name[MAX_NAME_LEN + strlen(".txt")];
    // strcpy(file_name, log->log_name);
    // strcat(file_name, ".txt");

    //checks if filename is null
    if (file_name == NULL) {
        //printf("file_name is NULL\n");
        return NULL;
    }

    //opens file and checks if null
    FILE *f = fopen(file_name, "r");

    if (f == NULL) {
        //free_contacts_log(new_log); //no need to do that (becomes more frees than mallocs error)
        return NULL;
    }

    //makes a log

    char filen[MAX_NAME_LEN];
    strncpy(filen, file_name, strlen(file_name) - 4);
    filen[strlen(file_name) - 4] = '\0';
    int size; //unsigned??


    contacts_log_t *new_log = create_contacts_log(filen);

    if (new_log  == NULL) {
        printf("log is NULL\n");
        return NULL;
    }


    //fscanf(f, "%u\n", &new_log->size); doubles size??

    fscanf(f, "%d\n", &size);

    char name[MAX_NAME_LEN];
    unsigned long phone_number;
    unsigned zip_code;

    //reads each contact

    for (int i = 0; i < size; i++) { //NUMbuckets orignally

        fscanf(f, "%s %lu %u", name, &phone_number, &zip_code); //got ride of newline
        add_contact(new_log, name, phone_number, zip_code);
    }


    fclose(f);

    return new_log;
}

int write_contacts_log_to_binary(const contacts_log_t *log) {
    // TODO Not yet implemented
    // //Lab 3 check it out!! (TREASURE!!!)

    char file_name[MAX_NAME_LEN + strlen(".bin")];
    strcpy(file_name, log->log_name);
    strcat(file_name, ".bin");
    FILE *f = fopen(file_name, "w");

    //checks if null
    if (f == NULL) {
        return -1;
    }

    if (log == NULL){
        return -1;
    }


    fwrite(&log->size, sizeof(unsigned), 1, f); //writes size 


    //for loop, each thing has to be done individually instead of one line
    for (int i = 0; i < NUM_BUCKETS; i++) {
        node_t *current = log->buckets[i];
        while (current != NULL) {
            // fwrite("%s %lu %u\n", current->name, current->phone_number, current->zip_code, f);
            // fwrite(log + i, sizeof(person_t), 1, f);
            //fwrite(current->name, sizeof(char), 1, f); //&

            unsigned name_len =strlen(current->name);
            fwrite(&name_len, sizeof(unsigned), 1, f);
            fwrite(current->name, sizeof(char), name_len, f); //&
            fwrite(&current->phone_number, sizeof(unsigned long), 1, f);
            fwrite(&current->zip_code, sizeof(unsigned), 1, f);

            current = current->next;
        }
        
    }


    fclose(f);

    return 0;
}

contacts_log_t *read_contacts_log_from_binary(const char *file_name) {
    // TODO Not yet implemented

    if (file_name == NULL) {
        //printf("file_name is NULL\n");
        return NULL;
    }


    FILE *f = fopen(file_name, "r");

    if (f == NULL) {
        //free_contacts_log(new_log); //no need to free brv
        return NULL;
    }

    char filen[MAX_NAME_LEN];
    strncpy(filen, file_name, strlen(file_name) - 4);
    filen[strlen(file_name) - 4] = '\0';
    unsigned size; //unsigned??
    contacts_log_t *new_log = create_contacts_log(filen);
    if (new_log  == NULL) {
        //printf("log is NULL\n");
        return NULL;
    }

    //fscanf(f, "%u\n", &new_log->size); doubles size??
    //reads size then read contact
    fread(&size, sizeof(unsigned), 1, f);
    unsigned long phone_number;
    unsigned zip_code;

    //for loop

    for (int i = 0; i < size; i++) { //NUMbuckets orignally
        //fread(f, "%s %lu %u", name, &phone_number, &zip_code); //got ride of newline
        char name[MAX_NAME_LEN] = {}; //clears name
        unsigned name_len = 0;
        fread(&name_len, sizeof(unsigned), 1, f); //overriding
        fread(name, sizeof(char), name_len, f); //&
        fread(&phone_number, sizeof(unsigned long), 1, f);
        fread(&zip_code, sizeof(unsigned), 1, f);

        add_contact(new_log, name, phone_number, zip_code);
    
    }

    fclose(f);

    return new_log;

}

