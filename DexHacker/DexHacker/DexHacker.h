//
//  DexHacker.h
//  
//
//  Created by BunnyBlue on 6/23/15.
//
//

#ifndef ____DexHacker__
#define ____DexHacker__
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
//#include "base64.h"
#define BUFLEN 1024

class DexDataBuf{
private:
       char * DexFileName;
       unsigned char *data;
       size_t length;
public:
       DexDataBuf(char *DexFilename,unsigned char *data,size_t length);
       ~DexDataBuf(){};
}

class DexHacker{
public:
	void  writeDex2Encoded(unsigned char * data,size_t length);
	//void  writeEncodedDex2Dex(const char *dexPath);
	void  writeDexBufToFile(DexDataBuf *dexbuf);
	char * getProcessName(char * buffer);
};
#endif /* defined(____DexHacker__) */
