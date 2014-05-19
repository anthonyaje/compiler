#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "symbolTable.h"
// This file is for reference only, you are not required to follow the implementation. //
// Yo
//u only need to check for errors stated in the hw4 document. //
//Assume write() is C-- buit-in function. read() is not.
//Assume write() can accept string float int
//
int g_anyErrorOccur = 0;

DATA_TYPE f_global_return_type;

DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2);
void processProgramNode(AST_NODE *programNode);
void processDeclarationNode(AST_NODE* declarationNode);
void declareIdList(AST_NODE* typeNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize);
void declareFunction(AST_NODE* returnTypeNode);
void processDeclDimList(AST_NODE* variableDeclDimList, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize);
void processTypeNode(AST_NODE* typeNode);
void processBlockNode(AST_NODE* blockNode,int OpenScope);
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
void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter,char* name);
void checkReturnStmt(AST_NODE* returnNode);
void processExprNode(AST_NODE* exprNode);  //aje: process the exp
void processVariableLValue(AST_NODE* idNode);
void processVariableRValue(AST_NODE* idNode);
void processConstValueNode(AST_NODE* constValueNode);
void getExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue); //aje: may be use in array
void evaluateExprValue(AST_NODE* exprNode,TypeDescriptor* outType); //aje: 
//additional functions
DATA_TYPE compareTool(char*);
int traverseExpr(AST_NODE* );


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
    /*g_anyErrorOccur = 1;
    printf("Error found in line %d\n", node1->linenumber);
    
    switch(errorMsgKind)
    {
    case TOO_FEW_ARGUMENTS:
	break;
    case TOO_MANY_ARGUMENTS:
	break;
    
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
    
    switch(errorMsgKind)
    {
        printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
        break;
    }
    
}


void semanticAnalysis(AST_NODE *root)
{
    processProgramNode(root->child);
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
 // printf("WAAA!! in  programNode\n");
  AST_NODE* p = programNode;
  //while(p!=NULL){
  if(p->nodeType == VARIABLE_DECL_LIST_NODE){
	processDeclarationNode(p->child);
	processDeclarationNode(p->rightSibling);
  }else{
     switch(p->nodeType){
       case DECLARATION_NODE:			//FUNCTION_DECL
	  processDeclarationNode(p);
          break;
       case VARIABLE_DECL_LIST_NODE:		//VARIABLE_DECL_LIST_NODE->child == VARIABLE_DECL
	  processDeclarationNode(p->child);
          break;
       default:
   	  printf("uncaught case1\n");
          printf("Error found in line %d\n", p->linenumber);
	  g_anyErrorOccur = 1;
     }
  }

}


void processDeclarationNode(AST_NODE* declarationNode)
{//recursive call to traverse the sibling
  //printf("WAAA! in processDeclarationNode();\n");
  if(declarationNode == NULL){ 
	return; 
  }
  else if(declarationNode->nodeType == VARIABLE_DECL_LIST_NODE){
     processProgramNode(declarationNode);
  }
  else {
     switch(declarationNode->semantic_value.declSemanticValue.kind){
        case VARIABLE_DECL :
  	    declareIdList(declarationNode, VARIABLE_ATTRIBUTE, 1);
            break;
        case  TYPE_DECL ://aje
	    processTypeNode(declarationNode);
            break;
        case FUNCTION_DECL:
            //printf("in processDeclNode-FUNCTION_DECL\n");
	    declareFunction(declarationNode);
            break;
        case FUNCTION_PARAMETER_DECL:
	   //Done in the function declaration
	   printf("declarationNode Err: FUNCTION_PARA_DECL. Should be done in the function decl");   
	    break;
        default:
   	    printf("uncaught case2\n"); 
	    printf("Error found in line %d\n", declarationNode->linenumber);
	          g_anyErrorOccur = 1;

   }
   processDeclarationNode(declarationNode->rightSibling);
 }

}


void processTypeNode(AST_NODE* idNodeAsType)
{//aje :dont need to traverse since the caller gonna do it
    AST_NODE* p = idNodeAsType->child;
    SymbolAttribute* symbol_att = (SymbolAttribute*) malloc(sizeof(SymbolAttribute));
    symbol_att->attributeKind = TYPE_ATTRIBUTE;
    TypeDescriptor* type_desc = (TypeDescriptor*) malloc(sizeof(TypeDescriptor));
    type_desc->kind = SCALAR_TYPE_DESCRIPTOR;
    
    type_desc->properties.dataType = compareTool(p->semantic_value.identifierSemanticValue.identifierName);
    symbol_att->attr.typeDescriptor = type_desc;

    p=p->rightSibling;
    while(p!=NULL){
    if(declaredLocally(p->semantic_value.identifierSemanticValue.identifierName)){
            printf("ID %s redeclared\n",p->semantic_value.identifierSemanticValue.identifierName);
            printf("Error found in line %d\n", p->linenumber);
             g_anyErrorOccur = 1;

    }

	enterSymbol(p->semantic_value.identifierSemanticValue.identifierName,symbol_att);
	p=p->rightSibling;
    }
}

void declareIdList(AST_NODE* declarationNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize)
{
 // printf("WAAA!! in declaredIdList()\n");
  AST_NODE* child = declarationNode->child;
  if(isVariableOrTypeAttribute == VARIABLE_ATTRIBUTE){
    DATA_TYPE var_type = compareTool(child->semantic_value.identifierSemanticValue.identifierName);
    if(var_type == ERROR_TYPE){
	     SymbolTableEntry* se = retrieveSymbol(child->semantic_value.identifierSemanticValue.identifierName);
            if(se != NULL){
	        var_type = se->attribute->attr.typeDescriptor->properties.dataType;
	    }
	    else{
	        printf("UNDEFINED type was used in line %d\n",child->linenumber);
		 g_anyErrorOccur = 1;

		return;
	    }
    }
  	AST_NODE* p = child->rightSibling;
        AST_NODE* q;
  	while(p!=NULL){
	    SymbolAttribute* symbol_att = (SymbolAttribute*) malloc(sizeof(SymbolAttribute));
	    symbol_att->attributeKind = isVariableOrTypeAttribute;
   	    TypeDescriptor* type_desc = (TypeDescriptor*) malloc(sizeof(TypeDescriptor));
	    type_desc->kind = SCALAR_TYPE_DESCRIPTOR;
	    type_desc->properties.dataType = var_type;
	    if(p->semantic_value.identifierSemanticValue.kind == ARRAY_ID){
	   	 //if array type then calculate dimension
	    	//printf("Ready to calculate array dim\n");
	    	q=p;
		p = p-> child;
		int dim = 0;
		if(traverseExpr(p) == 0){
		    //final_type = FLOAT_TYPE;
		    printf("array index must be an integer\n");
		    printf("Error found in line %d\n", p->linenumber);
		      g_anyErrorOccur = 1;

		}
		while(p != NULL){
			dim++;
			p = p->rightSibling; 
		}
		type_desc->kind = ARRAY_TYPE_DESCRIPTOR;
		type_desc->properties.arrayProperties.dimension = dim;
                p=q;
	    }
	    symbol_att->attr.typeDescriptor = type_desc;
	    //printf("Array dim calculation completed\n");
            //p=q;
            if(declaredLocally(p->semantic_value.identifierSemanticValue.identifierName)){
           	 printf("ID %s redeclared\n",p->semantic_value.identifierSemanticValue.identifierName);
            	 printf("Error found in line %d\n", p->linenumber);
	          g_anyErrorOccur = 1;

   	    }

  	    enterSymbol(p->semantic_value.identifierSemanticValue.identifierName,symbol_att);
  	    
	    //printf("Symbol added to symboltable\n");
	    p = p->rightSibling;
	}
  } else{
	//typedef
	DATA_TYPE var_type;
	if(strcmp(child->semantic_value.identifierSemanticValue.identifierName,"int")==0)
		var_type = INT_TYPE;
	else if(strcmp(child->semantic_value.identifierSemanticValue.identifierName,"float")==0)
		var_type = FLOAT_TYPE;
  	AST_NODE* p = child;
 	p = p->rightSibling;
  	while(p!=NULL){
	    SymbolAttribute* symbol_att = (SymbolAttribute*) malloc(sizeof(SymbolAttribute));
	    symbol_att->attributeKind = isVariableOrTypeAttribute;
   	    TypeDescriptor* type_desc = (TypeDescriptor*) malloc(sizeof(TypeDescriptor));
	    type_desc->kind = SCALAR_TYPE_DESCRIPTOR;
	    type_desc->properties.dataType = var_type;
	    symbol_att->attr.typeDescriptor = type_desc;
	    if(declaredLocally(p->semantic_value.identifierSemanticValue.identifierName)){
           	printf("ID %s redeclared\n",p->semantic_value.identifierSemanticValue.identifierName);
            	printf("Error found in line %d\n", p->linenumber);
	         g_anyErrorOccur = 1;
  
 	    }

	    enterSymbol(p->semantic_value.identifierSemanticValue.identifierName,symbol_att);
	    p = p->rightSibling;
	}
	
  }
}

void checkAssignOrExpr(AST_NODE* assignOrExprRelatedNode)
{
//printf("Wiii!! in checkAssignmenOrExpr()\n"); 
  //AST_NODE* p = assignOrExprRelatedNode->child;
  AST_NODE* p = assignOrExprRelatedNode->child;
  while(p!=NULL){
    if(p->nodeType==STMT_NODE){
      	checkAssignmentStmt(p);
    } 
    else if(p->nodeType==EXPR_NODE){
	processExprRelatedNode(p);
    }
    p = p->rightSibling;
  }
}

void checkWhileStmt(AST_NODE* whileNode)
{
    //DADA
    AST_NODE* p = whileNode->child;
    //evaluateExprValue(p);
    checkAssignOrExpr(p);
    p = p->rightSibling;
    processBlockNode(p,1); 
}


void checkForStmt(AST_NODE* forNode)
{
    //DADA
    AST_NODE* p = forNode->child;
    processGeneralNode(p);
    p = p->rightSibling;
    processGeneralNode(p);
    p = p->rightSibling;
    processGeneralNode(p);

    p = p->rightSibling;
    processBlockNode(p,1); 
}


void checkAssignmentStmt(AST_NODE* assignmentNode)
{
    //AJE
//    printf("in checkAssignment\n");
//printf("Wiii!! in checkAssignmenOrExpr()\n"); 
    AST_NODE* p = assignmentNode;
    //BONUS
    processVariableLValue(p->child);
    processExprRelatedNode(p->child->rightSibling);
}


void checkIfStmt(AST_NODE* ifNode)
{
    //DADA
    printf("in checkIfStmt\n");
    AST_NODE* p = ifNode;
    AST_NODE* q = ifNode->child;
    if(q!=NULL)
        processExprRelatedNode(q);
    p = p->rightSibling;
   printf("child is processed\n"); 
    while(p!=NULL){
        if(p->nodeType == BLOCK_NODE){
            processBlockNode(p,1);
        }
	else if(p->nodeType == STMT_NODE){
	    processStmtNode(p);
	    break;
	}
	else{
	    printf("Uncaught checkif case\n");
	   g_anyErrorOccur = 1;

	}
        p = p->rightSibling;
    }
    /*if(p!=NULL){
	//FIXME check if it is ELSEIF ELSE: block->stmt_if block->block 
	if(p->nodeType == STMT_NODE)
        checkIfStmt(p);
	else
	processBlockNode(p);
    }*/
   
}

