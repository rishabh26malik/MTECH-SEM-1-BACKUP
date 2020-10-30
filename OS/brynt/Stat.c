#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    struct stat sb;
char path[100]="/home/rishabh/F/MTECH/OS/brynt";
   /*if (argc != 2) {
        fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
        exit(EXIT_FAILURE);
    }*/

   if (stat(path, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    


   printf("File type:                ");

   switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:  printf("block device\n");            break;
    case S_IFCHR:  printf("character device\n");        break;
    case S_IFDIR:  printf("directory\n");               break;
    case S_IFIFO:  printf("FIFO/pipe\n");               break;
    case S_IFLNK:  printf("symlink\n");                 break;
    case S_IFREG:  printf("regular file\n");            break;
    case S_IFSOCK: printf("socket\n");                  break;
    default:       printf("unknown?\n");                break;
    }

   printf("I-node number:            %ld\n", (long) sb.st_ino);

   printf("Mode:                     %lo (octal)\n",
            (unsigned long) sb.st_mode);

   printf("Link count:               %ld\n", (long) sb.st_nlink);
    printf("Ownership:                UID=%ld   GID=%ld\n",
            (long) sb.st_uid, (long) sb.st_gid);

   printf("Preferred I/O block size: %ld bytes\n",
            (long) sb.st_blksize);
    printf("File size:                %lld bytes\n",
            (long long) sb.st_size);
    printf("Blocks allocated:         %lld\n",
            (long long) sb.st_blocks);

   printf("Last status change:       %s", ctime(&sb.st_ctime));
    printf("Last file access:         %s", ctime(&sb.st_atime));
    printf("Last file modification:   %s", ctime(&sb.st_mtime));

  printf((sb.st_mode & S_IRUSR)? "r":"-");
  printf((sb.st_mode & S_IWUSR)? "w":"-");
  printf((sb.st_mode & S_IXUSR)? "x":"-");
  printf(" ");
  printf((sb.st_mode & S_IRGRP)? "r":"-");
  printf((sb.st_mode & S_IWGRP)? "w":"-");
  printf((sb.st_mode & S_IXGRP)? "x":"-");
  printf(" ");
  printf((sb.st_mode & S_IROTH)? "r":"-");
  printf((sb.st_mode & S_IWOTH)? "w":"-");
  printf((sb.st_mode & S_IXOTH)? "x":"-");
  printf("\n");

   exit(EXIT_SUCCESS);
}