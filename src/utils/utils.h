#ifndef _UTILS_
#define _UTILS_

int randRange(int n);
double rand01();
int readFastaFiles(char* folderPath, char** sequences);
int countFastaFilesInFolder(char* folderPath);
void debug_print_sequences(int sequenceCount, char** sequences);
int maxLength(int sequenceCount, char** sequences);

#endif