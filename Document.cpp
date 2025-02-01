#include "Document.h"

Document* Document::singleton;

Document* Document::GetSingleton()
{
	if (singleton == 0) {
		singleton = new Document();
	}

	return singleton;
}

void Document::MakeDiagram()
{

}

bool Document::MoveDown()
{
	return false;
}

bool Document::MoveLeft()
{
	return false;
}

bool Document::MoveRight()
{
	return false;
}
