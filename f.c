#include <stdio.h>
#include <string.h>
#include <libgen.h>
#include <stdlib.h>

struct NODE {
  char name[64];
  char type;
  char *childPtr, *siblingPtr, *parentPtr; // is this how you declare "node pointers"?
} NODE;

//NODE *root, *cwd; *** doesn't recognize type ***
char line[128];
char command[16], pathname[64];
//char dirname[64], basename[64]; // giving me error

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

int mkdir()
{
  printf("mkdir test\n");
  
  return 0;
}

int rmdir()
{
  return 0;
}

int ls()
{
  return 0;
}

int cd()
{
  return 0;
}

int pwd()
{
  return 0;
}

int creat()
{
  return 0;
}

int rm()
{
  return 0;
}

int quit()
{
  // *** TODO : add code to save the file system tree ***
  printf("quit function\n");
  exit(0);
  
  return 0;
}

int reload()
{
  return 0;
}

int save()
{
  printf("save function");
  return 0;
}

int menu()
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
  //initialize(); // initialize "/" node of the file system tree
  printf("Type 'help' or '?' for help\n");
  while(1){
    printf("Input a command: ");
    scanf("%s", command);
    /* if (scanf("%s", pathname) != NULL) *** instead of this maybe do some if's where you only take in pathname if command is a command that needs a pathname ***
      {
	//scanf("%s", pathname);
	printf("%s", pathname);
	}*/
    scanf("%s", pathname);
    printf("%s\n", command);
    printf("%s\n", pathname);
    
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
      mkdir();
    else if (strcmp(command, "rmdir")==0)
      rmdir();
    else if (strcmp(command, "ls")==0)
      ls();
    else if (strcmp(command, "cd")==0)
      cd();
    else if (strcmp(command, "pwd")==0)
      pwd();
    else if (strcmp(command, "creat")==0)
      creat();
    else if (strcmp(command, "rm")==0)
      rm();
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
