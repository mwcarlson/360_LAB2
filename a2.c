#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>

typedef struct NODE {
  char *name;
  char type; // 'D' or 'F' for directory and file
  struct NODE *childPtr, *siblingPtr, *parentPtr;
} NODE;

struct NODE *root;
struct NODE *cwd;
char line[128];
char command[16], pathname[64];
char dname[64], bname[64];

char *cmd[] = {"mkdir", "rmdir", "ls", "cd", "pwd", "creat", "rm", "quit", "help", "?", "menu", "reload", "save", "\0"};

int findCmd(char *command)
{
  int i = 0;
  while(cmd[i]!="\0"){
    if (strcmp(command, cmd[i])==0)
    {
    	return i;
    }
    i++;
  }
  return -1;
}

/*int initialize()
{
  printf("Initializing root...\n");

  strcpy(root.name, "/");
  strcpy(root.type, "D");
  root.parentPtr = root;

  printf("Root successfully initialized\n");
  return 0;
}*/

int mkdir(char *pathname)
{
  printf("Creating directory %s...\n", pathname);



  printf("Directory %s created\n", pathname);

  return 0;
}

int rmdir(char *pathname)
{
  printf("Removing directory %s...\n", pathname);



  printf("Directory %s removed\n", pathname);

  return 0;
}

int ls()
{
	printf("Listing file contents...\n");



	printf("File contents listed\n");

  return 0;
}

NODE* getChildren(char *pathname, NODE* parent)
{
	NODE* temp = parent->childPtr;

	while (temp != NULL)
		temp = temp->siblingPtr;

	return temp;
}

int cd(char *pathname)
{
	printf("Changing directory...\n");

	if (pathname[0] == "\0")
	{
		cwd = root;
		return 1;
	}

	else if (pathname[0] == '.' && pathname[1] == '.')
	{
		cwd = cwd->parentPtr;
		return 1;
	}

	else
	{
		if (pathname[0] == "/")
		{
			cwd = root;
		}

	}

	printf("Directory changed\n");

  return 0;
}

int pwd() // a pathname is absolute if it begins with /, indicating it starts from the root
{         // otherwise, it is relative to the CWD
	printf("Printing pathname...\n");



	printf("Pathname printed\n");

  return 0;
}

int creat(char *pathname)
{
	printf("Creating file %s...\n", pathname);



	printf("File %s created\n", pathname);

  return 0;
}

int rm(char *pathname)
{
	printf("Removing file %s...\n", pathname);



	printf("File %s removed\n", pathname);

  return 0;
}

int quit()
{
  // *** TODO : add code to save the file system tree ***
  save();
  printf("Quitting program...\n");
  exit(0);

  return 0;
}

int reload()
{
	printf("Reloading tree from file...\n");



	printf("File reloaded\n");
  return 0;
}

int save()
{
  printf("Saving tree...\n");



  printf("Tree saved\n");
  return 0;
}

int menu() // DONE
{
  printf("*** COMMAND LIST ***\n mkdir | rmdir | ls | cd | pwd | creat | rm | quit | help | ? | menu | reload | save");

  return 0;
}

int removeChar(char *str, char c)
{
  char *pr = str, *pw = str;
  while (*pr) {
    *pw = *pr++;
    pw += (*pw != c);
  }
  *pw = "\0";

  return 0;
}

int main()
{
	root = malloc(sizeof(NODE));
	cwd = root;

	printf("Initializing root...\n");
	root->name = '/';
	root->type = 'D';
	root->childPtr = NULL;
	root->siblingPtr = root;
	root->parentPtr = root;
	printf("Root initialized\n");

  //initialize(); // initialize "/" node of the file system tree
  printf("Type 'help' or '?' for help\n");
  while(1){
    printf("Input a command: ");
    fgets(line, 128, stdin);

    sscanf(line, "%s %s", command, pathname);
    printf("%s %s\n", command, pathname);

    int ID = findCmd(command);
    //printf("%d", ID);

     switch(ID){
    case 0 : mkdir(pathname); break;
    case 1 : rmdir(pathname); break;
    case 2 : ls(pathname); break;
    case 3 : cd(pathname); break;
    case 4 : pwd(); break;
    case 5 : creat(pathname); break;
    case 6 : rm(pathname); break;
    case 7 : quit(); break;
    case 8 : menu(); break;
    case 9 : menu(); break;
    case 10 : menu(); break;
    case 11 : reload(); break;
    case 12 : save(); break;
    }

  }

  return 0;
}
