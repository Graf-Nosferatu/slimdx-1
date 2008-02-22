/*
* Copyright (c) 2007-2008 SlimDX Group
* 
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* 
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* 
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*/

#include <d3dx9.h>

#include "BoundingBox.h"

#include "BoundingSphere.h"
#include "BoundingFrustum.h"
#include "Ray.h"

using namespace System;
using namespace System::Globalization;

namespace SlimDX
{
	BoundingBox::BoundingBox( Vector3 minimum, Vector3 maximum )
	{
		Minimum = minimum;
		Maximum = maximum;
	}

	array<Vector3>^ BoundingBox::GetCorners()
	{
		array<Vector3>^ results = gcnew array<Vector3>( 8 );
		results[0] = Vector3(Minimum.X, Maximum.Y, Maximum.Z);
		results[1] = Vector3(Maximum.X, Maximum.Y, Maximum.Z);
		results[2] = Vector3(Maximum.X, Minimum.Y, Maximum.Z);
		results[3] = Vector3(Minimum.X, Minimum.Y, Maximum.Z);
		results[4] = Vector3(Minimum.X, Maximum.Y, Minimum.Z);
		results[5] = Vector3(Maximum.X, Maximum.Y, Minimum.Z);
		results[6] = Vector3(Maximum.X, Minimum.Y, Minimum.Z);
		results[7] = Vector3(Minimum.X, Minimum.Y, Minimum.Z);
		return results;
	}

	ContainmentType BoundingBox::Contains( BoundingBox box1, BoundingBox box2 )
	{
		if( box1.Maximum.X < box2.Minimum.X || box1.Minimum.X > box2.Maximum.X )
			return ContainmentType::Disjoint;

		if( box1.Maximum.Y < box2.Minimum.Y || box1.Minimum.Y > box2.Maximum.Y )
			return ContainmentType::Disjoint;

		if( box1.Maximum.Z < box2.Minimum.Z || box1.Minimum.Z > box2.Maximum.Z )
			return ContainmentType::Disjoint;

		if( box1.Minimum.X <= box2.Minimum.X && box2.Maximum.X <= box1.Maximum.X && box1.Minimum.Y <= box2.Minimum.Y && 
			box2.Maximum.Y <= box1.Maximum.Y && box1.Minimum.Z <= box2.Minimum.Z && box2.Maximum.Z <= box1.Maximum.Z )
			return ContainmentType::Contains;

		return ContainmentType::Intersects;
	}

	ContainmentType BoundingBox::Contains( BoundingBox box, BoundingSphere sphere )
	{
		float dist;
		Vector3 clamped;

		Vector3::Clamp( sphere.Center, box.Minimum, box.Maximum, clamped );

		float x = sphere.Center.X - clamped.X;
		float y = sphere.Center.Y - clamped.Y;
		float z = sphere.Center.Z - clamped.Z;

		dist = (x * x) + (y * y) + (z * z);
		float radius = sphere.Radius;

		if( dist > (radius * radius) )
			return ContainmentType::Disjoint;

		if( box.Minimum.X + radius <= sphere.Center.X && sphere.Center.X <= box.Maximum.X - radius && 
			box.Maximum.X - box.Minimum.X > radius && box.Minimum.Y + radius <= sphere.Center.Y && 
			sphere.Center.Y <= box.Maximum.Y - radius && box.Maximum.Y - box.Minimum.Y > radius && 
			box.Minimum.Z + radius <= sphere.Center.Z && sphere.Center.Z <= box.Maximum.Z - radius &&
			box.Maximum.X - box.Minimum.X > radius )
			return ContainmentType::Contains;

		return ContainmentType::Intersects;
	}

	ContainmentType BoundingBox::Contains( BoundingBox box, BoundingFrustum frustum )
	{
		if( !BoundingFrustum::Intersects( frustum, box ) )
			return ContainmentType::Disjoint;

		array<Vector3>^ corners = frustum.GetCorners();

		for each( Vector3 vector in corners )
		{
			if( BoundingBox::Contains( box, vector ) == ContainmentType::Disjoint )
				return ContainmentType::Intersects;
		}

		return ContainmentType::Contains;
	}

