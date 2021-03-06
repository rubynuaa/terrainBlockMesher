/*---------------------------------------------------------------------------*\
                               |
  _____        _______ ____    | IWESOL: IWES Open Library
 |_ _\ \      / / ____/ ___|   |
  | | \ \ /\ / /|  _| \___ \   | Copyright: Fraunhofer Institute for Wind
  | |  \ V  V / | |___ ___) |  | Energy and Energy System Technology IWES
 |___|  \_/\_/  |_____|____/   |
                               | http://www.iwes.fraunhofer.de
                               |
-------------------------------------------------------------------------------
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     |
    \\  /    A nd           | Copyright  held by original author
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of IWESOL and it is based on OpenFOAM.

    IWESOL and OpenFOAM are free software: you can redistribute them and/or modify
    them under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    IWESOL and OpenFOAM are distributed in the hope that they will be useful, but
    WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
    or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

#include "PointTransition.H"
#include "addToRunTimeSelectionTable.H"

namespace Foam
{

namespace oldev
{

defineTypeNameAndDebug(PointTransition, 0);
addToRunTimeSelectionTable(TransitionFunction,PointTransition,type);
addToRunTimeSelectionTable(TransitionFunction,PointTransition,dict);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

PointTransition::PointTransition(
			const pointField & pts,
			label interpolOrder
			){
	setControlPoints
	(
			pts,
			interpolOrder
	);
}

PointTransition::PointTransition(
			const dictionary & dict
			){
	setControlPoints
	(
			pointField(dict.lookup("controlPoints")),
			readLabel(dict.lookup("interpolOrder"))
	);
}

// * * * * * * * * * * * * * * * * Public member functions  * * * * * * * * * * * * * * //

void PointTransition::setControlPoints(
			const pointField & pts,
			label interpolOrder
			){
	path_ = ScalarRFunction(interpolOrder,"controlPath");
	path_.add(0,0);
	forAll(pts,pI){
		path_.add(pts[pI][0],pts[pI][1]);
	}
	path_.add(1,1);
}


// ************************************************************************* //

} // End namespace oldev

} // End namespace Foam