void checkWriteFunction(AST_NODE* functionCallNode)
{
}

void checkFunctionCall(AST_NODE* functionCallNode)
{
    //DADA
    AST_NODE* p = functionCallNode -> child;
    char* name = p->semantic_value.identifierSemanticValue.identifierName;
    if(strcmp(name,"write") != 0){
	if(declaredLocally(name) == 0){
	    printf("ID %s undeclared\n",name);
	    printf("Error found in line %d\n", p->linenumber);
          g_anyErrorOccur = 1;

        }else
        checkParameterPassing(retrieveSymbol(name)->attribute->attr.functionSignature->parameterList, p->rightSibling,name);
    } 
    else if(strcmp(name,"write") == 0){
    	/*char a,b;
	char* c =  p->rightSibling->child->semantic_value.const1->const_u.sc;
	a = c[0];
	b = c[strlen(c)-1];
    	if( (a!='"') || (b!='"')){
	    printf("parameter to write function is not CONST_STRING_TYPE\n");
	    printf("Error found in line %d\n", p->rightSibling->child->linenumber);
	}
	*/     
    }
    

}

void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter,char* name)
{
    if((formalParameter == NULL) && (actualParameter->nodeType == NUL_NODE)){
 	//ok fine
    } else if((formalParameter != NULL) && (actualParameter->nodeType == NUL_NODE)){
	printf("too few arguments to function: %s\n",name);
	printf("Error found in line %d\n", actualParameter->linenumber);
          g_anyErrorOccur = 1;

    } else if((formalParameter == NULL) && (actualParameter->nodeType != NUL_NODE)){
	printf("too many arguments to function %s\n",name);
	printf("Error found in line %d\n", actualParameter->linenumber);
          g_anyErrorOccur = 1;

    } else {
	// may have too many or too few arguments
	AST_NODE* p = actualParameter->child;
	Parameter* q = formalParameter;
	int i =0;
	int line_num;
	while((p!=NULL) && (q!=NULL)){
	    TypeDescriptor temp_type;
	    SymbolTableEntry* entry=NULL; 
	    char* param_name;
	    line_num = p->linenumber;
	    int type_flag; //0=scalar
            if(p->nodeType == IDENTIFIER_NODE){
		param_name = p->semantic_value.identifierSemanticValue.identifierName;
	    	entry = retrieveSymbol(param_name);
	    	//printf("$%s retrieved\n",param_name);
	    	if(entry!=NULL){
		    if(entry->attribute->attr.typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR)
		        type_flag = 0;
		    else
		        type_flag = 1;
	        }else{
		printf("ID %s undeclared\n",p->semantic_value.identifierSemanticValue.identifierName);
	        printf("Error found in line %d\n", p->linenumber);
	          g_anyErrorOccur = 1;

		    p = p->rightSibling;
		    q = q->next;
		    continue;
		}
	    } 
  	    else if(p->nodeType == CONST_VALUE_NODE){
		param_name = "Constant";
		type_flag = 0;
	    } 
	    if(p->nodeType == EXPR_NODE){ 
		//ASSUME: expr return a SCALAR_TYPE
		//evaluateExprValue(p->nodeType, &temp_type);
	        if(q->type->kind != SCALAR_TYPE_DESCRIPTOR){
		    printf("Scalar <EXPRESSION> passed to array\n");
	    	    printf("Error found in line %d\n", p->linenumber);
	          g_anyErrorOccur = 1;

		}
		else{
		    //FIXME
		    checkAssignOrExpr(p);
		}
	        
	    }
	    else if((type_flag==0)&&(q->type->kind == ARRAY_TYPE_DESCRIPTOR)){
		    printf("Scalar %s passed to array\n",param_name);
	            printf("Error found in line %d\n", p->linenumber);
	          g_anyErrorOccur = 1;

	    }   
	    else if((type_flag==1)&&(q->type->kind == SCALAR_TYPE_DESCRIPTOR)){
		    //printf("IN!!!!\n");
		    printf("Array %s passed to scalar\n",param_name);
	            printf("Error found in line %d\n", p->linenumber);
	          g_anyErrorOccur = 1;

	    }
	    p = p->rightSibling;
	    q = q->next;
	}
        if((q == NULL) && (p != NULL)){
	    printf("too many arguments to function: %s\n",name);
	    printf("Error found in line %d\n", p->linenumber);
          g_anyErrorOccur = 1;

        }
	else if((q != NULL) && (p == NULL)){
	    printf("too few arguments to function: %s\n",name);
	    printf("Error found in line %d\n", line_num);
          g_anyErrorOccur = 1;

        }
    }
    	
}


