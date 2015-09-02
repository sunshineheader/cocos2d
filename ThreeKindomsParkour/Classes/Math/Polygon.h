#ifndef __MATH_POLYGON_H__
#define __MATH_POLYGON_H__

#include <vector>
#include "cocos2d.h"

namespace Math {

	class Polygon
	{
	public:
		Polygon();
		Polygon(const std::vector<float> &vertices);
		Polygon(const std::vector<cocos2d::Vec2> &vertices);
		~Polygon();

		void setVertices(const std::vector<float> &vertices);
		const std::vector<float>& getVertices() const;
		// TODO: Try change to const mathod
		const std::vector<float>& getTransformedVertices();

		void setOrigin(float originX, float originY);
		float getOriginX() const;
		float getOriginY() const;

		void setPosition(float x, float y);
		float getPositionX() const;
		float getPositionY() const;
		void translate(float x, float y);

		void setRotation(float degrees);
		float getRotation() const;
		void rotate(float degrees);

		void setScale(float scaleX, float scaleY);
		void setScale(float scale);
		float getScaleX() const;
		float getScaleY() const;
		void scale(float amount);

		void dirty();

		bool contains(float x, float y);

	private:
		std::vector<float> _localVertices;
		std::vector<float> _worldVertices;
		float _x, _y;
		float _originX, _originY;
		float _rotation;
		float _scaleX, _scaleY;
		bool _dirty;
	};

};

#endif // __MATH_POLYGON_H__