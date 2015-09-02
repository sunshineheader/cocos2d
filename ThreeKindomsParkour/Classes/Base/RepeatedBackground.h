#ifndef __TKP_REPEATED_BACKGROUND_H__
#define __TKP_REPEATED_BACKGROUND_H__

#include "cocos2d.h"

class RepeatedBackground : public cocos2d::Node
{
public:
	static RepeatedBackground* create(const std::string &name);
	virtual void update(float delta) override;

protected:
	RepeatedBackground(const std::string &name);
	~RepeatedBackground();
	CC_DISALLOW_COPY_AND_ASSIGN(RepeatedBackground);

	virtual bool init();

private:
	void addBackground();

private:
	std::string _backgroundName;
	float _previousPositionX;
	float _lastPositionX;
	float _backgroundWidth;
	float _screenWidth;
};



#endif // __TKP_REPEATED_BACKGROUND_H__