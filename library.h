#pragma once

#ifndef LIBRARY_H
#define LIBRARY_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

//구조체 정의(타입정의)는 일반적으로 헤더파일에

typedef struct song Song;
typedef struct snode SNode;
typedef struct artist Artist;

struct song {
	Artist *artist;
	char *title;
	char *path;
	int index;  
};
struct snode {
	struct snode *next, *prev;
	Song *song;
};
struct artist {
	char *name;
	struct artist *next;
	SNode *head, *tail;
};

void initialize();
void add_song(char *artist, char *title, char *path);
void status();
void load(FILE *fp);
void search_song(char *artist, char *title);
void search_song(char *artist);

#endif  //LIBRARY_H