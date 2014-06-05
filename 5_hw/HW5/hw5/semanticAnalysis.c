#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"
#include "symbolTable.h"
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
int checkAssignOrExpr(AST_NODE* assignOrExprRelatedNode);
void checkWhileStmt(AST_NODE* whileNode);
void checkForStmt(AST_NODE* forNode);
int checkAssignmentStmt(AST_NODE* assignmentNode);
void checkIfStmt(AST_NODE* ifNode);
int checkWriteFunction(AST_NODE* functionCallNode);
void checkReadFunction(AST_NODE* functionCallNode);
void checkFunctionCall(AST_NODE* functionCallNode);
void processExprRelatedNode(AST_NODE* exprRelatedNode);
void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter);
void checkReturnStmt(AST_NODE* returnNode);
void processExprNode(AST_NODE* exprNode);
void processVariableLValue(AST_NODE* idNode);
//void processVariableRValue(AST_NODE* idNode);
int processVariableRValue(AST_NODE* idNode);
int processConstValueNode(AST_NODE* constValueNode);
void getExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue);
void evaluateExprValue(AST_NODE* exprNode);

//code gen

void write_prolog(char* label);
void write_epilog(char* label);
int getreg();

FILE* asm_out;
int frame_size=0;
int reg[15]={};
int if_num = 0;
int else_num = 0;
int exit_num = 0;
int while_num = 0;
int while_exit_num = 0;

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

//CODE Generation
void write_prolog(char* label){
    fprintf(asm_out,"%s:\n# prologue sequence\
\n	sw	$ra, 0($sp)\
\n	sw	$fp, -4($sp)\
\n	add	$fp, $sp, -4\
\n	add	$sp, $sp, -8\
\n	lw	$2, _framesize_of_%s\
\n	sub	$sp,$sp,$2\
\n	sw	$4,48($sp)\
\n	sw	$5,44($sp)\
\n	sw	$6,40($sp)\
\n	sw	$7,36($sp)\
\n	sw	$8,32($sp)\
\n	sw	$9,28($sp)\
\n	sw	$10,24($sp)\
\n	sw	$11,20($sp)\
\n	sw	$12,16($sp)\
\n	sw	$13,12($sp)\
\n	sw	$14,8($sp)\
\n	sw	$15,4($sp)\
\n	sw	$16,52($sp)\
\n	sw	$17,56($sp)\
\n	sw	$18,60($sp)\
\n	sw	$19,64($sp)\
\n	sw	$20,68($sp)\
\n	sw	$21,72($sp)\
\n	sw	$22,76($sp)\
\n	sw	$23,80($sp)\
\n	sw	$24,84($sp)\
\n	sw	$25,88($sp)\
     \n",label,label);

}