void processExprRelatedNode(AST_NODE* exprRelatedNode)
{
    AST_NODE* p = exprRelatedNode;
    while(p!=NULL){
	if(p->nodeType == IDENTIFIER_NODE){
	    /*if(declaredLocally(p->semantic_value.identifierSemanticValue.identifierName)==0){
		printf("ID %s undeclared\n",p->semantic_value.identifierSemanticValue.identifierName);
	        printf("Error found in line %d\n", p->linenumber);
	    }
	    */
	    processVariableLValue(p);
	}
        else if(p->nodeType == EXPR_NODE){
	    processExprNode(p);
        }else if(p->nodeType == STMT_NODE){
	    processStmtNode(p);
	    break;
	}else if(p->nodeType == NONEMPTY_ASSIGN_EXPR_LIST_NODE){
	    checkAssignOrExpr(p->child);
	}
	else if(p->nodeType == NONEMPTY_RELOP_EXPR_LIST_NODE){
	    processExprRelatedNode(p->child);
	}
	else if(p->nodeType == BLOCK_NODE){
	    processBlockNode(p,1);
	}
	else if(p->nodeType == NUL_NODE){
	    return;
        }
	else{
	    printf("my type %d",p->nodeType);
	    printf("uncaught case in processExprRelatedNode\n");
          g_anyErrorOccur = 1;

	}

        p = p->rightSibling;
    }
}

void getExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue)
{//traverse the expression node to the children and siblings
     AST_NODE* p = exprOrConstNode->child;
     int final_int_type = 1;
     while(p != NULL){
        if(p->nodeType == CONST_VALUE_NODE){
	    if(p->semantic_value.const1->const_type != INTEGERC){
	        printf("Array index must be an integer\n");
	        printf("Error found in line %d\n", p->linenumber);
	          g_anyErrorOccur = 1;

	    }
        } 
        else if(p->nodeType == EXPR_NODE){
            //dig 
	   // evaluateExprValue(p, NULL);
	   AST_NODE* q = p;
           while(q != NULL){
              //if(q->child->nodeType == EXPR_NODE){
                  getExprOrConstValue(q->child,NULL,NULL);
              //}else if(){
           
             // }
              q = q->rightSibling;
           }


	}else if(p->nodeType == IDENTIFIER_NODE){
	    if(declaredLocally(p->semantic_value.identifierSemanticValue.identifierName)==0){
		printf("ID %s undeclared\n",p->semantic_value.identifierSemanticValue.identifierName);	
		printf("Error found in line %d\n", p->linenumber);
	          g_anyErrorOccur = 1;

            }else if(p->dataType != INT_TYPE){
		printf("拍謝.. only integer\n");
		printf("Error found in line %d\n", p->linenumber);
	          g_anyErrorOccur = 1;

            }
        }

	p = p->rightSibling;
     }
}

