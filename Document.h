#pragma once
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