void write_epilog(char* label){
    fprintf(asm_out,"# epilogue sequence\n\
_end_%s:\n\
	lw	$8,32($sp)\n\
	lw	$9,28($sp)\n\
	lw	$10,24($sp)\n\
	lw	$11,20($sp)\n\
	lw	$12,16($sp)\n\
	lw	$13,12($sp)\n\
	lw	$14,8($sp)\n\
	lw	$15,4($sp)\
\n	sw	$16,52($sp)\
\n	sw	$17,56($sp)\
\n	sw	$18,60($sp)\
\n	sw	$19,64($sp)\
\n	sw	$20,68($sp)\
\n	sw	$21,72($sp)\
\n	sw	$22,76($sp)\
\n	sw	$23,80($sp)\
\n	sw	$24,84($sp)\
\n	sw	$25,88($sp)\
\n	sw	$4,48($sp)\
\n	sw	$5,44($sp)\
\n	sw	$6,40($sp)\
\n	sw	$7,36($sp)\n\
	lw	$ra, 4($fp)\n\
	add	$sp, $fp, 4\n\ 
	lw	$fp, 0($fp)\n\ 
	jr	$ra\n\
.data \n\
_framesize_of_%s: .word %d\n\
.data\n\
.text\n\
     ",label,label,frame_size);
}

int getreg(){


}

void printErrorMsgSpecial(AST_NODE* node1, char* name2, ErrorMsgKind errorMsgKind)
{
    g_anyErrorOccur = 1;
    printf("Error found in line %d\n", node1->linenumber);
    switch(errorMsgKind)
    {
    case PASS_ARRAY_TO_SCALAR:
        printf("Array \'%s\' passed to scalar parameter \'%s\'.\n",
            node1->semantic_value.identifierSemanticValue.identifierName,
            name2);
        break;
    case PASS_SCALAR_TO_ARRAY:
        printf("Scalar \'%s\' passed to array parameter \'%s\'.\n",
            node1->semantic_value.identifierSemanticValue.identifierName,
            name2);
        break;
    default:
        printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
        break;
    }
}


void printErrorMsg(AST_NODE* node, ErrorMsgKind errorMsgKind)
{
    g_anyErrorOccur = 1;
    printf("Error found in line %d\n", node->linenumber);
    switch(errorMsgKind)
    {
    case SYMBOL_IS_NOT_TYPE:
        printf("ID \'%s\' is not a type name.\n",
            node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case SYMBOL_REDECLARE:
        printf("ID \'%s\' redeclared.\n", 
            node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case SYMBOL_UNDECLARED:
        printf("ID \'%s\' undeclared.\n", 
            node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case NOT_FUNCTION_NAME:
        printf("ID \'%s\' is not a function.\n", 
            node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case TRY_TO_INIT_ARRAY:
        printf("Cannot initialize array \'%s\'.\n",
            node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case EXCESSIVE_ARRAY_DIM_DECLARATION:
        printf("ID \'%s\' array dimension cannot be greater than %d\n",
            node->semantic_value.identifierSemanticValue.identifierName,
            MAX_ARRAY_DIMENSION);
        break;
    case RETURN_ARRAY:
        printf("Function \'%s\' cannot return array.\n",
            node->rightSibling->semantic_value.identifierSemanticValue.identifierName);
        break;
    case VOID_VARIABLE:
        printf("Type \'%s\' cannot be a variable's type.\n",
            node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case TYPEDEF_VOID_ARRAY:
        printf("Declaration of \'%s\' as array of voids.\n",
            node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case PARAMETER_TYPE_UNMATCH:
        printf("Parameter is incompatible with parameter type.\n");
        break;
    case TOO_FEW_ARGUMENTS:
        printf("too few arguments to function \'%s\'.\n",
            node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case TOO_MANY_ARGUMENTS:
        printf("too many arguments to function \'%s\'.\n",
            node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case RETURN_TYPE_UNMATCH:
        printf("Incompatible return type.\n");
        break;
    case INCOMPATIBLE_ARRAY_DIMENSION:
        printf("Incompatible array dimensions.\n");
        break;
    case NOT_ASSIGNABLE:
        printf("ID \'%s\' is not assignable.\n",
            node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case NOT_ARRAY:
        printf("ID \'%s\' is not array.\n",
            node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case IS_TYPE_NOT_VARIABLE:
        printf("ID \'%s\' is a type, not a variable's name.\n",
            node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case IS_FUNCTION_NOT_VARIABLE:
        printf("ID \'%s\' is a function, not a variable's name.\n",
            node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case STRING_OPERATION:
        printf("String operation is unsupported.\n");
        break;
    case ARRAY_SIZE_NOT_INT:
        printf("Size of array \'%s\' has non-integer type.\n",
            node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case ARRAY_SIZE_NEGATIVE:
        printf("Size of array \'%s\' is negative.\n",
            node->semantic_value.identifierSemanticValue.identifierName);
        break;
    case ARRAY_SUBSCRIPT_NOT_INT:
        printf("Array subscript is not an integer.\n");
        break;
    default:
        printf("Unhandled case in void printErrorMsg(AST_NODE* node, ERROR_MSG_KIND* errorMsgKind)\n");
        break;
    }
    return;
}


void semanticAnalysis(AST_NODE *root)
{
    asm_out = fopen("code_gen.asm","w");
    processProgramNode(root);
    fclose(asm_out);
    return;
}


DATA_TYPE getBiggerType(DATA_TYPE dataType1, DATA_TYPE dataType2)
{
    if(dataType1 == FLOAT_TYPE || dataType2 == FLOAT_TYPE)
    {
        return FLOAT_TYPE;
    }
    else
    {
        return INT_TYPE;
    }
}


void processProgramNode(AST_NODE *programNode)
{
    AST_NODE *traverseDeclaration = programNode->child;
    while(traverseDeclaration)
    {
        if(traverseDeclaration->nodeType == VARIABLE_DECL_LIST_NODE)
        {
            processGeneralNode(traverseDeclaration);
        }
        else
        {
            //function declaration
            processDeclarationNode(traverseDeclaration);
        }

        
        if(traverseDeclaration->dataType == ERROR_TYPE)
        {
            programNode->dataType = ERROR_TYPE;
        }

        traverseDeclaration = traverseDeclaration->rightSibling;
    }
    return;
}

void processDeclarationNode(AST_NODE* declarationNode)
{
    AST_NODE *typeNode = declarationNode->child;
    processTypeNode(typeNode);
    if(typeNode->dataType == ERROR_TYPE)
    {
        declarationNode->dataType = ERROR_TYPE;
        return;
    }
    
    switch(declarationNode->semantic_value.declSemanticValue.kind)
    {
    case VARIABLE_DECL:
        declareIdList(declarationNode, VARIABLE_ATTRIBUTE, 0);
        break;
    case TYPE_DECL:
        declareIdList(declarationNode, TYPE_ATTRIBUTE, 0);
        break;
    case FUNCTION_DECL:
        declareFunction(declarationNode);
        break;
    case FUNCTION_PARAMETER_DECL:
        declareIdList(declarationNode, VARIABLE_ATTRIBUTE, 1);
        break;
    }
    return;
}


void processTypeNode(AST_NODE* idNodeAsType)
{
    SymbolTableEntry* symbolTableEntry = retrieveSymbol(idNodeAsType->semantic_value.identifierSemanticValue.identifierName);
    if((symbolTableEntry == NULL) || (symbolTableEntry->attribute->attributeKind != TYPE_ATTRIBUTE))
    {
        printErrorMsg(idNodeAsType, SYMBOL_IS_NOT_TYPE);
        idNodeAsType->dataType = ERROR_TYPE;
    }
    else
    {
        idNodeAsType->semantic_value.identifierSemanticValue.symbolTableEntry = symbolTableEntry;
        
        switch(symbolTableEntry->attribute->attr.typeDescriptor->kind)
        {
        case SCALAR_TYPE_DESCRIPTOR:
            idNodeAsType->dataType = symbolTableEntry->attribute->attr.typeDescriptor->properties.dataType;
            break;
        case ARRAY_TYPE_DESCRIPTOR:
            idNodeAsType->dataType = symbolTableEntry->attribute->attr.typeDescriptor->properties.arrayProperties.elementType;
            break;
        }
        //*/
    }
}


void declareIdList(AST_NODE* declarationNode, SymbolAttributeKind isVariableOrTypeAttribute, int ignoreArrayFirstDimSize)
{
    AST_NODE* typeNode = declarationNode->child;
    TypeDescriptor *typeDescriptorOfTypeNode = typeNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;
    if((isVariableOrTypeAttribute == VARIABLE_ATTRIBUTE) && 
       (typeDescriptorOfTypeNode->kind == SCALAR_TYPE_DESCRIPTOR) &&
       (typeDescriptorOfTypeNode->properties.dataType == VOID_TYPE))
    {
        printErrorMsg(typeNode, VOID_VARIABLE);
        typeNode->dataType = ERROR_TYPE;
        return;
    }
    AST_NODE* traverseIDList = typeNode->rightSibling;
    while(traverseIDList)
    {
        if(declaredLocally(traverseIDList->semantic_value.identifierSemanticValue.identifierName))
        {
            printErrorMsg(traverseIDList, SYMBOL_REDECLARE);
            traverseIDList->dataType = ERROR_TYPE;
            declarationNode->dataType = ERROR_TYPE;
        }
        else
        {
            SymbolAttribute* attribute = (SymbolAttribute*)malloc(sizeof(SymbolAttribute));
            attribute->attributeKind = isVariableOrTypeAttribute;
            switch(traverseIDList->semantic_value.identifierSemanticValue.kind)
            {
            case NORMAL_ID:
                attribute->attr.typeDescriptor = typeNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;
		attribute->offset = frame_size-84;
		frame_size+=4;
                break;
            case ARRAY_ID:
                if((isVariableOrTypeAttribute == TYPE_ATTRIBUTE) && 
                   (typeDescriptorOfTypeNode->kind == SCALAR_TYPE_DESCRIPTOR) &&
                   (typeDescriptorOfTypeNode->properties.dataType == VOID_TYPE))
                {
                    printErrorMsg(traverseIDList, TYPEDEF_VOID_ARRAY);
                    traverseIDList->dataType = ERROR_TYPE;
                    declarationNode->dataType = ERROR_TYPE;
                    break;
                }
                attribute->attr.typeDescriptor = (TypeDescriptor*)malloc(sizeof(TypeDescriptor));
                processDeclDimList(traverseIDList, attribute->attr.typeDescriptor, ignoreArrayFirstDimSize);
                if(traverseIDList->dataType == ERROR_TYPE)
                {
                    free(attribute->attr.typeDescriptor);
                    declarationNode->dataType = ERROR_TYPE;
                }
                else if(typeNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR)
                {
                    attribute->attr.typeDescriptor->properties.arrayProperties.elementType = 
                        typeNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor->properties.dataType;
                }
                else if(typeNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR)
                {
                    int typeArrayDimension = typeNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor->properties.arrayProperties.dimension;
                    int idArrayDimension = attribute->attr.typeDescriptor->properties.arrayProperties.dimension;
                    if((typeArrayDimension + idArrayDimension) > MAX_ARRAY_DIMENSION)
                    {
                        printErrorMsg(traverseIDList, EXCESSIVE_ARRAY_DIM_DECLARATION);
                        free(attribute->attr.typeDescriptor);
                        traverseIDList->dataType = ERROR_TYPE;
                        declarationNode->dataType = ERROR_TYPE;
                    }
                    else
                    {
                        attribute->attr.typeDescriptor->properties.arrayProperties.elementType = 
                            typeNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor->properties.arrayProperties.elementType;
                        attribute->attr.typeDescriptor->properties.arrayProperties.dimension = 
                            typeArrayDimension + idArrayDimension;
                        int indexType = 0;
                        int indexId = 0;
			int temp=1;
                        for(indexType = 0, indexId = idArrayDimension; indexId < idArrayDimension + typeArrayDimension; ++indexType, ++indexId)
                        {
                            attribute->attr.typeDescriptor->properties.arrayProperties.sizeInEachDimension[indexId] = 
                                typeNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor->properties.arrayProperties.sizeInEachDimension[indexType];
			    temp *= attribute->attr.typeDescriptor->properties.arrayProperties.sizeInEachDimension[indexId];
                        }
			    attribute->offset = frame_size-84;
			    frame_size += temp*4;
			
                    }
                }
                break;
            case WITH_INIT_ID:
                if(typeNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR)
                {
                    printErrorMsg(traverseIDList, TRY_TO_INIT_ARRAY);
                    traverseIDList->dataType = ERROR_TYPE;
                    declarationNode->dataType = ERROR_TYPE;
                }
                else
                {
                    attribute->attr.typeDescriptor = typeNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;
		    attribute->offset = frame_size-84;
		    frame_size += 4;
                }
                break;
            default:
                printf("Unhandle case in void declareIdList(AST_NODE* typeNode)\n");
                traverseIDList->dataType = ERROR_TYPE;
                declarationNode->dataType = ERROR_TYPE;
                break;
            }
            if(traverseIDList->dataType == ERROR_TYPE)
            {
                free(attribute);
                declarationNode->dataType = ERROR_TYPE;
            }
            else
            {
                traverseIDList->semantic_value.identifierSemanticValue.symbolTableEntry =
                    enterSymbol(traverseIDList->semantic_value.identifierSemanticValue.identifierName, attribute);
            }
        }
        traverseIDList = traverseIDList->rightSibling;
    }
}

int checkAssignOrExpr(AST_NODE* assignOrExpreelatedNode)
{
    if(assignOrExprRelatedNode->nodeType == STMT_NODE)
    {
        if(assignOrExprRelatedNode->semantic_value.stmtSemanticValue.kind == ASSIGN_STMT)
        {
            return checkAssignmentStmt(assignOrExprRelatedNode);
        }
        else if(assignOrExprRelatedNode->semantic_value.stmtSemanticValue.kind == FUNCTION_CALL_STMT)
        {
            int i = getreg();
            checkFunctionCall(assignOrExprRelatedNode);
            fprintf("move $%d, $v0\n",i);
	    return i;
        }
    }
    else
    {
        return processExprRelatedNode(assignOrExprRelatedNode);
    }
}

void checkWhileStmt(AST_NODE* whileNode)
{
    AST_NODE* boolExpression = whileNode->child;
    fprintf(asm_out,"_while%d:\n",++while_num);	
    int reg_return = checkAssignOrExpr(boolExpression);
    fprintf(asm_out,"beqz $%d, _while_exit%d\n",reg_return,++while_exit_num);	
    
    AST_NODE* bodyNode = boolExpression->rightSibling;
    processStmtNode(bodyNode);
    fprintf(asm_out,"j _while%d:",while_num);
    fprintf(asm_out,"_while_exit%d:",while_exit_num);
}


void checkForStmt(AST_NODE* forNode)
{
    AST_NODE* initExpression = forNode->child;
    processGeneralNode(initExpression);
    AST_NODE* conditionExpression = initExpression->rightSibling;
    processGeneralNode(conditionExpression);
    AST_NODE* loopExpression = conditionExpression->rightSibling;
    processGeneralNode(loopExpression);
    AST_NODE* bodyNode = loopExpression->rightSibling;
    processStmtNode(bodyNode);
}


int checkAssignmentStmt(AST_NODE* assignmentNode)
{
    AST_NODE* leftOp = assignmentNode->child;
    AST_NODE* rightOp = leftOp->rightSibling;
    int r1 = processVariableLValue(leftOp);
    int r2 = processExprRelatedNode(rightOp);
    
    if(r1 == -2) //global variable
	symbolTableEntry *symbolTableEntry = retrieveSymbol(leftOp->semantic_value.identifierSemanticValue.identifierName);
	fprintf(asm_out,"move $_%s, $%d\n",symbolTableEntry->name,r2);		
    }else if(r1 != -1) //assume local variable
    {	
	fprintf(asm_out,"add $%d, $%d, fp\n",r1,r1);	
	fprintf(asm_out,"sw $%d, $%d\n",r2,r1);
	free_reg(r1);
    }

    if(leftOp->dataType == ERROR_TYPE || rightOp->dataType == ERROR_TYPE)
    {
        assignmentNode->dataType = ERROR_TYPE;
    }
    if(rightOp->dataType == INT_PTR_TYPE || rightOp->dataType == FLOAT_PTR_TYPE)
    {
        printErrorMsg(rightOp, INCOMPATIBLE_ARRAY_DIMENSION);
        assignmentNode->dataType = ERROR_TYPE;
    }
    else if(rightOp->dataType == CONST_STRING_TYPE)
    {
        printErrorMsg(rightOp, STRING_OPERATION);
        assignmentNode->dataType = ERROR_TYPE;
    }
    else
    {
        assignmentNode->dataType = getBiggerType(leftOp->dataType, rightOp->dataType);
    }
    return r2; 
}


void checkIfStmt(AST_NODE* ifNode)
{
    int local_if,local_else,local_exit;
    local_if = ++if_num;
    local_else = ++else_num;
    local_exit = ++exit_num;
    fprintf(asm_out,"_if%d:\n",local_if);	
    AST_NODE* boolExpression = ifNode->child;
    int reg_num = checkAssignOrExpr(boolExpression);
    fprintf(asm_out,"beqz $%d, _else%d\n",reg_num,local_else);	
    AST_NODE* ifBodyNode = boolExpression->rightSibling;
    processStmtNode(ifBodyNode);
    processStmtNode(elsePartNode);
    fprintf(asm_out,"j _exit%d\n",local_exit);	
    fprintf(asm_out,"_else%d:\n",local_else);	
    AST_NODE* elsePartNode = ifBodyNode->rightSibling;
    processStmtNode(elsePartNode);
    fprintf(asm_out,"_exit%d:\n",local_exit);	
}

void checkWriteFunction(AST_NODE* functionCallNode)
{
    AST_NODE* functionIDNode = functionCallNode->child;

    AST_NODE* actualParameterList = functionIDNode->rightSibling;
    processGeneralNode(actualParameterList);

    AST_NODE* actualParameter = actualParameterList->child;
    
    int actualParameterNumber = 0;
    while(actualParameter)
    {
        ++actualParameterNumber;
        if(actualParameter->dataType == ERROR_TYPE)
        {
            functionCallNode->dataType = ERROR_TYPE;
        }
        else if(actualParameter->dataType != INT_TYPE &&
                actualParameter->dataType != FLOAT_TYPE &&
                actualParameter->dataType != CONST_STRING_TYPE)
        {
            printErrorMsg(actualParameter, PARAMETER_TYPE_UNMATCH);
            functionCallNode->dataType = ERROR_TYPE;
        }
	switch(actualParameter->dataType){
	//assume write's parameter is constant
	//TODO: identifier type
	    case INT_TYPE:
		fprintf(asm_out,".data\n");
		fprintf(asm_out,"_m%d: .word %d\n",++m_num,actualParameter->semantic_value.const1->const_u.intval);
		break;
	    case FLOAT_TYPE:
		fprintf(asm_out,".data\n");
		fprintf(asm_out,"_m%d: .word %d\n",++m_num,actualParameter->semantic_value.const1->const_u.fval);
		break;
	    case CONST_STRING_TYPE:
		fprintf(asm_out,".data");
		fprintf(asm_out,"_m%d: .asciiz \"%s\"\n",++m_num,actualParameter->semantic_value.const1->const_u.sc);
		break;
	}
        actualParameter = actualParameter->rightSibling;
    }
    
    if(actualParameterNumber > 1)
    {
        printErrorMsg(functionIDNode, TOO_MANY_ARGUMENTS);
        functionCallNode->dataType = ERROR_TYPE;
    }
    else if(actualParameterNumber < 1)
    {
        printErrorMsg(functionIDNode, TOO_FEW_ARGUMENTS);
        functionCallNode->dataType = ERROR_TYPE;
    }
    else
    {
        functionCallNode->dataType = VOID_TYPE;
    }
}

void checkReadFunction(AST_NODE* functionCallNode){
    fprintf(asm_out,"li $v0 5\n");
    fprintf(asm_out,"syscall\n");	
}


void checkFunctionCall(AST_NODE* functionCallNode)
{
    AST_NODE* functionIDNode = functionCallNode->child;
    //special case
    if(strcmp(functionIDNode->semantic_value.identifierSemanticValue.identifierName, "write") == 0)
    {
        checkWriteFunction(functionCallNode);
        return;
    }
    //special case: read
    if(strcmp(functionIDNode->semantic_value.identifierSemanticValue.identifierName, "read") == 0)
    {
        checkReadFunction(functionCallNode);
        return;
    }

    SymbolTableEntry* symbolTableEntry = retrieveSymbol(functionIDNode->semantic_value.identifierSemanticValue.identifierName);
    functionIDNode->semantic_value.identifierSemanticValue.symbolTableEntry = symbolTableEntry;

    if(symbolTableEntry == NULL)
    {
        printErrorMsg(functionIDNode, SYMBOL_UNDECLARED);
        functionIDNode->dataType = ERROR_TYPE;
        functionCallNode->dataType = ERROR_TYPE;
        return;
    }
    else if(symbolTableEntry->attribute->attributeKind != FUNCTION_SIGNATURE)
    {
        printErrorMsg(functionIDNode, NOT_FUNCTION_NAME);
        functionIDNode->dataType = ERROR_TYPE;
        functionCallNode->dataType = ERROR_TYPE;
        return;
    }

    AST_NODE* actualParameterList = functionIDNode->rightSibling;
    processGeneralNode(actualParameterList);

    AST_NODE* actualParameter = actualParameterList->child;
    Parameter* formalParameter = symbolTableEntry->attribute->attr.functionSignature->parameterList;

    int parameterPassingError = 0;
    while(actualParameter && formalParameter)
    {
        if(actualParameter->dataType == ERROR_TYPE)
        {
            parameterPassingError = 1;
        }
        else
        {
            checkParameterPassing(formalParameter, actualParameter);
            if(actualParameter->dataType == ERROR_TYPE)
            {
                parameterPassingError = 1;
            }
        }
        actualParameter = actualParameter->rightSibling;
        formalParameter = formalParameter->next;
    }
    
    if(parameterPassingError)
    {
        functionCallNode->dataType = ERROR_TYPE;
    }
    if(actualParameter != NULL)
    {
        printErrorMsg(functionIDNode, TOO_MANY_ARGUMENTS);
        functionCallNode->dataType = ERROR_TYPE;
    }
    else if(formalParameter != NULL)
    {
        printErrorMsg(functionIDNode, TOO_FEW_ARGUMENTS);
        functionCallNode->dataType = ERROR_TYPE;
    }
    else
    {
        functionCallNode->dataType = symbolTableEntry->attribute->attr.functionSignature->returnType;
    }
}

void checkParameterPassing(Parameter* formalParameter, AST_NODE* actualParameter)
{
    int actualParameterIsPtr = 0;
    DATA_TYPE actualParameterDataType = NONE_TYPE;
    actualParameterDataType = actualParameter->dataType;
    if(actualParameter->dataType == INT_PTR_TYPE || actualParameter->dataType == FLOAT_PTR_TYPE)
    {
        actualParameterIsPtr = 1;
    }
    
    if(formalParameter->type->kind == SCALAR_TYPE_DESCRIPTOR && actualParameterIsPtr)
    {
        printErrorMsgSpecial(actualParameter, formalParameter->parameterName, PASS_ARRAY_TO_SCALAR);
        actualParameter->dataType = ERROR_TYPE;
    }
    else if(formalParameter->type->kind == ARRAY_TYPE_DESCRIPTOR && !actualParameterIsPtr)
    {
        printErrorMsgSpecial(actualParameter, formalParameter->parameterName, PASS_SCALAR_TO_ARRAY);
        actualParameter->dataType = ERROR_TYPE;
    }
    else if(actualParameter->dataType == CONST_STRING_TYPE)
    {
        printErrorMsg(actualParameter, PARAMETER_TYPE_UNMATCH);
        actualParameter->dataType = ERROR_TYPE;
    }

}


int processExprRelatedNode(AST_NODE* exprRelatedNode)
{
    switch(exprRelatedNode->nodeType)
    {
    case EXPR_NODE:
        return processExprNode(exprRelatedNode);
        break;
    case STMT_NODE:
        //function call
        int i = getreg();
        checkFunctionCall(exprRelatedNode);
        fprintf("move $%d, $v0\n",i);
	return i;
	break;
    case IDENTIFIER_NODE:
        return processVariableRValue(exprRelatedNode);
        break;
    case CONST_VALUE_NODE:
        return processConstValueNode(exprRelatedNode);
        break;
    default:
        printf("Unhandle case in void processExprRelatedNode(AST_NODE* exprRelatedNode)\n");
        exprRelatedNode->dataType = ERROR_TYPE;
 	return -1;
        break;
    }
}

void getExprOrConstValue(AST_NODE* exprOrConstNode, int* iValue, float* fValue)
{
    if(exprOrConstNode->nodeType == CONST_VALUE_NODE)
    {
        if(exprOrConstNode->dataType == INT_TYPE)
        {
            if(fValue)
            {
                *fValue = exprOrConstNode->semantic_value.const1->const_u.intval;
            }
            else
            {
                *iValue = exprOrConstNode->semantic_value.const1->const_u.intval;
            }
        }
        else
        {
            *fValue = exprOrConstNode->semantic_value.const1->const_u.fval;
        }
    }
    else
    {
        if(exprOrConstNode->dataType == INT_TYPE)
        {
            if(fValue)
            {
                *fValue = exprOrConstNode->semantic_value.exprSemanticValue.constEvalValue.iValue;
            }
            else
            {
                *iValue = exprOrConstNode->semantic_value.exprSemanticValue.constEvalValue.iValue;
            }
        }
        else
        {
            *fValue = exprOrConstNode->semantic_value.exprSemanticValue.constEvalValue.fValue;
        }
    }
}

void evaluateExprValue(AST_NODE* exprNode)
{
    if(exprNode->semantic_value.exprSemanticValue.kind == BINARY_OPERATION)
    {
        AST_NODE* leftOp = exprNode->child;
        AST_NODE* rightOp = leftOp->rightSibling;
        if(leftOp->dataType == INT_TYPE && rightOp->dataType == INT_TYPE)
        {
            int leftValue = 0;
            int rightValue = 0;
            getExprOrConstValue(leftOp, &leftValue, NULL);
            getExprOrConstValue(rightOp, &rightValue, NULL);
            exprNode->dataType = INT_TYPE;
            switch(exprNode->semantic_value.exprSemanticValue.op.binaryOp)
            {
            case BINARY_OP_ADD:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue + rightValue;
                break;
            case BINARY_OP_SUB:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue - rightValue;
                break;
            case BINARY_OP_MUL:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue * rightValue;
                break;
            case BINARY_OP_DIV:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue / rightValue;
                break;
            case BINARY_OP_EQ:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue == rightValue;
                break;
            case BINARY_OP_GE:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue >= rightValue;
                break;
            case BINARY_OP_LE:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue <= rightValue;
                break;
            case BINARY_OP_NE:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue != rightValue;
                break;
            case BINARY_OP_GT:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue > rightValue;
                break;
            case BINARY_OP_LT:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue < rightValue;
                break;
            case BINARY_OP_AND:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue && rightValue;
                break;
            case BINARY_OP_OR:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = leftValue || rightValue;
                break;
            default:
                printf("Unhandled case in void evaluateExprValue(AST_NODE* exprNode)\n");
                break;
            }
            
            return;
        }
        else
        {
            float leftValue = 0;
            float rightValue = 0;
            getExprOrConstValue(leftOp, NULL, &leftValue);
            getExprOrConstValue(rightOp, NULL, &rightValue);
            exprNode->dataType = FLOAT_TYPE;
            switch(exprNode->semantic_value.exprSemanticValue.op.binaryOp)
            {
            case BINARY_OP_ADD:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = leftValue + rightValue;
                break;
            case BINARY_OP_SUB:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = leftValue - rightValue;
                break;
            case BINARY_OP_MUL:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = leftValue * rightValue;
                break;
            case BINARY_OP_DIV:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = leftValue / rightValue;
                break;
            case BINARY_OP_EQ:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = leftValue == rightValue;
                break;
            case BINARY_OP_GE:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = leftValue >= rightValue;
                break;
            case BINARY_OP_LE:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = leftValue <= rightValue;
                break;
            case BINARY_OP_NE:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = leftValue != rightValue;
                break;
            case BINARY_OP_GT:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = leftValue > rightValue;
                break;
            case BINARY_OP_LT:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = leftValue < rightValue;
                break;
            case BINARY_OP_AND:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = leftValue && rightValue;
                break;
            case BINARY_OP_OR:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = leftValue || rightValue;
                break;
            default:
                printf("Unhandled case in void evaluateExprValue(AST_NODE* exprNode)\n");
                break;
            }
        }
    }
    else
    {
        AST_NODE* operand = exprNode->child;
        if(operand->dataType == INT_TYPE)
        {
            int operandValue = 0;
            getExprOrConstValue(operand, &operandValue, NULL);
            exprNode->dataType = INT_TYPE;
            switch(exprNode->semantic_value.exprSemanticValue.op.unaryOp)
            {
            case UNARY_OP_POSITIVE:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = operandValue;
                break;
            case UNARY_OP_NEGATIVE:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = -operandValue;
                break;
            case UNARY_OP_LOGICAL_NEGATION:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.iValue = !operandValue;
                break;
            default:
                printf("Unhandled case in void evaluateExprValue(AST_NODE* exprNode)\n");
                break;
            }
        }
        else
        {
            float operandValue = 0;
            getExprOrConstValue(operand, NULL, &operandValue);
            exprNode->dataType = FLOAT_TYPE;
            switch(exprNode->semantic_value.exprSemanticValue.op.unaryOp)
            {
            case UNARY_OP_POSITIVE:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = operandValue;
                break;
            case UNARY_OP_NEGATIVE:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = -operandValue;
                break;
            case UNARY_OP_LOGICAL_NEGATION:
                exprNode->semantic_value.exprSemanticValue.constEvalValue.fValue = !operandValue;
                break;
            default:
                printf("Unhandled case in void evaluateExprValue(AST_NODE* exprNode)\n");
                break;
            }
        }
    }
}


int processExprNode(AST_NODE* exprNode)
{
    if(exprNode->semantic_value.exprSemanticValue.kind == BINARY_OPERATION)
    {
	BINARY_OPERATOR op = exprNode->semantic_value.exprSemanticValue.op.binaryOp;
        AST_NODE* leftOp = exprNode->child;
        AST_NODE* rightOp = leftOp->rightSibling;
        int r1 = processExprRelatedNode(leftOp);
        int r2 = processExprRelatedNode(rightOp);
	free_reg(r1);
	free_reg(r2);
	int reg_num = getreg();	
	switch(op){
            case BINARY_OP_ADD: 
		 fprintf(asm_out,"add $%d, $%d, $%d\n",reg_num,r1,r2);
	    	break;
	    case BINARY_OP_SUB:
		 fprintf(asm_out,"sub $%d, $%d, $%d\n",reg_num,r1,r2);
	    	break;    
	    case BINARY_OP_MUL:
		 fprintf(asm_out,"mul $%d, $%d, $%d\n",reg_num,r1,r2);
	    	break;
	    case BINARY_OP_DIV:
		 fprintf(asm_out,"div $%d, $%d, $%d\n",reg_num,r1,r2);
		break;
	    case BINARY_OP_EQ:
		//FIXME
		 fprintf(asm_out,"seq $%d, $%d, $%d\n",reg_num,r1,r2);
		break;
	    case BINARY_OP_GE:
		 fprintf(asm_out," $%d, $%d, $%d\n",reg_num,r1,r2);
		break;
	    case BINARY_OP_LE:
		 fprintf(asm_out," $%d, $%d, $%d\n",reg_num,r1,r2);
		break;
	    case BINARY_OP_NE:
		 fprintf(asm_out,"neg $%d, $%d, $%d\n",reg_num,r1,r2);
		break;
	    case BINARY_OP_GT:
		 fprintf(asm_out," $%d, $%d, $%d\n",reg_num,r1,r2);
		break;
	    case BINARY_OP_LT:
		 fprintf(asm_out," $%d, $%d, $%d\n",reg_num,r1,r2);
		break;
	    case BINARY_OP_AND:
		 fprintf(asm_out,"and $%d, $%d, $%d\n",reg_num,r1,r2);
		break;
	    case BINARY_OP_OR:
		 fprintf(asm_out,"or $%d, $%d, $%d\n",reg_num,r1,r2);
		break;
	}
        //special case
        if(leftOp->dataType == INT_PTR_TYPE || leftOp->dataType == FLOAT_PTR_TYPE)
        {
            printErrorMsg(leftOp, INCOMPATIBLE_ARRAY_DIMENSION);
            exprNode->dataType = ERROR_TYPE;
        }
        if(rightOp->dataType == INT_PTR_TYPE || rightOp->dataType == FLOAT_PTR_TYPE)
        {
            printErrorMsg(leftOp, INCOMPATIBLE_ARRAY_DIMENSION);
            exprNode->dataType = ERROR_TYPE;
        }
        if(leftOp->dataType == CONST_STRING_TYPE || rightOp->dataType == CONST_STRING_TYPE)
        {
            printErrorMsg(exprNode, STRING_OPERATION);
            exprNode->dataType = ERROR_TYPE;
        }
        //
        if(leftOp->dataType == ERROR_TYPE || rightOp->dataType == ERROR_TYPE)
        {
            exprNode->dataType = ERROR_TYPE;
        }

        if(exprNode->dataType != ERROR_TYPE)
        {
            exprNode->dataType = getBiggerType(leftOp->dataType, rightOp->dataType);
        }

        if((exprNode->dataType != ERROR_TYPE) &&
           (leftOp->nodeType == CONST_VALUE_NODE || (leftOp->nodeType == EXPR_NODE && leftOp->semantic_value.exprSemanticValue.isConstEval)) &&
           (rightOp->nodeType == CONST_VALUE_NODE || (rightOp->nodeType == EXPR_NODE && rightOp->semantic_value.exprSemanticValue.isConstEval))
          )
        {
            evaluateExprValue(exprNode);
            exprNode->semantic_value.exprSemanticValue.isConstEval = 1;
        }
        return reg_num;
    }
    else
    {
	//unary operation
	UNARY_OPERATOR op = exprNode->semantic_value.exprSemanticValue.op.unaryOp;
        AST_NODE* operand = exprNode->child;
        int r1 = processExprRelatedNode(operand);
	free_reg(r1);
	int reg_num = getreg();
	switch(op){
	    //FIXME
            case UNARY_OP_POSITIVE:
		 //fprintf(asm_out," $%d, $%d\n",reg_num,r1);
		break;
    	    case UNARY_OP_NEGATIVE:
		 fprintf(asm_out,"mul $%d, $%d, -1\n",reg_num,r1);
		break;
    	    case UNARY_OP_LOGICAL_NEGATION:
		 fprintf(asm_out," $%d, $%d\n",reg_num,r1);
		break;
	}
        //special case
        if(operand->dataType == INT_PTR_TYPE || operand->dataType == FLOAT_PTR_TYPE)
        {
            printErrorMsg(operand, INCOMPATIBLE_ARRAY_DIMENSION);
            exprNode->dataType = ERROR_TYPE;
        }
        else if(operand->dataType == CONST_STRING_TYPE)
        {
            printErrorMsg(exprNode, STRING_OPERATION);
            exprNode->dataType = ERROR_TYPE;
        }
        else if(operand->dataType == ERROR_TYPE)
        {
            exprNode->dataType = ERROR_TYPE;
        }
        else
        {
            exprNode->dataType = operand->dataType;
        }

        
        if((exprNode->dataType != ERROR_TYPE) &&
           (operand->nodeType == CONST_VALUE_NODE || (operand->nodeType == EXPR_NODE && operand->semantic_value.exprSemanticValue.isConstEval))
          )
        {
            evaluateExprValue(exprNode);
	    exprNode->semantic_value.exprSemanticValue.isConstEval = 1;
	}

	return reg_num;
    }
}


int processVariableLValue(AST_NODE* idNode)
{
    SymbolTableEntry *symbolTableEntry = retrieveSymbol(idNode->semantic_value.identifierSemanticValue.identifierName);
    int offset = symbolTableEntry->attribute.offset;
  
    TypeDescriptor *typeDescriptor = idNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;
    if(!symbolTableEntry)
    {
        printErrorMsg(idNode, SYMBOL_UNDECLARED);
        idNode->dataType = ERROR_TYPE;
        return -1;
    }
    idNode->semantic_value.identifierSemanticValue.symbolTableEntry = symbolTableEntry;

    if(symbolTableEntry->attribute->attributeKind == TYPE_ATTRIBUTE)
    {
        printErrorMsg(idNode, IS_TYPE_NOT_VARIABLE);
        idNode->dataType = ERROR_TYPE;
        return -1;
    }
    else if(symbolTableEntry->attribute->attributeKind == FUNCTION_SIGNATURE)
    {
        printErrorMsg(idNode, IS_FUNCTION_NOT_VARIABLE);
        idNode->dataType = ERROR_TYPE;
        return -1;
    }
    
    int reg_offset = getreg();
    if(symbolTableEntry->nestingLevel == 0){
	//FIXME return -2 for global
	return -2;
    }
    fprintf(asm_out,"lw $%d, %d\n",reg_offset,offset);
        
    if(idNode->semantic_value.identifierSemanticValue.kind == NORMAL_ID)
    {
        if(typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR)
        {
            //printErrorMsg(idNode, NOT_ASSIGNABLE);
            printErrorMsg(idNode, INCOMPATIBLE_ARRAY_DIMENSION);
            idNode->dataType = ERROR_TYPE;
        }
        else
        {
            idNode->dataType = typeDescriptor->properties.dataType;
        }
	return reg_offset;
    }
    else if(idNode->semantic_value.identifierSemanticValue.kind == ARRAY_ID)
    {
        int dimension = 0;
        int reg_return;
        int reg_num = getreg();
        AST_NODE *traverseDimList = idNode->child;
        while(traverseDimList)
        {
            reg_return = processExprRelatedNode(traverseDimList);
	    //reg_num = getreg();
            if(dimension == 0){
	        fprintf(asm_out,"move $%d, $%d\n",reg_num, reg_return);
	    }
	    else{
                int reg_ime = getreg();
		fprintf(asm_out,"li $%d, %d\n",reg_ime,typeDescriptor->properties.arrayProperties.sizeInEachDimension[dimension]);
		fprintf(asm_out,"mul $%d, $%d, $%d\n",reg_num,reg_ime,reg_num);
		fprintf(asm_out,"add $%d, $%d, $%d\n",reg_num,reg_return,reg_num);
	        free_reg(reg_ime);
	    }
  	    free_reg(reg_return);

            if(traverseDimList->dataType == ERROR_TYPE)
            {
                idNode->dataType = ERROR_TYPE;
            }
            else if(traverseDimList->dataType == FLOAT_TYPE)
            {
                printErrorMsg(idNode, ARRAY_SUBSCRIPT_NOT_INT);
                idNode->dataType = ERROR_TYPE;
            }
            traverseDimList = traverseDimList->rightSibling;
            ++dimension;
        }
        int temp_ime = getreg();
	fprintf(asm_out,"li $%d, 4\n",temp_ime);
	fprintf(asm_out,"mul $%d, $%d, $%d\n",reg_num,temp_ime,reg_num);
        fprintf(asm_out,"add $%d, $%d, $%d\n",reg_offset, reg_offset,reg_num);
	free_reg(reg_num);
	free_reg(temp_ime);
        if(typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR)
        {
            printErrorMsg(idNode, NOT_ARRAY);
            idNode->dataType = ERROR_TYPE;
        }
        else
        {
            if(dimension == typeDescriptor->properties.arrayProperties.dimension)
            {
                idNode->dataType = typeDescriptor->properties.arrayProperties.elementType;
            }
            else
            {
                printErrorMsg(idNode, INCOMPATIBLE_ARRAY_DIMENSION);
                idNode->dataType = ERROR_TYPE;
            }
        }
	return reg_offset;
    }
}

int processVariableRValue(AST_NODE* idNode)
{
    SymbolTableEntry *symbolTableEntry = retrieveSymbol(idNode->semantic_value.identifierSemanticValue.identifierName);
     
    idNode->semantic_value.identifierSemanticValue.symbolTableEntry = symbolTableEntry;
    if(!symbolTableEntry)
    {
        printErrorMsg(idNode, SYMBOL_UNDECLARED);
        idNode->dataType = ERROR_TYPE;
        return;
    }
    
    if(symbolTableEntry->attribute->attributeKind == TYPE_ATTRIBUTE)
    {
        printErrorMsg(idNode, IS_TYPE_NOT_VARIABLE);
        idNode->dataType = ERROR_TYPE;
        return;
    }    

    TypeDescriptor *typeDescriptor = idNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;
        
    if(idNode->semantic_value.identifierSemanticValue.kind == NORMAL_ID)
    {
        if(typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR)
        {
            if(typeDescriptor->properties.arrayProperties.elementType == INT_TYPE)
            {
                idNode->dataType = INT_PTR_TYPE;
            }
            else
            {
                idNode->dataType = FLOAT_PTR_TYPE;
            }
        }
        else
        {
            idNode->dataType = typeDescriptor->properties.dataType;
        }
    }
    else if(idNode->semantic_value.identifierSemanticValue.kind == ARRAY_ID)
    {
        if(typeDescriptor->kind == SCALAR_TYPE_DESCRIPTOR)
        {
            printErrorMsg(idNode, NOT_ARRAY);
            idNode->dataType = ERROR_TYPE;
        }
        else
        {
            int dimension = 0;
            AST_NODE *traverseDimList = idNode->child;
            while(traverseDimList)
            {
                ++dimension;
                processExprRelatedNode(traverseDimList);
                if(traverseDimList->dataType == ERROR_TYPE)
                {
                    idNode->dataType = ERROR_TYPE;
                }
                else if(traverseDimList->dataType == FLOAT_TYPE)
                {
                    printErrorMsg(idNode, ARRAY_SUBSCRIPT_NOT_INT);
                    idNode->dataType = ERROR_TYPE;
                }
                traverseDimList = traverseDimList->rightSibling;
            }
            if(idNode->dataType != ERROR_TYPE)
            {
                if(dimension == typeDescriptor->properties.arrayProperties.dimension)
                {
                    idNode->dataType = typeDescriptor->properties.arrayProperties.elementType;
                }
                else if(dimension > typeDescriptor->properties.arrayProperties.dimension)
                {
                    printErrorMsg(idNode, INCOMPATIBLE_ARRAY_DIMENSION);
                    idNode->dataType = ERROR_TYPE;
                }
                else if(typeDescriptor->properties.arrayProperties.elementType == INT_TYPE)
                {
                    idNode->dataType = INT_PTR_TYPE;
                }
                else
                {
                    idNode->dataType = FLOAT_PTR_TYPE;
                }
            }
        }
    }
    int reg_num = getreg();
    if(symbolTableEntry->nestingLevel == 0){
        fprintf(asm_out,"lw $%d, %s\n",reg_num,idNode->semantic_value.identifierSemanticValue.identifierName);
    }
    else{
        fprintf(asm_out,"lw $%d, -%d(fp)\n",reg_num,symbolTableEntry->attribute->offset);
    }

 return reg_num;
}


int processConstValueNode(AST_NODE* constValueNode)
{
    int reg_num = getreg();
    switch(constValueNode->semantic_value.const1->const_type)
    {
	case INTEGERC:
        constValueNode->dataType = INT_TYPE;
        constValueNode->semantic_value.exprSemanticValue.constEvalValue.iValue =
            constValueNode->semantic_value.const1->const_u.intval;
        fprintf(asm_out,"li $%d, %d\n",reg_num,constValueNode->semantic_value.const1->const_u.intval);
		break;
	case FLOATC:
        constValueNode->dataType = FLOAT_TYPE;
        constValueNode->semantic_value.exprSemanticValue.constEvalValue.fValue =
            constValueNode->semantic_value.const1->const_u.fval;
        fprintf(asm_out,"li $%d, %d\n",reg_num,constValueNode->semantic_value.const1->const_u.fval);
		break;
	case STRINGC:
        constValueNode->dataType = CONST_STRING_TYPE;
        //fprintf(asm_out,"li $%d, %d\n",reg_num,constValueNode->semantic_value.const1->const_u.fval);
		break;
    default:
        printf("Unhandle case in void processConstValueNode(AST_NODE* constValueNode)\n");
        constValueNode->dataType = ERROR_TYPE;
        break;
    }
 return reg_num;   
}


void checkReturnStmt(AST_NODE* returnNode)
{
    AST_NODE* parentNode = returnNode->parent;
    DATA_TYPE returnType = NONE_TYPE;
    char* funct_name;
    while(parentNode)
    {
        if(parentNode->nodeType == DECLARATION_NODE)
        {
            if(parentNode->semantic_value.declSemanticValue.kind == FUNCTION_DECL)
            {
                returnType = parentNode->child->dataType;
		funct_name = parentNode->child->rightSibling->semantic_value.identifierSemanticValue.identifierName;
            }
            break;
        }
        parentNode = parentNode->parent;
    }

    int errorOccur = 0;
    if(returnNode->child->nodeType == NUL_NODE)
    {
        //case for: return;
        if(returnType != VOID_TYPE)
        {
            errorOccur = 1;
        }
    }
    else
    {
        int reg_return = processExprRelatedNode(returnNode->child);
        if(returnType != returnNode->child->dataType)
        {
            if (!((returnType == FLOAT_TYPE && returnNode->child->dataType == INT_TYPE) || (returnType == INT_TYPE && returnNode->child->dataType == FLOAT_TYPE))) {
                errorOccur = 1;
            }
        }
	fprintf(asm_out,"move $v0, $%d\n",reg_return);
	free_reg(reg_return);
    }

    if(errorOccur)
    {
        printErrorMsg(returnNode, RETURN_TYPE_UNMATCH);
        returnNode->dataType = ERROR_TYPE;
    } else {
        returnNode->dataType = returnType;
    }
    fprintf(asm_out,"j _end_%s\n",funct_name);

}


void processBlockNode(AST_NODE* blockNode)
{
    openScope();

    AST_NODE *traverseListNode = blockNode->child;
    while(traverseListNode)
    {
        processGeneralNode(traverseListNode);
        traverseListNode = traverseListNode->rightSibling;
    }

    closeScope();
}


void processStmtNode(AST_NODE* stmtNode)
{
    if(stmtNode->nodeType == NUL_NODE)
    {
        return;
    }
    else if(stmtNode->nodeType == BLOCK_NODE)
    {
        processBlockNode(stmtNode);
    }
    else
    {
        switch(stmtNode->semantic_value.stmtSemanticValue.kind)
        {
        case WHILE_STMT:
            checkWhileStmt(stmtNode);
            break;
        case FOR_STMT:
            checkForStmt(stmtNode);
            break;
        case ASSIGN_STMT:
            int reg_num = checkAssignmentStmt(stmtNode);
	    free_reg(reg_num);
            break;
        case IF_STMT:
            checkIfStmt(stmtNode);
            break;
        case FUNCTION_CALL_STMT:
	    fprintf(asm_out,"jal %s\n",stmtNode->child->semantic_value.identifierSemanticValue.identifierName);
            checkFunctionCall(stmtNode);
            break;
        case RETURN_STMT:
            checkReturnStmt(stmtNode);
            break;
        default:
            printf("Unhandle case in void processStmtNode(AST_NODE* stmtNode)\n");
            stmtNode->dataType = ERROR_TYPE;
            break;
        }
    }
}


void processGeneralNode(AST_NODE *node)
{
    AST_NODE *traverseChildren = node->child;
    switch(node->nodeType)
    {
    case VARIABLE_DECL_LIST_NODE:
        while(traverseChildren)
        {
            processDeclarationNode(traverseChildren);
            if(traverseChildren->dataType == ERROR_TYPE)
            {
                node->dataType = ERROR_TYPE;
            }
            traverseChildren = traverseChildren->rightSibling;
        }
        break;
    case STMT_LIST_NODE:
        while(traverseChildren)
        {
            processStmtNode(traverseChildren);
            if(traverseChildren->dataType == ERROR_TYPE)
            {
                node->dataType = ERROR_TYPE;
            }
            traverseChildren = traverseChildren->rightSibling;
        }
        break;
    case NONEMPTY_ASSIGN_EXPR_LIST_NODE:
        while(traverseChildren)
        {
            checkAssignOrExpr(traverseChildren);
            if(traverseChildren->dataType == ERROR_TYPE)
            {
                node->dataType = ERROR_TYPE;
            }
            traverseChildren = traverseChildren->rightSibling;
        }
        break;
    case NONEMPTY_RELOP_EXPR_LIST_NODE:
        while(traverseChildren)
        {
            processExprRelatedNode(traverseChildren);
            if(traverseChildren->dataType == ERROR_TYPE)
            {
                node->dataType = ERROR_TYPE;
            }
            traverseChildren = traverseChildren->rightSibling;
        }
        break;
    case NUL_NODE:
        break;
    default:
        printf("Unhandle case in void processGeneralNode(AST_NODE *node)\n");
        node->dataType = ERROR_TYPE;
        break;
    }
}

void processDeclDimList(AST_NODE* idNode, TypeDescriptor* typeDescriptor, int ignoreFirstDimSize)
{
    AST_NODE* variableDeclDimList = idNode->child;
    typeDescriptor->kind = ARRAY_TYPE_DESCRIPTOR;
    AST_NODE* traverseDim = variableDeclDimList;
    int dimension = 0;
    if(ignoreFirstDimSize && traverseDim->nodeType == NUL_NODE)
    {
        typeDescriptor->properties.arrayProperties.sizeInEachDimension[dimension] = 0;
        ++dimension;
        traverseDim = traverseDim->rightSibling;
    }
    while(traverseDim)
    {
        if(dimension >= MAX_ARRAY_DIMENSION)
        {
            printErrorMsg(variableDeclDimList->parent, EXCESSIVE_ARRAY_DIM_DECLARATION);
            idNode->dataType = ERROR_TYPE;
            break;
        }

        processExprRelatedNode(traverseDim);
        if(traverseDim->dataType == ERROR_TYPE)
        {
            idNode->dataType = ERROR_TYPE;
        }
        else if(traverseDim->dataType == FLOAT_TYPE)
        {
            printErrorMsg(traverseDim->parent, ARRAY_SIZE_NOT_INT);
            idNode->dataType = ERROR_TYPE;
        }
        else if(traverseDim->semantic_value.exprSemanticValue.isConstEval &&
            traverseDim->semantic_value.exprSemanticValue.constEvalValue.iValue < 0)
        {
            printErrorMsg(traverseDim->parent, ARRAY_SIZE_NEGATIVE);
            idNode->dataType = ERROR_TYPE;
        }
        else
        {
            typeDescriptor->properties.arrayProperties.sizeInEachDimension[dimension] = 
                traverseDim->semantic_value.exprSemanticValue.constEvalValue.iValue;
        }

        ++dimension;
        traverseDim = traverseDim->rightSibling;
    }

    typeDescriptor->properties.arrayProperties.dimension = dimension;
}




void declareFunction(AST_NODE* declarationNode)
{

    AST_NODE* returnTypeNode = declarationNode->child;

    int errorOccur = 0;
    if(returnTypeNode->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor->kind == ARRAY_TYPE_DESCRIPTOR)
    {
        printErrorMsg(returnTypeNode, RETURN_ARRAY);
        returnTypeNode->dataType = ERROR_TYPE;
        errorOccur = 1;
    }

    AST_NODE* functionNameID = returnTypeNode->rightSibling;
    if(declaredLocally(functionNameID->semantic_value.identifierSemanticValue.identifierName))
    {
        printErrorMsg(functionNameID, SYMBOL_REDECLARE);
        functionNameID->dataType = ERROR_TYPE;
        errorOccur = 1;
    }
    
    SymbolAttribute* attribute = NULL;
    attribute = (SymbolAttribute*)malloc(sizeof(SymbolAttribute));
    attribute->attributeKind = FUNCTION_SIGNATURE;
    attribute->attr.functionSignature = (FunctionSignature*)malloc(sizeof(FunctionSignature));
    attribute->attr.functionSignature->returnType = returnTypeNode->dataType;
    attribute->attr.functionSignature->parameterList = NULL;

    int enterFunctionNameToSymbolTable = 0;
    if(!errorOccur)
    {
        enterSymbol(functionNameID->semantic_value.identifierSemanticValue.identifierName, attribute);
        enterFunctionNameToSymbolTable = 1;
    }

    openScope();

    AST_NODE *parameterListNode = functionNameID->rightSibling;
    AST_NODE *traverseParameter = parameterListNode->child;
    int parametersCount = 0;
    if(traverseParameter)
    {
        ++parametersCount;
        processDeclarationNode(traverseParameter);
        AST_NODE *parameterID = traverseParameter->child->rightSibling;
        if(traverseParameter->dataType == ERROR_TYPE)
        {
            errorOccur = 1;
        }
        else if(!errorOccur)
        {
            Parameter *parameter = (Parameter*)malloc(sizeof(Parameter));
            parameter->next = NULL;
            parameter->parameterName = parameterID->semantic_value.identifierSemanticValue.identifierName;
            parameter->type = parameterID->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;
            attribute->attr.functionSignature->parameterList = parameter;
        }
        traverseParameter = traverseParameter->rightSibling;
    }

    Parameter *parameterListTail = attribute->attr.functionSignature->parameterList;
    
    while(traverseParameter)
    {
        ++parametersCount;
        processDeclarationNode(traverseParameter);
        AST_NODE *parameterID = traverseParameter->child->rightSibling;
        if(traverseParameter->dataType == ERROR_TYPE)
        {
            errorOccur = 1;
        }
        else if(!errorOccur)
        {
            Parameter *parameter = (Parameter*)malloc(sizeof(Parameter));
            parameter->next = NULL;
            parameter->parameterName = parameterID->semantic_value.identifierSemanticValue.identifierName;
            parameter->type = parameterID->semantic_value.identifierSemanticValue.symbolTableEntry->attribute->attr.typeDescriptor;
            parameterListTail->next = parameter;
            parameterListTail = parameter;
        }
        traverseParameter = traverseParameter->rightSibling;
    }
    attribute->attr.functionSignature->parametersCount = parametersCount;

    if(errorOccur && (attribute != NULL))
    {
        Parameter* traverseParameter = attribute->attr.functionSignature->parameterList;
        Parameter* next = NULL; 
        while(traverseParameter)
        {
            next = traverseParameter->next;
            free(traverseParameter);
            traverseParameter = next;
        }
        free(attribute->attr.functionSignature);
        free(attribute);
    }

    if(!errorOccur)
    {
        //codegen
        write_prolog(functionNameID->semantic_value.identifierSemanticValue.identifierName);
	frame_size = 88;
        AST_NODE *blockNode = parameterListNode->rightSibling;
        AST_NODE *traverseListNode = blockNode->child;
        while(traverseListNode)
        {
            processGeneralNode(traverseListNode);
            traverseListNode = traverseListNode->rightSibling;
        }
    }

    closeScope();

    if(errorOccur && enterFunctionNameToSymbolTable)
    {
        declarationNode->dataType = ERROR_TYPE;
        if(enterFunctionNameToSymbolTable)
        {
            removeSymbol(functionNameID->semantic_value.identifierSemanticValue.identifierName);
        }
    }

    write_epilog(functionNameID->semantic_value.identifierSemanticValue.identifierName);
}