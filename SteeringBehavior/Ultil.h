#pragma once


float Rand();

glm::vec2 RotateVector(const glm::vec2& v, float angle);
int Vector2Angle(const glm::vec2& v);

glm::vec2 TransfromPoint(const glm::vec2& p, float angle, const glm::vec2 translate);
glm::vec2 WorldToLocal(const glm::vec2& p, float angle, const glm::vec2 translate);

bool LineIntersection(const glm::vec2& A, const glm::vec2& B, const glm::vec2& C, const glm::vec2& D, glm::vec2& p);
template< class T, class container>
void TagNeighbors(const T* enity, container& ObjectList, float Radius)
{
	for (typename container::iterator obj = ObjectList.begin(); obj != ObjectList.end(); obj++)
	{
		(*obj)->UnTag();
		glm::vec2 to = (*obj)->GetPos() - enity->GetPos();
		float range = Radius + (*obj)->GetHeight();

		if ((*obj) != enity && glm::length(to) < range)
			(*obj)->Tag();

	}
}