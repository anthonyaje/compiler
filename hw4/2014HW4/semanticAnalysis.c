#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "symbolTable.h"
// This file is for reference only, you are not required to follow the implementation. //
// You only need to check for errors stated in the hw4 document. //
int g_anyErrorOccur = 0;

DATA_TYPE f_global_return_type;

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
void processExprRelatedNode(AST_NODE* exprRelatedNode);  //Related?? or relative operator
void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter);
void checkReturnStmt(AST_NODE* returnNode);
void processExprNode(AST_NODE* exprNode);  //aje: process the exp
void processVariableLValue(AST_NODE* idNode);
void processVariableRValue(AST_NODE* idNode);
void processConstValueNode(AST_NODE* constValueNode);
void getExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue); //aje: may be use in array
void evaluateExprValue(AST_NODE* exprNode); //aje: 


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
  switch(child->declarationNode->semantic_value.declSemanticValue.kind){
      case DECLARATION_NODE:			//FUNCTION_DECL
	  processDeclarationNode(child);
          break;
      case VARIABLE_DECL_LIST_NODE:		//VARIABLE_DECL_LIST_NODE->child == VARIABLE_DECL
	  processDeclarationNode(childi->child);
          break;
      default:
   	  printf("uncaught case\n"); 
  }
}


void processDeclarationNode(AST_NODE* declarationNode)
{//recursive call to traverse the sibling
  if(declarationNode == NULL){ return; }
  else{
     AST_NODE* child = declarationNode->child;
     switch(declarationNode->semantic_value.declSemanticValue.kind){
        case VARIABLE_DECL :
  	    declareIdList(declarationNode, VARIABLE_ATTRIBUTE, 1);
            break;
        case  TYPE_DECL ://aje
	    processTypeNode(declarationNode);
            break;
        case FUNCTION_DECL:
	    declareFunction(declarationNode);
            break;
        case FUNCTION_PARAMETER_DECL:
	   //Done in the function declaration
	   prinf("declarationNode Err: FUNCTION_PARA_DECL. Should be done in the function decl")
            break;
        default:
   	    printf("uncaught case\n"); 
   }
   processDeclarationNode(child->rightSibling);
 }

}


void processTypeNode(AST_NODE* idNodeAsType)
{//aje :dont need to traverse since the caller gonna do it
    AST_NODE* p = idNodeAsType->child;
    SymbolAttribute* symbol_att = (SymbolAttribute*) malloc(sizeof(SymbolAttribute));
    symbol_att->attributeKind = TYPE_ATTRIBUTE;
    TypeDescriptor* type_desc = (TypeDescriptor*) malloc(sizeof(TypeDescriptor));
    type_desc->kind = SCALAR_TYPE_DESCRIPTOR;//FIXME
    type_desc->properties = p->dataType;
    symbol_att->attr = type_desc;

    p=p->rightSibling;
    while(p!=NULL){
	enterSymbol(p->semantic_value.identifierSemanticValue.identifierName,symbol_att);
	p=p->rightSibling;
    }
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
    //DADA
    AST_NODE* p = whileNode->child;
    evaluateExprValue(p);
    p = p->rightSibling;
    processBlockNode(p); 
}


void checkForStmt(AST_NODE* forNode)
{
<<<<<<< HEAD
	//DADA
    AST_NODE* p = forNode->child;
    evaluateExprValue(p);
    p = p->rightSibling;
    processBlockNode(p); 
=======
    
>>>>>>> ce8d3e9a348a56bf04e0d830cca2710187563bea
}


void checkAssignmentStmt(AST_NODE* assignmentNode)
{
    //AJE
    AST_NODE* p = assignmentNode->child;
    char* name = (p->semantic_value.identifierSemanticValue.identifierName);
    if(declaredLocally(name) 
	== 0){
 	printf("ID %s undeclared",name);
    }
    //FIXME check which one to use: evaluateExprValue processExprNode processExprRelatedNode getExprOrConstValue
    evaluateExprValue(p->rightSibling); 
}


void checkIfStmt(AST_NODE* ifNode)
{
    //AJE
    AST_NODE* p = ifNode->child;
    evaluateExprValue(p);
    p = p->rightSibling;
    while(p!=NULL){
	//FIXME check if it is ELSEIF ELSE: block->stmt_if block->block 
	processBlockNode(p);
	p = p->rightSibling;
    }
   
}

void checkWriteFunction(AST_NODE* functionCallNode)
{
}

