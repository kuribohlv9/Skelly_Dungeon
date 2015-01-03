#include "stdafx.h"
#include "SpriteAnimation.h"
#include "Sprite.h"


SpriteAnimation::SpriteAnimation(SDL_Texture* texture) : Sprite(texture)
{
	m_timer = 0.0f;
	m_frame = 0;
}


SpriteAnimation::~SpriteAnimation()
{
}

void SpriteAnimation::Update(float deltatime)
{
	m_timer += deltatime;
	auto itr = m_animations.find(m_active_animation);													// m_active_animation är en sträng som alla animationer har (se Player.cpp)
	if (itr != m_animations.end())
	{
		const AnimationFrameVector& ver = itr->second;
		if (m_timer > 1.0f/ver[m_frame].m_duration)
		{
			m_frame++;
			m_frame = m_frame % ver.size();
			m_timer = 0.0f;
		}
		m_region = ver[m_frame].m_region;																
	}																									// vi uppdaterar inte regionen om den är tom, dvs om vi inte hittar en keypress. Detta gör att animationen stannar om spelaren slutar trycka på en tangent att röra sig
}

void SpriteAnimation::AddFrame(const std::string& animationName, const AnimFrame& frame)
{
	auto itr = m_animations.find(animationName);
	if (itr == m_animations.end())
	{
		m_animations.insert(std::pair<std::string, AnimationFrameVector>(animationName, AnimationFrameVector()));
		itr = m_animations.find(animationName);
	}
	itr->second.push_back(frame);
}

void SpriteAnimation::SetAnimation(const std::string& animationName)
{
	m_active_animation = animationName;
	m_frame = 0;
	auto itr = m_animations.find(m_active_animation);
	if (itr != m_animations.end())
	{
		if (itr->second.size() > 0)
		{
			m_region = itr->second[0].m_region;
		}
	}
}
std::string SpriteAnimation::GetAnimationName()
{
	return m_active_animation;
}