/*
 * test.cpp
 *
 *  Created on: 2012-12-3
 *      Author: mtawaken
 */

#include<stdio.h>
#include"HashMap.h"
int main(){
	HashMap map;
	map.put(1,2);
	map.put(2,3);
	map.put(1,4);
	printf("%d",map.get(1));
}

