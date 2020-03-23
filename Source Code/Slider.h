#pragma once
/*
* @author : Rahul Mishra
*
*
* This Class Is For Detection Of Position Of Slider ;
* Which Is Blue Color :
* Working 
* It Captures The IMage Which
* Reduces The Resolution Of Image
* Then It Removes The Noise Using GaussianBlur
* Then It Switch To The HSV (Hue,Saturation And Value) Model
* And Then It Filters All Shades Of Blue Color And Then Remove Everything Else
* After That It Detects The First Lit Up Pixel Position And Give Correspoinding Value Based On Slider Position
* Easy.
* Streaming Link For LiveFeed Is http://192.168.43.1:8080/video, The Streaming Content Type is MPEG
* Since OpenCV has ffmpeg supported/included.
*
*/
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <Windows.h>
#include <iostream>
#include "SetWindowVolume.h"
class Slider
{
	cv::VideoCapture cap;
	std::string ImgPath;
	cv::Mat img;
	SetWindowVolume* op;
public :
	Slider();
	void Capture();
	int Detect(cv::Mat);
};
Slider::Slider()
{ 
	op = new SetWindowVolume();
	std::cout << std::endl << "Waiting For Feed" << std::endl;
	cap = cv::VideoCapture("http://192.168.43.1:8080/video");
	std::cout << std::endl << "Waiting For Feed" << std::endl;
	Capture();
	
}
void Slider::Capture()
{
	system("cls");
	cv::Mat frame;
	if (!cap.isOpened())
	{
		std::cout << "Not Getting The Video Feed!" <<std::endl;
		return;
	}
	int val = 0;
	while (true)
	{
		std::cin.clear();
		cap >> frame;
		if (!frame.empty())
		{
			val = Detect(frame);
		}
	    std::cout << "Curent Value :" << val << " ";
		op->setVol(val);
		system("cls");
		//Sleep(30);
	}
}
int Slider::Detect(cv::Mat img)
{
	
	int val = 0;
	bool found = false;
	cv::Mat src = img;
	cv::resize(src, src, cv::Size(100,100), 0, 0, 1);
	cv::GaussianBlur(src, src, cv::Size(5, 5), 0);
	cv::cvtColor(src, src, cv::COLOR_BGR2HSV);
	cv::inRange(src, cv::Scalar(35, 140, 60),cv::Scalar(255,255,180) , src);
	//cv::imshow("khsab",src);
	//cv::waitKey(1);
	for (int i = 0;i < src.cols && !found;i++)
	{
		for (int j = 0;j < src.rows && !found;j++)
		{
			if (src.at<bool>(j, i))
			{
				found = true;
				val =  j;
	
			}
		}
	}
	//if(val != 0 )
	//std::cout << (100 - val)  << " " ;
	int netval = 100 - val;
	if (val == 0)
		netval = 0; 
	return netval;
}
