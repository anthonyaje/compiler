#include "symbolTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
// This file is for reference only, you are not required to follow the implementation. //

#define SCOPE_SIZE 1000

int HASH(char * str) {
	int idx=0;
	while (*str){
		idx = idx << 1;
		idx+=*str;
		str++;
	}
	return (idx & (HASH_TABLE_SIZE-1));
}

SymbolTable symbolTable;

SymbolTableEntry* newSymbolTableEntry(int nestingLevel)
{
    SymbolTableEntry* symbolTableEntry = (SymbolTableEntry*)malloc(sizeof(SymbolTableEntry));
    symbolTableEntry->nextInHashChain = NULL;
    symbolTableEntry->prevInHashChain = NULL;
    symbolTableEntry->nextInSameLevel = NULL;
    symbolTableEntry->sameNameInOuterLevel = NULL;
    symbolTableEntry->attribute = NULL;
    symbolTableEntry->name = NULL;
    symbolTableEntry->nestingLevel = nestingLevel;
    return symbolTableEntry;
}

void removeFromHashTrain(int hashIndex, SymbolTableEntry* entry)
{
    printf("IN removefromhash\n");
    if(entry == NULL){
	printf("Warning: try to remove NULL entry\n");
	return;
    } 
    if(entry->nextInHashChain != NULL){
	printf("IN removefromhash first if\n");
	if(entry->prevInHashChain != NULL)
		entry->prevInHashChain->nextInHashChain = entry->nextInHashChain;
	else
		symbolTable.hashTable[hashIndex] = entry->nextInHashChain;	
	
	entry->nextInHashChain->prevInHashChain = entry->prevInHashChain;
	
	entry->nextInHashChain = NULL;
	entry->prevInHashChain = NULL;
   } 
   else{
	printf("IN removefromhash second if\n");
	if(entry->prevInHashChain != NULL)
		entry->prevInHashChain->nextInHashChain = NULL;
	else
		symbolTable.hashTable[hashIndex] = NULL;
	
	entry->prevInHashChain = NULL;
	
   }

    printf("OUT removefromhash\n");
}

void enterIntoHashTrain(int hashIndex, SymbolTableEntry* entry)
{
	printf("IN enterIntoHashTrain\n");
	entry->nextInHashChain = symbolTable.hashTable[hashIndex];
	symbolTable.hashTable[hashIndex] = entry;
    printf("OUT enterIntoHashTrain\n");
}

void initializeSymbolTable()
{
   symbolTable.scopeDisplay = (SymbolTableEntry**)malloc(sizeof(SymbolTableEntry*)*SCOPE_SIZE);
   symbolTable.currentLevel = 0;
   //FIXME
   symbolTable.scopeDisplayElementCount = 0;
}

void symbolTableEnd()
{
   //FIXME: free them
   //free(symbolTable.scopeDisplay);
   //free()
}

SymbolTableEntry* retrieveSymbol(char* symbolName)
{
     SymbolTableEntry* p = symbolTable.hashTable[HASH(symbolName)];
     while(p != NULL){
		if(strcmp(p->name,symbolName) == 0){
			return p;
		}
		p = p->nextInHashChain; 
	 }	
     return NULL;
}

//int check_old_symbol_depth(SymbolTableEntry* old_symbol){
//	if(old_symbol)
//}

SymbolTableEntry* enterSymbol(char* symbolName, SymbolAttribute* attribute)
{
	printf("START: enterSymbol\n");
	//int i=0;
	//printf("i: %d\n",i++);
	SymbolTableEntry* entry = newSymbolTableEntry(symbolTable.currentLevel);
	entry->name = symbolName;
	entry->attribute = attribute;
	//printf("i:  %d\n",i++);
    SymbolTableEntry* old_symbol = retrieveSymbol(entry->name);
	//printf("i:  %d\n",i++);
    if((old_symbol != NULL)&&(old_symbol->nestingLevel == entry->nestingLevel)){
	       printf("ID %s redeclared.\n");
 	}
	if(old_symbol == NULL){
		enterIntoHashTrain(HASH(entry->name),entry);
	}else{
		removeFromHashTrain(HASH(old_symbol->name),old_symbol);
		enterIntoHashTrain(HASH(entry->name),entry);
	}
	entry->sameNameInOuterLevel = old_symbol;
	
	//scope pointer
 	entry->nextInSameLevel = symbolTable.scopeDisplay[entry->nestingLevel]; 
	symbolTable.scopeDisplay[entry->nestingLevel] = entry;
	printf("CLOSE: enterSymbol\n");
}

//remove the symbol from the current scope
void removeSymbol(char* symbolName)
{
     printf("START: removeSymbol\n");
	 SymbolTableEntry* old_symbol = retrieveSymbol(symbolName);
        if((old_symbol != NULL) && (old_symbol->nestingLevel == symbolTable.currentLevel)){
	   removeFromHashTrain(HASH(old_symbol->name),old_symbol);
	   //free(old_symbol);
 	}
	else{
	   printf("ID %s not found.\n",symbolName);
	}
	printf("CLOSE: removeSymbol\n");	
}

int declaredLocally(char* symbolName)
{
    SymbolTableEntry* old_symbol = retrieveSymbol(symbolName);
        if((old_symbol != NULL) && (old_symbol->nestingLevel == symbolTable.currentLevel)){
	   return 1;
	}else{
	   return 0;
 	}
}

void openScope()
{
  printf("START: Scope %d opened\n",symbolTable.currentLevel+1);
  int i = symbolTable.currentLevel;
  symbolTable.currentLevel++;
  symbolTable.scopeDisplay[i] = NULL;
  //FIXME 
  /*
  if(symbolTable.currentLevel > symbolTable.scopeDisplayElementCount)
  symbolTable.scopeDisplayElementCount = symbolTable.currentLevel;
  */
}

void closeScope()
{
   printf("START: closeScope\n");
   SymbolTableEntry* p = symbolTable.scopeDisplay[symbolTable.currentLevel];
   while(p != NULL){ 
      SymbolTableEntry* next_node  = p->nextInSameLevel;
      SymbolTableEntry* prev_sym  = p->sameNameInOuterLevel;
/*<<<<<<< HEAD
      //free(p);
        printf("BEFORE REMOVING!!\n");
      removeSymbol(p->name);
	printf("SUCCESSFULLY REMOVED!!!\n");
      p = next_node;
      enterIntoHashTrain(HASH(prev_sym->name),prev_sym);
   }
   symbolTable.scopeDisplay[symbolTable.currentLevel] = NULL;
   symbolTable.currentLevel--;
=======*/
      removeSymbol(p->name);
	  printf("After removeSymbol\n");
	  if(prev_sym!=NULL){
		 enterIntoHashTrain(HASH(prev_sym->name),prev_sym);
		 printf("Prev_sym is not NULL\n");
	  }
	  else{
			printf("Prev_sym is NULL\n");
	  }
	  p = next_node;
   }
   symbolTable.scopeDisplay[symbolTable.currentLevel] = NULL;
   symbolTable.currentLevel--;
   printf("Scope %d closed\n",symbolTable.currentLevel+1);
//>>>>>>> 0856867a8f5e324017713fcfd3b914ff6f512912
}
