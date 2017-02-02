#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>

struct NODE {
  char name[64];
  char type; // 'D' or 'F' for directory and file
  struct NODE *childPtr, *siblingPtr, *parentPtr;
} NODE;

struct NODE *root;
struct NODE *cwd;
char line[128];
char command[16], pathname[64];
//char dirname[64], basename[64]; // giving me error due to libgen

char *cmd[] = {'mkdir', 'rmdir', 'ls', 'cd', 'pwd', 'creat', 'rm', 'quit', 'help', '?', 'menu', 'reload', 'save', 0};

int findCmd(char *command)
{
  int i = 0;
  while(cmd[i]){
    if (strcmp(command, cmd[i])==0)
	return i;
    i++;
  }
  return -1;
}

int initialize()
{
  printf("Initializing root...\n");
  
  //strcpy(root.name, "/");
  //strcpy(root.type, "D");
  //root.parentPtr = root;
  
  printf("Root successfully initialized\n");
  return 0;
}

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

int cd(char *pathname)
{
	printf("Changing directory...\n");



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
	char *command;
	char *pathname;
	int hasPathname = 0;
  initialize(); // initialize "/" node of the file system tree
  printf("Type 'help' or '?' for help\n");
  while(1){
    printf("Input a command: ");
    gets(line);
    //command = strtok(line, " ");
    //pathname = strtok(NULL, " ");
    //scanf("%s %s", command, pathname);
    //scanf("%s", command);
    //printf("%s\n", command);

    if (strchr(line, " ") != NULL)
    	hasPathname = 1;


    if (hasPathname == 1)
    {
    	command = strtok(line, " ");
    	pathname = strtok(NULL, " ");
    	printf("%s\n%s\n", command, pathname);
    }
    else
    {
    	scanf("%s", command);
    	printf("%s\n", command);
    }
    /* if (scanf("%s", pathname) != NULL) *** instead of this maybe do some if's where you only take in pathname if command is a command that needs a pathname ***
      {
	//scanf("%s", pathname);
	printf("%s", pathname);
	}*/
    
    /*int ID = findCmd(command);
    printf("%d", ID);
    
     switch(ID){
    case 0 : mkdir(); break;
    case 1 : rmdir(); break;
    case 2 : ls(); break;
    case 3 : cd(); break;
    case 4 : pwd(); break;
    case 5 : creat(); break;
    case 6 : rm(); break;
    case 7 : quit(); break;
    case 8 : menu(); break;
    case 9 : menu(); break;
    case 10 : menu(); break;
    case 11 : reload(); break;
    case 12 : save(); break;
    }*/

    // removeChar(command, " "); // might need to removeChar for pathname as well *** no need for this actually ***
    // printf("%s", command);
    if (strcmp(command, "mkdir")==0)
      mkdir(pathname);
    else if (strcmp(command, "rmdir")==0)
      rmdir(pathname);
    else if (strcmp(command, "ls")==0)
      ls();
    else if (strcmp(command, "cd")==0)
      cd(pathname);
    else if (strcmp(command, "pwd")==0)
      pwd();
    else if (strcmp(command, "creat")==0)
      creat(pathname);
    else if (strcmp(command, "rm")==0)
      rm(pathname);
    else if (strcmp(command, "quit")==0)
      quit();
    else if (strcmp(command, "help")==0)
      menu();
    else if (strcmp(command, "?")==0)
      menu();
    else if (strcmp(command, "menu")==0)
      menu();
    else if (strcmp(command, "reload")==0)
      reload();
    else
      save();   
    }
  
  return 0;
}
