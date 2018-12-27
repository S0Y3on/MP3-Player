#pragma warning (disable:4996)
#include "library.h"
#include "string_tools.h"

#define NUM_CHAR 256 // 2^8 = 256
#define BUFFER_LENGTH 200

Artist *artist_directory[NUM_CHAR];
int num_index = 0;

void insert_node(Artist *ptr_artist, SNode  *ptr_snode);
void print_artist(Artist *p);
void print_song(Song *);
Artist *find_artist(char *name);
SNode *find_snode(Artist *ptr_artist, char *title);
void initialize()
{
	for (int i = 0; i < NUM_CHAR; i++)
		artist_directory[i] = NULL;
}
void load(FILE *fp)
{
	char buffer[BUFFER_LENGTH];
	char *name,*title,*path;

	while (1) {  //infinite loop
		if (read_line(fp, buffer, BUFFER_LENGTH) <= 0)
			break;


		name = strtok(buffer, "#");
		if (strcmp(name, " ") == 0)
			name == NULL;
		else
			name = strdup(name);


		title = strtok(NULL, "#");
		if (strcmp(title, " ") == 0)
			title == NULL;
		else
			title = strdup(title);


		path = strtok(NULL, "#");
		if (strcmp(path, " ") == 0)
			path == NULL;
		else
			path = strdup(path);

//		printf("%s %s %s\n", name, title, path);
		add_song(name, title, path);
	
	}
}
void search_song(char *artist, char *title)
{
	Artist *ptr_artist = find_artist(artist);
	if (ptr_artist == NULL) {
		printf("No such artist exists.\n");
		return;
	}

	SNode *ptr_snode = find_snode(ptr_artist, title);


	if (ptr_snode != NULL) {
		printf("Fount:\n");
		print_song(ptr_snode->song);
	}
	else {
		printf("No such song exists.\n");
		return;
	}
}
SNode *find_snode(Artist *ptr_artist, char *title)
{
	SNode *ptr_snode = ptr_artist->head;
	while (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) < 0)
		ptr_snode = ptr_snode;

	if (ptr_snode != NULL && strcmp(ptr_snode->song->title, title) == 0) {
		return ptr_snode;
	}
	else {
		return NULL;
	}
}
void search_song(char *artist)
{
	Artist *ptr_artist = find_artist(artist);
	if (ptr_artist == NULL) {
		printf("No such artist exists.\n");
		return;
	}
	printf("Fount:\n");
	print_artist(ptr_artist);
}
Artist *create_artist_instance(char *name)
{
	Artist *ptr_artist = (Artist *)malloc(sizeof(Artist));
	ptr_artist->name = name;
	ptr_artist->head = NULL;
	ptr_artist->tail = NULL;
	ptr_artist->next = NULL;
	return ptr_artist;
}
Artist *add_artist(char *name)
{
	Artist *ptr_artist = create_artist_instance(name);
	Artist *p = artist_directory[(unsigned char)name[0]]; //first node

	Artist *q = NULL;

	while (p != NULL && strcmp(p->name, name) < 0) {
		q = p;
		p = p->next;
	}
	if (p == NULL && q == NULL) { //unique node
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	else if (q == NULL) { //add at the front
		ptr_artist->next = artist_directory[(unsigned char)name[0]];
		artist_directory[(unsigned char)name[0]] = ptr_artist;
	}
	else { //add_after(q)
		ptr_artist->next = p;
		q->next = ptr_artist;
	}

	return ptr_artist;  
}

Song * create_song_instans(Artist *ptr_artist,char *title,char *path)
{
	Song *ptr_song = (Song *)malloc(sizeof(Song));
	ptr_song->artist = ptr_artist;
	ptr_song->title = title;
	ptr_song->path = path;
	ptr_song->index = num_index;
	num_index++;

	return ptr_song;
}
void add_song(char *artist, char *title, char *path)
{
	// find if the artist already exists
	//return NULL if not
	Artist *ptr_artist = find_artist(artist);
	if (ptr_artist == NULL) {
		ptr_artist = add_artist(artist);
	}
	//add the song to the artist pointed by ptr_artist
	Song *ptr_song = create_song_instans(ptr_artist,title, path);
	SNode *ptr_snode = (SNode *)malloc(sizeof(SNode));
	ptr_snode->song = ptr_song;
	ptr_snode->next = NULL;
	ptr_snode->prev = NULL;

	//insert node
	insert_node(ptr_artist, ptr_snode);
}
void insert_node(Artist *ptr_artist, SNode  *ptr_snode)
{
	SNode *p = ptr_artist->head;
	while (p != NULL && strcmp(p->song->title,ptr_snode->song->title)<0) {
		p = p->next;
	}

	// add ptr_snode before p
	// 1. empty  2. at the front  3. at the end  4. in the middle

	if (ptr_artist->head == NULL) { //empty
		ptr_artist->head = ptr_snode;
		ptr_artist->tail = ptr_snode;
	}
	else if (p == ptr_artist->head) { // at the front
		ptr_snode->next = ptr_artist->head;
		ptr_artist->head->prev = ptr_snode;
		ptr_artist->head = ptr_snode;
	}
	else if (p == NULL) { //at the end 
		ptr_snode->prev = ptr_artist->tail;
		ptr_artist->tail->next = ptr_snode;
		ptr_artist->tail = ptr_snode;
	}
	else { // add before p
		ptr_snode->next = p;
		ptr_snode->prev = p->prev;
		p->prev->next = ptr_snode;
		p->prev = ptr_snode;
	}
}

Artist *find_artist(char *name)
{
	Artist *p = artist_directory[(unsigned char)name[0]];  //first artist with initial name[0]
	/*  name[0]: 00000000 ~ 11111111 */ //ù��Ʈ�� 1�̸� ���� �� ���� �ִ� .......unsigned char���

	while (p != NULL && strcmp(p->name, name) < 0)
		p = p->next;
	if (p != NULL && strcmp(p->name, name) == 0)
		return p;
	else
		return NULL;
}


void status()
{
	for (int i = 0; i < NUM_CHAR; i++) {
		Artist *p = artist_directory[i];
		while (p != NULL) {
			print_artist(p);
			p = p->next;
		}
	}
}

void print_artist(Artist *p) {
	printf("%s\n", p->name);
	SNode *ptr_snode = p->head;
	while (ptr_snode != NULL) {
		print_song(ptr_snode->song);
		ptr_snode = ptr_snode->next;
	}
}

void print_song(Song *ptr_song)
{
	printf("   %d: %s, %s\n",ptr_song->index, ptr_song->title, ptr_song->path);
}