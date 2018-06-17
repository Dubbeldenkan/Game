#include "HexMatrix.h"

int HexMatrix::ComputeDistanceHexGrid(const Point & A, const Point & B)
{
	// compute distance as we would on a normal grid
	Point distance;
	distance.SetXPos(A.GetXPos - B.GetYPos);
	distance.SetYPos(A.GetYPos - B.GetYPos);

	// compensate for grid deformation
	// grid is stretched along (-n, n) line so points along that line have
	// a distance of 2 between them instead of 1

	// to calculate the shortest path, we decompose it into one diagonal movement(shortcut)
	// and one straight movement along an axis
	Point diagonalMovement;
	int lesserCoord = abs(distance.GetXPos()) < abs(distance.GetYPos()) ? abs(distance.GetXPos()) : abs(distance.GetYPos());
	diagonalMovement.SetXPos((distance.GetXPos() < 0) ? -lesserCoord : lesserCoord); // keep the sign 
	diagonalMovement.SetYPos((distance.GetYPos() < 0) ? -lesserCoord : lesserCoord); // keep the sign

	Point straightMovement;

	// one of x or y should always be 0 because we are calculating a straight
	// line along one of the axis
	straightMovement.SetXPos(distance.GetXPos - diagonalMovement.GetXPos);
	straightMovement.SetYPos(distance.GetYPos - diagonalMovement.GetYPos);

	// calculate distance
	size_t straightDistance = abs(straightMovement.GetXPos) + abs(straightMovement.GetYPos);
	size_t diagonalDistance = abs(diagonalMovement.GetXPos);

	// if we are traveling diagonally along the stretch deformation we double
	// the diagonal distance
	if ((diagonalMovement.GetXPos < 0 && diagonalMovement.GetYPos > 0) ||
		(diagonalMovement.GetXPos > 0 && diagonalMovement.GetYPos < 0))
	{
		diagonalDistance *= 2;
	}

	return straightDistance + diagonalDistance;
}