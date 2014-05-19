/*
 * =====================================================================================
 *
 *       Filename:  curses.c
 *
 *    Description:  This is used to test curses
 *
 *        Version:  1.0
 *        Created:  2012年10月19日 09时48分12秒
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
int main(){
    initscr();
    const char str[] = "Lily,yesterday i had a dream,that all will come true!You never understand,the day you went away,how my heart broke. However...";
    const char str2[] = "NOW YOU WILL PAY!!!";
    int len = strlen(str);
    int index = 0;
    move(1,4);
    while(index<len){
        addch(str[index]);
        index++;
        refresh();
        usleep(150000);
    }
    flash();
    usleep(500000);
    flash();
    usleep(500000);
    
    len = strlen(str2);
    move(LINES/2,(COLS-len)/2);
    index=0;
    attron(A_STANDOUT);
    while(index<len){
        addch(str2[index]);
        index++;
        refresh();
        usleep(150000);
    }
    sleep(5);

    endwin();
    exit(EXIT_SUCCESS);
}
