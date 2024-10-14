#include "../../include/Utility.h"

std::string openFile()
{
	char szFile[260] = { 0 };
	HWND hwnd = NULL;  // Owner window (can be NULL)
	// Use the common file open dialog for file selection (ANSI version)
	const char* filter = "Image Files\0*.jpg;*.jpeg;*.png;*.bmp;*.gif;*.tiff\0";

	OPENFILENAMEA ofn;  // Common dialog box structure (A for ANSI version)

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFile = szFile;
	ofn.lpstrFile[0] = '\0';  // Initialize buffer to empty string
	ofn.nMaxFile = sizeof(szFile);
	ofn.lpstrFilter = filter;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	// Display the Open dialog box for file selection
	if (GetOpenFileNameA(&ofn) == TRUE) {
		return std::string(ofn.lpstrFile);  // Return the selected file path
	}
	return std::string();
}

std::string saveFile()
{
	char szFile[260] = { 0 };
	BROWSEINFOA bi = { 0 };
	bi.lpszTitle = "Select Folder";
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;  // Only show file system directories

	// Display the folder selection dialog (ANSI version)
	LPITEMIDLIST pidl = SHBrowseForFolderA(&bi);

	if (pidl != NULL) {
		// Get the folder path from the item ID list (ANSI version)
		SHGetPathFromIDListA(pidl, szFile);
		IMalloc* imalloc = 0;
		if (SUCCEEDED(SHGetMalloc(&imalloc))) {
			imalloc->Free(pidl);  // Free memory
			imalloc->Release();
		}
		return std::string(szFile);  // Return the selected folder path
	}
	return std::string();
}
