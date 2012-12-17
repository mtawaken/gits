/*
 * =====================================================================================
 *
 *       Filename:  nana.c
 *
 *    Description:  nano structure
 *
 *        Version:  1.0
 *        Created:  2012年10月20日 14时30分34秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  mtawaken (gcs), mtawaken@gmail.com
 *        Company:  NJU
 *
 * =====================================================================================
 */

#include<unistd.h>
#include<stdlib.h>
#include<curses.h>
#include<string.h>
#include<locale.h>


/*
 * defines
*/
#define TOPWIN_H 2
#define BOTTOMWIN_H 3
#define EDITWIN_H (LINES-TOPWIN_H-BOTTOMWIN_H)
#define TMP_SIZE ((COLS+1)*3)//support only one line input at one time
typedef struct ScreenLine{
    int lineNo;
    int shift;
} ScreenLine;
typedef struct Func{
    void (*func)();
    int invokeKey;
    struct Func* next;
} Func;
typedef struct Line{
    char *content;
    int contentFactor;
    int lineNo;
    int size;
    int lines;
    int lastCols;
    struct Line *next;
    struct Line *previous;
} Line;
typedef struct MCursor{
    int x,y;
} MCursor;


/*
 * methods
 */
int doInput();
void doOutput(int);
void functionInit();
Func* createFunction(int,void*,Func*);
void freeFunctionList(Func*);
void doExit();
void doDelete();
void cursorBackward();
void updateLine(Line*);
void reAllocLine(Line*);
void getPositionByYX(Line**,int*,int,int);    
void cursorForward();
void cursorUp();
void cursorDown();
/*
 * globals
 */
WINDOW *topScr,*bottomScr,*editScr;
char *tmp;
int *rawInput;
bool mExit;
ScreenLine screenLine;
Func *functionList;
Line *lineList;
bool newAppending;
bool needRefresh;
bool needAdjustCursor;
MCursor mCursor;

int main(int args,char * argv[]){
    setlocale(LC_ALL,"");
    initscr();
    raw();
    noecho();
    start_color();
    init_pair(1,COLOR_CYAN,COLOR_BLACK);
    init_pair(2,COLOR_WHITE,COLOR_BLACK);
    /*
     * split windows
     */
    topScr = newwin(TOPWIN_H,COLS,0,0);
    editScr = newwin(EDITWIN_H,COLS,TOPWIN_H,0);
    bottomScr = newwin(BOTTOMWIN_H,COLS,LINES-BOTTOMWIN_H,0);

    leaveok(topScr,false);
    leaveok(editScr,false);
    leaveok(bottomScr,false);

    keypad(topScr,TRUE);
    keypad(editScr,TRUE);
    keypad(bottomScr,TRUE);
   
    scrollok(editScr,false);
    scrollok(topScr,false);
    scrollok(bottomScr,false);
    
    wattrset(topScr,COLOR_PAIR(1));
    wattrset(bottomScr,COLOR_PAIR(1));
    wattrset(editScr,COLOR_PAIR(2));

    attron(A_BOLD);
    tmp = (char*)malloc(TMP_SIZE*sizeof(char));
    memset(tmp,'-',TMP_SIZE);
    tmp[COLS] = 0;
    mvwprintw(topScr,TOPWIN_H-1,0,"%s",tmp);
    mvwprintw(bottomScr,0,0,"%s",tmp);
    mvwprintw(topScr,0,0,"%s","NANO");
    mvwprintw(bottomScr,1,0,"%s","STATUS");
    wrefresh(topScr);
    wrefresh(bottomScr);
    attroff(A_BOLD);

    /*
     * function initialization
     */
    functionInit();        

   
    /*
     * line initialization
     */
    lineList = (Line*)malloc(sizeof(Line));
    memset(lineList,0,sizeof(Line));
    Line* tmpLine = (Line*)malloc(sizeof(Line));
    memset(tmpLine,0,sizeof(Line));
    reAllocLine(tmpLine);
    tmpLine->lineNo = 1;
    tmpLine->lines = 1;
    tmpLine->previous = lineList;
    lineList->next = tmpLine;

    /*
     * data initialization
     */
    screenLine.lineNo = 1;
    screenLine.shift = 0;
    mExit = false;
    rawInput = (int*)malloc(sizeof(int)*TMP_SIZE);
    newAppending = true;
    needRefresh = true;
    needAdjustCursor = false;

    /*
     * main process
     */
    move(TOPWIN_H+1,0);
    //func-1,ctrl+x-1,character-1,chineses-3,byinputmethod-n
    int size;
    while(!mExit){
        size = doInput();
        doOutput(size);
    }
    wrefresh(editScr);
    endwin();
    return EXIT_SUCCESS;
}
void functionInit(){
    functionList = (Func*)malloc(sizeof(Func));
    memset(functionList,0,sizeof(Func));
    Func *lastFunc;
    lastFunc = createFunction(24,(void*)&doExit,functionList);
    lastFunc = createFunction(263,(void*)&doDelete,lastFunc);
    lastFunc = createFunction(260,(void*)&cursorBackward,lastFunc);
    lastFunc = createFunction(261,(void*)&cursorForward,lastFunc);
    lastFunc = createFunction(259,(void*)&cursorUp,lastFunc);
    lastFunc = createFunction(258,(void*)&cursorDown,lastFunc);
}

