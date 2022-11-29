#include "file_explorer_backend.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define BUF 20

void current_directory(char current[])
{
    printf("Current directory is %s\n", current);
}

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
    char prev[100];
    current[0] = 'C';
    printf("Starting in the C drive\n");
    dir = opendir(current);
    strcpy(prev,current);
    int found;
    int contains = 0;
    int mode;
    char* ptr;
    char hold[100];
    while(1){
        
        printf("Input a command\n0 for current directory\n1 for ls\n2 for cd\n3 to delete file\n4 to create a folder\n5 search for a file\n6 to exit\n\n");
        scanf("%d",&input);
        fflush (stdin);
        switch(input){
            case 0: 
                //printf("Current directory is %s\n", current);
                current_directory(current);
                break;
            case 1:
                printf("Displaying contents of folder\n");
                entity = readdir(dir);
                while(entity != NULL){
                    printf("%s\n",entity->d_name);
                    entity = readdir(dir);
                }
                printf("\n");
                closedir(dir);
                dir = opendir(current);
                break;
            case 2:
                printf(""); //idk why but it needs this
                char path[100] = { 0 };
                while(1){
                    printf("Would you like to input a path(0), or a directory(1)\n");
                    scanf("%d",&mode);
                    fflush(stdin);
                    if(mode == 1 || mode == 0){
                        break;
                    }

                    printf("invalid input, try again\n");
                }
                if (mode == 1){
                    printf("enter name of folder\n");
                    gets(go_to);
                    fflush(stdin);
                    if(!strcmp(go_to,"..")){
                        if(!strcmp(current,prev)){
                            printf("Lowest level directory, doing nothing\n");
                            break;
                        }
                        closedir(dir);
                        dir = opendir(prev);
                        printf("going back\n");
                        sprintf(current,"%s",prev);
                        snprintf(hold,strlen(prev)-1,"%s\n",prev);
                        ptr = strrchr(hold,'/');
                        if (ptr != NULL){
                            //strncpy(hold1,hold,strlen(hold)-strlen(ptr)+1);//doesn't work unless I do this garbage
                            //strcpy(prev,hold1);
                            snprintf(prev,strlen(hold)-strlen(ptr)+2,"%s",hold);
                        }
                        
                        break;
                    }
                    strcat(path,current);
                    strcat(path,go_to);
                    strcat(path,"/");
                    dir = opendir(path);
                    if(dir == NULL){
                        closedir(dir);
                        printf("invalid directory, reverting to previous directory\n");
                        dir = opendir(current);
                    }
                    else{
                        printf("succesful, moving to %s\n",path);
                        strcpy(prev,current);
                        strcpy(current,path);
                    }
                }
                else{
                    printf("enter path\n");
                    gets(path);
                    fflush(stdin);
                    dir = opendir(path);
                    if(dir == NULL){
                        closedir(dir);
                        printf("invalid directory, reverting to previous directory\n");
                        dir = opendir(current);
                    }
                    else{
                        printf("succesful, moving to %s\n",path);
                        strcpy(prev,path);
                        strcat(path,"/");
                        strcpy(current,path);     
                        ptr = strrchr(prev,'/');
                        if (ptr == NULL){
                            sprintf(prev,"%s",current);
                        }
                        else{
                            //strncpy(hold,prev,strlen(prev)-strlen(ptr)+1);//doesn't work unless I do this because c is a garbage language
                            //strcpy(prev,hold);
                            snprintf(prev,strlen(prev)-strlen(ptr)+2,"%s",prev);
                        }
                    }
                }

                break;

            case 3: 
                printf("enter name of folder you want to remove\n");
                char path1[100] = { 0 };
                gets(rm_file);
                fflush(stdin);
                found = 0;
                entity = readdir(dir);
                while(entity != NULL){
                    printf("%s\n",entity->d_name);
                    if(!strcmp(entity->d_name,rm_file)){
                        found = 1;
                        printf("removing %s\n",rm_file);
                        strcat(path1,current);
                        strcat(path1,rm_file);
                        strcat(path1,"/");
                        if (rmdir(path1)==0)
                        {
                            printf("Given empty directory removed successfully\n");
                        }    
                        else
                        {
                            printf("Unable to remove directory %s\n", rm_file);
                        }
                    }
                    entity = readdir(dir);
                }
                if(found == 0){
                        printf("File not found\n");
                }
                closedir(dir);
                dir = opendir(current);
                /* use a for loop to check to see if the folder already exists
                   if it doesnt then print an error message and break
                   else delete the folder*/
                break;
            case 4: 
                printf("enter name of folder you want to create\n");
                char path2[100] = { 0 };
                gets(rm_file);
                fflush(stdin);
                found = 0;
                entity = readdir(dir);
                while(entity != NULL){
                    printf("%s\n",entity->d_name);
                    if(!strcmp(entity->d_name,rm_file)){
                        found = 1;
                        printf("found %s, folder creation failed\n",rm_file);
                    }
                    entity = readdir(dir);
                }
                if(found == 0){
                        printf("Double not found, Creating folder\n");
                        strcat(path2,current);
                        strcat(path2,rm_file);
                        strcat(path2,"/");
                        if(mkdir(path2)){
                            printf("Succesful\n");
                        }
                }
                
                closedir(dir);
                dir = opendir(current);
                /* use a for loop to check to see if the folder already exists
                   if it does then print an error message and break
                   else create the folder*/
                break;
            case 5: //lists all files that contain keyword or share name
                printf("enter keyword or name\n");
                gets(rm_file);
                fflush(stdin);
                found = 0;
                entity = readdir(dir);
                while(entity != NULL){
                    if(strstr(entity->d_name,rm_file)){
                        found = 1;
                        printf("%s\n",entity->d_name);
                    }
                    entity = readdir(dir);
                }
                if (found == 0){
                    printf("no hits\n");
                }

                closedir(dir);
                dir = opendir(current);
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