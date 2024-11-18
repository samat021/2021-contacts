#include <stdio.h>
#include <string.h>

#include "contacts.h"

#define MAX_CMD_LEN 128

/*
 * This is in general *very* similar to the list_main file seen in lab 2
 * One big difference is the notion of switching between contact logs in one
 * run of the program.
 * You have to create or load a contact log from a file before you can do things
 * like add, lookup, or write.
 * The code below has to check if contact log is NULL before the operations
 * occur. Also, the user has to explicitly clear the current contact log before
 * they can create or load in a new one.
 */
int main(int argc, char **argv) {
    contacts_log_t *log = NULL;

    //array of strings

    //command line arg!!! argc - how many arg have been passed (will be 2?)
    //argv is an array of strings
    if(argc == 2){ //checks if valid

        char *str = strrchr(argv[1], '.');
        //printf("SHTUFF: %s\n", str); //checking what it prints university.txt
        int count = 0;
        //i made count or else there will be errors for the bigerror in the else condition

        //what is needed is just to compare either .txt
        //or .bin
        if ( strcmp(str, ".txt") == 0 && count == 0) {
            count++;
            log = read_contacts_log_from_text(argv[1]);
            if (log != NULL){
                printf("Contacts log loaded from text file\n");
            }
            else {
                printf("Failed to read contacts log from text file\n");
            }

        }


        if ( strcmp(str, ".bin") == 0 && count == 0) {
            log = read_contacts_log_from_binary(argv[1]);
            count++;
            if (log != NULL){
                printf("Contacts log loaded from binary file\n");
            }
            else {
                printf("Failed to read contacts log from binary file\n");
            }


        }

        //last condition, if not either .bin or .txt
        if ((( strcmp(str, ".bin") != 0 ) && count == 0) || (( strcmp(str, ".txt") != 0 ) && count == 0)){
            printf("Error: Unknown contacts log file extension\n");
        }

    

        //og practices below (IGNORE)
        //university.txt turns into university
        //char file1[MAX_NAME_LEN];
        //char file2[MAX_NAME_LEN];

        // strncpy(file1, argv[1], strlen(argv[1]) -4);
        // file1[strlen(argv[1]) -4] = '\0';
        // int len = strlen(argv[1]);
        // char *id = &argv[1][len-4];

    }

    printf("CSCI 2021 Contact Log System\n");
    printf("Commands:\n");
    printf("  create <name>:            creates a new log with specified name\n");
    printf("  log:                      shows the name of the active contacts log\n");
    printf("  add <name> <phone> <zip>: adds a new contact\n");
    printf("  lookup <name>:            searches for a phone number by contact name\n");
    printf("  clear:                    resets current contacts log\n");
    printf("  print:                    shows all contacts in active log\n");
    printf("  write_text:               saves all contacts to text file\n");
    printf("  read_text <file_name>:    loads contacts from text file\n");
    printf("  write_bin:                saves all contacts to binary file\n");
    printf("  read_bin <file_name>:     loads contacts from binary file\n");
    printf("  exit:                     exits the program\n");

    char cmd[MAX_CMD_LEN];





    while (1) {
        printf("contacts> ");
        if (scanf("%s", cmd) == EOF) {
            printf("\n");
            break;
        }

        if (strcmp("exit", cmd) == 0) {
            break;
        }

        else if (strcmp("create", cmd) == 0) {
            scanf("%s", cmd); // Read in new log name
            //creates new log
            if (log != NULL) {
                printf("Error: You already have an contacts log.\n");
                printf("You can remove it with the \'clear\' command\n");
            } else {
                log = create_contacts_log(cmd);
            }
        }

        else if (strcmp("log", cmd) == 0) {
            // char name[MAX_NAME_LEN];
            // scanf("%s", name);

            if (log == NULL) {
                printf("Error: You must create or load a contacts log first\n");
            } else {

                
        const char *log_name = get_contacts_log_name(log);

        //gets a conacts name
        if (log_name != NULL) {
            printf("%s\n", log_name);
        } else {
            printf("Error: No active contacts log name available\n");
        }

            //     const char *log_name = get_contacts_log_name(log);
            //     if (log_name != NULL){
            //         printf("%s\n", log->log_name);
            //     }
            //     else {
            //         printf("Error: You must create or load a contacts log first\n");
            //     }
            // }     
        
        }
        }


        else if (strcmp("add", cmd) == 0) {
            char name[MAX_NAME_LEN];
            unsigned long phone_number;
            unsigned zip_code;
            //contacts_log_t *log;

            //adds a contact

            scanf("%s", name);// Read in new log name
            scanf("%lu", &phone_number);
            scanf("%u", &zip_code);

            if (log == NULL) {
                printf("Error: You must create or load a contacts log first\n");
            } else {
                int contact = add_contact(log, name, phone_number, zip_code);
                if (contact == -1){
                    printf("Error: Invalid phone number and/or zip code\n");
                }
                
            }
        }

        else if (strcmp("print", cmd) == 0) {

            //prints the contact

            if (log == NULL) {
                printf("Error: You must create or load a contacts log first\n");
            } else {
                printf("All contacts in %s:\n", log->log_name);
                print_contacts_log(log);
            }
        
        }


        else if (strcmp("lookup", cmd) == 0) {
            char name[MAX_NAME_LEN];
            //lookup by phonenumber

            scanf("%s", name);// Read in new log name

            if (log == NULL) {
                printf("Error: You must create or load a contacts log first\n");
            } else {
                long number = find_phone_number(log, name);
                if (number != -1){
                    printf("%s: %lu\n", name, number);
                } else {
                    printf("No phone number for '%s' found\n", name);
                }
            }
        }



                // char log = get_contacts_log_name(log);
                // if (log != NULL){
                //     printf("%s", name);
                // }
                // else {
                //     printf("Error: You must create or load a contacts log first\n");
                // }

        else if (strcmp("clear", cmd) == 0) {
            //clears using free

            if (log == NULL) {
                printf("Error: No contacts log to clear\n");
            } else {
        
                free_contacts_log(log);
                log = NULL;
            }
        
        }


        else if (strcmp("write_text", cmd) == 0) {

            //writes a text file

            if (log == NULL) {
                printf("Error: You must create or load a contacts log first\n");
            } else {
                int writetxt = write_contacts_log_to_text(log);
                if (writetxt == 0){
                    //get_contacts_log_name(log)
                    printf("Contacts log successfully written to %s.txt\n", log-> log_name); //log-> log_name
                }
                else {
                    printf("Failed to write contacts log to text file\n");
                }
            }
        
        }


        else if (strcmp("read_text", cmd) == 0) {
            char file_name[MAX_NAME_LEN];
            scanf("%s", file_name);

            //reads a text file

            if (log != NULL) {
                printf("Error: You must clear current contacts log first\n");
            } else {
                log = read_contacts_log_from_text(file_name);
                if(log != NULL){
                    printf("Contacts log loaded from text file\n");
                    //free_contacts_log(new_log);
                }
                else {
                    printf("Failed to read contacts log from text file\n");
                }

                //og before improvement! pretty sure it works
                // contacts_log_t *new_log = read_contacts_log_from_text(file_name);
                // if(new_log != NULL){
                //     printf("Contacts log loaded from text file\n");
                //     //free_contacts_log(new_log);
                //     log = new_log;
                // }
                // else {
                //     printf("Failed to read contacts log from text file\n");
                // }
            }
        
        }

        else if (strcmp("write_bin", cmd) == 0) {
            //writes a binary file
            
            if (log == NULL) {
                printf("Error: You must create or load a contacts log first\n");
            } else {
                int writebin = write_contacts_log_to_binary(log);
                if(writebin == 0){
                    printf("Contacts log successfully written to %s.bin\n", log->log_name);
                }
                else {
                    printf("Failed to write contacts log to binary file\n");
                }
            }
        
        }

        else if (strcmp("read_bin", cmd) == 0) {

            //reads a binary file

            char file_name[MAX_NAME_LEN];
            scanf("%s", file_name);

            if (log != NULL) {
                printf("Error: You must clear current contacts log first\n");
            } else {
                log = read_contacts_log_from_binary(file_name);
                //contacts_log_t *newlog = read_contacts_log_from_binary(file_name);
                if(log != NULL){
                    printf("Contacts log loaded from binary file\n");
                    //free_contacts_log(log); //free is uneeded
                    
                }
                else {
                    printf("Failed to read contacts log from binary file\n");
                }
            }
        
        }


        // TODO Add cases for other commands
        // Read in the command and (possibly) additional arguments with scanf()
        



        else {
            printf("Unknown command %s\n", cmd);
        }
    }

    if (log != NULL) {
        free_contacts_log(log);
    }
    return 0;
}
