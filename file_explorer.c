#include <stdio.h>
#include <dirent.h>

int main(){
    int input;
    int end = 0;
    char current[] = "C:\\";
    char go_to[] = "";
    DIR* dir;
    struct dirent* entity;
    for(int i = 'C'; i< 'Z'; i++){
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
        printf("Input a command\n0 for current directory\n1 for ls\n2 for cd\n3 to delete \n4 to create a folder\n5 to exit\n\n");
        scanf("%d",&input);
        switch(input){
            case 0: 
                printf("Current directory is %s\n", current);
                break;
            case 1:
                printf("Displaying contents of folder\n");
                end = 1;
                break;
            case 2:
                printf("enter name of folder\n");
                scanf("%d", go_to);
                break;
            case 5:
                printf("exiting file explorer\n");
                
                return 0;
        }
    }
    //should not get here
   return 0;
}
