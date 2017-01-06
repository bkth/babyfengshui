#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>

#define MAX_C 50

// compile with
// gcc -s -Wl,-z,relro -fstack-protector-all -m32 userstore.c -o userstore


typedef struct user {
	char *desc;
	char name[0x7c];
} user;

user *store[MAX_C];
uint8_t cnt = 0;

void read_len(char *dst, size_t len)
{
	fgets(dst, len, stdin);
	char *c = strchr(dst, '\n');
	if (c)
		*c = '\0';
}


void update_desc(uint8_t idx)
{
	if (idx < 0 || idx >= cnt)
	{
		return;
	}
	if (store[idx] == NULL)
	{
		return;
	}
	uint32_t sz = 0;
	printf("text length: ");
	char trash;
	scanf("%u%c", &sz, &trash);
	if ((uint32_t) store[idx]->desc + sz >= (uint32_t) store[idx] - 4)
	{
		printf("my l33t defenses cannot be fooled, cya!\n");
		exit(1);	
	}
	printf("text: ");
	read_len(store[idx]->desc, sz+1);
}

user *add_user(size_t sz)
{
	char *p_desc = (char *) malloc(sz); 
	memset(p_desc, 0, sz);
	user *p_user = (user *) malloc(sizeof(user));
	memset(p_user, 0, sizeof(user));
	p_user->desc = p_desc;
	store[cnt] = p_user;
	printf("name: ");
	read_len(store[cnt]->name, 0x7c);
	cnt++;
	update_desc(cnt - 1);
	return p_user;
}

void delete_user(uint8_t idx)
{
	if (idx < 0 || idx >= cnt)
	{
		return;
	}
	if (store[idx] == NULL)
	{
		return;
	}
	free(store[idx]->desc);
	free(store[idx]);
	store[idx] = NULL;
}

void display_user(uint8_t idx)
{
	if (idx < 0 || idx >= cnt)
	{
		return;
	}
	if (store[idx] == NULL)
	{
		return;
	}
	printf("name: %s\n", store[idx]->name);	
	printf("description: %s\n", store[idx]->desc);	
}

int main(void)
{
	int c, d;
	char trash;
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	alarm(20);	
	for (;;)
	{
		printf("0: Add a user\n");
		printf("1: Delete a user\n");
		printf("2: Display a user\n");
		printf("3: Update a user description\n");
		printf("4: Exit\n");
		printf("Action: ");
		if (scanf("%d", &c) == EOF)
			exit(1);
		if (c == 0)
		{	
			printf("size of description: ");
		       	scanf("%u%c", &d, &trash);
			add_user(d);
		}
		if (c == 1)
		{
			printf("index: ");
			scanf("%d", &d);
			delete_user(d);
		}
		if (c == 2)
		{
			printf("index: ");
			scanf("%d", &d);
			display_user(d);
		}
		if (c == 3)
		{
			printf("index: ");
			scanf("%d", &d);
			update_desc(d);
		}
		if (c == 4)
		{
			printf("Bye\n");
			exit(0);
		}
		if (cnt >= MAX_C)
		{
			printf("maximum capacity exceeded, bye\n");
			exit(0);
		}
	}


}