Func* createFunction(int invokeKey,void* realFunction,Func *previous){
    Func *currentFunc = (Func*)malloc(sizeof(Func));
    memset(currentFunc,0,sizeof(Func));
    currentFunc->func = realFunction;
    currentFunc->invokeKey = invokeKey;
    currentFunc->next = 0;
    previous->next = currentFunc;
    return currentFunc;
}
void freeFunctionList(Func*current){
    if(!current)
        return;
    if(current->next){
        freeFunctionList(current->next);
    }
    free(current);
}
void freeOneLine(Line* line){
    if(line){
        if(line->content){
            free(line->content);
        }
        free(line);
    }
}
void freeLines(){
    Line*tempLine,*nextLine;
    tempLine=lineList;
    while(tempLine){
        nextLine = tempLine->next;
        freeOneLine(tempLine);
        tempLine = nextLine;
    }
}
void updateLineNoAfter(Line* line){
        int lineNoUpdater = line->lineNo+1;
        Line *tmpLine = line->next;
        while(tmpLine){
            tmpLine->lineNo = lineNoUpdater;
            lineNoUpdater++;
            tmpLine = tmpLine->next;
        }
}
void jumpLineUnit(char *p,char** newP,int* jumpCol){
    if(!*p){
        *newP = p;
        *jumpCol = 0;
        return;
    }
    int mbLen,wcWidth;
    mbLen = mblen(p,MB_CUR_MAX);    
    if(mbLen == 3){
        //it's a chinese
        *jumpCol = 2;
    }else if(mbLen == 1){
        if(*p == 9){
            //it's a tab
            *jumpCol = 8;
        }else if(*p == 10){
            *newP = 0;
        }else{
            wchar_t wChar;
            mbtowc(&wChar,p,MB_CUR_MAX);
            wcWidth = wcwidth(wChar);
            if(wcWidth == 1){
                //normal character
                *jumpCol = 1;
            }else{
                //unprintable contorl letter
                *jumpCol = 2;
            }
        }
    }else{
        *newP = 0;
    }
    *newP = p + mbLen;
}
void updateLine(Line* line){
    char *p = line->content;
    int colCount,jumpCol,size;
    char *newP;
    colCount = 0;
    size = 0;
    while(p&&*p){
        jumpLineUnit(p,&newP,&jumpCol);
        if(newP!=0){
            colCount +=jumpCol;
            size += (newP-p);
        }
        p = newP;
    }

    line->lines = (colCount/COLS)+1;
    line->lastCols = colCount%COLS;
    line->size = size;
}
void reAllocLine(Line* line){
    int oldSize = (line->contentFactor) * TMP_SIZE;
    line->contentFactor += 1;
    int newSize = (line->contentFactor) * TMP_SIZE;
    char *newContent = (char*)malloc(sizeof(char)*newSize);
    memset(newContent,0,newSize);
    char *p = line->content;
    int index = 0;
    while(index<oldSize && p[index]){
        newContent[index] = p[index];
        index++;
    }
    free(p);
    line->content = newContent;

}
void jumpCols(int jumpCols,char*p,char**newP,char**beforeNewP){
    int jumpedCols = 0;
    int jumpUnit;
    char* startP = p;
    char* beforeP = p;
    *newP=p;
    while(startP&&*startP&&jumpedCols<jumpCols){
        beforeP = *newP;
        jumpLineUnit(startP,&*newP,&jumpUnit);
        if(*newP!=0){
            jumpedCols+=jumpUnit;
        }
        startP = *newP;
    }
    if(beforeNewP){
       *beforeNewP = beforeP;
    }
}

