#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "symbolTable.h"
// This file is for reference only, you are not required to follow the implementation. //
// You only need to check for errors stated in the hw4 document. //
int g_anyErrorOccur = 0;

DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2);
void processProgramNode(AST_NODE *programNode);
void processDeclarationNode(AST_NODE* declarationNode);
void declareIdList(AST_NODE* typeNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize);
void declareFunction(AST_NODE* returnTypeNode);
void processDeclDimList(AST_NODE* variableDeclDimList, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize);
void processTypeNode(AST_NODE* typeNode);
void processBlockNode(AST_NODE* blockNode);
void processStmtNode(AST_NODE* stmtNode);
void processGeneralNode(AST_NODE *node);
void checkAssignOrExpr(AST_NODE* assignOrExprRelatedNode);
void checkWhileStmt(AST_NODE* whileNode);
void checkForStmt(AST_NODE* forNode);
void checkAssignmentStmt(AST_NODE* assignmentNode);
void checkIfStmt(AST_NODE* ifNode);
void checkWriteFunction(AST_NODE* functionCallNode);
void checkFunctionCall(AST_NODE* functionCallNode);
void processExprRelatedNode(AST_NODE* exprRelatedNode);
void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter);
void checkReturnStmt(AST_NODE* returnNode);
void processExprNode(AST_NODE* exprNode);
void processVariableLValue(AST_NODE* idNode);
void processVariableRValue(AST_NODE* idNode);
void processConstValueNode(AST_NODE* constValueNode);
void getExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue);
void evaluateExprValue(AST_NODE* exprNode);


typedef enum ErrorMsgKind
{
    SYMBOL_IS_NOT_TYPE,
    SYMBOL_REDECLARE,
    SYMBOL_UNDECLARED,
    NOT_FUNCTION_NAME,
    TRY_TO_INIT_ARRAY,
    EXCESSIVE_ARRAY_DIM_DECLARATION,
    RETURN_ARRAY,
    VOID_VARIABLE,
    TYPEDEF_VOID_ARRAY,
    PARAMETER_TYPE_UNMATCH,
    
TOO_FEW_ARGUMENTS,
    TOO_MANY_ARGUMENTS,
    RETURN_TYPE_UNMATCH,
    INCOMPATIBLE_ARRAY_DIMENSION,
    NOT_ASSIGNABLE,
    NOT_ARRAY,
    IS_TYPE_NOT_VARIABLE,
    IS_FUNCTION_NOT_VARIABLE,
    STRING_OPERATION,
    ARRAY_SIZE_NOT_INT,
    ARRAY_SIZE_NEGATIVE,
    ARRAY_SUBSCRIPT_NOT_INT,
    PASS_ARRAY_TO_SCALAR,
    PASS_SCALAR_TO_ARRAY
} ErrorMsgKind;

void printErrorMsgSpecial(AST_NODE* node1, char* name2, ErrorMsgKind errorMsgKind)
{
    g_anyErrorOccur = 1;
    printf("Error found in line %d\n", node1->linenumber);
    /*
    switch(errorMsgKind)
    {
    default:
        printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
        break;
    }
    */
}


void printErrorMsg(AST_NODE* node, ErrorMsgKind errorMsgKind)
{
    g_anyErrorOccur = 1;
    printf("Error found in line %d\n", node->linenumber);
    /*
    switch(errorMsgKind)
    {
        printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
        break;
    }
    */
}


void semanticAnalysis(AST_NODE *root)
{
    processProgramNode(root);
}


DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2)
{
    if(dataType1 == FLOAT_TYPE || dataType2 == FLOAT_TYPE) {
        return FLOAT_TYPE;
    } else {
        return INT_TYPE;
    }
}


void processProgramNode(AST_NODE *programNode)
{
  AST_NODE* child = programNode->child;
  switch(child){
      case DECLARATION_NODE:
	  processDeclarationNode(child);
          break;
      default:
   	  printf("uncaught case\n"); 
  }
}

void processDeclarationNode(AST_NODE* declarationNode)
{
  if(declarationNode == NULL){ return; }
  else{
     AST_NODE* child = declarationNode->child;
     switch(declarationNode->semantic_value.declSemanticValue.kind){
        case VARIABLE_DECL :
  	    declareIdList(declarationNode, VARIABLE_ATTRIBUTE, 1);
            break;

        case TYPE_DECL :
            break;

        case FUNCTION_DECL:
	    declareFunction(declarationNode);
            break;

        case FUNCTION_PARAMETER_DECL:
	    
            break;
        default:
   	    printf("uncaught case\n"); 
   }
   processDeclarationNode(declarationNode->rightSibling);
 }



}


void processTypeNode(AST_NODE* idNodeAsType)
{
}

