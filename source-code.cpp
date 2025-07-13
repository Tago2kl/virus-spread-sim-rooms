

// Made by Hector D. Carlo and Hector J. Carlo
//12/31/23


#include <SDL.h>
#include <iostream>
#include <ctime>
#include <cstdlib> 
#include <windows.h>


void Move(double target[][6], int xPos, int yPos, int i, double& nextX, double& nextY)
{

	double iniX = xPos ;
	double iniY = yPos;
	//std::cout << iniX << "\n" <<  iniY << "\n";
	const double vel = target[i][2];
	int left = target[i][3];
	int up = target[i][4];
	double m = target[i][5];
	double a = (pow(m, 2) + 1);
	double b = (-2 * iniX - 2 * pow(m, 2) * iniX);
	double c = (pow(m, 2) * pow(iniX, 2)) + pow(iniX, 2) - pow(vel, 2);

	

	if (up == 1 && left == 0)// up right
	{
		nextX = (-1) * b + sqrt(pow(b, 2) - 4 * a * c);
		nextX = nextX / (2 * a);
		nextY = (m * nextX) - (m * iniX) + iniY;
	}
	else if (up == 0 && left == 1)//down left 
	{
		nextX = (-1) * b - sqrt(pow(b, 2) - 4 * a * c);
		nextX = nextX / (2 * a);
		nextY = (m * nextX) - (m * iniX) + iniY;
	}
	else if (up == 1 && left == 1)// up left 
	{
		nextX = (-1) * b - sqrt(pow(b, 2) - 4 * a * c);
		nextX = nextX / (2 * a);
		nextY = (m * nextX) - (m * iniX) + iniY;
	}
	else if (up == 0 && left == 0)//down right 
	{
		nextX = (-1) * b + sqrt(pow(b, 2) - 4 * a * c);
		nextX = nextX / (2 * a);
		nextY = (m * nextX) - (m * iniX) + iniY;
	}
	
	
}

