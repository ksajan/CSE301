#include <unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdio.h>
#include<fcntl.h>
int main( int argc,char *argv[] )
{
int i,fd1,fd2; // creating variables
char *file1,*file2,buf[2]; // variables
file1=argv[1]; // taking argument
file2=argv[2]; // taking argument
printf("file1=%s file2=%s",file1,file2); // printing files names
fd1=open(file1,O_RDONLY,0777);  // giving file permissions
fd2=creat(file2,0777); // cresting the file if doesn't exist
while(i=read(fd1,buf,1)>0) // reading the file and storing it in buffer of size and then copying it the other file using write system function.
write(fd2,buf,1);
remove(file1);
close(fd1);
close(fd2);
}
