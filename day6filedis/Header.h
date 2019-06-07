#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define BLOCKSIZE 16384
#define BLOCKS 6400
#define FILENAMESIZE 20

struct filedata {
	char filename[20];
	unsigned int blocks;
	unsigned int startBlock;
	int fileLength;
};

struct metadata {
	int magicNum;
	struct filedata files[32];
	int freespace;
	int freeBlocks;
	int fileCount;
	char blocks[BLOCKS];
};
