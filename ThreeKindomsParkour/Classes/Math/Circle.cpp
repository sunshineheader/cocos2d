#include "Circle.h"

USING_NS_CC;

Circle::Circle()
{
	setCircle(0, 0, 0);
}

Circle::Circle(float x, float y, float radius)
{
	setCircle(x, y, radius);
}

Circle::~Circle()
{

}

Circle::Circle(const Circle &other)
{
	setCircle(other);
}

Circle& Circle::operator= (const Circle &other)
{
	setCircle(other);
	return *this;
}

void Circle::setCircle(float x, float y, float radius)
{
	this->origin.x = x;
	this->origin.y = y;
	this->radius = radius;
}

void Circle::setCircle(const Circle &other)
{
	setCircle(other.origin.x, other.origin.y, other.radius);
}

bool Circle::containsPoint(float x, float y) const
{
	x = this->origin.x - x;
	y = this->origin.y - y;
	return x * x + y * y <= this->radius * this->radius;
}

bool Circle::containsPoint(const Vec2 &point) const
{
	return containsPoint(point.x, point.y);
}

bool Circle::containsCircle(const Circle &other) const
{
	float dx = this->origin.x - other.origin.x;
	float dy = this->origin.y - other.origin.y;
	float maxDistanceSqrd = dx * dx + dy * dy + other.radius * other.radius;

	return maxDistanceSqrd <= this->radius * this->radius;
}

bool Circle::overlapsCircle(const Circle &other) const
{
	float dx = this->origin.x - other.origin.x;
	float dy = this->origin.y - other.origin.y;
	float distance = dx * dx + dy * dy;
	float radiusSum = this->radius + other.radius;

	return distance < radiusSum * radiusSum;
}
