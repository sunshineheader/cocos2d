#ifndef __OVAL_ACTIONINTERAL_H__ 
#define __OVAL_ACTIONINTERAL_H__
#include "cocos2d.h"

using namespace cocos2d;

  
// 定义一个结构来包含确定椭圆的参数
typedef struct OvalConfig {
    //中心点坐标
    Vec2 centerPosition;
    //椭圆a长半轴
    float a;
    //椭圆b短半轴
    float b;
    //是否逆时针运动
    bool moveInAnticlockwise;
    //two zOrder
    std::pair<int, int> zOrder;
} OvalConfig;
  
/**
  以椭圆方式移动
*/
  
class  MoveOvalBy : public ActionInterval{
public:
    MoveOvalBy();
    //用“动作持续时间”和“椭圆控制参数”初始化动作
    bool initWithDuration(float t, const OvalConfig& c);
    virtual MoveOvalBy* clone() const override;
    virtual MoveOvalBy* reverse() const override;
    virtual void update(float t);//利用update函数来不断的设定坐标
    virtual void startWithTarget(Node *target) override;
public:
    //用“动作持续时间”和“椭圆控制参数”创建动作
    static MoveOvalBy* create(float t, const OvalConfig& c);
  
protected:
    OvalConfig _config;
  
    //x = a * cos(t)  t = [0, 2Pi]
    inline float getPositionXAtOval(float t ){//返回X坐标
        //参数方程
        if(_config.moveInAnticlockwise == false){
            return _config.a * cos(6.2831852 * (1 - t));
        }else{
            return _config.a * cos(6.2831852 * t);
        }
  
    }
    //y = b * sin(t)  t = [0, 2Pi]
    inline float getPositionYAtOval(float t ){//返回Y坐标
        //参数方程
        if(_config.moveInAnticlockwise == false){
            return _config.b * sin(6.2831852 * (1 - t));
        }else{
            return _config.b * sin(6.2831852 * t);
        }
    }
private:
    //CC_DISALLOW_COPY_AND_ASSIGN(MoveOvalBy);
};


#endif