
#include <stdio.h>
#include <dirent.h>
#include <string.h>

void	list_dir(char *dirpath)
{
	
	printf("%s:\n",dirpath);

	DIR *dir = opendir(dirpath);

	if (dir ==NULL)
	{
		printf("파일을 열수없습니다");
		return ;
	}
	
	struct dirent *entry;

	while((entry = readdir(dir))!=NULL)
	{
		if (entry->d_name[0] == '.')
			continue;
		printf("%s\n",entry->d_name);
	}

	rewinddir(dir);

	while((entry = readdir(dir))!=NULL)
	{
		if(entry->d_name[0] == '.')
			continue;
		if ( entry->d_type == DT_DIR)
		{
			printf("\n");
			char full[1000];
			snprintf(full,sizeof(full),"%s/%s",dirpath,entry->d_name);
			list_dir(full);
		}
	}



	closedir(dir);

}

int	main(void)
{
	list_dir(".");
	return (0);
}
