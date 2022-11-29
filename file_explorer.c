#include <stdio.h>
#include <dirent.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define BUF 20
/*void listFiles(const char* dirname) {
    DIR* dir = opendir(dirname);
    if (dir == NULL) {
        return;
    }
    printf("Reading files in: %s\n", dirname);
    struct dirent* entity;
    entity = readdir(dir);
    while (entity != NULL) {
        printf("%hhd %s/%s\n", entity->d_type, dirname, entity->d_name);
        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
            char path[100] = { 0 };
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, entity->d_name);
            listFiles(path);
        }
        entity = readdir(dir);
    }
    closedir(dir);
}*/

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
    int found;
    int contains = 0;
    int mode;
    while(1){
        
        printf("Input a command\n0 for current directory\n1 for ls\n2 for cd\n3 to delete file\n4 to create a folder\n5 cp a file\n6 to exit\n\n");
        scanf("%d",&input);
        fflush (stdin);
        switch(input){
            case 0: 
                printf("Current directory is %s\n", current);
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
                    printf("Would you like to input a path(0), or a directory");
                    scanf("%d",mode);
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
                    printf("%s\n",go_to);
                    if(!strcmp(go_to,"..")){
                        closedir(dir);
                        printf("going back\n");
                        strcpy(current,prev);
                        dir = opendir(prev);
                        break;
                    }
                    strcpy(prev, current);
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
                }
                else{
                    printf("enter path\n");
                    gets(path);
                    fflush(stdin);
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
            case 5:
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