#include <HashMap.h>
#include <kmalloc.h>
#include <string.h>
#include <screen.h>

HashMap *newHashMap()
{
	HashMap *hashmap;

	hashmap = (HashMap *)kmalloc(sizeof(HashMap));
	hashmap->node = (HashMapNode *)0;
	hashmap->count = 0;

	return hashmap;
}

void addHashMapValue(HashMap *hashMap, char *key, char *value, int sizeOfValue)
{
	HashMapNode *tempHashNode;
	HashMapNode *newHashNode;
	int count = 0;

	kprint("adding ");
	kprint(key);
	kprint(" -> ");
	kprint(value);
	kprint(" (");
	put_int(sizeOfValue, 10);
	kprint(")\n");

	tempHashNode = hashMap->node;

	/*setup new node*/
	newHashNode = (HashMapNode *)kmalloc(sizeof(HashMapNode));
	strcpy(newHashNode->key, key);
	newHashNode->value = (char *)kmalloc(sizeOfValue);
	memcpy(newHashNode->value, value, sizeOfValue);
	newHashNode->next = 0;

	/*is this the first item in the list?*/
	if (tempHashNode == 0)
	{
		kprint("hashmap is 0\n");

		/*add the new node*/
		hashMap->node = newHashNode;
	} else {
		/*find the last node in the list*/
		while (tempHashNode->next != 0)
		{
			kprint("passing ");
			kprint(tempHashNode->key);
			kprint(" -> ");
			kprint(tempHashNode->value);
			kprint("\n");
			tempHashNode = (HashMapNode *)tempHashNode->next;
		}

		/*add the new node*/
		tempHashNode->next = newHashNode;
	}

	hashMap->count++;
}

char *getHashMapValue(HashMap *hashMap, char *key)
{
	HashMapNode *tempHashNode;

	tempHashNode = hashMap->node;

	if (tempHashNode == 0);
		return "empty value";

	/*find the node that has the key*/
		kprint("\n");
	//while (tempHashNode)// || strcmp(tempHashNode->key, key))
	{
		kprint("key: ");
		kprint(tempHashNode->key);
		kprint("\n");
	//	tempHashNode = (HashMapNode *)tempHashNode->next;
	}
		kprint("\n");
		while(1);
	
	return tempHashNode->value;
}

int getHashMapCount(HashMap *hashMap)
{
	return hashMap->count;
}

