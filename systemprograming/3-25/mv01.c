#include <stdio.h>
#include <sys/stat.h>
#include <string.h>

int	main(int argc, char *argv[])
{
	
	struct stat info;
	struct stat dest_info;
	char *a;
	
	if (argc != 3)
	{
		printf("input error\n");
		return (1);
	}

		
	if( stat(argv[1],&info) != -1)
	{
		if(S_ISDIR(info.st_mode) == 0)
		{
			if( stat(argv[2],&dest_info)!=-1)
			{
				if(S_ISDIR(dest_info.st_mode))
				{
					strcat(argv[2],"/");
					strcat(argv[2],argv[1]);
					rename(argv[1],argv[2]);
				}
			}
			
			rename(argv[1],argv[2]);
			
		}
	}
	
	return (0);
}