void evaluateExprValue(AST_NODE* exprNode, TypeDescriptor* outType)
{
	//unused by our assumption 
	/*
	AST_NODE* p = exprNode;
	while(p != NULL){
	  if(p->child->nodeType == EXPR_NODE){
		getExprOrConstValue(p->child);
           }else if(){
	   	
	   } 
 	   p->rightSibling;
	}*/
	
}


void processExprNode(AST_NODE* exprNode)
{
printf("IN processExprNode()\n");
    AST_NODE* p = exprNode->child;
    while(p!=NULL){
        if(p->nodeType == IDENTIFIER_NODE)
	    processVariableLValue(p);
            /*if(declaredLocally(p->semantic_value.identifierSemanticValue.identifierName)==0){
                printf("ID %s undeclared",p->semantic_value.identifierSemanticValue.identifierName);
		printf("Error found in line %d\n", p->linenumber);
            }*/
        else if(p->nodeType == EXPR_NODE){
            processExprNode(p);
        }

        p = p->rightSibling;
    }
printf("EXIT processExprNode()\n");

}


void processVariableLValue(AST_NODE* idNode)
{ 
    //BONUS
    char* name = (idNode->semantic_value.identifierSemanticValue.identifierName);
    if(declaredLocally(name) == 0){
 	printf("ID %s undeclared\n",name);
	printf("Error found in line %d\n", idNode->linenumber);
          g_anyErrorOccur = 1;

	return;
    }
    int formal_dim = 0;
    if(retrieveSymbol(name)->attribute->attr.typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR){
	formal_dim = retrieveSymbol(name)->attribute->attr.typeDescriptor->properties.arrayProperties.dimension;
        if(idNode->semantic_value.identifierSemanticValue.kind == ARRAY_ID){
    	   int dim = 0;
	   AST_NODE* p = idNode->child;
 	   if(traverseExpr(p) == 0){
	      //makesure expression is an int
 	      printf("array index must be an integer\n");
	      printf("Error found in line %d\n", idNode->linenumber);
	          g_anyErrorOccur = 1;

	   }
	   while(p != NULL){
		dim++;
		p = p->rightSibling;
	   }
 	   if(dim != formal_dim){
	        printf("Incompatible array dimension\n");
	        printf("Error found in line %d\n", idNode->linenumber);
	          g_anyErrorOccur = 1;

	   }
        }
	else {
	 //   printf();
	}
	
    }else{
        if(idNode->semantic_value.identifierSemanticValue.kind == ARRAY_ID){
	    printf("$%s is not an array type",name);
	    printf("Error found in line %d\n", idNode->linenumber);
          g_anyErrorOccur = 1;

        }
    }
}

