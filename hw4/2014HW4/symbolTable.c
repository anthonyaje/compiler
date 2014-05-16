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
   if(entry->nextInHashChain != NULL){
	entry->prevInHashChain->nextInHashChain = entry->nextInHashChain;
	entry->nextInHashChain->prevInHashChain = entry->prevInHashChain;
	
	entry->nextInHashChain = NULL;
	entry->prevInHashChain = NULL;
	//free(entry);    
   } 
   else{
	entry->prevInHashChain->nextInHashChain = NULL;
	entry->prevInHashChain = NULL;
   }
}

void enterIntoHashTrain(int hashIndex, SymbolTableEntry* entry)
{
	entry->nextInHashChain = symbolTable.hashTable[hashIndex];
	symbolTable.hashTable[hashIndex] = entry;
   
}

void initializeSymbolTable()
{
   symbolTable.scopeDisplay = (SymbolTableEntry**)malloc(sizeof(SymbolTableEntry*)*SCOPE_SIZE);
   symbolTable.currentLevel = -1;
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
     while(p != NULL && (strcmp(p->name,symbolName) != 0)){ p = p->nextInHashChain; }	
     return p;
}

//int check_old_symbol_depth(SymbolTableEntry* old_symbol){
//	if(old_symbol)
//}

SymbolTableEntry* enterSymbol(char* symbolName, SymbolAttribute* attribute)
{
	int i=0;
	//printf("i: %d\n",i++);
	SymbolTableEntry* entry = newSymbolTableEntry(symbolTable.currentLevel);
	entry->name = symbolName;
	entry->attribute = attribute;
	//printf("i:  %d\n",i++);
        SymbolTableEntry* old_symbol = retrieveSymbol(entry->name);
	//printf("i:  %d\n",i++);
        if((old_symbol != NULL) && (old_symbol->nestingLevel == entry->nestingLevel)){
	   //raise error
	   printf("ID %s redeclared.\n");
	   removeFromHashTrain(HASH(old_symbol->name),old_symbol);
 	}
	//printf("i:  %d\n",i++);
	enterIntoHashTrain(HASH(entry->name),entry);
	//printf("i:  %d\n",i++);
	//scope pointer
 	entry->nextInSameLevel = symbolTable.scopeDisplay[entry->nestingLevel]; 
	//printf("i:  %d\n",i++);
	symbolTable.scopeDisplay[entry->nestingLevel] = entry;
	//printf("i:  %d\n",i++);

}

//remove the symbol from the current scope
void removeSymbol(char* symbolName)
{
        SymbolTableEntry* old_symbol = retrieveSymbol(symbolName);
        if((old_symbol != NULL) && (old_symbol->nestingLevel == symbolTable.currentLevel)){
	   removeFromHashTrain(HASH(old_symbol->name),old_symbol);
	   free(old_symbol);
 	}
	else{
	   printf("ID %s not found.\n");
	}
		
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
  int i = ++symbolTable.currentLevel;
  symbolTable.scopeDisplay[i] = NULL;
  //FIXME 
  if(symbolTable.currentLevel > symbolTable.scopeDisplayElementCount)
  symbolTable.scopeDisplayElementCount = symbolTable.currentLevel;
}

void closeScope()
{
   SymbolTableEntry* p = symbolTable.scopeDisplay[symbolTable.currentLevel];
   while(p != NULL){ 
      SymbolTableEntry* next_node  = p->nextInSameLevel;
      SymbolTableEntry* prev_sym  = p->sameNameInOuterLevel;
      //free(p);
      removeSymbol(p->name);
      p = next_node;
      enterIntoHashTrain(HASH(prev_sym->name),prev_sym);
   }
   symbolTable.scopeDisplay[symbolTable.currentLevel--] = NULL;
}
