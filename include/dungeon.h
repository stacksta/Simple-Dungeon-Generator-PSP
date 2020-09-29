#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROWS 10
#define COLS 10

int randomRange(int low, int high)
{
	return (rand() % (high - low + 1)) + 1;
}


void generate(int map[ROWS][COLS], int noOfRooms)
{
	//int map[ROWS][COLS] = {0};

	int neighborCount = 0;

	//int noOfRooms = 7;

	int roomCount = 1;

	int roomXList[COLS] = {0};
	int roomYList[ROWS] = {0};

	srand(time(0));

	int x = randomRange(1, ROWS - 2);
	int y = randomRange(1, COLS - 2);

	//set the start room
    map[x][y] = 1;
    roomCount++;
    roomXList[0] = x;
    roomYList[0] = y;

    x = 1;//use it for list index later
		
	//not more than room count
	while(roomCount != noOfRooms + 1) 
	{
		int sx = randomRange(1, ROWS - 2);
		int sy = randomRange(1, COLS - 2);

		//make sure room isnt same as previous room or start room
		int count;
		for(count= 0;count<COLS;count++) 
		{
			while((sx == roomXList[count] && roomYList[count])/*previous rooms*/ || (sx == roomXList[0] && sy == roomYList[0])/*start room*/)
			{
				sx = randomRange(1, ROWS - 2);
				sy = randomRange(1, COLS - 2);
			}
		}

		//check for neighbors
		// check left
		if(map[sx-1][sy] != 0)
			neighborCount++;
		// check top
		if(map[sx][sy+1] != 0) 
			neighborCount++;
		// check bottom
		if(map[sx][sy-1] != 0) 
			neighborCount++;
		// check right
		if(map[sx+1][sy] != 0) 
			neighborCount++;

		//if assumed room has no or less than 2 neighbors
		//make it a room!
		if(neighborCount > 0 && neighborCount < 3) 
		{
			map[sx][sy] = roomCount;
			roomCount++;
			neighborCount = 0;
			roomXList[x] = sx;
			roomYList[x] = sy;
			x++;
		}
		else 
		{
			neighborCount = 0;
		}
	}


	//for debug
	//print the map array
	// int i,j;
	// for(i = 0;i < ROWS;i++) 
	// {
	// 	for(j = 0;j < COLS;j++) 
	// 	{
	// 		printf("%d ",map[i][j]);
	// 	}
	// 	printf("\n");
	// }

	// return 0;
}