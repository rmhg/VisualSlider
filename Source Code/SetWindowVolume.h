#pragma once
#include <stdlib.h>
#include <iostream>
#include <fstream>
/*
*
* @author Rahul Mishra
* This Is The Class That Manipulates The Volume Of The Windows
* Using AutoHotKey 
* It Will Only Works If U Have 'AutoHotKey' installed in "c://program files"
* Or Change The ahk_path
* change The script_path To a Exsisting Place Except C (Or the Program Going To Need Admin Priviledges).
**\
*/
class SetWindowVolume {
	std::fstream obj;
	std::string ahk_path;
	std::string script_path;
	std::string cmd;
	int vol;
public :
	SetWindowVolume()
	{
		vol = 0;
	}
	bool setVol(int v)
	{
		vol = v;
		if (vol > 100)
			vol = 100;
		vol = abs(vol);
		ahk_path = "\"C://Program Files/AutoHotKey/AutoHotKey.exe\"";
		script_path = "f://s.ahk";
		cmd = ahk_path + " " + script_path;
		makeScript();
		if (system(cmd.c_str()))
			return true;
		return false;
	}
	void makeScript()
	{
		obj.open(script_path,std::ios::out|std::ios::trunc);
		obj << "SoundSetWaveVolume, "<< vol;
		obj.close();
	}
};