#pragma once

#include <utils/direction.h>
#include <utils/types.h>

#include <algorithm>
#include <iostream>
#include <vector>

class BaseMap {
	protected:
		std::map<Coordinate, OBJECT::ObjectType> map_;
		std::vector<Coordinate> targets_;
		int x_;
		int y_;
		BaseMap();
		virtual void SetObject(const Coordinate &coord, OBJECT::ObjectType obj) = 0;
		virtual void SetTarget(const Coordinate &coord);

	public:
		virtual ~BaseMap();
		virtual OBJECT::ObjectType GetObjectInitType(const Coordinate &coord) const;
		virtual Coordinate GetVoidBorder(DIRECTION::Direction dir) const = 0;
		virtual Coordinate CalcCoordByAction(const Coordinate &coord, ACTION::Action act) const = 0;
		bool IsBorder(const Coordinate &coord) const;
		bool IsOutOfBorder(const Coordinate &coord) const;
		bool IsTarget(const Coordinate &coord) const;
		uint64_t GetID() const;
		int GetMapX() const;
		int GetMapY() const;
};
