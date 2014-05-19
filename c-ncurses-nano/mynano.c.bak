/*
说明
编译
   gcc -g -o a.exe mynano.c -I/usr/include/ncursesw -lncursesw
调试
   先英语 再中文 再特殊符号(例如<- del 回车)
调试方法 参照gdb的attach命令

////////////////////////////////
struct

123 456 78 8   87 78 67

main
  while
    do_input
    do_output
do_input
  if inputlen == 0
     getinputs
  inputs[0]->returnInt
     
do_output
  if returnInt isnot func
    subinputs[]=returninput
  if func or inputs==0 then
    if subinputs then output 
  if func
   execfunc
///////////////////////////////
//scroll
//curses的wscrl用处不大，出界的行，再次回到窗口中是就空了
//scroll的原理
file    win
-----   -----
|   ｜  |   |
|   ｜  |   |
|   ｜  -----
|   ｜ 
-----
当up滚动时
-----   
|   ｜  -----
|   ｜  |   |
|   ｜  |   |
|   ｜  -----
-----
所以file不动，而win在动
只要1 改动winbegin winend
    2 输入file中winbegin到end的数据即可
///////////////////////////////
question
无法显示中文 -Incursew -lncursew
无法边输入边调试，所以写入文件，例如王文:  
  我是王文献,无法一口气输入 则分段输出 找出原因
小例子实验，例如先输出出界再滚动后的效果
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <locale.h>

typedef struct linestruct {
  char* data;char* pdata_x; int lineno;
  struct linestruct* prev,*next; int win_x;
} linestruct;

typedef struct funcstruct{
  void(*func2)();
  int seq;
  struct funcstruct* next;
} funcstruct;

int do_input();
void do_output(int);
  void do_outputchar(char*);
  void do_exit(); 
  void do_backspace();
  void sub_outputline(linestruct*);  
  void do_delete();
  void do_left();
  void do_right();
  void do_enter(); 
  void do_up(); 
  void do_down();
  void finish2();
void debug2(funcstruct* func);
int getcols(char* p);
void createfunc(funcstruct** pfunc,funcstruct** ptmpfunc2,int dosth,int seq);
void readfile(char* p);

WINDOW *topwin,*editwin,*bottomwin;

linestruct* curline;
funcstruct* funcs;
int* inputs=0; int inputlen=0;
int* subinputs=0; 
int subinputlen=0;
FILE* fdebug=0;
int beginlineno=0, endlineno=9;

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
  getchar();

  setlocale(LC_ALL,""); //???
  ///////////////////////////////////////////////
  //init window

  //tcgetattr  

  //curses
  initscr();
  raw(); noecho();
  
  //window
  topwin = newwin(1,COLS,0,0);
  editwin = newwin(10,COLS,1,0);
  bottomwin = newwin(1,COLS,11,0);
  keypad(topwin, TRUE); keypad(editwin, TRUE); keypad(bottomwin, TRUE);

  //prompt
  start_color(); 
  init_pair(1, COLOR_RED, COLOR_BLACK);
  wattrset(topwin,COLOR_PAIR(1)); wattrset(bottomwin,COLOR_PAIR(1)); 
    //wattron?
  mvwprintw(topwin, 0, 0, "%s",    "-------------------mynano");
  mvwprintw(bottomwin, 0, 0, "%s", "-------------------CtrlX to exit");
  
  wrefresh(topwin); wrefresh(bottomwin); 
  
  //////////////////////////////////////////////////
  //init data
  funcstruct* func,*tmpfunc2;
    func = malloc(sizeof(funcstruct));
    func->func2 =&do_exit;
    func->seq = 'X'-64;  //无论是输入X还是x都触发
    func->next = NULL;
    tmpfunc2 = func;

    //ctrl_?与keyleft等的冲突?
    createfunc(&func,&tmpfunc2,(int)&do_backspace,8); //望8完8王 最后才得到王
    createfunc(&func,&tmpfunc2,(int)&do_backspace,KEY_BACKSPACE);
    createfunc(&func,&tmpfunc2,(int)&do_left,KEY_LEFT);
    createfunc(&func,&tmpfunc2,(int)&do_right,KEY_RIGHT);
    createfunc(&func,&tmpfunc2,(int)&do_delete,KEY_DC);
    createfunc(&func,&tmpfunc2,(int)&do_enter,'\n');
    createfunc(&func,&tmpfunc2,(int)&do_up,KEY_UP);
    createfunc(&func,&tmpfunc2,(int)&do_down,KEY_DOWN);
    
    funcs=func;

  //if args then readfile
  if (argc>1) 
     readfile(argv[1]);
  else
  {
    curline=malloc(sizeof(linestruct));
    memset(curline,0,sizeof(linestruct));
    curline->pdata_x=curline->data = malloc(1); memset(curline->data,0,1); 
  }

  //output
  wmove(editwin,0,0); //为何光标跑到了bottomwin?
  wrefresh(editwin);
  //////////////////////////////////////////////////
  //main
  int cInput; 
  while(true)
  {
    cInput = do_input();
    do_output(cInput);
  }
  
  exit(0); 
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
int do_input()
{
  int tmpi;
  int ret;
 
  //get 
  if (inputlen == 0)
  {
    tmpi=wgetch(editwin);      
    inputs = malloc(sizeof(int));
    inputs[inputlen++]=tmpi;
 
    nodelay(editwin,TRUE); //?
    while(1)
    {
      if ((tmpi=wgetch(editwin))==ERR) break;
      inputs = realloc(inputs,(inputlen+1)*sizeof(int));
      inputs[inputlen++]=tmpi;
    }
    nodelay(editwin,FALSE);
  }

  //inputs->returnInt
  ret = inputs[0];  
  memmove(inputs,inputs+1,sizeof(int)*(inputlen-1) );
  inputlen--;

  return ret;
}

void do_output(int cInput)
{
  int i;
  //set func
  funcstruct* func=0;  

  funcstruct* tmpfunc;
  for (tmpfunc=funcs;tmpfunc!=NULL;tmpfunc=tmpfunc->next)
  {
    if (tmpfunc->seq == cInput)
    {
       func = tmpfunc; 
       break;
    }
  }   

  //if not func, remember the input
  if (!func) 
  {
    if (!subinputs) subinputs=malloc(sizeof(int)*1);
    else subinputs=realloc(subinputs,sizeof(int)*(subinputlen+1));
    subinputs[subinputlen++]=cInput;
  }
  //if func or inputs=0 then
  if (func || (inputlen==0))
  {
     debug2(func);
     //if subinputs then output it
     if (subinputlen>0)
     { 
        char* chars=malloc(sizeof(char)*(subinputlen+1));
          //写成sizeof(chars)导致无法输入四个字的中文
        memset(chars,0,sizeof(char)*(subinputlen+1)); 
        for (i=0;i<subinputlen;i++)
           chars[i]=(char)(subinputs[i]);
        subinputlen=0;
        do_outputchar(chars);
     }
  }
  
  //if func then do func
  if (func)
  { 
    (*(func->func2))(); 
  }
 
  //refresh 
  if (inputlen==0)
  {
    wmove(editwin,curline->lineno-beginlineno,curline->win_x);
    wrefresh(editwin);  
  }
} 
void do_outputchar(char* chars)
{
  int charslen=strlen(chars); //not mblen,maybe望文
  int i;
  int len = curline->pdata_x-curline->data;
  //curline->data
     //如果写成realloc(p) 则当输入10个字母时，数据突然丢失
     //并且应该相应改动pdata_x? 需要改动相关的指针吗? 
  char* data2 = curline->data = 
      realloc(curline->data, strlen(curline->data)+charslen+1);
  char* data_x2 = curline->pdata_x=curline->data+len;  
 
  memmove(data_x2+charslen,
          data_x2,
          strlen(data_x2) + 1);
  memcpy(data_x2,  chars,charslen);
  
  //curline->data_x
  curline->pdata_x+=charslen;

  //output 
  curline->win_x+=getcols(chars);  
  sub_outputline(curline);
}
//////////////////////////////////////////////////////////////////////////////////////////// 
//////////////////////////////////////////////////////////////////////////////////////////// 
//////////////////////////////////////////////////////////////////////////////////////////// 
// 
void do_backspace()
{
  do_left();
  do_delete();
}
void do_left()
{
  if (curline->pdata_x>curline->data)
  {
     char* p=curline->data;
     int len=0;
     while(p<curline->pdata_x)
     {
       len = mblen(p,MB_CUR_MAX);
       p+=len; 
     }
     curline->pdata_x-=len;

     if (len > 1) //偷懒的写法,汉字的bytelen>1所以winlen=2
        curline->win_x-=2;
     else
       curline->win_x--;
  } 
}
void do_delete()
{
  char* data_x2 = curline->pdata_x;
  int data_x2len = mblen(data_x2,MB_CUR_MAX);
  char* data_x2after = data_x2+data_x2len; 
  char* data_last = curline->data + strlen(curline->data);
  /////////////////////////////oneline
  if (data_x2 < data_last) 
  {
     memmove(data_x2,
          data_x2after,
          strlen(data_x2after) + 1);
     sub_outputline(curline);
  }
  /////////////////////////////lines
  else if (curline->next)
  {
    linestruct* tmpline;

    //data
    linestruct* nextline=curline->next;
    curline->data = realloc(
      curline->data,
      strlen(curline->data) + strlen(nextline->data) + 1);
    memcpy(curline->pdata_x,
           nextline->data,
           strlen(nextline->data) + 1);

    //next prev
    curline->next = nextline->next;
    if (nextline->next)      
       nextline->next->prev=curline;
    free(nextline);
  
    //lineno
    int newlineno = curline->lineno+1;
    for (tmpline=curline->next; tmpline!=NULL; tmpline=tmpline->next)
       tmpline->lineno = newlineno++;
 
    //output    
    for (tmpline=curline; tmpline!=NULL; tmpline=tmpline->next)
       sub_outputline(tmpline);
  }  
}

void do_right()
{
  if (curline->pdata_x<
      curline->data+strlen(curline->data))
  {
     int bytelen=mblen(curline->pdata_x,MB_CUR_MAX);
     curline->pdata_x+=bytelen;
     curline->win_x+=  (bytelen>1)?2:1;
  } 
}

void do_exit()
{
  //writeFile
  linestruct* tmpline,*firstline;
     //既然firstline的特点是prev为0，则使用这种简单的写法，
     //当循环结束，就得到了prev=null的line
  for (firstline=curline;firstline->prev!=NULL;firstline=firstline->prev);
  
  FILE* fa = fopen("tmpfile","w");
  for (tmpline=firstline;tmpline!=NULL;tmpline=tmpline->next)
  {
     fprintf(fa,"%s%c",tmpline->data,'\n');
  }
  fclose(fa);    

  //finish
  finish2();
}

void do_enter()
{
  linestruct* tmpline;
  //////////////////////data
  //data
  linestruct * newline=malloc(sizeof(linestruct));
  
  newline->data = malloc(strlen(curline->pdata_x)+1);
  memcpy(newline->data,
         curline->pdata_x,
         strlen(curline->pdata_x)+1);
  curline->pdata_x[0]=0;

  //pdata and winx
  newline->pdata_x=newline->data;    newline->win_x=0;

  //next prev
  newline->next = curline->next;
  curline->next = newline;   
  newline->prev = curline;
  if (newline->next)
    newline->next->prev=newline;

  //lineno etc..
  int newlineno = curline->lineno+1;
  for (tmpline=newline; tmpline!=NULL; tmpline=tmpline->next)
     tmpline->lineno = newlineno++;
 
  curline = newline;

  /////////////////////////output 
  for (tmpline=curline->prev; tmpline!=NULL; tmpline=tmpline->next)
     sub_outputline(tmpline);

  //if exceed then scroll //same to dodown,so merge!
  if (curline->lineno > endlineno )
  {
    beginlineno++; endlineno++;
    
    for (tmpline=curline; (tmpline)&&(tmpline->lineno>=beginlineno); tmpline=tmpline->prev)
       sub_outputline(tmpline);
  }
}

void do_up()
{
  linestruct* tmpline;
  //if first line,do nothing 
  if (curline->prev == 0) return;

  linestruct* newline = curline->prev;
  newline->pdata_x=newline->data;    newline->win_x=0; 
  curline = newline;
  
  if (curline->lineno < beginlineno )
  {
    beginlineno--; endlineno--;
    
    for (tmpline=curline; (tmpline)&&(tmpline->lineno<=endlineno); tmpline=tmpline->next)
       sub_outputline(tmpline);
  }
}
void do_down()
{
  //if lastline,do nothing
  if (curline->next==0) return;

  linestruct* tmpline;
  linestruct* newline = curline->next;
  newline->pdata_x=newline->data;    newline->win_x=0; 
  curline = newline;

  if (curline->lineno > endlineno )
  {
    beginlineno++; endlineno++;
    
    for (tmpline=curline; (tmpline)&&(tmpline->lineno>=beginlineno); tmpline=tmpline->prev)
       sub_outputline(tmpline);
  }
}
//////////////////////////////////////////////////////////////////////////////////////////// 
//////////////////////////////////////////////////////////////////////////////////////////// 
//////////////////////////////////////////////////////////////////////////////////////////// 
void sub_outputline(linestruct* line)
{
  wmove(editwin,line->lineno-beginlineno,0); wclrtoeol(editwin);  
  mvwprintw(editwin,line->lineno-beginlineno,0,"%s",line->data);
}
void createfunc(funcstruct** pfunc,funcstruct** ptmpfunc2,int dosth,int seq)
{
  *pfunc =malloc(sizeof(funcstruct));
  (*pfunc)->func2 = dosth;
  (*pfunc)->seq = seq; 
  (*pfunc)->next = *ptmpfunc2;
  *ptmpfunc2 = *pfunc;
}
void debug2(funcstruct* func)
{  
  if (!fdebug) fdebug=fopen("tmpdebug","w");

  int i;
  fprintf(fdebug,"\n\n\n======\n");
  //curline
  fprintf(fdebug,"\ndata:%s; pdata:%s; win_x:%d;\n",
    curline->data,
    curline->pdata_x,
    curline->win_x);

  //subinputs
  fprintf(fdebug,"\nsubinputs:");
  for (i=0;i<subinputlen;i++)
    fprintf(fdebug,"%d;",subinputs[i]);
  
  //func 
  fprintf(fdebug,"\nfunc=%d",func?func->seq:0);
  
  //inputs inputlen
  fprintf(fdebug,"\ninputs:");
  for (i=0;i<inputlen;i++)
    fprintf(fdebug,"%d;",inputs[i]);
 
  fflush(fdebug);      
}
int getcols(char* p)
{
   int cols=0;
   int bytelen=0;
   wchar_t wc;
   int charslen=strlen(p);
   char chars[100];
   while(*p)
   {
     mbtowc(&wc,p,MB_CUR_MAX);
     cols+=wcwidth(wc);
     bytelen=mblen(p,MB_CUR_MAX);
     p+=bytelen;
   }
   return cols;
}
void finish2()
{
  fclose(fdebug);
  delwin(topwin); delwin(editwin); delwin(bottomwin); 
  echo(); noraw();  
  endwin();
  exit(0);
}

void readfile(char* filename)
{ 
  //readfile
  linestruct* tmpline,*prevline;
  
  FILE* fa = fopen(filename,"r");
  char buf[100]; int bufsize=sizeof(buf);
  int lineno=0;
  
  //不必管什么效率，只要可读性，所谓印度式写法
  fgets(buf,bufsize,fa); 
  curline = malloc(sizeof(linestruct)); memset(curline,0,sizeof(linestruct));
  curline->pdata_x=curline->data=malloc(strlen(buf)+1);
  strcpy(curline->data,buf);
  curline->lineno=lineno++;
  
  prevline=curline;
  
  while(fgets(buf,bufsize,fa))
  {
    tmpline = malloc(sizeof(linestruct)); memset(tmpline,0,sizeof(linestruct));
    tmpline->pdata_x=tmpline->data=malloc(strlen(buf)+1);
    strcpy(tmpline->data,buf);
    tmpline->lineno=lineno++;

    tmpline->prev=prevline;  prevline->next=tmpline;

    prevline=tmpline;
  }
  
  fclose(fa);    
  
  //output
  for (tmpline=curline; (tmpline)&&(tmpline->lineno<=endlineno); tmpline=tmpline->next)
     sub_outputline(tmpline);
 
}
void debug3(bool condi,char* chars)
{
  if (condi)
  {
    fprintf(fdebug,"%s",chars);fflush(fdebug);
  }   
}
/*
if------------------
  int i=10;

  if (i>1)
  {
    printf("i>1");
  }
  else if (i<100) //短路
  {
    printf("i<100");
  }
*/