void getPosition(Line** plineToInsert,int *pshift,int* pcursorY,int* pcursorX){    int cursorY,cursorX;
   getyx(editScr,cursorY,cursorX);
   getPositionByYX(plineToInsert,pshift,cursorY,cursorX);
   *pcursorX=cursorX;
   *pcursorY=cursorY;
}
void getPositionByYX(Line** plineToInsert,int *pshift,int cursorY,int cursorX){    
    int scrLine,scrShift;
    Line* lineToInsert;
    int lineShift;
    scrLine = screenLine.lineNo;
    scrShift = screenLine.shift;
    Line* line = lineList->next;
    while(line->lineNo != scrLine){
        line = line->next;
    }    
    int left = line->lines - scrShift;
    if(left >= (cursorY+1)){//cursor starts from 0
        lineToInsert = line;
        lineShift = scrShift + cursorY;
    }else{
        left = cursorY+1 - left;
        while(left > 0){
            line = line->next;
            left = left - line->lines;
        }
        lineToInsert = line;
        lineShift = line->lines + left -1;
    }
    *plineToInsert=lineToInsert;
    *pshift = lineShift;
}
void insert(char* p,int size){
    int cursorY,cursorX;
    Line* lineToInsert;
    int lineShift;
    getPosition(&lineToInsert,&lineShift,&cursorY,&cursorX);     
    if(lineToInsert->next == 0 && (lineToInsert->lines - lineShift == 0) && (lineToInsert->lastCols == cursorX)){
        newAppending = true;
    }else{
        newAppending = false;
        needAdjustCursor = true;
        mCursor.x=cursorX;
        mCursor.y=cursorY;
    }
    int colsToOvercome = COLS*lineShift + cursorX;
    char*insertPoint;
    jumpCols(colsToOvercome,lineToInsert->content,&insertPoint,0);

    if(size == 1 && *p ==10){
        //deal with \n
        if(!newAppending){
            if((cursorY+1)>=EDITWIN_H){
                mCursor.x = 0;
                mCursor.y = cursorY;
            }else{
                mCursor.x = 0;
                mCursor.y = cursorY + 1;
            }
        }
        Line* newLine = (Line*)malloc(sizeof(Line));
        memset(newLine,0,sizeof(Line));
        newLine->next =  lineToInsert->next;
        if(lineToInsert->next){
            (lineToInsert->next)->previous = newLine;
        }
        lineToInsert->next = newLine;
        newLine->previous = lineToInsert;

        reAllocLine(newLine);
        char*newLineInsertP=newLine->content;
        char*origLineMoveP=insertPoint;
        while(origLineMoveP&&*origLineMoveP){
            *newLineInsertP = *origLineMoveP;
            *origLineMoveP = 0;
            newLineInsertP++;
            origLineMoveP++;
        }
        *insertPoint=10;
        updateLine(newLine);
        updateLine(lineToInsert);
        updateLineNoAfter(lineToInsert);
    }else{
        if((size + lineToInsert->size) >= ((lineToInsert->contentFactor)*TMP_SIZE)){
             reAllocLine(lineToInsert);
        }
        if(lineToInsert->size!=0){
            char*toMove = lineToInsert->content + lineToInsert->size - 1;
            while(toMove>=insertPoint){
                *(toMove+size)=*(toMove);
                toMove--;
            }
        }
        int moveIndex = 0;
        while(moveIndex<size){
            insertPoint[moveIndex] = p[moveIndex];
            moveIndex++;
        }   
        lineToInsert->size += size;
        updateLine(lineToInsert);
        if(!newAppending){
            int jumpCol;                        
            char* newP;
            jumpLineUnit(p,&newP,&jumpCol);
            if((cursorX+jumpCol)>=COLS){
                if((cursorY+1)>=EDITWIN_H){
                    mCursor.x = (cursorX+jumpCol) - COLS;
                    mCursor.y = cursorY;
                }else{
                    mCursor.x = (cursorX+jumpCol) - COLS;
                    mCursor.y = cursorY + 1;
                }
            }else{
                mCursor.x = cursorX + jumpCol;
                mCursor.y = cursorY;
            }
        }
    }
    needRefresh = true;
}
void cursorDown(){
    int cursorY,cursorX,newY,newX;
    getyx(editScr,cursorY,cursorX);
    if(cursorY==(EDITWIN_H-1)){
        needRefresh = true;
        newAppending = false;
        Line*tempLine = lineList->next;
        while(tempLine->lineNo != screenLine.lineNo){
            tempLine = tempLine->next;
        }
        Line*lastLine;
        int lineShift;
        getPositionByYX(&lastLine,&lineShift,cursorY,cursorX);
        if(lastLine->lines-lineShift-1>0){
            newY = cursorY;
            if(lastLine->lines-lineShift-1==1){
                if(lastLine->lastCols>cursorX){
                    newX = cursorX;
                }else{
                    newX = lastLine->lastCols;
                }
            }else{
                newX = cursorX;
            }
        }else{
            newY = cursorY;
            if(lastLine->next){
                lastLine = lastLine->next;
                if(lastLine->lines>1){
                    newX = cursorX;
                }else{
                    if(lastLine->lastCols>(cursorX+1)){
                        newX = cursorX;
                    }else{
                        newX = lastLine->lastCols-1;
                    }
                }
            }
        }
        if(tempLine->lines-screenLine.shift-1>0){
            screenLine.shift = screenLine.shift+1;
        }else{
            tempLine = tempLine->next;
            screenLine.lineNo = tempLine->lineNo;
            screenLine.shift = 0;
        }
    }else{
        Line* lastLine;
        int lineShift;
        getPositionByYX(&lastLine,&lineShift,cursorY,cursorX);
        if(lastLine->lines-lineShift-1>0){
            newY = cursorY + 1;
            if(lastLine->lines-lineShift-1==1){
                if(lastLine->lastCols>(cursorX+1)){
                    newX = cursorX;
                }else{
                    newX = lastLine->lastCols-1;
                }
            }else{
                newX = cursorX;
            }
        }else{
            if(lastLine->next){
                newY = cursorY + 1;
                lastLine = lastLine->next;
                if(lastLine->lines == 1){
                    if(lastLine->lastCols>(cursorX+1)){
                        newX = cursorX;
                    }else{
                        newX = lastLine->lastCols-1;
                    }
                }else{
                    newX = cursorX;
                }
            }else{
                newY = cursorY;
                newX = cursorX;
            }
        }
    }
    wmove(editScr,newY,newX);
}
void cursorUp(){
    int cursorY,cursorX,newY,newX;
    getyx(editScr,cursorY,cursorX);
    if(cursorY==0){
        needRefresh = true;
        newAppending = false;
        Line*tempLine = lineList->next;
        while(tempLine->lineNo != screenLine.lineNo){
            tempLine = tempLine->next;
        }
        if(screenLine.shift==0){
            if(tempLine->previous!=lineList){
                tempLine = tempLine->previous;
                screenLine.lineNo = tempLine->lineNo;
                screenLine.shift = tempLine->lines - 1;
                if(tempLine->lastCols<cursorX){
                    newX = tempLine->lastCols;
                }else{
                    newX = cursorX;
                }
                newY = 0;
            }else{
                newX = cursorX;
                needAdjustCursor = true;
                mCursor.x = 0;
                mCursor.y = 0;
            }
        }else{
            screenLine.shift = screenLine.shift - 1;
            newX = cursorX;
            newY = cursorY;
        }
    }else{
        Line*currentLine,*previousLine;
        int lineShift;
        getPositionByYX(&currentLine,&lineShift,cursorY,cursorX);
        newY = cursorY - 1;
        newX = 0;
        getPositionByYX(&previousLine,&lineShift,newY,newX);
        if(currentLine == previousLine){
            newX = cursorX;
        }else{
            if(previousLine->lastCols<(cursorX+1)){
                newX = previousLine->lastCols-1;
                if(newX<0){
                    newX=0;
                }
            }else{
                newX = cursorX;
            }
        }
    }
    wmove(editScr,newY,newX);
}
void cursorForward(){
    int cursorY,cursorX,newY,newX;
    getyx(editScr,cursorY,cursorX);
    Line*currentLine;
    int lineShift;
    getPositionByYX(&currentLine,&lineShift,cursorY,cursorX);
    if((currentLine->lines - lineShift) == 1){
        char ch = *(currentLine->content + currentLine->size -1);
        if(ch==10){
            if(currentLine->lastCols>(cursorX+1)){
                newX = cursorX + 1;
            }else{
                newX = cursorX;
            }
        }else{
            if(currentLine->lastCols>(cursorX)){
                newX = cursorX + 1;
            }else{
                newX = cursorX;
            }
        }
        newY = cursorY;
    }else{
        if(cursorX == (COLS-1)){
            newY = cursorY + 1;
            newX = 0;
            if(newY>(EDITWIN_H-1)){
                needRefresh = true;
                newAppending = false;
                newY = cursorY;
                Line*tempLine = lineList->next;
                while(tempLine->lineNo != screenLine.lineNo){
                    tempLine = tempLine->next;
                }
                if(tempLine->lines-screenLine.shift-1>0){
                    screenLine.shift = screenLine.shift + 1;
                }else{
                    if(tempLine->next){
                        tempLine = tempLine->next;
                        screenLine.lineNo = tempLine->lineNo;
                        screenLine.shift = 0;
                    }
                }
            }
        }else{
            Line*currentLine;
            int lineShift;
            getPositionByYX(&currentLine,&lineShift,cursorY,cursorX);
            int colsToOvercome = lineShift*COLS + cursorX+1;
            char *startP,*beforeP;
            jumpCols(colsToOvercome,currentLine->content,&startP,&beforeP);
            char *newP;
            int jumpCol;
            jumpLineUnit(beforeP,&newP,&jumpCol);        
            newY = cursorY;
            newX = cursorX + jumpCol;
        }
    }
    wmove(editScr,newY,newX);
}
void cursorBackward(){
    int cursorY,cursorX,newY,newX;
    getyx(editScr,cursorY,cursorX);
    if(cursorX==0){
        if(cursorY>0){
            Line*currentLine,*previousLine;
            int lineShift;
            getPositionByYX(&currentLine,&lineShift,cursorY,cursorX);
            newY=cursorY-1;
            newX=0;
            getPositionByYX(&previousLine,&lineShift,newY,newX);
            if(previousLine == currentLine){
                newX = COLS-1;
            }else{
                newX = previousLine->lastCols-1;
                if(newX<0)
                    newX = 0;
            }
            wmove(editScr,newY,newX);
        }else{
            needRefresh = true;
            newAppending = false;
            Line*tempLine = lineList->next;
            while(tempLine->lineNo != screenLine.lineNo){
                tempLine = tempLine->next;
            }
            if(screenLine.shift==0){
                if(tempLine->previous!=lineList){
                    tempLine = tempLine->previous;
                    screenLine.lineNo = tempLine->lineNo;
                    screenLine.shift = tempLine->lines-1;
                }else{
                    //do nothing
                }
            }else{
                screenLine.shift = screenLine.shift - 1;
            }
            needAdjustCursor = true;
            mCursor.x=0;
            mCursor.y=0;
        }
    }else{
        Line*currentLine;
        int lineShift;
        getPositionByYX(&currentLine,&lineShift,cursorY,cursorX);
        int colsToOvercome = lineShift*COLS + cursorX-1;
        char *startP,*beforeP;
        jumpCols(colsToOvercome,currentLine->content,&startP,&beforeP);
        char *newP;
        int jumpCol;
        jumpLineUnit(beforeP,&newP,&jumpCol);        
        newY=cursorY;
        newX=cursorX-jumpCol;
        wmove(editScr,newY,newX);
    }
}
void doDelete(){
    needRefresh = true;
    Line* lineToDelete;
    int lineShift;
    int cursorX,cursorY;
    getPosition(&lineToDelete,&lineShift,&cursorY,&cursorX);
    if(lineToDelete->next == 0 && (lineToDelete->lines-lineShift == 0) && (lineToDelete->lastCols==cursorX)){
        newAppending = true;
    }else{
        newAppending = false;
        needAdjustCursor = true;
        mCursor.x = cursorX;
        mCursor.y = cursorY;
    }
    int colsToOvercome = lineShift*COLS+cursorX-1;
    if(colsToOvercome == -1){
        // line combine
        if(lineToDelete->previous==lineList){
            //first line,do nothing
        }else{
            Line* previousLine = lineToDelete->previous;
            mCursor.y = cursorY - 1;
            mCursor.x = previousLine->lastCols - 1;
            int newSize = previousLine->size + lineToDelete->size;
            if(newSize>=(previousLine->contentFactor * TMP_SIZE)){
                reAllocLine(previousLine);
            }
            char *toPut = previousLine->content + previousLine->size - 1;
            char *toCopy = lineToDelete->content;
            *toPut=0;
            int index = 0;
            while(index<lineToDelete->size){
                toPut[index]=toCopy[index];
                index++;
            }
            previousLine->next = lineToDelete->next;
            if(lineToDelete->next){                
                (lineToDelete->next)->previous = previousLine;
            }
            freeOneLine(lineToDelete);
            updateLine(previousLine);
            updateLineNoAfter(previousLine);
        }
    }else{
        //delete one char or a chinese
        char* startP,*beforeP;
        jumpCols(colsToOvercome,lineToDelete->content,&startP,&beforeP);
        char* newP;
        int jumpCol;
        jumpLineUnit(beforeP,&newP,&jumpCol);
        if(jumpCol>1){
            startP = beforeP;
        }else{
            jumpLineUnit(startP,&newP,&jumpCol);
        }
        if(startP == newP||newP==0){
            return;
        }else{
            char *toMove = newP;
            char *toPut = startP;
            while(toMove&&*toMove){
                *toPut = *toMove;
                toPut++;
                toMove++;
            }
            while(toPut!=toMove){
                *toPut=0;
                toPut++;
            }
        }
        updateLine(lineToDelete);
        if(cursorX-jumpCol<0){
            if(cursorY==0){
                mCursor.y=0;
                mCursor.x=0;
            }else{
                mCursor.y = cursorY - 1;
                mCursor.x = COLS - (jumpCol - cursorX);
            }
        }else{
            mCursor.y = cursorY;
            mCursor.x = cursorX - jumpCol;
        }
    }
}
void doExit(){
    mExit = true;
    free(rawInput);
    free(tmp);
    freeFunctionList(functionList);
    freeLines();
}

