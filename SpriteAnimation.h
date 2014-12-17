#pragma once
#include "Sprite.h"

struct AnimFrame
{
	float m_duration;
	SDL_Rect m_region;
};

typedef std::vector<AnimFrame> AnimationFrameVector;
typedef std::map<std::string, AnimationFrameVector> AnimationMap;

class SpriteAnimation : public Sprite
{
public:
	SpriteAnimation(SDL_Texture* texture);
	~SpriteAnimation();

	void Update(float deltatime);
	void AddFrame(const std::string& animationName, const AnimFrame &frame);
	void SetAnimation(const std::string& animationName);
	std::string GetAnimationName();

private:
	std::string m_active_animation;
	float m_timer;
	unsigned int m_frame;
	AnimationMap m_animations;

};