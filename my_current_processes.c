#include <dirent.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    DIR *dir;
    FILE *fp;
    fp = fopen("output1.txt", "w");
    struct dirent *entry;

    if ((dir = opendir("/proc")) == NULL)
        perror("operation error");
    printf("PID\tCOMMAND\n");
    while ((entry = readdir(dir)))
    {

        if (strlen(entry->d_name) == strspn(entry->d_name, "0123456789"))
        {

            FILE *file;
            FILE *file1;
            char buffer[1024] = {0};
            char buffer1[1024]={0};

            sprintf(buffer, "/proc/%s/stat", entry->d_name);
            file = fopen(buffer, "r");

            if (!file)
                break;
            if (!file1)
                break;
            fgets(buffer, sizeof(buffer), file);

            char temp[10]={0};
            for (int i = 0; i < sizeof(buffer); i++)
            {
                if (buffer[i] == ' ')
                    break;
                temp[i]=buffer[i];
                fputc(buffer[i], fp);
            }
            printf("%s",temp);
            sprintf(buffer1, "/proc/%s/cmdline", temp);
            file1=fopen(buffer1,"r");
            fgets(buffer1, sizeof(buffer1), file1);
            printf("\t%s\n", buffer1);

            fputs("\n", fp);
            if (file)
                fclose(file);
            if (file1)
                fclose(file1);
        }
    }

    if (dir)
        closedir(dir);
    fclose(fp);
    return 0;
}