void processVariableRValue(AST_NODE* idNode)
{ //DONE in the getExprOrConstValue for array_index
}


void processConstValueNode(AST_NODE* constValueNode)
{
  //seem useless
}

int traverseExpr(AST_NODE* p){
    if(p->nodeType == EXPR_NODE){
        if(p->rightSibling != NULL){
	    return traverseExpr(p->rightSibling);
	}
	if(p->child != NULL)
	    return traverseExpr(p->child);	
    }
    else if(p->nodeType == CONST_VALUE_NODE){
	if(p->semantic_value.const1->const_type == FLOATC){
	    return 0;
	} 
	else{
	    if(p->rightSibling != NULL){
	        return traverseExpr(p->rightSibling);
	    }
	    else{
	        return 1;
	    }
	}
    }
    else if(p->nodeType == IDENTIFIER_NODE){
	if(retrieveSymbol(p->semantic_value.identifierSemanticValue.identifierName)->attribute->attr.typeDescriptor->properties.dataType == FLOAT_TYPE){
	    return 0;
	} 
 	else{
 	    if(p->rightSibling != NULL){
		return traverseExpr(p->rightSibling);
	    } else{
		return 1;
	    }
	}
    }
    //DADA
    else if(p->nodeType == STMT_NODE){
	if(p->semantic_value.stmtSemanticValue.kind == FUNCTION_CALL_STMT){
	    AST_NODE* q = p->child;//q est un identifier node
	    //verifier le return type de la fonction
	    char* funcName = q->semantic_value.identifierSemanticValue.identifierName;
	    DATA_TYPE returnType;
	    if(declaredLocally(funcName)){
	    	returnType = retrieveSymbol(funcName)->attribute->attr.functionSignature->returnType;
		if(returnType == INT_TYPE)
		    return 1;
		else return 0;
	    }else{
		printf("ID %s undeclared\n",funcName);
		printf("Error found in line %d\n", q->linenumber);
	          g_anyErrorOccur = 1;

	    }
	}
	else{
	    printf("uncaught statement node in checkif \n");
          g_anyErrorOccur = 1;

	}
    }
    else{
	printf("traverseExpr(): uncaught if case\n");
          g_anyErrorOccur = 1;

    }
}

