#include "file_explorer_backend.h"
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#define BUF 20

void current_directory(char *current)
{
    printf("Current directory is %s\n", current);
}
void list_contents(char *current)
{
    DIR *dir;
    struct dirent *entity;
    dir = opendir(current);
    printf("Displaying contents of folder\n");
    entity = readdir(dir);
    while (entity != NULL)
    {
        printf("%s\n", entity->d_name);
        entity = readdir(dir);
    }
    closedir(dir);
}

void change_directory(char *current, char *prev, char *go_to)
{
    DIR *dir;
    struct dirent *entity;
    dir = opendir(current);
    char path[100] = {0};
    char hold[100];
    char *ptr;
    if (!strstr(go_to,"/"))
    {
        if (!strcmp(go_to, ".."))
        {
            if (!strcmp(current, prev))
            {
                printf("Lowest level directory, doing nothing\n");
                return;
            }
            closedir(dir);
            dir = opendir(prev);
            printf("going back\n");
            sprintf(current, "%s", prev);
            snprintf(hold, strlen(prev) - 1, "%s\n", prev);
            ptr = strrchr(hold, '/');
            if (ptr != NULL)
            {
                snprintf(prev, strlen(hold) - strlen(ptr) + 2, "%s", hold);
            }
            return;
        }
        strcat(path, current);
        strcat(path, go_to);
        strcat(path, "/");
        dir = opendir(path);
        if (dir == NULL)
        {
            closedir(dir);
            printf("invalid directory, reverting to previous directory\n");
            dir = opendir(current);
        }
        else
        {
            printf("succesful, moving to %s\n", path);
            strcpy(prev, current);
            strcpy(current, path);
        }
    }
    else
    {
        dir = opendir(go_to);
        if (dir == NULL)
        {
            closedir(dir);
            printf("invalid directory, reverting to previous directory\n");
            dir = opendir(current);
        }
        else
        {
            printf("succesful, moving to %s\n", go_to);
            strcpy(prev, go_to);
            strcat(go_to, "/");
            strcpy(current, go_to);
            ptr = strrchr(prev, '/');
            if (ptr == NULL)
            {
                sprintf(prev, "%s", current);
            }
            else
            {
                snprintf(prev, strlen(prev) - strlen(ptr) + 2, "%s", prev);
            }
        }
    }
}

void delete_file(char *current, char *rm_file)
{
    DIR *dir;
    struct dirent *entity;
    dir = opendir(current);
    char path[100] = {0};
    int found = 0;
    entity = readdir(dir);
    while (entity != NULL)
    {
        printf("%s\n", entity->d_name);
        if (!strcmp(entity->d_name, rm_file))
        {
            found = 1;
            printf("removing %s\n", rm_file);
            strcat(path, current);
            strcat(path, rm_file);
            strcat(path, "/");
            if (rmdir(path) == 0)
            {
                printf("Given empty directory removed successfully\n");
            }
            else
            {
                printf("Unable to remove directory %s\n", rm_file);
            }
            break;
        }
        if (found == 0)
        {
            entity = readdir(dir);
        }
    }
    printf("File not found\n");
}

void create_directory(char *current, char *rm_file)
{
    char path2[100] = {0};
    DIR *dir;
    struct dirent *entity;
    dir = opendir(current);
    entity = readdir(dir);
    while (entity != NULL)
    {
        printf("%s\n", entity->d_name);
        if (!strcmp(entity->d_name, rm_file))
        {
            printf("found %s, folder creation failed\n", rm_file);
            break;
        }
        entity = readdir(dir);
    }
    printf("Double not found, Creating folder\n");
    strcat(path2, current);
    strcat(path2, rm_file);
    strcat(path2, "/");
    if (mkdir(path2))
    {
        printf("Succesful\n");
    }
    else
    {
        printf("weird stuff happened\n");
    }
}

void search(char *current, char *rm_file)
{
    DIR *dir;
    struct dirent *entity;
    dir = opendir(current);
    int found = 0;
    entity = readdir(dir);
    while (entity != NULL)
    {
        if (strstr(entity->d_name, rm_file))
        {
            found = 1;
            printf("%s\n", entity->d_name);
        }
        entity = readdir(dir);
    }
    if (found == 0)
    {
        printf("no hits\n");
    }
}

int main()
{
    int input;
    char current[200] = {'C', ':', '/'};
    char go_to[BUF];
    DIR *dir;
    struct dirent *entity;
    char rm_file[BUF];
    char new_file[BUF];
    char initial_file[BUF];
    char prev[100];
    printf("Starting in the C drive\n");
    dir = opendir(current);
    strcpy(prev, current);
    int found;
    int contains = 0;
    int mode;
    char *ptr;
    char hold[100];
    while (1)
    {

        printf("Input a command\n0 for current directory\n1 for ls\n2 for cd\n3 to delete file\n4 to create a folder\n5 search for a file\n6 to exit\n\n");
        scanf("%d", &input);
        fflush(stdin);
        switch (input)
        {
        case 0:
            // printf("Current directory is %s\n", current);
            current_directory(current);
            break;
        case 1:
            list_contents(current);
            break;
        case 2:
            printf("enter name of folder or path to enter\n");
            gets(go_to);
            fflush(stdin);
            change_directory(current, prev, go_to);
            break;

        case 3:
            printf("enter name of folder you want to remove\n");
            gets(rm_file);
            fflush(stdin);
            delete_file(current, rm_file);
            break;
        case 4:
            printf("enter name of folder you want to create\n");
            gets(rm_file);
            fflush(stdin);
            create_directory(current, rm_file);
            break;
        case 5: // lists all files that contain keyword or share name
            printf("enter keyword or name\n");
            gets(rm_file);
            fflush(stdin);
            search(current, rm_file);
            break;
        case 6:
            printf("exiting file explorer\n");
            return 0;
        default:
            printf("Did not enter an acceptable command\n");
            break;
        }
    }
    // should not get here
    return 0;
}
