#include "Observer.h"
#include "Event/EventSystem.h"

Observer::~Observer()
{
	{
		REMOVE_OBSERVER
	}
}