void checkReturnStmt(AST_NODE* returnNode)
{
    //Assume each function must "return", otherwise no error detected
    printf("in CheckReturnStmt()\n");
    DATA_TYPE final_type;
    AST_NODE* p = returnNode->child;
    switch(p->nodeType){
	case IDENTIFIER_NODE:
	    final_type = retrieveSymbol(p->semantic_value.identifierSemanticValue.identifierName)->attribute->attr.typeDescriptor->properties.dataType;
            break;
	case CONST_VALUE_NODE:
	   if(p->semantic_value.const1->const_type == INTEGERC)
		final_type = INT_TYPE;
	   else if(p->semantic_value.const1->const_type == FLOATC)
		final_type = FLOAT_TYPE;
	   else
		final_type = CONST_STRING_TYPE; 
	   break;
	case EXPR_NODE:
	    final_type = INT_TYPE;
	   /* while(p != NULL){
		
		p = p->rightSibling;	
	    }
	   */
 	    if(traverseExpr(p) == 0){
		final_type = FLOAT_TYPE;
	    }
	    break;
	case NUL_NODE:
	   final_type = VOID_TYPE; 
	   break;
	default:
	    printf("checkReturnStmt(): default case\n");
    }

    if(final_type != f_global_return_type){
  	    printf("incompatible return type.\n");
  	    printf("Warning in line %d\n", returnNode->linenumber);
          g_anyErrorOccur = 1;

    }  
    printf("EXIT CheckReturnStmt()\n");
}

void processBlockNode(AST_NODE* blockNode,int OpenScope)
{
   // printf("in processBlockNode\n");
    if(OpenScope)
    	openScope();
    AST_NODE* p = blockNode->child;
    while(p != NULL ){
       switch(p->nodeType){
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
		printf("Error found in line %d\n", p->linenumber);
          g_anyErrorOccur = 1;

      }
       p = p->rightSibling;
    }
    closeScope();
}


void processStmtNode(AST_NODE* stmtNode)
{
  printf("in processStmtNode\n");
  AST_NODE* p = stmtNode;
  while(p!=NULL){
    if(p->nodeType == NUL_NODE){ return; } 
    else if(p->nodeType == BLOCK_NODE){ return; } 
    switch(p->semantic_value.stmtSemanticValue.kind){
        case RETURN_STMT:
	        checkReturnStmt(p);	
        	break;
	case FUNCTION_CALL_STMT:
		checkFunctionCall(p);
		break;
	case WHILE_STMT:
		checkWhileStmt(p);
		break;
 	case FOR_STMT:
		checkForStmt(p);
		break;
 	case ASSIGN_STMT:
		checkAssignmentStmt(p); 
		break;
 	case IF_STMT:		//aje
		checkIfStmt(p);
		break;
        default:
		printf("unhandled stmnt kind\n");
		printf("Error found in line %d\n", p->linenumber);
          g_anyErrorOccur = 1;

    }
    p = p->rightSibling;
  }
}


