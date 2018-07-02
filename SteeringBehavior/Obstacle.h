#pragma once

class Obstacle : public GameObject
{
private:
	float m_fRadius;
	glm::vec2 m_Pos;
public:
	Obstacle(const char* name,const glm::vec2& pos, float r) :m_Pos(pos), m_fRadius(r),GameObject(name){}

	const glm::vec2& GetPos() { return m_Pos; }
	void SetPos(const glm::vec2& p) { m_Pos = p; }
	float GetRadius() { return m_fRadius; }
	void SetRadius(float r) { m_fRadius = r; }

	void Update(float dt) {};
	void Render();
	void RenderUI() {}
};