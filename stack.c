#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int bof(char *str)
{
    char buffer[12];
    
    /* Print the starting address of buffer */
    printf("The starting address of buffer is %p\n", buffer);
    
    /* Safely copy data into buffer using strncpy to avoid overflow */
    strncpy(buffer, str, sizeof(buffer) - 1);
    
    /* Ensure null termination of the string */
    buffer[sizeof(buffer) - 1] = '\0';
    
    /* Print the frame pointer address */
    printf("Frame Pointer Address is: %p\n", __builtin_frame_address(0));

    /* Use this address to find the return address */
    return 1;
}

int main(int argc, char **argv)
{
    char str[517];
    FILE *badfile;

    /* Open the file and check if it opened successfully */
    badfile = fopen("badfile", "r");
    if (badfile == NULL) {
        perror("Error opening file");
        return 1;
    }

    /* Read the contents of the file into str */
    fread(str, sizeof(char), 517, badfile);
    
    /* Close the file after reading */
    fclose(badfile);

    /* Call the bof function to test for the overflow */
    bof(str);

    printf("Returned Properly\n");

    return 1;
}