void declareIdList(AST_NODE* declarationNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize)
{
  AST_NODE* child = declarationNode->child;
  if(isVariableOrTypeAttribute == VARIABLE_ATTRIBUTE){
  	AST_NODE* p = child->rightSibling;
  	while(p!=NULL){
	    SymbolAttribute* symbol_att = (SymbolAttribute*) malloc(sizeof(SymbolAttribute));
	    symbol_att->attributeKind = isVariableOrTypeAttribute;
   	    TypeDescriptor* type_desc = (TypeDescriptor*) malloc(sizeof(TypeDescriptor));
	    type_desc->kind = SCALAR_TYPE_DESCRIPTOR;
	    type_desc->properties = p->dataType;
	    symbol_att->attr = type_desc;
  	    enterSymbol(p->semantic_value.identifierSemanticValue.identifierName,symbol_att);
	    p = p->rightSibling;
	}
  } else{
	//FIXME ignore
  	AST_NODE* p = child;
  	while(p!=NULL){
	    SymbolAttribute* symbol_att = (SymbolAttribute*) malloc(sizeof(SymbolAttribute));
	    symbol_att->attributeKind = isVariableOrTypeAttribute;
   	    TypeDescriptor* type_desc = (TypeDescriptor*) malloc(sizeof(TypeDescriptor));
	    type_desc->kind = SCALAR_TYPE_DESCRIPTOR;
	    type_desc->properties = p->dataType;
	    symbol_att->attr = type_desc;

	    enterSymbol(p->semantic_value.identifierSemanticValue.identifierName,symbol_att);
	    p = p->rightSibling;
	}
	
  }
}

void checkAssignOrExpr(AST_NODE* assignOrExprRelatedNode)
{
	
}

void checkWhileStmt(AST_NODE* whileNode)
{
}


void checkForStmt(AST_NODE* forNode)
{
}


void checkAssignmentStmt(AST_NODE* assignmentNode)
{
}


void checkIfStmt(AST_NODE* ifNode)
{
}

void checkWriteFunction(AST_NODE* functionCallNode)
{
}

void checkFunctionCall(AST_NODE* functionCallNode)
{
}

void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter)
{
}


void processExprRelatedNode(AST_NODE* exprRelatedNode)
{
}

void getExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue)
{
}

void evaluateExprValue(AST_NODE* exprNode)
{
}


void processExprNode(AST_NODE* exprNode)
{
}


void processVariableLValue(AST_NODE* idNode)
{
}

void processVariableRValue(AST_NODE* idNode)
{
}


void processConstValueNode(AST_NODE* constValueNode)
{
}


void checkReturnStmt(AST_NODE* returnNode)
{
}


void processBlockNode(AST_NODE* blockNode)
{
}


void processStmtNode(AST_NODE* stmtNode)
{
}


void processGeneralNode(AST_NODE *node)
{
}

void processDeclDimList(AST_NODE* idNode, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize)
{
}


void declareFunction(AST_NODE* declarationNode)
{
    AST_NODE* p = declarationNode->child;   
    FunctionSignature* functionSig;
    functionSig = (FunctionSignature*) malloc(sizeof(FunctionSignature));
    functionSig->parameterList = NULL;
    functionSig->parametersCount = 0;
    functionSig->returnType = p->DATA_TYPE;
    
    p = p->rightSibling;
    char* function_name = p->semantic_value.identifierSemanticValue.identifierName;

    p = p->rightSibling;
    AST_NODE* p_to_block = p;
    
    //p = p->child==NULL?p:p->child;
    if(p->child != NULL){
	p = p->child;
	while(p!=NULL){
           AST_NODE* q = p->child;
	   functionSig->parametersCount++;
           if(functionSig->parameterList == NULL){
	       functionSig->parameterList = (Parameter*) malloc(sizeof(Parameter)); 	    
	       functionSig->parameterList->next=NULL;
	        	    
   	       TypeDescriptor* type_desc = (TypeDescriptor*) malloc(sizeof(TypeDescriptor));
	       type_desc->kind = q->rightSibling->semantic_value.identifierSemanticValue.kind==NORMAL_ID?SCALAR_TYPE_DESCRIPTOR:ARRAY_TYPE_DESCRIPTOR;
	       if(type_desc->kind==SCALAR_TYPE_DESCRIPTOR){
		//FIXME assume: dataType in the variable name
 		  type_desc->properties.dataType  = q->rightSibling->dataType;
	       }else{
		//TODO: traverse once to compute the dim
			  AST_NODE* temp =
			  type_desc->properties.arrayProperties.dimension = 0;	//ASSIGN
			  type_desc->properties.arrayProperties.sizeInEachDimension; 
			  type_desc->properties.arrayProperties.elementType; //??
			  /*DADA*///Assume the size of each dimension is a constant
			  //ELSE IF it's an expression THEN we're going to have a very hard time
			  while(temp!=NULL){
			    int index = type_desc->properties.arrayProperties.dimension;
				type_desc->properties.arrayProperties.dimension++;				
				type_desc->properties.arrayProperties.sizeInEachDimension[index] = temp->semantic_value.const1->const_u.intval;
			  }
	       }
	       functionSig->parameterList->type=type_desc;
	       functionSig->parameterList->parameterName = q->semantic_value.identifierSemanticValue.identifierName;	    
 	   }
	   //TODO:IMPORTANT!: if parameterList != NULL
	   //cannot put it on the leftmost

	    p = p->rightSibling;
        }
    }

    SymbolAttribute* symbol_att = (SymbolAttribute*) malloc(sizeof(SymbolAttribute));
    symbol_att->attributeKind = FUNCTION_SIGNATURE;
    symbol_att->attr = functionSig;
    enterSymbol(function_name,symbol_att);
}