void processGeneralNode(AST_NODE *node)
{
    switch(node->nodeType){
        case NONEMPTY_ASSIGN_EXPR_LIST_NODE:
	    //check the assignment
            checkAssignOrExpr(node->child);
            break;
        case NONEMPTY_RELOP_EXPR_LIST_NODE:
	    //check the expression
            processExprRelatedNode(node->child);
	    break;
    }
}

void processDeclDimList(AST_NODE* idNode, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize)
{
  //seems like integrated withe the declareFunction  
}

DATA_TYPE compareTool(char* p){
DATA_TYPE final_type;
if(strcmp(p,"int")==0)
    final_type = INT_TYPE;
else if(strcmp(p,"float")==0)
    final_type = FLOAT_TYPE;
else if(strcmp(p,"void")==0)
    final_type = VOID_TYPE;
else if(strcmp(p,"string")==0)
    final_type = CONST_STRING_TYPE;
else if(strcmp(p,"int*")==0)
    final_type = INT_PTR_TYPE;
else if(strcmp(p,"float*")==0)
    final_type = FLOAT_PTR_TYPE;
else 
    final_type = ERROR_TYPE;
return final_type;
}


void declareFunction(AST_NODE* declarationNode)
{
    AST_NODE* p = declarationNode->child;   
    FunctionSignature* functionSig;
    functionSig = (FunctionSignature*) malloc(sizeof(FunctionSignature));
    functionSig->parameterList = NULL;
    functionSig->parametersCount = 0;
    DATA_TYPE var_type = compareTool(p->semantic_value.identifierSemanticValue.identifierName);
    if(var_type == ERROR_TYPE){
	     SymbolTableEntry* se = retrieveSymbol(p->semantic_value.identifierSemanticValue.identifierName);
            if(se != NULL){
	        var_type = se->attribute->attr.typeDescriptor->properties.dataType;
	    }
	    else{
	        printf("UNDEFINED type was used in line %d\n",p->linenumber);
          g_anyErrorOccur = 1;

		return;
	    }
    }
    f_global_return_type = functionSig->returnType = var_type;
    
    p = p->rightSibling;
    char* function_name = p->semantic_value.identifierSemanticValue.identifierName;

    p = p->rightSibling;
    AST_NODE* p_to_block = p;
    openScope();
    if(p->child != NULL){//if the function has at least one parameter
	p = p->child;
	Parameter* para_this = NULL; 
	//para_this = (Parameter*) malloc(sizeof(Parameter)); 	    
	while(p!=NULL){//while there is an unvisited parameter
           AST_NODE* q = p->child;//q is the type name
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
		para_this->next = (Parameter*) malloc(sizeof(Parameter));
		para_this = para_this->next;
		para_this->next = NULL;
	   }
	    para_this->type=type_desc;
	    //DADA
	    para_this->parameterName = q->rightSibling->semantic_value.identifierSemanticValue.identifierName;	    
	    SymbolAttribute* param_attr = (SymbolAttribute*)malloc(sizeof(SymbolAttribute));
	    param_attr->attributeKind = VARIABLE_ATTRIBUTE;
	    param_attr->attr.typeDescriptor = type_desc;
	    if(declaredLocally(para_this->parameterName)){
                printf("ID %s redeclared\n",para_this->parameterName);
                printf("Error found in line %d\n", p_to_block->linenumber);
	    }
	    enterSymbol(para_this->parameterName,param_attr);
	    p = p->rightSibling;
        }
    }

    SymbolAttribute* symbol_att = (SymbolAttribute*) malloc(sizeof(SymbolAttribute));
    symbol_att->attributeKind = FUNCTION_SIGNATURE;
    symbol_att->attr.functionSignature = functionSig;
    minusScope();
    if(declaredLocally(function_name)){
            printf("ID %s redeclared\n",function_name);
            printf("Error found in line %d\n", p_to_block->linenumber);
    }
    enterSymbol(function_name,symbol_att);
    plusScope();
    //printf("calling processBlockNode\n");
    processBlockNode(p_to_block->rightSibling,0);
}
