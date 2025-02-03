#pragma once
#define BOARD_COL	10
#define BOARD_ROW	18

#define SX			3
#define SY			0

class Document
{
	static Document* singleton;

public :
	static Document* GetSingleton();
	
	void MakeDiagram();

	bool MoveDown();
	bool MoveLeft();
	bool MoveRight();

};

