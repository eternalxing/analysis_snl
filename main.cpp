#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;

#define MAXTOKENLEN 30 //单词最大长度
#define MAXCODELEN 1000 //代码最大长度
typedef enum    //定义枚举类型
{
    START,INASSIGN,INCOMMENT,INCHAR,INID,INNUM,INRANGE,DONE //开始状态、复制状态、注释状态、数字状态、标识符状态、字符标志状态、数组下标界限状态、完成状态
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
ChainNodeType *getTokenList(char *buf,int bufSize,int *tokennumber)
{
    int linenum = 1;
    int tokennum = 0;
    ChainNodeType *firstnode = new ChainNodeType;
    firstnode->nextToken = NULL;
    ChainNodeType *currentnode = firstnode;
    ChainNodeType *prenode = firstnode;
    TokenType currentToken;
    int bufpos = 0;
    int tokenpos = 0;
    StateType state = START;
    char tempchar;
    while(true)
    {
        state = START;
        tokenpos = 0;
        currentToken.val[0] = '\0';

        while(state!=DONE)
        {
            if(bufpos == bufSize) //没有程序，行数为0
            {
                currentToken.Lex = ERROR;
                break;
            }
            char c;
            c = tempchar = buf[bufpos++];//下一行
            tokenpos++;
            switch (state)
            {
            case START:
            {
                if (isdigit(c))//判断是否为数字
                {
                    currentToken.val[tokenpos-1] = c;
                    state = INNUM;
                }
                else if (isalpha(c))//是否为字母
                {
                    state = INID;
                    currentToken.val[tokenpos-1] = c;
                }
                else if (c == ':')
                    state = INASSIGN;
                else if (c == '.')
                    state = INRANGE;
                else if (c == '\'')
                {
                    currentToken.val[tokenpos-1] = c;
                    state = INCHAR;
                }
                else if ((c == ' ') || (c == '\t') || (c == '\n'))
                {
                    tokenpos--;
                    if(c=='\n')
                        linenum++;
                }
                else if (c == '{')
                {
                    state = INCOMMENT;
                }
                else
                 {
                     state = DONE;
                     switch (c)
                     {
                       case -1:
                       {
                           currentToken.Lex = END_OF_FILE;
                           break;
                       }
                       case '=':
                       {
                           currentToken.Lex = EQ;
                           break;
                       }
                       case '<':
                       {
                           currentToken.Lex = LT;
                           break;
                       }
                       case '+':
                       {
                           currentToken.Lex = PLUS;
                           break;
                       }
                       case '-':
                       {
                           currentToken.Lex = MINUS;
                           break;
                       }
                       case '*':
                       {
                           currentToken.Lex = TIMES;
                           break;
                       }
                       case '/':
                       {
                           currentToken.Lex = OVER;
                           break;
                       }
                       case '(':
                       {
                           currentToken.Lex = LPAREN;
                           break;
                       }
                       case ')':
                       {
                           currentToken.Lex = RPAREN;
                           break;
                       }
                       case ';':
                       {
                           currentToken.Lex = SEMI;
                           break;
                       }
                       case ',':
                       {
                           currentToken.Lex = COMMA;
                           break;
                       }
                       case '[':
                       {
                           currentToken.Lex = LMIDPAREN;
                           break;
                       }
                       case ']':
                       {
                           currentToken.Lex = RMIDPAREN;
                           break;
                       }
                       default:
                       {
                            currentToken.Lex = ERROR;
                           break;
                       }
                    }
                }
                break;
            }
            case INASSIGN:
            {
                state = DONE;
                if (c == '=')
                    currentToken.Lex = ASSIGN;
                else
                {
                    bufpos--;
                    currentToken.Lex = ERROR;
                }
                break;
            }
            case INRANGE:
            {
                state = DONE;
                if (c == '.')
                    currentToken.Lex = UNDERANGE;
                else
                {
                    bufpos--;
                    currentToken.Lex = DOT;
                }
                break;
            }
            case INCOMMENT:
            {
                if(c=='\n')
                    linenum++;
                if (c == '}')
                {
                    state = START;
                    tokenpos = 0;
                }
                break;
            }
            case INNUM:
            {
                if (!isdigit(c))
                {
                    if(isalpha(c))
                    {
                        while(isalpha(buf[bufpos]))
                            bufpos++;
                        state = DONE;
                        currentToken.Lex = ERROR;
                    }
                    else
                    {
                        bufpos--;
                        state = DONE;
                        currentToken.val[tokenpos-1]='\0';
                        currentToken.Lex = INTC;
                    }
                }
                else
                    currentToken.val[tokenpos-1] = c;
                break;
            }
            case INID:
            {
                if (!isalnum(c))
                {
                    bufpos--;
                    state = DONE;
                    currentToken.val[tokenpos-1]='\0';
                    currentToken.Lex = is_ID(currentToken.val);
                }
                else
                {
                    currentToken.val[tokenpos-1] = c;
                }
                break;
            }
            case INCHAR:
            {
                if (isalnum(c))
                {
                    int c1=buf[bufpos++];
                    if (c1 =='\'')
                    {
                        currentToken.val[0] = c;
                        currentToken.val[1] = '\0';
                        state = DONE;
                        currentToken.Lex = CHARC;
                    }
                    else
                    {
                        bufpos-=2;
                        state = DONE;
                        currentToken.Lex = ERROR;
                    }
                }
                else
                {
                    bufpos--;
                    state = DONE;
                    currentToken.Lex = ERROR;
                }
                break;
            }
            case DONE:
            {
                break;
            }

            default:
            {
                state = DONE;
                currentToken.Lex = ERROR;
                break;
            }
            }
        }

        currentToken.token_line = linenum;
        (currentnode->Token).token_line=currentToken.token_line;
        (currentnode->Token).Lex=currentToken.Lex;
        strcpy((currentnode->Token).val,currentToken.val);

        tokennum++;


        if (prenode!=currentnode)
        {
            prenode->nextToken = currentnode;
            prenode = currentnode;
        }
        else
        {
            prenode = currentnode;
        }
        currentnode = new ChainNodeType;
        currentnode->nextToken=NULL;
        if(currentToken.Lex==END_OF_FILE)
            break;
    }
    *tokennumber = tokennum;
    return firstnode;
}
int main()
{
    ifstream ifile("SNL.txt");
    char *SNLstr = new char[MAXCODELEN];//读取文件并转换
    int i;
    for(i=0;!ifile.eof();i++)
    {
        SNLstr[i] = ifile.get();
    }
    SNLstr[i++] = '\0';
    cout<<"*************************************************"<<endl;
    cout<<"***********     Source   Program:     ***********"<<endl;
    cout<<"*************************************************"<<endl;
    cout<<SNLstr;
    cout<<endl;

    ChainNodeType *tokenlist;
    int tokennum;
    tokenlist = getTokenList(SNLstr,MAXCODELEN,&tokennum); //词法分析

    ChainNodeType *templist;
    cout<<"*************************************************"<<endl;
    cout<<"*********    Lexical Aalysis Result:   **********"<<endl;
    cout<<"*************************************************"<<endl;
    cout<<"Line\tType"<<endl;
    for(templist=tokenlist;templist!=NULL;templist = templist->nextToken)
    {
        show_token(&(templist->Token));  //输出词法分析结果
        cout<<endl;
        if(templist->nextToken!=NULL)
            if(templist->Token.token_line!=templist->nextToken->Token.token_line)
                cout<<endl;
    }
}
