//
//  DexHacker.cpp
//  
//
//  Created by BunnyBlue on 6/23/15.
//
//

#include <log/log.h>
#include "DexHacker.h"

DexDataCache* dexbuf_wait=NULL;

void DexHacker::writeDex2Encoded(unsigned char *data, size_t length){
   
	char dexbuffer[64]={0};
	char dexbufferNamed[128]={0};
	sprintf(dexbuffer, "classes_%d", length);
	ALOGE("--pacthed--  inject  .dex length %d",length);
#ifdef CODE_DVM
	char bufferProcess[256]={0};

	bufferProcess= getProcessName(bufferProcess);
	strcat(dexbufferNamed,"/sdcard/");
	if (bufferProcess!=NULL) {
	 	strcat(dexbufferNamed,bufferProcess);
		strcat(dexbufferNamed,dexbuffer);
	}else{
		ALOGE("--pacthed-- , FAULT pid not  found\n");
		return;
	}
#else 
	strcat(dexbufferNamed,dexbuffer);
#endif
	strcat(dexbufferNamed,".dex");

	ALOGE("--pacthed-- , %s\n", dexbufferNamed);
	ALOGE("--pacthed--  debug dalvikParse   find dex try write file  ");

	int status = remove(dexbufferNamed);
	if( status == 0 )
	    ALOGE("%s file deleted successfully.\n",dexbufferNamed);
	else
	{
	    ALOGE("Unable to delete the file\n");
	    
	}

	if(dexbuf_wait != NULL){
	     writeDexBufToFile(dexbuf_wait);
	}
	static DexDataCache* dexbuf = new DexDataCache(dexbufferNamed,data,length);
	writeDexBufToFile(dexbuf);
}

void DexHacker::writeDexBufToFile(DexDataCache *dexbuf)
{
	FILE *fp = fopen(dexbuf->DexFileName,"wb");
	 
	if(NULL==fp){
		ALOGE("--pacthed-- , can't create file ! ");
		ALOGE( "%s data %s\n", strerror(errno),dexbuf->data);
		if(dexbuf_wait == NULL)
			dexbuf_wait = dexbuf;
	}else{
		ALOGE("--pacthed--   create file  %s ",dexbuf->DexFileName);
		//int dex_lem_local=length>2048?1024:length;

		//unsigned char *dst=(unsigned char*)malloc(length*2.5);
		//unsigned long dlen=length*2.5;
		//base64_encode(dst, &dlen, dexbuf->data, length);

		//fwrite(dst, dlen, 1, fp);
		fwrite(dexbuf->data, sizeof(unsigned char), dexbuf->length, fp);
		ALOGE("--pacthed--  create file  end ");

		//fflush(fp);
		fclose(fp);
		fp = NULL;
		delete dexbuf;
	}
}

#if 0
void DexHacker::writeEncodedDex2Dex(const char *encodedDex){
	FILE *srcDexFile=fopen(encodedDex,"rb");
	std::string outDexFile(encodedDex);
	outDexFile.append(".read.dex");
	
	
	FILE *outFile=fopen(outDexFile.c_str(), "wb");
	
	if (srcDexFile!=NULL) {
	    fseek(srcDexFile,0,SEEK_END);
	    long fsize =ftell(srcDexFile);
	    rewind(srcDexFile);
	    
	    std::cout<<sizeof(char)<<"\nxxxxxxxx"<<fsize;
	    unsigned  char *list=(unsigned char*)malloc(sizeof(char)*fsize);
	    unsigned long  numread =fread(list,sizeof(char),fsize,srcDexFile);
	    // blue_dump_data(list, (unsigned long )fsize);
	    unsigned char *dst=(unsigned char*)malloc(numread);
	    unsigned long dlen=numread;
	    base64_decode(dst, &dlen, list, numread);
	    
	    fclose(srcDexFile);
	    
	    int ret=fwrite(dst, 1, dlen, outFile);
	    fclose(outFile);
	    
	}
	
}

char* itoa(int i, char b[]){
	char const digit[] = "0123456789";
	char* p = b;
	if(i<0){
		*p++ = '-';
		i *= -1;
	}
	int shifter = i;
	do{ //Move to where representation ends
		++p;
		shifter = shifter/10;
	}while(shifter);
	*p = '\0';
	do{ //Move back, inserting digits as u go
		*--p = digit[i%10];
		i = i/10;
	}while(i);
	return b;
}
#endif

char * DexHacker::getProcessName(char * buffer){
	char path_t[256]={0};

	pid_t pid=getpid();
	char str[15];
	sprintf(str, "%d", pid);
	memset(path_t, 0 , sizeof(path_t));
	strcat(path_t, "/proc/");
	strcat(path_t, str);
	strcat(path_t, "/cmdline");
	//LOG_ERROR("zhw", "path:%s", path_t);
	int fd_t = open(path_t, O_RDONLY);
	if(fd_t>0){
		int read_count = read(fd_t, buffer, BUFLEN);
		if(read_count>0){
			return buffer;
		}
	}

	return NULL;
}

DexDataCache::DexDataCache(char *DexFilename,unsigned char *data,size_t length)
{
	if(NULL != (void*)(this->DexFileName=(char*)malloc(strlen(DexFilename) + 1)))
		strcpy(this->DexFileName,DexFilename);
	if(NULL != (void*)(this->data = (unsigned char*)malloc(length)))
		memcpy(this->data,data,length);
}

DexDataCache::~DexDataCache()
{
	if(this->DexFileName)
		free(this->DexFileName);
	if(this->data)
		free(this->data);
	this->DexFileName = NULL;
	this->data = NULL;
};