int doInput(){
    needRefresh = false;
    memset(rawInput,0,sizeof(int)*TMP_SIZE);
    int index = 0;
    nodelay(editScr,FALSE);
    int getC = wgetch(editScr);
    nodelay(editScr,TRUE);
    while(getC!=ERR){
        rawInput[index++]=getC;
        getC=wgetch(editScr);
    }
    nodelay(editScr,FALSE);
    return index;
}
void newAppendingScreenOut(){
   Line *endLine,*startLine;
   int startLineShift;
   endLine = lineList->next;
   while(endLine->next){
       endLine = endLine->next;
   }
   int appears = endLine->lines;
   if(appears > EDITWIN_H) {
        startLineShift = endLine->lines - EDITWIN_H;
   }else{
        Line*nextLine = endLine;
        startLine = endLine->previous;
        while(appears<EDITWIN_H&&startLine!=lineList){
            appears += startLine->lines;
            nextLine = startLine;
            startLine = startLine->previous;
        }
        startLine = nextLine;
        if(appears>=EDITWIN_H){
            startLineShift = appears-EDITWIN_H;
        }else{
            startLineShift = -1;
        }
   }
   wclear(editScr);
   wmove(editScr,0,0);
   int colsToOvercome;
   char* startP;
   if( endLine == startLine ){
       if(startLineShift == -1){
           wprintw(editScr,"%s",endLine->content);
           screenLine.lineNo = endLine->lineNo;
           screenLine.shift = 0;
       }else{
           colsToOvercome = startLineShift * COLS;
           jumpCols(colsToOvercome,endLine->content,&startP,0);
           wprintw(editScr,"%s",startP);
           screenLine.lineNo = endLine->lineNo;
           screenLine.shift = startLineShift;
       }
   }else{
       if(startLineShift == -1){
           startLine = lineList->next;
           while(startLine){
               wprintw(editScr,"%s",startLine->content);
               startLine = startLine->next;
           }
           screenLine.lineNo = 1;
           screenLine.shift = 0;
       }else{
           screenLine.lineNo = startLine->lineNo;
           screenLine.shift = startLineShift;
           colsToOvercome = startLineShift * COLS;
           jumpCols(colsToOvercome,startLine->content,&startP,0);
           wprintw(editScr,"%s",startP);
           startLine = startLine->next;
           while(startLine){
               wprintw(editScr,"%s",startLine->content);
               startLine = startLine->next;
           }
       }
   }
   wrefresh(editScr);
}
void insertScreenOut(){
    char *startP,*endP;
    Line *endLine;
    int endLineAppears;
    Line*tmpLine = lineList->next;
    while(tmpLine->lineNo != screenLine.lineNo){
        tmpLine = tmpLine->next;
    }
    int colsToOvercome = screenLine.shift * COLS;
    jumpCols(colsToOvercome,tmpLine->content,&startP,0);
    int appears = tmpLine->lines - screenLine.shift;
    if(appears>EDITWIN_H){
        endLine = tmpLine;
    }else{
        Line*previous=tmpLine;
        endLine=tmpLine->next;
        
        while(appears<EDITWIN_H&&endLine){
            appears += endLine->lines;
            previous = endLine;
            endLine = endLine->next;
        }
        endLine = previous;
        if(appears>=EDITWIN_H){
            endLineAppears = EDITWIN_H- (appears-endLine->lines);
        }else{
            endLineAppears = -1;//endline print all
        }

    }
    wclear(editScr);
    wmove(editScr,0,0);
    if(tmpLine == endLine){        
        if(endLineAppears == -1){
            wprintw(editScr,"%s",endLine->content);
        }else{
            colsToOvercome = endLineAppears * COLS;
            jumpCols(colsToOvercome,startP,&endP,0);
            char x = *endP; 
            *endP = 0;
            wprintw(editScr,"%s",startP);
            *endP = x;
        }
    }else{
        wprintw(editScr,"%s",startP);    
        tmpLine = tmpLine->next;
        while(tmpLine->lineNo < endLine->lineNo){
            wprintw(editScr,"%s",tmpLine->content);
            tmpLine = tmpLine->next;
        }    
        if(endLineAppears == -1){
            wprintw(editScr,"%s",endLine->content);
        }else{
            colsToOvercome = endLineAppears * COLS;
            jumpCols(colsToOvercome,endLine->content,&endP,0);
            char x = *endP; 
            *endP = 0;
            wprintw(editScr,"%s",endLine->content);
            *endP = x;
        }
    }
    wrefresh(editScr);
}

void screenOut(){
    if(newAppending){
        newAppendingScreenOut();
    }else{
        insertScreenOut();
    }
}
void doOutput(int size){
    if(size == 1){
        //try function
        int cmd = rawInput[0];
        Func *testFunc = functionList->next;
        while(testFunc){
            if(testFunc->invokeKey == cmd){
                (*(testFunc->func))();
                break;
            }else{
                testFunc = testFunc->next;
            }
        }
        //or it's a character
        if(!testFunc){
            char output = cmd;
            //wprintw(editScr,"%c", output);    
            insert(&output,1);
        }
        
    }else{
        //it's characters by inputmethod or chinese,anyway not function
        int i;
        for(i=0;i<size;i++){
            tmp[i] = rawInput[i];
        }
        tmp[size]=0;
        //wprintw(editScr,"%s",tmp);
        insert(tmp,size);
    }
    if(needRefresh){
        screenOut();
    }
    if(needAdjustCursor){
        needAdjustCursor = false;
        wmove(editScr,mCursor.y,mCursor.x);
    }
}
