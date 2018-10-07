// FSMPattern.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include "Animation.h"
#include "State.h"
#include "Idle.h"
#include "Jumping.h"
#include "Climbing.h"
#include <chrono>
#include <thread>

using namespace std;

int main()
{
	
    //std::cout << "Hello World!\n";
	Animation fsm; int i = 0;
	while(true)
		if(i == 0)
	{
			fsm.jumping();
			this_thread::sleep_for(chrono::microseconds::duration(1000));
			//this_thread::sleep_for(chrono::milliseconds dura(1000));
			i = 1;
		}
		else
		{
			fsm.climbing();
			this_thread::sleep_for(chrono::microseconds::duration(1000));
			//this_thread::sleep_for(chrono::milliseconds dura(1000));
			i = 0;
		}

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
