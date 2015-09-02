#include "Polygon.h"
#include "MathUtils.h"

using namespace Math;

Polygon::Polygon()
: Polygon(std::vector<float>(6, 0))
{
}

Polygon::Polygon(const std::vector<float> &vertices)
: _x(0)
, _y(0)
, _originX(0)
, _originY(0)
, _rotation(0)
, _scaleX(1)
, _scaleY(1)
, _dirty(true)
, _localVertices(vertices)
{
}

Polygon::Polygon(const std::vector<cocos2d::Vec2> &vertices)
: _x(0)
, _y(0)
, _originX(0)
, _originY(0)
, _rotation(0)
, _scaleX(1)
, _scaleY(1)
, _dirty(true)
{
	for (auto point : vertices)
	{
		_localVertices.push_back(point.x);
		_localVertices.push_back(point.y);
	}
}

Polygon::~Polygon()
{
}

void Polygon::setVertices(const std::vector<float> &vertices)
{
	// TODO: throw illegal argument exception if vertices.size < 6
	_localVertices.assign(vertices.begin(), vertices.end());
}

const std::vector<float>& Polygon::getVertices() const
{
	return _localVertices;
}

const std::vector<float>& Polygon::getTransformedVertices()
{
	if (!_dirty) return _worldVertices;
	_dirty = false;

	if (_worldVertices.size() != _localVertices.size()) {
		_worldVertices.assign(_localVertices.size(), 0.0f);
	}

	const float positionX = _x;
	const float positionY = _y;
	const float originX = _originX;
	const float originY = _originY;
	const float scaleX = _scaleX;
	const float scaleY = _scaleY;
	const bool scale = scaleX != 1 || scaleY != 1;
	const float rotation = _rotation;
	const float cos = MathUtils::cosDeg(rotation);
	const float sin = MathUtils::sinDeg(rotation);

	for (int i = 0, n = _localVertices.size(); i < n; i += 2) {
		float x = _localVertices[i] - originX;
		float y = _localVertices[i + 1] - originY;

		// scale if needed
		if (scale) {
			x *= scaleX;
			y *= scaleY;
		}

		// rotate if needed
		if (rotation != 0) {
			float oldX = x;
			x = cos * x - sin * y;
			y = sin * oldX + cos * y;
		}

		_worldVertices[i] = positionX + x + originX;
		_worldVertices[i + 1] = positionY + y + originY;
	}
	return _worldVertices;
}

void Polygon::setOrigin(float originX, float originY)
{
	_originX = originX;
	_originY = originY;
	_dirty = true;
}

float Polygon::getOriginX() const
{
	return _originX;
}

float Polygon::getOriginY() const
{
	return _originY;
}

void Polygon::setPosition(float x, float y)
{
	_x = x;
	_y = y;
	_dirty = true;
}

float Polygon::getPositionX() const
{
	return _x;
}

float Polygon::getPositionY() const
{
	return _y;
}

void Polygon::translate(float x, float y)
{
	_x += x;
	_y += y;
	_dirty = true;
}

void Polygon::setRotation(float degrees)
{
	_rotation = degrees;
	_dirty = true;
}

float Polygon::getRotation() const
{
	return _rotation;
}

void Polygon::rotate(float degrees)
{
	_rotation += degrees;
	_dirty = true;
}

void Polygon::setScale(float scaleX, float scaleY)
{
	_scaleX = scaleX;
	_scaleY = scaleY;
	_dirty = true;
}

void Polygon::setScale(float scale)
{
	setScale(scale, scale);
}

float Polygon::getScaleX() const
{
	return _scaleX;
}

float Polygon::getScaleY() const
{
	return _scaleY;
}

void Polygon::scale(float amount)
{
	_scaleX += amount;
	_scaleY += amount;
	_dirty = true;
}

void Polygon::dirty()
{
	_dirty = true;
}

bool Polygon::contains(float x, float y)
{
	const auto &vertices = getTransformedVertices();
	const int numFloats = vertices.size();
	int intersects = 0;

	for (int i = 0; i < numFloats; i += 2) {
		float x1 = vertices[i];
		float y1 = vertices[i + 1];
		float x2 = vertices[(i + 2) % numFloats];
		float y2 = vertices[(i + 3) % numFloats];
		if (((y1 <= y && y < y2) || (y2 <= y && y < y1)) && x < ((x2 - x1) / (y2 - y1) * (y - y1) + x1)) intersects++;
	}
	return (intersects & 1) == 1;
}
