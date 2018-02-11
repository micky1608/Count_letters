/*
 * Created by TEAUDORS Mickael on 11/02/2018
 * This program allows to count the occurences of each letter in a text.
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

/**
 * Exit the program after an error
 * @param message : the error message to be printed before exiting the program
 */
void erreur( char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

/**
 * args[1] : name of the file which contains the text
 * @return
 */
int main(int argc , char *args[]) {

    /* ********** Verification of the arguments ********** */
    if(argc != 2)
        erreur("Arguments are not corrects\n1 : Name of the file which contains the text");

    /* ********** Variables ********** */

    int fd , *count;
    char *text;
    struct stat file_info;

    count = calloc(26 , sizeof(int));

    /* ********** Files opening ********** */

    fd = open(args[1] , O_RDONLY);

    if(fd == -1)
        erreur("Error during file opening");

    /* ********** Get size of the file and memory allocation for the text ********** */

    if (fstat(fd , &file_info) != 0)
        erreur("Error fstat");

    text = (char*)malloc(sizeof(char)*(file_info.st_size + 1));

    /* ********** Text recovery ********** */

    for(int i=0 ; i<file_info.st_size ; i++)
        read(fd , &text[i] , 1);

    text[file_info.st_size] = '\0';
    

    /* ********** Count the letters ********** */

    char actual_letter;

    for(int i=0 ; i<file_info.st_size ; i++) {
        actual_letter = text[i];
        if(actual_letter >= 'A' && actual_letter <= 'Z')
            count[actual_letter - 'A']++;
        else if(actual_letter >= 'a' && actual_letter <= 'z')
            count[actual_letter - 'a']++;
    }

    /* ********** Display results ********** */

    for(int i=0 ; i<26 ; i++)
        printf("%c : %d\t" , 'A' + i , count[i]);

    /* ********** Release of resources ********** */

    free(text);
    free(count);
    close(fd);

    return EXIT_SUCCESS;
}