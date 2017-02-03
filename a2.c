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
char *dname;
char *bname;

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

int initialize()
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
	cwd = root;

	return 0;
}

NODE* getChildren(char *path, NODE* parent)
{
	NODE* temp = parent->childPtr;

	while (temp != NULL)
		temp = temp->siblingPtr;

	return temp;
}

int mkdir(char *pathname)
{
  printf("Creating directory %s...\n", pathname);

  NODE *cwdNode = cwd;
  NODE *tempNode;
  char *tempStr;

  strcpy(tempStr, pathname);
  strcpy(dname, dirname(tempStr)); // gives path up to the final '/'

  strcpy(tempStr, pathname);
  strcpy(bname, basename(tempStr)); // gives component after the final '/'

  cd(&dname[0]); // go to the first directory in the path
  tempNode = getChildren(bname, cwd);

  tempNode = cwd->childPtr;

  while (tempNode->siblingPtr != NULL)
  	tempNode = tempNode->siblingPtr;

  tempNode->siblingPtr = malloc(sizeof(NODE)); // create a new NODE for new directory

  tempNode->siblingPtr->parentPtr = cwd;
  tempNode->siblingPtr->siblingPtr = NULL;
  tempNode->siblingPtr->childPtr = NULL;
  tempNode->siblingPtr->type = "D";

  strcpy(tempNode->siblingPtr->name, bname);

  cwd = cwdNode;

  printf("Directory %s created\n", pathname);

  return 0;
}

int rmdir(char *pathname)
{
  printf("Removing directory %s...\n", pathname);

  NODE *cwdNode = cwd;
  NODE *tempNode;
  char *tempStr;

  strcpy(tempStr, pathname);
  strcpy(dname, dirname(tempStr)); // gives path up to the final '/'

  strcpy(tempStr, pathname);
  strcpy(bname, basename(tempStr)); // gives component after the final '/'

  cd(&dname[0]); // go to the first directory in the path
  tempNode = getChildren(bname, cwd);

  if (tempNode->parentPtr->childPtr == tempNode)
  {
  	if (tempNode->siblingPtr == NULL)
  		tempNode->parentPtr->childPtr = NULL;
  	else
  		tempNode->parentPtr->childPtr = tempNode->siblingPtr;
  }

  else
  {
  	NODE *ttempNode = tempNode->parentPtr->childPtr;

  	while (ttempNode->siblingPtr != tempNode)
  		ttempNode = ttempNode->siblingPtr;

  	ttempNode->siblingPtr = tempNode->siblingPtr;
  }

  free(tempNode); // deallocate memory

  cwd = cwdNode;

  printf("Directory %s removed\n", pathname);

  return 0;
}

int ls()
{
	printf("Listing file contents...\n");

	NODE *cwdNode = cwd; // save contents of cwd

	NODE *tempNode = cwd->childPtr;

	while (tempNode)
	{
		printf("| Name: %s, Type: %c | ", tempNode->name, tempNode->type);
		tempNode = tempNode->siblingPtr;
	}

	cwd = cwdNode;

	printf("File contents listed\n");

  return 0;
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

		NODE *tempNode = cwd;

		char *pathItem;
		strcpy(pathItem, pathname);
		char *pathList;
		pathList = strtok(pathItem, "/");

		while (pathList != NULL && tempNode != NULL)
		{
			tempNode = getChildren(pathname, tempNode);
			pathList = strtok(NULL, "/");
		}

		cwd = tempNode;

		return 0;
	}

	printf("Directory changed\n");

  return 0;
}

int pwdRec(NODE *tempNode)
{
	if (tempNode != root) // reaching the root is the base case
	{
		pwdRec(tempNode->parentPtr);  // recursively call for the parent
		printf("/%s", tempNode->name);
	}
}

int pwd() // a pathname is absolute if it begins with /, indicating it starts from the root
{         // otherwise, it is relative to the CWD
	printf("Printing pathname...\n");

	NODE *tempNode;

	if (cwd != root)
	{
		tempNode = cwd;\
		pwdRec(tempNode);
	}
	else
		printf("/");

	printf("\nPathname printed\n");

  return 0;
}

int creat(char *pathname)
{
	printf("Creating file %s...\n", pathname);

	NODE *cwdNode = cwd;
	NODE *tempNode;
	char *tempStr;

	strcpy(tempStr, pathname);
	strcpy(dname, dirname(tempStr)); // gives path up to the final '/'

	strcpy(tempStr, pathname);
	strcpy(bname, basename(tempStr)); // gives component after the final '/'

	cd(&dname[0]); // go to the first directory in the path
	tempNode = getChildren(bname, cwd);

	tempNode = cwd->childPtr;

	while (tempNode->siblingPtr != NULL)
	  tempNode = tempNode->siblingPtr;

	tempNode->siblingPtr = malloc(sizeof(NODE)); // create a new NODE for new directory

	tempNode->siblingPtr->parentPtr = cwd;
	tempNode->siblingPtr->siblingPtr = NULL;
	tempNode->siblingPtr->childPtr = NULL;
	tempNode->siblingPtr->type = "F";

	strcpy(tempNode->siblingPtr->name, bname);

	cwd = cwdNode;

	printf("File %s created\n", pathname);

  return 0;
}

int rm(char *pathname)
{
	printf("Removing file %s...\n", pathname);

	NODE *cwdNode = cwd;
	NODE *tempNode;
	char *tempStr;

	strcpy(tempStr, pathname);
  strcpy(dname, dirname(tempStr)); // gives path up to the final '/'

	strcpy(tempStr, pathname);
	strcpy(bname, basename(tempStr)); // gives component after the final '/'

	cd(&dname[0]); // go to the first directory in the path
	tempNode = getChildren(bname, cwd);

	if (tempNode->parentPtr->childPtr == tempNode)
	{
	  if (tempNode->siblingPtr == NULL)
	  	tempNode->parentPtr->childPtr = NULL;
	  else
	  	tempNode->parentPtr->childPtr = tempNode->siblingPtr;
	}

	else
	{
	  NODE *ttempNode = tempNode->parentPtr->childPtr;

	  while (ttempNode->siblingPtr != tempNode)
	  ttempNode = ttempNode->siblingPtr;

	  ttempNode->siblingPtr = tempNode->siblingPtr;
	}

	free(tempNode); // deallocate memory

	cwd = cwdNode;

	printf("File %s removed\n", pathname);

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

int quit()
{
  // *** TODO : add code to save the file system tree ***
	//printf("Saving tree...\n");
  save();
  printf("Quitting program...\n");
  exit(0);

  return 0;
}

int menu() // DONE
{
  printf("*** COMMAND LIST ***\n mkdir | rmdir | ls | cd | pwd | creat | rm | quit | help | ? | menu | reload | save");

  return 0;
}

int main()
{
	initialize(); // initialize "/" node of the file system tree
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
