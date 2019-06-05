#include "stdafx.h"
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void deleteFile(int blockNum, bool *blocks) {
	blocks[blockNum] = 0;
}


void write(int blockNum, char *buffer) {
	FILE *fp = fopen("hardDisk.hdd", "rb+");
	if (fp != NULL) {
		fseek(fp, blockNum*BLOCKSIZE, SEEK_SET);
		fwrite(buffer, BLOCKSIZE, 1,fp);
		fclose(fp);
	}
	else
		printf("File not opened\n");
	fclose(fp);
}


void read(int blockNum, char *buffer) {
	FILE *fp = fopen("hardDisk.hdd", "rb+");
	if (fp != NULL) {
		fseek(fp, blockNum*BLOCKSIZE, SEEK_SET);
		fread(buffer, BLOCKSIZE,1, fp);
		fclose(fp);
	}
	else
		printf("File not opened\n");
	fclose(fp);
}

void getMetadata(char *buffer) {
	read(0, buffer);
}

void debug() {
	char buffer[BLOCKSIZE];
	read(0, buffer);
	struct metadata *n = (struct metadata *)buffer;
	int fileCnt = n->fileCount;
	for (int i = 0; i < fileCnt; i++)
		printf("%s\t%d\t%d\t%d\n", n->files[i].filename,n->files[i].startBlock,n->files[i].endBlock,n->files[i].fileLength);
}

int freeBlock(int blocksRequired) {
	char buffer[BLOCKSIZE];
	struct metadata m;
	read(0, buffer);
	memcpy(&m, buffer, sizeof(buffer));
	//printf("%d\n", m.fileCount);
	int blocksCount = 0;
	for (int i = 0; i < BLOCKS; i++) {
		//printf("%c\n", m.blocks[i]);
		if (m.blocks[i] == '0') {
			int j = i+1;
			while (j < BLOCKS) {
				if (m.blocks[j] == '1')
					break;
				else
					blocksCount++;
				if (blocksCount == blocksRequired)
					return i;
				j++;
			}
		}
	}
}


void updateMetadata(char *dest,int size,int blocksRequired,int startBlock) {
	char buffer[BLOCKSIZE];
	getMetadata(buffer);
	struct metadata m;
	memcpy(&m, buffer, sizeof(buffer));
	m.freeBlocks = m.freeBlocks - blocksRequired;
	int filecount = m.fileCount;
	m.files[m.fileCount].startBlock = startBlock;
	m.files[m.fileCount].endBlock = startBlock + blocksRequired - 1;
	strcpy(m.files[m.fileCount].filename,dest);
	m.files[m.fileCount].fileLength = size;
	m.fileCount = m.fileCount + 1;
	while (blocksRequired > 0) {
		m.blocks[startBlock] = '1';
		startBlock++;
		blocksRequired--;
	}
	memcpy(buffer, &m, sizeof(struct metadata));
	write(0, buffer);
}


void initialiseMetadata() {
	char buffer[BLOCKSIZE];
	struct metadata m;
	m.magicNum = 0x444E524D;
	m.freeBlocks = BLOCKS-4;
	m.fileCount = 0;
	for (int i = 0; i < 32; i++) {
		strcpy(m.files[i].filename , " ");
		m.files[i].startBlock = 0;
		m.files[i].endBlock = 0;
		m.files[i].fileLength = 0;
	}
	for (int i = 0; i < BLOCKS; i++) {
		if (i < 4)
			m.blocks[i] = '1';
		else
			m.blocks[i] = '0';
	}
	memcpy(buffer, &m, sizeof(struct metadata));
	write(0, buffer);
}


void copyfromfs(char *dest, char *src) {
	char buffer[BLOCKSIZE];
	getMetadata(buffer);
	struct metadata m;
	memcpy(&m, buffer, sizeof(struct metadata));
	int startBlock, endBlock, len;
	for (int i = 0; i < 32; i++) {
		//printf("%s\t%s", m.files[i].filename, src);
		if (strcmp(m.files[i].filename, src) == 0) {
			startBlock = m.files[i].startBlock;
			endBlock = m.files[i].endBlock;
			len = m.files[i].fileLength;
			break;
		}	
	}
	int size;
	FILE *fp = fopen(dest, "w");
	if (fp != NULL) {
		while (startBlock <= endBlock ) {
			if (len < BLOCKSIZE)
				size = len;
			else {
				size = BLOCKSIZE;
				len -= BLOCKSIZE;
			}
			char *buffer = (char *)malloc(sizeof(char)*BLOCKSIZE);
			read(startBlock, buffer);
			fwrite(buffer,len,1, fp);
			startBlock++;
		}
	}
	fclose(fp);
	return;
}

int getSrcFileSize(char *source) {
	FILE *fp = fopen(source, "r");
	fseek(fp, 0, SEEK_END);
	int size = ftell(fp);
	fclose(fp);
	return size;
}

void copydata(int freeBlockNum,int bytes,int blocksRequired,char *source) {
	int readBytes;
	int prevEnd = 0;
	FILE *fp = fopen(source, "r");
	while (blocksRequired > 0) {
		if (bytes < BLOCKSIZE) {
			readBytes = bytes;
			prevEnd += readBytes;
		}
		else {
			readBytes = BLOCKSIZE;
			bytes -= readBytes;
			prevEnd += readBytes;
		}
		char *buffer = (char *)malloc(sizeof(char)*BLOCKSIZE);
		fread(buffer, 1,readBytes, fp);
		write(freeBlockNum, buffer);
		fseek(fp, prevEnd, SEEK_SET);
		blocksRequired--;
		freeBlockNum++;
	}
	fclose(fp);
}

void copytodisk(char *destination, char *source) {
	int bytes = getSrcFileSize(source);
	int blocksRequired;
	if ( bytes % BLOCKSIZE == 0 )
		blocksRequired = bytes / BLOCKSIZE;
	else
		blocksRequired = (bytes / BLOCKSIZE) + 1;
	char buffer[BLOCKSIZE];
	read(0, buffer);
	struct metadata *n = (struct metadata *)buffer;
	int startBlock = freeBlock(blocksRequired); 
	copydata(startBlock, bytes, blocksRequired,source);
	updateMetadata(destination,bytes,blocksRequired,startBlock);
	return;
}

void listFiles() {
	char buffer[BLOCKSIZE];
	read(0, buffer);
	struct metadata *n = (struct metadata *)buffer;
	int fileCnt = n->fileCount;
	for (int i = 0; i < fileCnt; i++)
		printf("%s\n", n->files[i].filename);
}




void run_prompt() {
	initialiseMetadata();
	while (1) {
		printf(">");
		char *command = (char *)malloc(sizeof(char) * 50);
		gets(command);
		if (strstr(command, "COPYTOFS")) {
			char *destination = (char *)malloc(sizeof(char) * 20);
			sscanf(command, "%*s %s %*s", destination);
			char *src = (char *)malloc(sizeof(char) * 20);
			sscanf(command, "%*s %*s %s", src);
			copytodisk(destination, src);
		}
		else if (strstr(command, "COPYFROMFS")) {
			char *dest = (char *)malloc(sizeof(char) * 20);
			sscanf(command, "%*s %s %*s", dest);
			char *src = (char *)malloc(sizeof(char) * 20);
			sscanf(command, "%*s %*s %s", src);
			copyfromfs(dest, src);
		}
		else if (strstr(command, "LIST")) {
			listFiles();
		}
		else if (strstr(command, "DEBUG"))
			debug();
		else if (strstr(command, "exit"))
			exit(0);
	}
}

int main() {
	run_prompt();
	return 0;
}