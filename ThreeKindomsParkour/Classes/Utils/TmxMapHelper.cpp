#include "TmxMapHelper.h"

USING_NS_CC;
using namespace std;

void TmxMapHelper::objectToVertices(int mapHeihgt, int groupHeight,
	ValueMap &object, vector<float> &vertices)
{
	auto it = object.find("points");
	if (it == object.end())
		return;

	Vec2 origin(object["x"].asInt(), object["y"].asInt());
	origin.y = mapHeihgt - origin.y;

	ValueVector &points = it->second.asValueVector();
	vertices.clear();
	vertices.reserve(points.size() * 2);
	for (size_t i = 0; i < points.size(); ++i)
	{
		ValueMap &point = points[i].asValueMap();
		float x = origin.x + point["x"].asInt();
		float y = groupHeight - (origin.y + point["y"].asInt());
		vertices.push_back(x);
		vertices.push_back(y);
	}
}