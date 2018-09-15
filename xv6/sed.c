#include "types.h"
#include "stat.h"
#include "user.h"

char buf[512];
char res[10000];
int line[100];

void
wc(int fd, char *name)
{
  int i, n;
  int w = 0;
  int l = 0;
  int res_c = 0;
  int line_c = 0;
  //int start = 0; int end; int flg = 0;

  while((n = read(fd, buf, sizeof(buf))) > 0){

    for(i=0; i<n; i++){
            if (buf[i] == '\n'){
                l++;
            }

            if (buf[i]=='t' && buf[i+1]=='h' && buf[i+2]=='e'){
                buf[i]='x';buf[i+1]='y';buf[i+2]='z';

                if (line_c==0){
                    line[line_c] = l;
                    line_c++;
                }
                else if(l!=line[line_c-1]){
                    line[line_c] = l;
                    line_c++;
                }
                w++;
            }
            res[res_c] = buf[i];
            res_c++;
        }

    }

    //int k;
    //for(k=0; k<9;k++){
    //    printf(1,"line#:%d,",line[k]);
    //}

    line_c = 0;
    l=0;
    int j=0;
    int start = 0; int end=0;

    while(j<10000){
        if(res[j]=='\n'){
            if(l>0){
                start = end +1;
                end = j;
            }
            else{
                end = j;
            }

            if(line[line_c] == l){
                    //printf(1,"line:%d\n",l);
                    int s;
                    for (s=start;s<end+1;s++){
                        printf(1,"%c",res[s]);
                    }
                    j=end;

                line_c++;
            }
            l++;
        }
        j++;
    }


  if(n < 0){
    printf(1, "wc: read error\n");
    exit();
  }
  printf(1,"%d\n",w);
}


int main(int argc, char *argv[])
{
  int fd, i;

  if(argc <= 1){
    wc(0, "");
    exit();
  }

  for(i = 1; i < argc; i++){
    if((fd = open(argv[i], 0)) < 0){
      printf(1, "wc: cannot open %s\n", argv[i]);
      exit();
    }
    //printf(1,"fd: %d\n",fd);
    wc(fd, argv[i]);
    close(fd);
  }
  exit();
}
