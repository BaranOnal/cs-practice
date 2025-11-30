/*#include <stdio.h>

int hash(char key, int tableSize);


void printArray(int arr[], int n);

int main() {


    int Arr[12] = { 54,99,5,0,27,39,2,35,156,58,35,123 };
    char key[2];

    printf("Enter");
    scanf_s("%d", key);

   

    return 0;
}


int hash(char key, int tableSize)
{
    int hashVal = 0;

    for (int i = 0; i<tableSize; i++)
    {
        if (arr)
        {

        }
    }


    return 0;
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// MapNode yapýsý
typedef struct MapNode {
    int key;
    int value;
    struct MapNode* next;
} MapNode;

// Map yapýsý
typedef struct Map {
    MapNode** buckets;
    int size;
    int numBuckets;
    double DEFAULT_LOAD_FACTOR;
} Map;

// Fonksiyonlar
MapNode* createNode(int key, int value) {
    MapNode* newNode = (MapNode*)malloc(sizeof(MapNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

int getBucketIndex(Map* map, int key) {
    int hashCode = key; // Basit hash hesaplama (key'e eþit)
    return abs(hashCode % map->numBuckets);
}

Map* createMap() {
    Map* map = (Map*)malloc(sizeof(Map));
    map->numBuckets = 5;
    map->size = 0;
    map->DEFAULT_LOAD_FACTOR = 0.75;

    map->buckets = (MapNode**)malloc(map->numBuckets * sizeof(MapNode*));
    for (int i = 0; i < map->numBuckets; i++) {
        map->buckets[i] = NULL;
    }

    printf("HashMap created\n");
    printf("Number of pairs in the Map: %d\n", map->size);
    printf("Size of Map: %d\n", map->numBuckets);
    printf("Default Load Factor: %.2f\n", map->DEFAULT_LOAD_FACTOR);
    return map;
}

void rehash(Map* map);

void insert(Map* map, int key, int value) {
    int bucketIndex = getBucketIndex(map, key);
    MapNode* head = map->buckets[bucketIndex];

    // Var olan anahtarý güncelle
    while (head != NULL) {
        if (head->key == key) {
            head->value = value;
            return;
        }
        head = head->next;
    }

    // Yeni düðüm oluþtur ve baðla
    MapNode* newNode = createNode(key, value);
    newNode->next = map->buckets[bucketIndex];
    map->buckets[bucketIndex] = newNode;

    map->size++;
    printf("Pair(%d, %d) inserted successfully.\n", key, value);

    double loadFactor = (double)map->size / map->numBuckets;
    printf("Current Load factor = %.2f\n", loadFactor);

    if (loadFactor > map->DEFAULT_LOAD_FACTOR) {
        printf("%.2f is greater than %.2f\n", loadFactor, map->DEFAULT_LOAD_FACTOR);
        printf("Therefore Rehashing will be done.\n");
        rehash(map);
    }

    printf("Number of pairs in the Map: %d\n", map->size);
}

void rehash(Map* map) {
    printf("\n***Rehashing Started***\n");

    int oldNumBuckets = map->numBuckets;
    MapNode** oldBuckets = map->buckets;

    map->numBuckets *= 2;
    map->buckets = (MapNode**)malloc(map->numBuckets * sizeof(MapNode*));
    for (int i = 0; i < map->numBuckets; i++) {
        map->buckets[i] = NULL;
    }
    map->size = 0;

    for (int i = 0; i < oldNumBuckets; i++) {
        MapNode* head = oldBuckets[i];
        while (head != NULL) {
            insert(map, head->key, head->value);
            MapNode* temp = head;
            head = head->next;
            free(temp);
        }
    }
    free(oldBuckets);
    printf("***Rehashing Done***\n");
}

void freeMap(Map* map) {
    for (int i = 0; i < map->numBuckets; i++) {
        MapNode* head = map->buckets[i];
        while (head != NULL) {
            MapNode* temp = head;
            head = head->next;
            free(temp);
        }
    }
    free(map->buckets);
    free(map);
}

int main() {
    Map* map = createMap();

    // Elemanlarý ekle
    insert(map, 1, 1);
    insert(map, 2, 2);
    insert(map, 3, 3);
    insert(map, 4, 4);
    insert(map, 5, 5);
    insert(map, 6, 6);
    insert(map, 7, 7);
    insert(map, 8, 8);
    insert(map, 9, 9);
    insert(map, 10, 10);

    // Belleði temizle
    freeMap(map);

    return 0;
}