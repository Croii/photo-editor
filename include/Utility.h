#pragma once
#define NOMINMAX
#include <windows.h>
#include <shlobj.h>     // For SHBrowseForFolder
#include <commdlg.h>    // For OPENFILENAME
#include <string>

enum class Orientation
{
	LEFT,
	RIGHT
};

//std::string openFileDialog(const Operation operation);
std::string openFile();
std::string saveFile();