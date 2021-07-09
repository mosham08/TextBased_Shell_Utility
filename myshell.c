/*  Some example code and prototype - 
    contains many, many problems: should check for return values 
    (especially system calls), handle errors, not use fixed paths,
    handle parameters, put comments, watch out for buffer overflows,
    security problems, use environment variables, etc.
 */
/*
 * Mohammad Abdellatif
 * 1001534657
 * CSE 3320-001
 * Assignment 1
 */
#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

struct stat stat1;

//struct for files to sort with
struct Files
        {
            char name[30];
            long int fileSize;
            long int fileTime;
        };

void swapFiles(struct Files *xp, struct Files *yp)
{
    struct Files temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//sorts files by size
void selectionSortFiles(struct Files files[], int n)
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++) {

        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (files[j].fileSize < files[min_idx].fileSize)
                min_idx = j;

        swapFiles(&files[min_idx], &files[i]);
    }
}

//sorts files by date
void selectionSortFilesDate(struct Files files[], int n)
{
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++) {

        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (files[j].fileTime < files[min_idx].fileTime)
                min_idx = j;

        swapFiles(&files[min_idx], &files[i]);
    }
}


int main(void) {
    DIR * d;
    struct dirent * de;
    int c, k, h;
    char s[256], cmd[256];
    time_t t;

    while (1) {

      t = time( NULL );
      printf("\n\n-----------------------------------------------\n" );
      printf( "\n\nTime: %s\n", ctime( &t ));


      getcwd(s, 200);
      printf( "\nCurrent Directory: %s \n", s);


      int nD = 0;
      //counting number directories
      d = opendir( "." );
      if (d == NULL)  // checking for errors
    {
        printf("Could not open current directory" );
        return 0;
    }
      while ((de = readdir(d))){
          if ((de->d_type) & DT_DIR) {
             nD++; //counting number of directories
             }
      }
      char *directory[nD];
      closedir( d );

      //counting number of files
      d = opendir( "." );
      if (d == NULL)  // checking for errors
    {
        printf("Could not open current directory" );
        return 0;
    }
      int nF = 0;
      while ((de = readdir(d))){
          if (((de->d_type) & DT_REG))
             nF++;//counting number of files
      }
      closedir( d );
      char *arr[nF]; //array of file names
      int fileSize[nF]; //array of the sizes
      int fileTime[nF]; //array of the times
      struct Files fileArray[nF]; //array of everything

      // creating arrays for directories and files
      d = opendir( "." );
      if (d == NULL)  // checking for errors
    {
        printf("Could not open current directory" );
        return 0;
    }
      c = 0;
      int m = 0;
      while ((de = readdir(d))){
          if ((de->d_type) & DT_DIR) {
             //printf( " ( %d Directory:  %s ) \n", c++, de->d_name);
             directory[m] = (de->d_name);
             m++;
             }
      }
      closedir( d );

      d = opendir( "." );
      if (d == NULL)  // checking for errors
    {
        printf("Could not open current directory" );
        return 0;
    }
      c = 0;
      int i = 0;
      while ((de = readdir(d))){
          stat(de->d_name, &stat1);
             arr[i] = (de->d_name);
             fileSize[i] = (stat1.st_size);
             fileTime[i] = (stat1.st_ctime);
             i++;
      }
      closedir( d );


      printf("Operations:\n");
      printf("\n\tD Display Directories\n\tF Display Files\n\tE Edit File\n\tR Run A Program\n\tC Change Directory\n\tS Sort Directory listing\n"
             "\tQ Quit\n\n");

      c = 0;
      printf("\n\nInsert a command from the operations\n");
      c = getchar( ); getchar( );
      switch (c) {


        case 'Q': exit(0); /* quit */


        case 'E': printf( "Edit what?:" );//Edits a program
                  scanf( "%s", s );
                  strcpy( cmd, "pico ");
                  strcat( cmd, s );
                  system( cmd );
                  break;


        case 'R': printf( "Run what?:" );//Runs a program
                  scanf( "%s", cmd );
                  system( cmd );
                  break;


        case 'C': printf( "Change Directory To?:" );//Changes Directories
                  scanf( "%s", cmd );
                  chdir( cmd );   
                  break;


        case 'S': printf( "Sort Files by Size or Date? (Input S or D):" );//Sorts files in current directory by size or date
                  k = getchar(); getchar();

                  d = opendir( "." );
      if (d == NULL)  // checking for errors
    {
        printf("Could not open current directory" );
        return 0;
    }
      int i = 0;
      while ((de = readdir(d))){
          stat(de->d_name, &stat1);
          // placing information into struct
          strcpy(fileArray[i].name, de->d_name);
          fileArray[i].fileSize = stat1.st_size;
          fileArray[i].fileTime = stat1.st_ctime;
          i++;
      }
      closedir( d );
      //////////////////////////////////////////////
                  int n1 = sizeof(fileArray)/sizeof(fileArray[0]);
                  if (k == 'S')
                      {
                        selectionSortFiles(fileArray, n1);
                        for(i = 0; i < n1; i++){
                            printf("\nFile: %s \tSize: %ld Bytes\tTime: %ld",fileArray[i].name, fileArray[i].fileSize, fileArray[i].fileTime);
                          }
                      }
                  if (k == 'D')
                      {
                        selectionSortFilesDate(fileArray, n1);
                        for(i = 0; i < n1; i++){
                            printf("\nFile: %s \tSize: %ld Bytes\tTime: %ld",fileArray[i].name, fileArray[i].fileSize, fileArray[i].fileTime);
                          }
                      }
                  break;


        case 'D': printf("\nDisplaying Directory Files:\n");
            for (i = 0; i < nD; ++i)
            {
                printf("\nDirectory %d : %s", i, directory[i]);
            }
                    break;


        case 'F': printf("Files:\n\n");
                    int h = 0; // counter
                    while (arr[h] != NULL){
                        printf("\nFile %d : %s \tSize: %d bytes \tTime: %d", h, arr[h], fileSize[h], fileTime[h]);
                        h++;
                        if (h == 11){
                            printf("\n\nEnd of list, type N to start over or type Q to quit: ");
                            k = getchar( ); getchar ( );
                            if (k == 'N')
                                h = 0;
                            else
                                break;
                        }

                        if ((h % 5) == 0)
                            {
                                printf("\n\nType N for next or P for prevous: ");
                                k = getchar( ); getchar();
                                if (k == 'P')
                                    h = h-10;
                            }
                    }
                    break;
      printf( "\n-----------------------------------------\n" );
      }
       
    }
}
