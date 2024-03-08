#pragma once

class IManagerInterface
{
public:
	virtual void ObjectiveFound(int DroneID, FString ClassName) = 0;
	virtual float GetGroupDroneSpeed() = 0;
};
