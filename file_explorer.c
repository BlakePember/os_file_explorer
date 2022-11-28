#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define BUF 20
int main(){
    int input;
    int end = 0;
    char current[200] = {'C',':','/'};
    char go_to[BUF];
    DIR* dir;
    struct dirent* entity;
    for(int i = 'A'; i< 'Z'; i++){
        current[0] = i;
        dir = opendir(current);
        if (dir != NULL){
            printf("%s\n",current);
            entity = readdir(dir);
            while(entity != NULL){
                printf("%s\n",entity->d_name);
                entity = readdir(dir);
            }
        }
        closedir(dir);
    }
    char rm_file[BUF];
    char new_file[BUF];
    char initial_file[BUF];
    char prev[BUF];
    current[0] = 'C';
    printf("Starting in the C drive\n");
    dir = opendir(current);
    int remove;
    int contains = 0;
    while(1){
        
        printf("Input a command\n0 for current directory\n1 for ls\n2 for cd\n3 to delete file\n4 to create a folder\n5 cp a file\n6 to exit\n\n");
        scanf("%d",&input);
        fflush (stdin);
        switch(input){
            case 0:  // prints current directory
                printf("Current directory is %s\n", current);
                break;
            case 1: // prints all files in current directory
                printf("Displaying contents of folder\n");
                entity = readdir(dir);
                while(entity != NULL){
                    printf("%s\n",entity->d_name);
                    entity = readdir(dir);
                }
                printf("\n");
                break;
            case 2: // changes the current directory
                closedir(dir);
                char path[100] = { 0 };
                strcpy(prev, current);
                printf("enter name of folder\n");
                gets(go_to);
                fflush(stdin);
                strcat(path,current);
                strcat(path,go_to);
                strcat(path,"/");
                dir = opendir(path);
                if(dir == NULL){
                    closedir(dir);
                    printf("invalid directory, reverting to previous directory\n");
                    dir = opendir(prev);
                    strcpy(current,prev);
                }
                else{
                    printf("succesful, moving to %s\n",path);
                    strcpy(current,path);
                }
                break;

            case 3: //deletes file in current directory
                printf("enter name of folder you want to remove\n");
                //scanf("%s", rm_file);
                gets(rm_file);
                fflush(stdin);
                remove = rmdir(rm_file);
                printf("Remove is: %d\n", remove);
                if (remove == 0)
                {
                    printf("Given empty directory removed successfully\n");
                }    
                else
                {
                    printf("Unable to remove directory %s\n", rm_file);
                }
                    
                /* use a for loop to check to see if the folder already exists
                   if it doesnt then print an error message and break
                   else delete the folder*/
                break;
            case 4: //creates a file in current directory
                printf("enter name of folder you want to create\n");
                scanf("%s", new_file);
                /* use a for loop to check to see if the folder already exists
                   if it does then print an error message and break
                   else create the folder*/
                break;
            case 5: //copies a file in the currrent directory
                printf("enter name of folder you want to copy\n");
                //scanf("%s", initial_file);
                gets(initial_file);
                fflush(stdin);
                entity = readdir(dir);
                while(entity != NULL) // goes through each item in directory
                {
                    printf("%s\n",entity->d_name);
                    if(entity->d_name == initial_file) //checks to see if the file you wish to copy exists
                    {
                        contains = 1; //if it does it makes the flag 1 maening true
                        break; //dont need to go thorugh the rest of the directory so break out
                    }
                    entity = readdir(dir);
                }
                if (contains)
                {
                    contains = 0; // if exist turn the flag back to 0, then continue 
                }
                else
                {
                    printf("file or directroy does not exist\n"); //prints error essage cause the file does not exist in the directory
                    break;
                }
                printf("enter name of folder you want to copy to\n");
                //scanf("%s", new_file);
                gets(new_file);
                fflush(stdin);
                entity = readdir(dir);
                while(entity != NULL) // goes through each item in directory
                {
                    printf("%s\n",entity->d_name);
                    if(entity->d_name == new_file) //checks to see if the file you wish to copy to exists
                    {
                        contains = 1; //if it does it makes the flag 1 maening true
                        break;
                    }
                    entity = readdir(dir);
                }
                if (contains)
                {
                    //do not need to create a new file or folder
                    contains = 0;
                    break;
                }
                else
                {
                    //need to create a new file or folder
                }
                // copy contents of the file or directory
                break;
            case 6:
                printf("exiting file explorer\n");
                return 0;
            default:
                printf("Did not enter an acceptable command\n");
                break;
        }
    }
    //should not get here
   return 0;
}