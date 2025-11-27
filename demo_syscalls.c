#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <stdlib.h>

void print_permissions(mode_t mode) {
    printf( (S_ISDIR(mode)) ? "d" : "-");
    printf( (mode & S_IRUSR) ? "r" : "-");
    printf( (mode & S_IWUSR) ? "w" : "-");
    printf( (mode & S_IXUSR) ? "x" : "-");
    printf( (mode & S_IRGRP) ? "r" : "-");
    printf( (mode & S_IWGRP) ? "w" : "-");
    printf( (mode & S_IXGRP) ? "x" : "-");
    printf( (mode & S_IROTH) ? "r" : "-");
    printf( (mode & S_IWOTH) ? "w" : "-");
    printf( (mode & S_IXOTH) ? "x" : "-");
}

int main(void) {
    DIR *dir;
    struct dirent *entry;
    struct stat file_stat;
    
    // 1. opendir: Open the current directory
    dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        return 1;
    }

    printf("Listing files in current directory:\n");
    printf("%-12s %-20s %-10s %s", "Permissions", "Filename", "Size", "Last Modified\n");
    printf("------------------------------------------------------------------------\n");

    // 2. readdir: Read entries one by one

    
    while ((entry = readdir(dir)) != NULL) {
        // 3. stat: Get metadata for the file
        if (stat(entry->d_name, &file_stat) == -1) {
            perror("stat");
            continue;
        }

        // 4. Print details
        print_permissions(file_stat.st_mode);
        printf(" %-20s %-10ld %s", 
               entry->d_name, 
               file_stat.st_size, 
               ctime(&file_stat.st_mtime));
    }

    // Close the directory
    closedir(dir);
    return 0;
}