	ContainmentType BoundingBox::Contains( BoundingBox box, Vector3 vector )
	{
		if( box.Minimum.X <= vector.X && vector.X <= box.Maximum.X && box.Minimum.Y <= vector.Y && 
			vector.Y <= box.Maximum.Y && box.Minimum.Z <= vector.Z && vector.Z <= box.Maximum.Z )
			return ContainmentType::Contains;

		return ContainmentType::Disjoint;
	}

	BoundingBox BoundingBox::FromPoints( array<Vector3>^ points )
	{
		if( points == nullptr || points->Length <= 0 )
			throw gcnew ArgumentNullException();

		Vector3 min = Vector3( float::MaxValue );
		Vector3 max = Vector3( float::MinValue );

		for each( Vector3 vector in points )
		{
			Vector3::Minimize( min, vector, min );
			Vector3::Maximize( max, vector, max );
		}

		return BoundingBox( min, max );
	}

	BoundingBox BoundingBox::FromSphere( BoundingSphere sphere )
	{
		BoundingBox box;
		box.Minimum = Vector3( sphere.Center.X - sphere.Radius, sphere.Center.Y - sphere.Radius, sphere.Center.Z - sphere.Radius );
		box.Maximum = Vector3( sphere.Center.X + sphere.Radius, sphere.Center.Y + sphere.Radius, sphere.Center.Z + sphere.Radius );
		return box;
	}

	BoundingBox BoundingBox::Merge( BoundingBox box1, BoundingBox box2 )
	{
		BoundingBox box;
		Vector3::Minimize( box1.Minimum, box2.Minimum, box.Minimum );
		Vector3::Maximize( box1.Maximum, box2.Maximum, box.Maximum );
		return box;
	}

	bool BoundingBox::Intersects( BoundingBox box1, BoundingBox box2 )
	{
		if ( box1.Maximum.X < box2.Minimum.X || box1.Minimum.X > box2.Maximum.X )
			return false;

		if ( box1.Maximum.Y < box2.Minimum.Y || box1.Minimum.Y > box2.Maximum.Y )
			return false;

		return ( box1.Maximum.Z >= box2.Minimum.Z && box1.Minimum.Z <= box2.Maximum.Z );
	}

	bool BoundingBox::Intersects( BoundingBox box, BoundingSphere sphere )
	{
		float dist;
		Vector3 clamped;

		Vector3::Clamp( sphere.Center, box.Minimum, box.Maximum, clamped );

		float x = sphere.Center.X - clamped.X;
		float y = sphere.Center.Y - clamped.Y;
		float z = sphere.Center.Z - clamped.Z;

		dist = (x * x) + (y * y) + (z * z);

		return ( dist <= (sphere.Radius * sphere.Radius) );
	}

	bool BoundingBox::Intersects( BoundingBox box, BoundingFrustum frustum )
	{
		return BoundingBox::Contains( box, frustum ) == ContainmentType::Intersects;
	}

	bool BoundingBox::Intersects( BoundingBox box, Ray ray, [Out] float% distance )
	{
		return Ray::Intersects( ray, box, distance );
	}

	PlaneIntersectionType BoundingBox::Intersects( BoundingBox box, Plane plane )
	{
		return Plane::Intersects( plane, box );
	}

	bool BoundingBox::operator == ( BoundingBox left, BoundingBox right )
	{
		return BoundingBox::Equals( left, right );
	}

	bool BoundingBox::operator != ( BoundingBox left, BoundingBox right )
	{
		return !BoundingBox::Equals( left, right );
	}

	String^ BoundingBox::ToString()
	{
		return String::Format( CultureInfo::CurrentCulture, "Minimum:{0} Maximum:{1}", Minimum.ToString(), Maximum.ToString() );
	}

	int BoundingBox::GetHashCode()
	{
		return Minimum.GetHashCode() + Maximum.GetHashCode();
	}

	bool BoundingBox::Equals( Object^ value )
	{
		if( value == nullptr )
			return false;

		if( value->GetType() != GetType() )
			return false;

		return Equals( static_cast<BoundingBox>( value ) );
	}

	bool BoundingBox::Equals( BoundingBox value )
	{
		return ( Minimum == value.Minimum && Maximum == value.Maximum );
	}

	bool BoundingBox::Equals( BoundingBox% value1, BoundingBox% value2 )
	{
		return ( value1.Minimum == value2.Minimum && value1.Maximum == value2.Maximum );
	}
}