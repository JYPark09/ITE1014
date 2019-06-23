#ifndef MML_SONG_H
#define MML_SONG_H

#include "defs.h"

typedef struct _tagTime
{
	int minute;
	int second;
} Time;

typedef struct _tagSong
{
	char title[100];
	char artist[100];
	Time length;
} Song, *SongPtr;

typedef struct _tagSongNode
{
	struct _tagSongNode* next;

	Song value;
} SongNode, *SongNodePtr;

typedef struct _tagSongList
{
	SongNodePtr root;
	int size;
} SongList, *SongListPtr;

int initSongList(SongListPtr list);
void freeSongList(SongListPtr list);

SongList dataLoad(void);
void dataSave(SongListPtr list);

int nodeCount(SongListPtr list);

int addSong(SongListPtr list, SongPtr song);
int delSong(SongListPtr list, SongPtr song);
int deleteAll(SongListPtr list);

int compareNode(SongNodePtr node, const char* title, const char* artist);
SongPtr searchSong(SongListPtr list, const char* title, const char* artist);

void printSong(SongPtr song);
void printAll(SongListPtr list);

#endif
