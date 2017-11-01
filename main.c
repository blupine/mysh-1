#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
int main()
{
	char *path = getenv("HOME");
	char *inp = "ls";
	char *full_path;
	printf("%s\n", path);
	char *parsed_path = strtok(path, ":");
	while(parsed_path != NULL)
	{
//		char * dir = malloc(strlen(parsed_path) + strlen(inp)+1);
//		strcpy(dir, parsed_path);
//		strcat(dir, "/");
//		strcat(dir, inp);
//		if(!access(dir, X_OK))
//		{
//			full_path = malloc(strlen(dir));
//			strcpy(full_path, dir);
//			break;
//		}
//		printf("%s\n", dir);
		printf("%s\n", parsed_path);
		parsed_path = strtok(NULL, ":"); 
	}
	printf("\n\n%s\n", full_path);
}
