#include "shapes.h"

#include <iostream>

namespace Assignment
{
	const float Shape::PI_F = 3.14159265358979f;

	void Shape::setPosition(Vector3 pos)
	{
		this->transform(2, 0) = pos.x();
		this->transform(2, 1) = pos.y();
		this->transform(2, 2) = pos.z();
	}

	void Shape::Bounce(Vector3 norm)
	{
		velocity = velocity.getReflection(norm);
	}

	Vector3 Shape::getPosition()
	{
		return Vector3(transform(2, 0), transform(2, 1), transform(2, 2));
	}

	void Shape::Connect()
	{

		for (int i = 0; i < vertexCount - 1; i++)
		{
			_lines[i].x1 = _vertices[i].x();
			_lines[i].y1 = _vertices[i].y();
			_lines[i].x2 = _vertices[i + 1].x();
			_lines[i].y2 = _vertices[i + 1].y();
			_lines[i].c1 = color;
			_lines[i].c2 = color;
		}

		_lines[vertexCount - 1].x1 = _vertices[0].x();
		_lines[vertexCount - 1].y1 = _vertices[0].y();
		_lines[vertexCount - 1].x2 = _vertices[vertexCount - 1].x();
		_lines[vertexCount - 1].y2 = _vertices[vertexCount - 1].y();
		_lines[vertexCount - 1].c1 = color;
		_lines[vertexCount - 1].c2 = color;
	}

	void Shape::Globalize()
	{
		for (int i = 0; i < vertexCount; i++)
		{
			_vertices[i] *= transform;
		}
	}

	void Shape::Draw()
	{
		for (int i = 0; i < vertexCount; i++)
		{
			AssignmentApp::DrawLine(_lines[i]);
		}
	}

	void Shape::UpdatePosition()
	{
		Vector3 pos = this->getPosition();

		if (pos.x() + velocity.x() > 1)
		{
			pos.x(1);
			Bounce(Vector3(-1, 0, 0));
		}

		else if (pos.x() + velocity.x() < -1)
		{
			pos.x(-1);
			Bounce(Vector3(1, 0, 0));
		}

		if (pos.y() + velocity.y() > 1)
		{
			pos.y(1);
			Bounce(Vector3(0, -1, 0));
		}

		else if (pos.y() + velocity.y() < -1)
		{
			pos.y(-1);
			Bounce(Vector3(0, 1, 0));
		}

		pos += velocity;
		this->setPosition(pos);
	}

	Shape::~Shape()
	{
		delete[] _lines;
		delete[] _vertices;
	}
}