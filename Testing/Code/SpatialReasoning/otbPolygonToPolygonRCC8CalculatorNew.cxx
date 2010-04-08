/*=========================================================================

  Program:   ORFEO Toolbox
  Language:  C++
  Date:      $Date$
  Version:   $Revision$


  Copyright (c) Centre National d'Etudes Spatiales. All rights reserved.
  See OTBCopyright.txt for details.


     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "itkExceptionObject.h"
#include "otbPolygonToPolygonRCC8Calculator.h"
#include "otbPolygon.h"

int otbPolygonToPolygonRCC8CalculatorNew(int argc, char* argv[])
{
  typedef otb::Polygon<>                                   PolygonType;
  typedef otb::PolygonToPolygonRCC8Calculator<PolygonType> CalculatorType;

  //Instantiation
  CalculatorType::Pointer calc = CalculatorType::New();

  return EXIT_SUCCESS;
}
