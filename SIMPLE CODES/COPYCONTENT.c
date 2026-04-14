#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc, char *argv[]){
        int f1,f2;
        char ch;

        if(argc < 3)
        {
                printf("Usage: %s source destination\n",argv[0]);
                return 1;
        }
        f1 = open(argv[1],O_RDONLY);

                if(f1 < 0)
                {
                        printf("Source file is not find\n");
                }

                f2 = open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644);
                        if(f2 < 0)
                        {
                                printf("Cannot create file\n");
                                return 1;
                        }
                        while(read(f1,&ch,1) > 0)
                        {
                                write(f2,&ch,1);
                        }
                        close(f1);
                        close(f2);
                        printf("Copied successfully");
                        return 0;
}