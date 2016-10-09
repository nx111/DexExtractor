//
//  DexHacker.h
//  
//
//  Created by BunnyBlue on 6/23/15.
//
//

#ifndef ____DexHacker__
#define ____DexHacker__
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <fcntl.h>
#include <errno.h>

//#include "base64.h"
#define BUFLEN 1024

class DexDataCache{
public:
       char * DexFileName;
       unsigned char *data;
       size_t length;

       DexDataCache(char *DexFilename,unsigned char *data,size_t length);
       ~DexDataCache();
};

class DexHacker{
public:
	void  writeDex2Encoded(unsigned char * data,size_t length);
	//void  writeEncodedDex2Dex(const char *dexPath);
	void  writeDexBufToFile(DexDataCache *dexbuf);
	char * getProcessName(char * buffer);
};
#endif /* defined(____DexHacker__) */
