#include "song.h"
#include "utils.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void getSongInfo(SongPtr song);
void printSongMenu(void);
void printSearchMenu(void);
void searchMenu(SongListPtr list);
void newSongMenu(SongListPtr list);
void printMenu(SongListPtr list);
void deleteMenu(SongListPtr list);
void errorMenu(SongListPtr list);

typedef void (*menuFunc)(SongListPtr);

int main(void)
{
	printf("----- Mini Music Library -----\n");

	SongList list = dataLoad();

	menuFunc menus[] = {
		searchMenu,
		newSongMenu,
		printMenu,
		deleteMenu,
		errorMenu
	};

	while (1)
	{
		int choice = -1;
		printSongMenu();

		if (parseInt(&choice))
		{
			if (choice == 0)
			{
				printf("Good Bye!\n");
				break;
			}
			else
			{
				cut_range(choice - 1, 4)[menus](&list);
			}
		}
		else
		{
			clearBuffer();
			4[menus](&list);
		}
	}

	dataSave(&list);

	freeSongList(&list);
}

void getSongInfo(SongPtr song)
{
	do
	{
		printf("Input title: ");
		scanf(" %[^\n]s", song->title);
	} while (strlen(song->title) == 0);

	do
	{
		printf("Input artist: ");
		scanf(" %[^\n]s", song->artist);
	} while (strlen(song->artist) == 0);

	printf("Input length\n");

	bool done = false;

	while (!done)
	{
		printf("       minute: ");
		if (parseInt(&song->length.minute))
		{
			if (song->length.minute >= 0)
				done = true;
		}
	}

	done = false;

	while (!done)
	{
		printf("       second: ");
		if (parseInt(&song->length.second))
		{
			if (song->length.second >= 0 && song->length.second < 60)
				done = true;
		}
	}
}

void printSongMenu(void)
{
	printf(
		"----------------------------\n"
		"1. Search\n"
		"2. New song\n"
		"3. Print all\n"
		"4. Delete all\n"
		"0. Exit\n"
		"----------------------------\n"
		">>> "
	);
}

void searchMenu(SongListPtr list)
{
	char title[256], artist[256];

	do
	{
		printf("Input title: ");
		scanf(" %[^\n]s", title);
	} while (strlen(title) == 0);

	do
	{
		printf("Input artist: ");
		scanf(" %[^\n]s", artist);
	} while (strlen(artist) == 0);

	SongPtr songPtr = searchSong(list, title, artist);

	if (songPtr == NULL)
	{
		printf("<ERROR> Song not found\n");

		return;
	}

	putchar('\n');

	printf(
		"\n"
		"Title  : %s\n"
		"Artist : %s\n"
		"Length : %d min %d sec\n\n",
		songPtr->title,
		songPtr->artist,
		songPtr->length.minute, songPtr->length.second
	);
	
	int choice = -1;

	for (;;)
	{
		printSearchMenu();

		if (parseInt(&choice))
		{
			if (choice == 1)
			{
				Song song;
				getSongInfo(&song);

				if (searchSong(list, song.title, song.artist) != NULL)
				{
					printf("<ERROR> song already exists.\n");
				}
				else
				{
					strcpy(songPtr->title, song.title);
					strcpy(songPtr->artist, song.artist);
					memcpy(&songPtr->length, &song.length, sizeof(Time));
				}

				break;
			}
			else if (choice == 2)
			{
				delSong(list, songPtr);
				
				printf("... delete success.\n");
				
				break;
			}
			else if (choice == 0)
			{
				break;
			}
			else
			{
				errorMenu(list);
			}
		}
	}
}

void printSearchMenu(void)
{
	printf(
		"----------------------------\n"
		"1. Edit\n"
		"2. Delete\n"
		"0. Previous\n"
		"----------------------------\n"
		">>> "
	);
}

void newSongMenu(SongListPtr list)
{
	Song song;

	getSongInfo(&song);
	
	if (searchSong(list, song.title, song.artist) != NULL)
	{
		printf("<ERROR> song already exists.\n");
	}
	else
	{
		addSong(list, &song);

		printf("... add success\n");
	}
}

void printMenu(SongListPtr list)
{
	putchar('\n');

	printAll(list);

	putchar('\n');
}

void deleteMenu(SongListPtr list)
{
	char tmp[256];

	printf("Are you sure? (y or n): ");
	
	scanf(" %[^\n]s", tmp);

	if (strcmp(tmp, "y") == 0 || strcmp(tmp, "Y") == 0)
	{
		deleteAll(list);

		printf("Delete all complete.\n");
	}
}

void errorMenu(SongListPtr list)
{
	printf(
		"Invalid input!\n"
		"Please input again.\n\n");
}
