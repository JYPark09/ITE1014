#include "song.h"

#include "defs.h"

#include <assert.h>
#include <malloc.h>
#include <memory.h>
#include <stdio.h>
#include <string.h>

int initSongList(SongListPtr list)
{
	list->root = NEW(SongNode, 1);
	if (list->root == NULL)
		return ALLOC_ERROR;
	
	list->root->next = NULL;
	list->size = 0;

	return SUCCESS;
}

void freeSongList(SongListPtr list)
{
	deleteAll(list);

	if (list->root != NULL)
		free(list->root);
}

SongList dataLoad(void)
{
	SongList list;
	initSongList(&list);

	FILE* fp = fopen("mml.txt", "r");
	if (fp == NULL)
	{
		dataSave(&list);
		return list;
	}

	int nLen;
	fscanf(fp, "%d\n", &nLen);
	
	for (int i = 0; i < nLen; ++i)
	{
		Song song;

		fscanf(fp,
			" %d %d",
			&song.length.minute, 
			&song.length.second);
		fscanf(fp,
			" %[^\n]s",
			song.title);
		fscanf(fp,
			" %[^\n]s",
			song.artist);

		addSong(&list, &song);
	}

	fclose(fp);

	return list;
}

void dataSave(SongListPtr list)
{
	FILE* fp = fopen("mml.txt", "w");
	if (fp == NULL)
	{
		printf("Cannot open file to write.\n");
		return;
	}

	int nLen = nodeCount(list);
	fprintf(fp, "%d\n", nLen);

	SongNodePtr node = list->root->next;

	for (int i = 0; i < nLen; ++i)
	{
		assert(node != NULL);

		fprintf(fp, 
			"%d %d\n"
			"%s\n"
			"%s\n",
			node->value.length.minute,
			node->value.length.second,
			node->value.title,
			node->value.artist);

		node = node->next;
	}

	fclose(fp);
}

int nodeCount(SongListPtr list)
{
	return list->size;
}

int addSong(SongListPtr list, SongPtr song)
{
	SongNodePtr node = list->root;

	while (node->next != NULL)
	{
		node = node->next;
	}

	node->next = NEW(SongNode, 1);

	if (node->next == NULL)
		return ALLOC_ERROR;

	node->next->next = NULL;

	strcpy(node->next->value.title, song->title);
	strcpy(node->next->value.artist, song->artist);
	memcpy(&node->next->value.length, &song->length, sizeof(Time));

	++list->size;

	return SUCCESS;
}

int delSong(SongListPtr list, SongPtr song)
{
	SongNodePtr node = list->root->next, prev = list->root;

	while (node != NULL)
	{
		if (compareNode(node, song->title, song->artist))
		{
			prev->next = node->next;
			free(node);
			--list->size;

			return SUCCESS;
		}

		prev = node;
		node = node->next;
	}

	return FAIL;
}

int deleteAll(SongListPtr list)
{
	SongNodePtr node = list->root->next;

	while (node != NULL)
	{
		list->root->next = node->next;
		free(node);

		node = list->root->next;
	}

	list->size = 0;

	return SUCCESS;
}

int compareNode(SongNodePtr node, const char* title, const char* artist)
{
	return ((strcmp(node->value.title, title) == 0) &&
		(strcmp(node->value.artist, artist) == 0));
}

SongPtr searchSong(SongListPtr list, const char* title, const char* artist)
{
	SongNodePtr node = list->root->next;

	while (node != NULL)
	{
		if (compareNode(node, title, artist))
			return &node->value;

		node = node->next;
	}

	return NULL;
}

void printSong(SongPtr song)
{
	printf("%s - %s (%d:%02d)\n",
		song->artist,
		song->title,
		song->length.minute,
		song->length.second);
}

void printAll(SongListPtr list)
{
	SongNodePtr node = list->root->next;

	while (node != NULL)
	{
		printSong(&node->value);

		node = node->next;
	}
}