void checkFunctionCall(AST_NODE* functionCallNode)
{
	//DADA
    AST_NODE* p = functionCallNode -> child;
    char name[] = p->semantic_value->identifierSemanticValue->identifierName;
    if(strcmp(name,"write") != 0){
		if(declaredLocally(name) == 0){
		    printf("ID %s undeclared",name);
	    }else{
		    checkParameterPassing(retrieveSymbol(name)->attribute->attr.functionSignature->parameterList, p->child);
	    }
    }
}

void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter)
{
	//DADA
	
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
	if(returnNode->child->dataType == f_global_return_type)
	    printf("incompatible return type.\n");
}

void processBlockNode(AST_NODE* blockNode)
{
    
    AST_NODE* p = blockNode->child;
    while(p != NULL ){
       switch(p->child->semantic_value.kind){
	   case STMT_LIST_NODE:
		processStmtNode(p->child);
		break;
	// case DECLARATION_NODE:
	//	processDeclarationNode(p->child);
	//	break;
	   case VARIABLE_DECL_LIST_NODE:
		processDeclarationNode(p->child);
		break;
	   default:
	        printf("blocknode's child case undefined\n");
       }
       p = p->rightSibling;
    }
}


void processStmtNode(AST_NODE* stmtNode)
{
  AST_NODE* p = stmtNode->child;
  while(p!=NULL){ 
    switch(stmtNode->semantic_value.kind){
        case RETURN_STMT:
		processStmtNode(p);
        	break;
	case FUNCTION_CALL_STMT:
		checkFunctionCall(p);//TODO
		break;
	case WHILE_STMT:
		checkWhileStmt(p);//TODO
		break;
 	case FOR_STMT:
		checkForStmt(p);//TODO
		break;
 	case ASSIGN_STMT:
		checkAssignmentStmt(p); //aje trying
		break;
 	case IF_STMT:		//aje
		checkIfStmt(p);
		break;
        default:
		printf("unhandled stmnt kind\n");
    }
    p = p->rightSibling;
  }
}


void processGeneralNode(AST_NODE *node)
{
    switch(node->semantic_value.kind){
        case NONEMPTY_ASSIGN_EXPR_LIST_NODE:
	    //TODO:check the assignment
            break;
        case NONEMPTY_RELOP_EXPR_LIST_NODE:
	    //TODO: check the expression

	    break;
    }
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
    f_global_return_type = functionSig->returnType = p->DATA_TYPE;
    
    p = p->rightSibling;
    char* function_name = p->semantic_value.identifierSemanticValue.identifierName;

    p = p->rightSibling;
    AST_NODE* p_to_block = p;
    
    if(p->child != NULL){//if the function has at least one parameter
	p = p->child;
	Parameter* para_this = NULL: 
	while(p!=NULL){//while there is an unvisited parameter
           AST_NODE* q = p->child;
	   functionSig->parametersCount++;

       	   TypeDescriptor* type_desc = (TypeDescriptor*) malloc(sizeof(TypeDescriptor));
	   type_desc->kind = q->rightSibling->semantic_value.identifierSemanticValue.kind==NORMAL_ID?SCALAR_TYPE_DESCRIPTOR:ARRAY_TYPE_DESCRIPTOR;
	   if(type_desc->kind==SCALAR_TYPE_DESCRIPTOR){
 	      type_desc->properties.dataType  = q->dataType;
	   }else{
	   //traverse once to compute the dim
		  AST_NODE* temp = q->rightSibling->child;
		  type_desc->properties.arrayProperties.dimension = 0;	//ASSIGN
		  //type_desc->properties.arrayProperties.sizeInEachDimension; 
		  type_desc->properties.arrayProperties.elementType = q->dataType; //??
		  while(temp!=NULL){
			type_desc->properties.arrayProperties.dimension++;
			temp = temp->rightSibling;				
		  }
	    }
           if(functionSig->parameterList == NULL){
	       functionSig->parameterList = (Parameter*) malloc(sizeof(Parameter)); 	    
	       functionSig->parameterList->next=NULL;
	       para_this = functionSig->parameterList; 
 	   }else{
	        para_this->next= (Parameter*) malloc(sizeof(Parameter)); 	    
		para_this->next->next = NULL;
		para_this = para_this->next;
	   }
	    functionSig->parameterList->type=type_desc;
	    functionSig->parameterList->parameterName = q->semantic_value.identifierSemanticValue.identifierName;	    
	    
	    p = p->rightSibling;
        }
    }

    SymbolAttribute* symbol_att = (SymbolAttribute*) malloc(sizeof(SymbolAttribute));
    symbol_att->attributeKind = FUNCTION_SIGNATURE;
    symbol_att->attr = functionSig;
    enterSymbol(function_name,symbol_att);

    processBlockNode(p_to_block->rightSibling);
    
}



