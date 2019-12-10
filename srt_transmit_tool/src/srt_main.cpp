#include "tinyxml2.h"
#include<unistd.h>
#include<sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>
#include <csignal>
#include <vector>
#include <string>

using namespace tinyxml2;
using namespace std;

static bool runflag = true;

void signalHandler( int signum )
{
    printf("Interrupt signal %d received.\n",signum);
    if(signum == 2){
        runflag = false;
    }
}

int check_process(const char * command){
    FILE* fp;
	int count;
	char buf[512];   
	char commandbuf[512];   
	
	sprintf(commandbuf, "ps -ef | grep %s | grep -v grep | wc -l",command );
    //printf("commandbuf:%s\n",commandbuf);
	if((fp = popen(commandbuf,"r")) == NULL) {
        printf("check_process failed ! popen failed !\n");
        return -1;
    }

	if( (fgets(buf,sizeof(buf),fp))!= NULL ) { 
		count = atoi(buf);   
		if(count  == 0){
            printf("进程不存在!\n");
            pclose(fp);
            return 0;
        }
		else{
            //printf("进程已找到，有%d个!\n",count);
            pclose(fp);
            return 1;
        }

	}

	pclose(fp);
    return -1;
}

void run_command(std::string commstr){
    if(commstr.length()>512){
        return;
    }
    char command[512] = {0};
    strcpy(command,commstr.c_str());
    for(int i = 0;i < commstr.length();i++){
        if(command[i] == '\\'){
            command[i] = ' ';
        }
    }
    system(command);
    printf("%d has been killed!\n",getpid());
    exit(0);
}

int main(int argc ,char *argv[]){
    if(argc != 3){
        printf("please enter full command ! like this:\n");
        printf("./build/srt_master_tool ./config/config.xml ../srt-live-transmit \n");
        return -1;
    }
    XMLDocument doc;
    XMLElement* root;
    XMLElement* param_list;
    XMLElement* param;
    vector<std::string> command_v;

    char path[512] = {0};
    char toolpath[512] = {0};
    if((strlen(argv[1]) >= 512)  || (strlen(argv[2]) >= 512)){
        printf("config path too long !\n");
        return -1;
    }
    strcpy(path,argv[1]);
    strcpy(toolpath,argv[2]);

    if(0 != doc.LoadFile(path)) { 
        printf("loadFile failed %s! \n",path);
        return -1;
    }

    root=doc.RootElement();
    if(NULL == root){
        printf("get doc.rootelement failed!\n");
        return -1;
    }

    param_list=root->FirstChildElement("param_list");
    param=param_list->FirstChildElement("param");
    while(param != NULL)
    {
        char commbuf[512] = {0};
        char commbuf2[512] = {0};
        char dstip[32] = {0};
        int srcport = atoi(param->Attribute("srcport"));
        int dstport = atoi(param->Attribute("dstport"));
        
        if(strlen(param->Attribute("dstip")) > 16){
            strcpy(dstip,"127.0.0.1");
        }
        else{
            strcpy(dstip,param->Attribute("dstip"));
        }
        
        sprintf(commbuf,"%s srt://:%d udp://%s:%d",toolpath,srcport,dstip,dstport);
        sprintf(commbuf2,"%s\\ srt://:%d\\ udp://%s:%d",toolpath,srcport,dstip,dstport);
        string commstr = commbuf2;
        command_v.push_back(commstr);

        pid_t fpid=fork();

        if ( fpid < 0 ) {
            printf("fork error !\n");
            return -1;
        }
        else if( fpid == 0 ) {
            system(commbuf);
            printf("%d has been killed!\n",getpid());
            exit(0);
        }
        param = param->NextSiblingElement();
    }

    signal(SIGINT, signalHandler);  

    pid_t tmppid;
    while( 1 /*(tmppid = waitpid(-1,NULL,WNOHANG)) >= 0 */){
        sleep(1);
        
        for(int i = 0;i < command_v.size();i++){

            int res = check_process(command_v[i].c_str());
            if(res == 0){
                if(0 == fork()){
                    run_command(command_v[i]);
                }
                
            }
        }
        if(!runflag){
            system("killall -9 srt-live-transmit");
            break;
        }
    }

    printf("-------------------------\n");

    return 0;
}