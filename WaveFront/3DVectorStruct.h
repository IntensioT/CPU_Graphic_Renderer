#pragma once

#ifndef _3DVECTORSTRUCT_H_
#define _3DVECTORSTRUCT_H_


struct CoordinateStruct
{
	float x, y, z;

	CoordinateStruct operator*(const CoordinateStruct& other) const;
	
	CoordinateStruct operator*(const float other) const;
	
	CoordinateStruct operator/(const float other) const;
	
	CoordinateStruct operator-(const CoordinateStruct& other) const;
	
	CoordinateStruct operator-(const float other) const;
	
	

};


#endif // _3DVECTORSTRUCT_H_