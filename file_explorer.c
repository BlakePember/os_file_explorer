#include <stdio.h>
#include <dirent.h>
#include <string.h>
int main(){
    int input;
    int end = 0;
    char current[] = "C:\\";
    char go_to[] = "";
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
    current[0] = 'C';
    while(1){
        printf("Starting in the C drive\n");
        dir = opendir("C:\\");
        printf("Input a command\n0 for current directory\n1 for ls\n2 for cd\n3 to delete \n4 to create a folder\n5 to exit\n\n");
        scanf("%d",&input);
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
                break;
            case 2:
                closedir(dir);
                printf("enter name of folder\n");
                scanf("%s", go_to);
                strcat(current,go_to);
                strcat(current,"\\");
                printf("%s\n", current);
                dir = opendir(current);
                break;
            case 3: 
                printf("enter name of folder you wnat to remove\n");
                scanf("%s", rm_file);
                # use a for loop to check to see if the folder already exists
                # if it doesnt then print an error message and break
                # else delete the folder
                break;
            case 4: 
                printf("enter name of folder you want to create\n");
                scanf("%s", new_file);
                # use a for loop to check to see if the folder already exists
                # if it does then print an error message and break
                # else create the folder
                break;
            case 5:
                printf("exiting file explorer\n");
                return 0;
            default:
                printf("Did not enter an acceptable command\n");
                break
        }
    }
    //should not get here
   return 0;
}
