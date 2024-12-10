#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
//this createFile Function will create file in the disk.
void createFile(char *filename)
{
    int file = open(filename, O_WRONLY | O_CREAT | O_EXCL, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (file == -1)
    {
        perror("Error creating file");
    }
    else
    {
        printf("File '%s' created successfully.\n", filename);
        close(file);
    }
}
//this writeFile Function will Write in the file.
void writeFile(char *filename)
{
    int file = open(filename, O_WRONLY | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    char content[100];

    if (file == -1)
    {
        perror("Error opening file for writing");
    }
    else
    {
        printf("Enter content to write (max 100 characters):\n");
        scanf(" %[^\n]", content);
        write(file, content, strlen(content));
        printf("Content written to '%s' successfully.\n", filename);
        close(file);
    }
}
//this readFile Function will Read from the file.
void readFile(char *filename)
{
    int file = open(filename, O_RDONLY);
    char buffer[1024];
    ssize_t bytesRead;

    if (file == -1)
    {
        perror("Error opening file for reading");
    }
    else
    {
        printf("File Content of '%s':\n", filename);
        while ((bytesRead = read(file, buffer, sizeof(buffer))) > 0)
        {
            write(STDOUT_FILENO, buffer, bytesRead);
            printf("\n");
        }
        close(file);
    }
}
//this fileDescription Function will Show the details of the file.
void fileDescription(char *filename)
{
    struct stat fileStat;

    if (stat(filename, &fileStat) == 0)
    {
        printf("File Description for '%s':\n", filename);
        printf("Size: %ld bytes\n", fileStat.st_size);
        printf("Permissions: %o\n", fileStat.st_mode & 0777);
    }
    else
    {
        perror("Error getting file description");
    }
}
//this deleteFile Function will Delete the file.
void deleteFile(char *filename)
{
    if (unlink(filename) == 0)
    {
        printf("File '%s' deleted successfully.\n", filename);
    }
    else
    {
        perror("Error deleting file");
    }
}

int main()
{
    char choice;
    char filename[100];
    //here is our welcome note
    printf("---Welcome To OS File Manager---\n");
    printf("Build By return to_sleep;\n");
    printf("Project Of CSE323.11\n");
    printf("Group Members\n1.Tamim Ahmed Rijan\n2.Saber Hossain");
    printf("\nPress Any Key to Continue to The Project\n");
    getchar();

    while (1)
    {
        // here is the File Manager Menu.
        printf("\nFile Manager Menu:\n");
        printf("1. Create File\n");
        printf("2. Write to File\n");
        printf("3. Read File\n");
        printf("4. File Description\n");
        printf("5. Delete File\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice)
        {
        case '1':
            printf("Enter filename: ");
            scanf("%s", filename);
            createFile(filename);
            break;
        case '2':
            printf("Enter filename to write: ");
            scanf("%s", filename);
            writeFile(filename);
            break;
        case '3':
            printf("Enter filename to read: ");
            scanf("%s", filename);
            readFile(filename);
            break;
        case '4':
            printf("Enter filename for description: ");
            scanf("%s", filename);
            fileDescription(filename);
            break;
        case '5':
            printf("Enter filename: ");
            scanf("%s", filename);
            deleteFile(filename);
            break;
        case '6':
            printf("Exiting program.\n");
            exit(0);
        default:
            printf("Invalid choice. Please enter a valid option.\n");
        }
    }
}

