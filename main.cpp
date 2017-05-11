#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAXTOKENLEN 30 //单词最大长度

typedef enum    //定义枚举类型
{
    START,INASSIGN,INCOMMENT,INCHAR,INID,INNUM,INRANGE,DONE
}StateType;

typedef enum
{
	ARRAY,		OF,			RECORD,	RETURN,//保留字
    PROGRAM,	PROCEDURE,	TYPE,	VAR,		IF,
	THEN,		ELSE,		FI,		INTEGER,	CHAR,
	WHILE,		DO,         ENDWH,	BEGIN,		END,
	READ,		WRITE,      END_OF_FILE,	    ERROR,//簿记单词符号
    ID,			INTC,		CHARC,//多字符单词符号
	ASSIGN,		EQ,			LT,		PLUS,		MINUS,//特殊符号
	TIMES,		OVER,		LPAREN,	RPAREN,		DOT,
	COLON,		SEMI,		COMMA,	LMIDPAREN,	RMIDPAREN,      UNDERANGE
}LexicalType;

typedef struct tokenType
{
    int token_line;  //行号
    LexicalType Lex;  //类型
    char val[MAXTOKENLEN+1];  //值
}TokenType;

typedef struct node
{
    TokenType Token;      //单词
    struct node *nextToken; //指向下一个单词的指针
}ChainNodeType;

void show_token(TokenType* t)
{
    cout<<t->token_line;
    cout<<"\t";  //tab
    switch(t->Lex)
    {
    case PROGRAM :
        cout<<"PROGRAM";
        break;
    case PROCEDURE :
        cout<<"PROCEDURE";
        break;
    case TYPE :
        cout<<"TYPE";
        break;
    case VAR :
        cout<<"VAR";
        break;
    case IF :
        cout<<"IF";
        break;
    case THEN :
        cout<<"THEN";
        break;
    case ELSE :
        cout<<"ELSE";
        break;
    case FI :
        cout<<"FI";
        break;
    case WHILE :
        cout<<"WHILE";
        break;
    case DO :
        cout<<"DO";
        break;
    case ENDWH :
        cout<<"ENDWH";
        break;
    case BEGIN :
        cout<<"BEGIN";
        break;
    case END :
        cout<<"END";
        break;
    case READ :
        cout<<"READ";
        break;
    case WRITE :
        cout<<"WRITE";
        break;
    case ARRAY :
        cout<<"ARRAY";
        break;
    case OF :
        cout<<"OF";
        break;
    case RECORD :
        cout<<"RECORD";
        break;
    case RETURN :
        cout<<"RETURN";
        break;
    case INTEGER :
        cout<<"INTEGER";
        break;
    case CHAR :
        cout<<"CHAR";
        break;
    case ID :
        cout<<"ID\t\tIDname: ";
        cout<<t->val;
        break;
    case INTC :
        cout<<"INTC\t\tval  =  ";
        cout<<t->val;
        break;
    case CHARC :
        cout<<"CHARC:\t";
        cout<<t->val;
        break;
    case ASSIGN :
        cout<<"ASSIGN";
        break;
    case EQ :
        cout<<"EQ";
        break;
    case LT :
        cout<<"LT";
        break;
    case PLUS :
        cout<<"PLUS";
        break;
    case MINUS :
        cout<<"MINUS";
        break;
    case TIMES :
        cout<<"TIMES";
        break;
    case OVER :
        cout<<"OVER";
        break;
    case LPAREN :
        cout<<"LPAREN";
        break;
    case RPAREN :
        cout<<"RPAREN";
        break;
    case DOT :
        cout<<"DOT";
        break;
    case COLON :
        cout<<"COLON";
        break;
    case SEMI :
        cout<<"SEMI";
        break;
    case COMMA :
        cout<<"COMMA";
        break;
    case LMIDPAREN :
        cout<<"LMIDPAREN";
        break;
    case RMIDPAREN :
        cout<<"RMIDPAREN";
        break;
    case UNDERANGE :
        cout<<"UNDERANGE";
        break;
    case END_OF_FILE :
        cout<<"END_OF_FILE";
        break;
    case ERROR :
        cout<<"ERROR:";
        break;
    default:
        cout<<"OTHERS";
        break;
    }
}
LexicalType is_ID(const char *s){
    switch(s[0])
    {
    case 'a':
        if(strcmp(s+1,"rray")==0)
            return ARRAY;
        break;
    case 'b':
        if(strcmp(s+1,"egin")==0)
            return BEGIN;
        break;
    case 'c':
        if(strcmp(s,"char")==0)
            return CHAR;
        break;
    case 'd':
        if(s[1]=='o'&&s[2]=='\0')
            return DO;
        break;
    case 'e':
        switch(s[1])
        {
        case 'l':
            if(s[2]=='s'&&s[3]=='e'&&s[4]=='\0')
                return ELSE;
            break;
        case 'n':
            if(s[2]=='d')
            {
                if(s[3]=='\0')
                    return END;
                else if(s[3]=='w'&&s[4]=='h'&&s[5]=='\0')
                    return ENDWH;
            }
            break;
        }
        break;
    case 'f':
        if(s[1]=='i'&&s[2]=='\0')
            return FI;
        break;
    case 'i':
        if(s[1]=='f'&&s[2]=='\0')
            return IF;
        if(strcmp(s,"integer")==0)
            return INTEGER;
        break;
    case 'o':
        if(s[1]=='f'&&s[2]=='\0')
            return OF;
        break;
    case 'p':
        if(strcmp(s+1,"rocedure")==0)
            return PROCEDURE;
        if(strcmp(s+1,"rogram")==0)
            return PROGRAM;
        break;
    case 'r':
        if(strcmp(s+1,"ead")==0)
            return READ;
        if(strcmp(s+1,"ecord")==0)
            return RECORD;
        if(strcmp(s+1,"eturn")==0)
            return RETURN;
        break;
    case 't':
        if(strcmp(s+1,"hen")==0)
            return THEN;
        if(strcmp(s+1,"ype")==0)
            return TYPE;
        break;
    case 'v':
        if(strcmp(s+1,"ar")==0)
            return VAR;
        break;
    case 'w':
        if(strcmp(s+1,"hile")==0)
            return WHILE;
        if(strcmp(s+1,"rite")==0)
            return WRITE;
        break;
    }
    return ID;
}
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
