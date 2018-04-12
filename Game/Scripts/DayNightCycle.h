#pragma once
#include "components\Light.h"

enum class TIME : bool {
	DAY = true,
	NIGHT = false
};
class DayNightCycle
{
public:
	DayNightCycle();
	void OnLoad();
	void Update(double dt);
	/** Get the current time of the game: ENUM TIME::DAY or TIME::FALSE*/
	TIME GetTime();
private:
	TIME time;
	Light * directional;
	float angle = 0;
	float rotation = 0;
	float adjustedAngle = 0;
	float distance = 10000000;

	vec3 color;
	static const vec3 DAYCOLOR;
	static const vec3 DUSKCOLOR;
	static const vec3 DAWNCOLOR;
	static const vec3 NIGHTCOLOR;
};