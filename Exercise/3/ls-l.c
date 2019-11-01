#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<sys/stat.h>
#include<string.h>
#include<stdlib.h>
#include<grp.h>
#include<pwd.h>

void list(char[]);
void getstat(char *, char *);
void show_file_info(char *, struct stat *);
void getfilepermissions(int, char[]);
char *uid_to_name(uid_t);
char *gid_to_name(gid_t);

int main(int ac, char *av[])
{
	if (ac == 1)
		list(".");
	else
		while(--ac){
			printf("%s:\n", * ++av);
			list(*av);
		}
	return 0;
}



void list(char dirname[])
/*
 * listing files in directory called dirname
 * */
{
	int count;
	DIR	*dir_ptr;	// the directory
	struct dirent	*direntp;
dir_ptr = opendir(dirname);	// each entry
	while((direntp=readdir(dir_ptr)) != NULL){
		count = count +1;
}
printf("\n");
printf("Total Number of Files are: %d", count);
printf("\n");
	if((dir_ptr = opendir(dirname)) == NULL)
		fprintf(stderr, "ls: cannot open %s\n", dirname);
	else
	{
		while((direntp=readdir(dir_ptr)) != NULL){
			//count = count + 1;			
			char *p = (char *)malloc(strlen(dirname) + strlen(direntp->d_name) + 2);
			if(p){
				strcpy(p, dirname);
				strcat(p, "/");
				strcat(p, direntp->d_name);
				getstat(p, direntp->d_name);
				free(p);
			}
			else
			{
				printf("Allocate memory failed!");
				exit(1);
			}
		}		
		closedir(dir_ptr);
		
	}
}

void getstat(char *absoluteFileName, char *filename)
{
	struct stat info;
	if(stat(absoluteFileName, &info) == -1)		// cannot stat
		perror(filename);				// say why
	else
		show_file_info(filename, &info);
}

void show_file_info(char *filename, struct stat *info_p)
/*
 * display the info about filename. The info is stored in struct at *info_p
 * */
{
	char	*uid_to_name(), *ctime(), *gid_to_name(), *filemode();
	void getfilepermissions();
	char modestr[11];

	getfilepermissions(info_p->st_mode, modestr);

	printf("%s",modestr);
	printf("%4d ", (int)info_p->st_nlink);
	printf("%-8s ", uid_to_name(info_p->st_uid));
	printf("%-8s ", gid_to_name(info_p->st_gid));
	printf("%8ld ", (long)info_p->st_size);
	printf("%.12s ", 4+ctime(&info_p->st_mtime));
	printf("%s\n", filename);
}


void getfilepermissions(int mode, char str[])
{
/*
Getting the file permission details using sys/stat.h 
*/
	strcpy(str, "----------");		// default = no perms

	if(S_ISDIR(mode)) str[0] = 'd';		// directory?
	if(S_ISCHR(mode)) str[0] = 'c';		// char devices
	if(S_ISBLK(mode)) str[0] = 'b';		// block device

	if(mode & S_IRUSR) str[1] = 'r';	// 3 bits for user
	if(mode & S_IWUSR) str[2] = 'w';
	if(mode & S_IXUSR) str[3] = 'x';

	if(mode & S_IRGRP) str[4] = 'r';	// 3 bits for group
	if(mode & S_IWGRP) str[5] = 'w';
	if(mode & S_IXGRP) str[6] = 'x';

	if(mode & S_IROTH) str[7] = 'r';	// 3 bits for other
	if(mode & S_IWOTH) str[8] = 'w';
	if(mode & S_IXOTH) str[9] = 'x';

}



char *uid_to_name(uid_t uid)
/*
 * returns pointer to username associated with uid, uses getpw()
 * 
 * */
{
	struct passwd *getpwuid(), *pw_ptr;
	static char numstr[10];

	if((pw_ptr = getpwuid(uid)) == NULL){
		sprintf(numstr, "%d", uid);
		return numstr;
	}
	else
		return pw_ptr->pw_name;
}



char *gid_to_name(gid_t gid)
/*
 * returns pointer to group number gid. used getgrgid(3)
 * 
 * */
{
	struct group *getgrgid(), *grp_ptr;
	static char numstr[10];

	if((grp_ptr = getgrgid(gid)) == NULL){
		sprintf(numstr, "%d", gid);
		return numstr;
	}
	else
		return grp_ptr->gr_name;
}
