/***********************************

	Author: Berkay Barýþ Turan
	Date: 15.05.2021

***********************************/
#include <iostream>
#include <thread>
#include <mutex>
#include <random>
#include <iomanip> //for put_time
#include <time.h>
#include <chrono>
#include <ctime>
#include "HW7DynIntQueue.h"
using namespace std;

int produced_box_number = 1;
bool not_finished = true; 
mutex for_output, for_fillers, for_packagers, for_fillerAndPackager, for_producerAndFiller;

int random_range(const int & min, const int & max) 
{   
	/* Begin: code taken from CS204_Homework7_Spring2021.pdf */
	static mt19937 generator(time(0));     
	uniform_int_distribution<int> distribution(min, max);     
	return distribution(generator); 
	/* End: code taken from CS204_Homework7_Spring2021.pdf */
}

void display_current_time()
{
	/* Begin: code taken from threads8.cpp */
	time_t tt = chrono::system_clock::to_time_t(chrono::system_clock::now());
	struct tm *ptm = new struct tm;
	localtime_s(ptm,&tt);
	/* End: code taken from threads8.cpp */

	cout << put_time(ptm,"%X") << endl;
	delete ptm;
}

void produce(HW7DynIntQueue & filling_queue, int total_box_count, int min_time, int max_time)
{
	while(produced_box_number <= total_box_count)
	{
		this_thread::sleep_for(chrono::seconds(random_range(min_time,max_time)));
		for_producerAndFiller.lock();
		filling_queue.enqueue(produced_box_number);
		for_output.lock();
		cout << "Producer has enqueued a new box " << produced_box_number << 
			" to filling queue (filling queue size is 1): ";
		display_current_time();
		for_output.unlock();
		for_producerAndFiller.unlock();
		produced_box_number++;
	}
}

void filling(HW7DynIntQueue & filling_queue, HW7DynIntQueue & packaging_queue, int filler_id,
			 int fill_min, int fill_max)
{
	while(not_finished)
	{
		for_fillers.lock();
		if(!filling_queue.isEmpty())
		{
			int transfer_box;
			for_producerAndFiller.lock();
			filling_queue.dequeue(transfer_box);
			for_producerAndFiller.unlock();

			for_output.lock();
			cout << "Filler " << filler_id << " started filling the box " << transfer_box << " (filling queue size is " << filling_queue.getCurrentSize() << "): ";
			display_current_time();
			for_output.unlock();
			for_fillers.unlock();

			this_thread::sleep_for(chrono::seconds(random_range(fill_min,fill_max)));

			for_output.lock();
			cout << "Filler " << filler_id << " finished filling the box "<< transfer_box << ": ";
			display_current_time();
			for_output.unlock();

			for_fillerAndPackager.lock();
			packaging_queue.enqueue(transfer_box);
			for_output.lock();
			cout << "Filler " << filler_id << " put box "<< transfer_box << " into packaging queue (packaging queue size is " << packaging_queue.getCurrentSize() << "): ";
			display_current_time();
			for_output.unlock();
			for_fillerAndPackager.unlock();


		}
		else
			for_fillers.unlock();
	}

}

void packaging(HW7DynIntQueue & packaging_queue, int packager_id, int pack_min, int pack_max, int total_box_count)
{
	while(not_finished)
	{
		for_packagers.lock();
		if(!packaging_queue.isEmpty())
		{
			int packaging_box;
			for_fillerAndPackager.lock();
			packaging_queue.dequeue(packaging_box);
			for_fillerAndPackager.unlock();

			for_output.lock();
			cout << "Packager " << packager_id << " started packaging the box " << packaging_box << " (packaging queue size is " << packaging_queue.getCurrentSize() <<"): ";
			display_current_time();
			for_output.unlock();
			for_packagers.unlock();

			this_thread::sleep_for(chrono::seconds(random_range(pack_min,pack_max)));

			for_output.lock();
			cout << "Packager " << packager_id << " finished packaging the box " << packaging_box << ": ";
			display_current_time();
			for_output.unlock();

			if(packaging_box == total_box_count)
			{
				not_finished = false;
			}
		}
		else
			for_packagers.unlock();
	}

}

int main()
{
	HW7DynIntQueue filling_queue, packaging_queue;
	thread producer, filler1, filler2, packager1, packager2;
	int total_box_count, min_production, max_production, min_filling_time, max_filling_time,
		min_packaging_time, max_packaging_time;

	cout << "Please enter the total number of items: ";
	cin >> total_box_count;

	cout << "Please enter the min-max waiting time range of producer:" << endl ;
	cout << "Min: ";
	cin >> min_production;
	cout << "Max: ";
	cin >> max_production;

	cout << "Please enter the min-max waiting time range of filler workers:" << endl ;
	cout << "Min: ";
	cin >> min_filling_time;
	cout << "Max: ";
	cin >> max_filling_time;

	cout << "Please enter the min-max waiting time range of packager workers:" << endl ;
	cout << "Min: ";
	cin >> min_packaging_time;
	cout << "Max: ";
	cin >> max_packaging_time;

	cout << "Simulation starts "; 
	display_current_time();

	producer = thread(&produce,ref(filling_queue),total_box_count,min_production,max_production);
	filler1 = thread(&filling,ref(filling_queue),ref(packaging_queue),1,min_filling_time,max_filling_time);
	packager1 = thread(&packaging,ref(packaging_queue),1,min_packaging_time,max_packaging_time,total_box_count);
	filler2 = thread(&filling,ref(filling_queue),ref(packaging_queue),2,min_filling_time,max_filling_time);
	packager2 = thread(&packaging,ref(packaging_queue),2,min_packaging_time,max_packaging_time,total_box_count);

	producer.join();
	filler1.join();
	packager1.join();
	filler2.join();
	packager2.join();

	cout << "End of the simulation ends: ";
	display_current_time();

	return 0;
}