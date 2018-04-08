#include "DayNightCycle.h"
#include "core\GameEngine.h"
#include "glm\glm.hpp"
#include "glm\gtx\compatibility.hpp"

const vec3 DayNightCycle::DAYCOLOR = vec3(1.0f);
const vec3 DayNightCycle::DAWNCOLOR = vec3(0.6f, 0.4f, 0.4f);
const vec3 DayNightCycle::DUSKCOLOR= vec3(0.6f, 0.2f, 0.2f);
const vec3 DayNightCycle::NIGHTCOLOR = vec3(0.05f);
DayNightCycle::DayNightCycle()
{
}
void DayNightCycle::OnLoad()
{
	//Set up our Directional Light
	GameObject *dirLightObj = GameEngine::manager.gameObjectManager->CreateGameObject("dirLight");
	directional = Light::Create(dirLightObj, DIRECTIONAL_LIGHT);
	LightProperties dirProp = {
		DIRECTIONAL_LIGHT,
		vec3(0.7f),
		vec3(0.7f),
		vec3(0.05f),

		1.0f, 0.1f, 3.0f
	};

	directional->SetLightProperties(dirProp);

	directional->transform->SetPosition(vec3(10000000, 10000000, 1000000));

	time = TIME::NIGHT;

	color = DAWNCOLOR;
}

void DayNightCycle::Update(double dt)
{
	angle += 360/60 * dt;
	adjustedAngle += 360 / 60 * dt;
	rotation += 360 / 60 * dt;

	if (adjustedAngle > 180)
	{
		adjustedAngle = 0;
	}
	if ((int(angle) / 180) % 2 == 0)
	{
		time = TIME::DAY;
	}
	else {
		time = TIME::NIGHT;
	}

	if (time == TIME::DAY)
	{
		if (adjustedAngle > 0 && adjustedAngle < 40)
		{
			color = lerp(color, DAWNCOLOR, 0.1f * float(dt));
		}
		else if (adjustedAngle >= 40)
		{
			color = lerp(color, DAYCOLOR, 0.1f * float(dt));
		}
		else if (adjustedAngle > 140)
		{
			color = lerp(color, DUSKCOLOR, 0.1f * float(dt));
		}
	}
	else if (time == TIME::NIGHT)
	{
		if (adjustedAngle > 0 && adjustedAngle < 40)
		{
			color = lerp(color, NIGHTCOLOR, 0.2f * float(dt));
		}
		else if (adjustedAngle >= 40)
		{
			color = lerp(color, NIGHTCOLOR, 0.2f * float(dt));
		}
		else if (adjustedAngle > 130)
		{
			color = lerp(color, DAWNCOLOR, 0.1f * float(dt));
		}

	}

	/*color.x = min(0.1f, color.x);
	color.y = min(0.1f, color.y);
	color.z = min(0.1f, color.z);*/
	vec3 position;
	float x, y, z;
	x = cos(radians(adjustedAngle)) * sin(radians(rotation)) * distance;
	y = sin(radians(adjustedAngle)) * sin(radians(rotation)) * distance;
	z = cos(radians(rotation)) * distance;

	position = vec3(x, y, distance);
	directional->transform->SetPosition(position);

	auto prop = directional->GetProperties();
	prop.ambient = color;
	prop.diffuse = color;

	directional->SetLightProperties(prop);
}

TIME DayNightCycle::GetTime()
{
	return time;
}
