#include "OvalActionInterval.h"
  
MoveOvalBy::MoveOvalBy(){
  
}
  
//
//MoveOvalBy
//
MoveOvalBy* MoveOvalBy::create(float t, const OvalConfig& c){//利用之前定义的椭圆的参数初始化椭圆
    MoveOvalBy *action = new MoveOvalBy();
    action->initWithDuration(t, c);
    action->autorelease(); 
    return action;
}
  
bool MoveOvalBy::initWithDuration(float t, const OvalConfig& c){
    if (ActionInterval::initWithDuration(t)){
        _config = c;
        return true;
    }  
    return false;
}
void MoveOvalBy::update(float t){
    if (_target){
        float x = getPositionXAtOval(t);//调用之前的坐标计算函数来计算出坐标值
        float y = getPositionYAtOval(t);
        _target->setPosition(_config.centerPosition + Vec2(x, y));//由于我们画计算出的椭圆你做值是以原点为中心的，所以需要加上我们设定的中心点坐标  
        /*if(t <= 0.5){
            _target->setLocalZOrder(_config.zOrder.first);
        }else{
            _target->setLocalZOrder(_config.zOrder.second);
        }*/
    }
}
  
MoveOvalBy* MoveOvalBy::clone() const{
    auto action = new MoveOvalBy();
    action->initWithDuration(_duration, _config);
    action->autorelease();
    return action;
}
  
MoveOvalBy* MoveOvalBy::reverse() const{
    OvalConfig newConfig;
    newConfig.centerPosition = _config.centerPosition;
    newConfig.a = _config.a;
    newConfig.b = _config.b;
    newConfig.moveInAnticlockwise = !_config.moveInAnticlockwise;
    newConfig.zOrder = _config.zOrder;
    return MoveOvalBy::create(_duration, newConfig);
}
  
void MoveOvalBy::startWithTarget(Node *target){
    ActionInterval::startWithTarget(target);
}