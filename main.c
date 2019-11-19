#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){
  if (argc == 1){
    printf("Please enter a directory after the program name\n");
    return 0;
  }
  DIR *dr = opendir(argv[1]);
  if (errno){
    printf("Error %d: %s\n", errno, strerror(errno));
    return 0;
  }
  printf("Listing all files:\n");
  struct dirent *d;
  int size = 0;
  printf("Directories:\n");
  while (d = readdir(dr)){
    if (d->d_type == 4){
      printf("%s\n", d->d_name);
      struct stat s;
      stat(d->d_name, &s);
      if (errno){
        printf("Error %d: %s\n", errno, strerror(errno));
      }
      else{
        printf("%d\n", s.st_size);
        size += s.st_size;
      }
    }
  }
  dr = opendir(argv[1]);
  if (errno){
    printf("Error %d: %s\n", errno, strerror(errno));
    return 0;
  }
  printf("\nRegular files:\n");
  while (d = readdir(dr)){
    if (d->d_type == 8){
      printf("%s\n", d->d_name);
      struct stat s;
      stat(d->d_name, &s);
      if (errno){
        printf("Error %d: %s\n", errno, strerror(errno));
      }
      else{
        printf("%d\n", s.st_size);
        size += s.st_size;
      }
    }
  }
  printf("\nTotal directory size: %d Bytes\n", size);
  closedir(dr);
  return 0;
}