int main(int argc, char* argv[])
{
	//-----Variable Definition-------//
	const int wh = 400;
	const int vel = 5;
	const int NumRectangles = 50;
	const int Targets = NumRectangles;
	double target[NumRectangles][6]; //xTar,yTar,vel, left, up, m
	double status[NumRectangles][3]; // xPos , yPos ,infected
	bool running = true;
	double xPos = 0;
	double yPos = 0;
	double xTar = 0;
	double yTar = 0;
	double infected = false;
	double xMove = 0;
	double yMove = 0;
	double xTarMove = 0;
	double yTarMove = 0;
	int done = 0;
	int allInfected = false;
	double nextX;
	double nextY;
	int changed = 0; //reached target, get new coordinates
	double sRadius = 0;
	int steps = 0;

	for (int i = 0; i < NumRectangles; i++)
	{
			status[i][2] = 0;
	}
	status[0][2] = 1;

	//-----SDL Setup-------//
	SDL_Init(SDL_INIT_EVERYTHING);
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "no video \n" <<
			SDL_GetError();
	}
	else
	{
		std::cout << "yes video \n";
	}

	SDL_Window* window = nullptr;
	SDL_Surface* screen = SDL_GetWindowSurface(window);
	window = SDL_CreateWindow("Sciene Fair", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 600, 400, SDL_WINDOW_SHOWN);
	SDL_Renderer* renderer = nullptr;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	SDL_Rect rectangles[NumRectangles];

	//seeded random
	srand(33); // srand(time(0));
	//delta time 
	Uint32 lastTicks = SDL_GetTicks();
	////////Testing new init
	//SDL_Init(SDL_INIT_VIDEO);


	//initialize rects
	for (int i = 0; i < NumRectangles; i++)
	{
		
		xPos = rand() % 600;
		yPos = rand() % 400;
		status[i][0] = xPos;
		status[i][1] = yPos;
		rectangles[i].x = xPos;
		rectangles[i].y = wh - yPos;
		rectangles[i].w = 4;
		rectangles[i].h = 4;
		target[i][0] = rand() % 600;
		target[i][1] = rand() % 400;
		//std::cout << target[i][0] << "\n" << target[i][1] << "\n";
		target[i][2] = vel;
		target[i][5] = (target[i][1] - yPos) / (target[i][0] - xPos);
		if (target[i][0] < xPos)
		{
			target[i][3] = 1; //left = 1
		}
		else
		{
			target[i][3] = 0; //left = 0
		}
		if (target[i][1] < yPos)
		{
			target[i][4] = 0; //up = 0
		}
		else
		{
			target[i][4] = 1; //up = 1
		}

	}
	//create rects
	//std::cout << target[5][0] << "\n" << target[5][1];

	//SDL_Rect targetVisual[NumRectangles];//point
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRects(renderer, rectangles, NumRectangles);
	SDL_RenderPresent(renderer);

	int SDL_PollEvent(SDL_Event * event); //Creates an Initializer for Event
	SDL_Event ev;






	
	
	int numInfected = 1;
	int xcheck = 0 ;
	int ycheck = 0;
	do {
		for (int i = 0; i < NumRectangles; i++)
		{
			//std::cout << rectangles[i].x << "\n";
			//std::cout << rectangles[i].y << "\n \n";
			xPos = status[i][0];
			yPos = status[i][1];
			Move(target, xPos, yPos, i, nextX, nextY);
			xPos = nextX;
			yPos = nextY;
			xcheck = nextX;
			ycheck = nextY;
			rectangles[i].x = xPos;
			rectangles[i].y = wh - yPos;
			//std::cout << target[i][0] << ", " << target[i][1] << " # "<<i<<"\n";
			//std::cout << xcheck << ", " << ycheck << " # " << i << "\n" << "\n";
			//std::cout << rectangles[i].x << "\n" ;
			//std::cout << rectangles[i].y << "\n \n";


			changed = 0;
			 if (target[i][3] == 0 && target[i][4] == 1)//right up
			 {
				if (nextX >= target[i][0] || nextY >= target[i][1])
				{
					changed = 1;
					//xPos = target[i][0];
					//yPos = target[i][1];
			 	}
			 }
			 else if (target[i][3] == 0 && target[i][4] == 0)//right  down
			 {
				 if (nextX >= target[i][0] || nextY <= target[i][1])
				 {
					 changed = 1;
					 //xPos = target[i][0];
					 //yPos = target[i][1];
				 }
			 }
			else if (target[i][3] == 1 && target[i][4] == 0)// left down
			{
				if (nextX <= target[i][0] || nextY <= target[i][1])
				{
					changed = 1;
					//xPos = target[i][0];
					//yPos = target[i][1];
				}
			}
	
			else if (target[i][3] == 1 && target[i][4] == 1)// left up
			{
				if (nextX <= target[i][0] || nextY >= target[i][1])
				{
					changed = 1;
					//xPos = target[i][0];
					//yPos = target[i][1];
				}
			}
		
			if (changed == 1)
			{
				target[i][0] = rand() % 600;
				target[i][1] = rand() % 400;
				if (xPos == target[i][0])
				{
					target[i][0] = rand() % 600;
				}
				target[i][5] = (target[i][1] - yPos) / (target[i][0] -xPos); //update slope

				//---update left and up---//
				if (target[i][0] < xPos)
				{
					target[i][3] = 1; //left = 1
				}
				else
				{
					target[i][3] = 0; //left = 0
				}
				if (target[i][1] < yPos)
				{
					target[i][4] = 0; //up = 0
				}
				else
				{
					target[i][4] = 1; //up = 1
				}
			}
			status[i][0] = xPos;
			status[i][1] = yPos;
			

			
			
			

		}

		SDL_Delay(25);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRects(renderer, rectangles, NumRectangles);
		SDL_RenderPresent(renderer);
		
		for (int i =0; i < NumRectangles; i++)
		{
			for (int j = i+1; j < NumRectangles; j++)
			{
				sRadius = sqrt(pow((rectangles[i].y - rectangles[j].y), 2) + pow((rectangles[i].x - rectangles[j].x), 2));
				if (sRadius <= 2)
				{
					std::cout << "yippie";

					if (status[i][2] == 1 && status[j][2] == 0 )
					{
						status[j][2] = 1;
						numInfected++;
					}
					if (status[i][2] == 0 && status[j][2] == 1)
					{
						status[i][2] = 1;
						numInfected++;
					}
				}
				
			}
		}

	


		
		
		steps++;
		
	} while (numInfected < NumRectangles);
	std::cout << steps;


	// Main loop
	while (running) {
		// Event loop
		while (SDL_PollEvent(&ev) != 0) {
			// check event type
			switch (ev.type) {
			case SDL_QUIT:
				// shut down
				running = false;
				break;
			}
		}

		// Wait before next frame
		SDL_Delay(100);
	}



	//kill
	SDL_DestroyWindow(window);
	SDL_Quit();
	std::cout << "Tago Out \n";
	std::cout << " \n";










	return 0;
}


