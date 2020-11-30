#include <stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>


//Alphabet's size
const int DICTIONARY_SIZE = 26;

//TrieNode structure
struct TrieNode {
    struct TrieNode *letter[26];
    bool isTheEndOfKey;
    bool isUsed;
};

//Methods
struct TrieNode *createTrieNode();

void insertKeyToTree(struct TrieNode *root, char *key);

bool searchTrieForKey(struct TrieNode *root, const char *keyToFind);

int main() {

    //Def attributes
    FILE *INPUT_FILE;
    char *tmp;
    char *letter[26], *coupon, *word;
    struct TrieNode *root = createTrieNode();

    tmp = (char *) malloc(sizeof(char));
    coupon = (char *) malloc(sizeof(char));
    word = (char *) malloc(sizeof(char));

    INPUT_FILE = fopen("../input.txt", "r");

    if (INPUT_FILE == NULL) {
        printf("File input.txt not in path! Exiting...");
        exit(-1);
    }


    //If file is not empty put key into trees
    while (fscanf(INPUT_FILE, "%s", &letter) != EOF) {
        tmp = &letter[0];
        insertKeyToTree(root, tmp);

    }

    printf("Please enter your coupon to checks its validity!\n");
    scanf("%s", coupon);
    word = &coupon;

    while (word != "END") {
        for (int k = 0; k < strlen(coupon); ++k) {

            //Check if coupon is uppercase and 10 letters, modify to our need
            if (!isupper(coupon[k]) || strlen(coupon) != 10) {
                printf("Code not valid. Only Uppercase allowed for coupons and should be 10 letters long");
                exit(1);
            }
        }

        if (searchTrieForKey(root, coupon)) {
            printf("\n %s --- Code is Valid\n", coupon);
        } else {
            printf("\n %s --- Code is NOT Valid\n", coupon);
        }
        scanf("%s", coupon);
        word = &coupon;
    }

    return 0;
}


//Create a new node
struct TrieNode *createTrieNode(void) {
    struct TrieNode *pNode = (struct TrieNode *) malloc(sizeof(struct TrieNode));


    pNode->isTheEndOfKey = false;

    for (int i = 0; i < DICTIONARY_SIZE; ++i) {
        pNode->letter[i] = NULL;
    }

    return pNode;
}

bool searchTrieForKey(struct TrieNode *root, const char *keyToFind) {
    struct TrieNode *pCrawl = root;


    for (int i = 0; i < strlen(keyToFind); ++i) {

        int indexForSearch = keyToFind[i] - 'A';

        //If doesnt exist in trie return false
        if (!pCrawl->letter[indexForSearch])
            return false;

        pCrawl = pCrawl->letter[indexForSearch];

    }

    if (pCrawl->isTheEndOfKey && !(pCrawl->isUsed) && pCrawl != NULL) { // if exists in trie and not used return true
        //Find coupon and mark it as used
        pCrawl->isUsed = true;
        return true;
    } else if (pCrawl->isTheEndOfKey && (pCrawl->isUsed) && pCrawl != NULL) { // if exists in trie and used return false
        printf("\n Coupon already in use!");
        return false;
    }


}


//Creates nodes for given keys. The last element is consider as leaf
void insertKeyToTree(struct TrieNode *root, char *key) {
    struct TrieNode *pCrawl = root;

    for (int i = 0; i < strlen(key); i++) {
        int index = key[i] - 'A';
        if (!pCrawl->letter[index])
            pCrawl->letter[index] = createTrieNode();

        pCrawl = pCrawl->letter[index];
    }

    pCrawl->isTheEndOfKey = true;

}


