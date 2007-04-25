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
#include "otbVectorizationPathListFilter.h"
#include "otbImage.h"
#include "itkPolyLineParametricPath.h"
#include "otbImageFileReader.h"
#include <fstream>

#include "otbDrawPathListFilter.h"
#include "otbImageFileWriter.h"

int otbVectorizationPathListFilter(int argc, char * argv[])
{
  try
    {
      const char * modfname = argv[1];
      const char * dirfname = argv[2];
      const char * outfname = argv[3];

      const unsigned int Dimension = 2;
      typedef double PixelType;
      typedef otb::Image<PixelType,Dimension> ImageType;
      typedef otb::ImageFileReader<ImageType> ReaderType;
      typedef itk::PolyLineParametricPath<Dimension> PathType;
      typedef otb::VectorizationPathListFilter<ImageType,ImageType,PathType> VectorizationPathListFilterType;
      typedef VectorizationPathListFilterType::OutputPathListType PathListType;
      typedef PathListType::ConstIterator PathListIteratorType;
      typedef PathType::VertexListType VertexListType;
      typedef VertexListType::ConstIterator VertexIteratorType;
      // Instantiating objects
      VectorizationPathListFilterType::Pointer filter = VectorizationPathListFilterType::New();
      ReaderType::Pointer modReader = ReaderType::New();
      ReaderType::Pointer dirReader = ReaderType::New();

      modReader->SetFileName(modfname);
      dirReader->SetFileName(dirfname);

      filter->SetInput(modReader->GetOutput());
      filter->SetInputDirection(dirReader->GetOutput());
      filter->Update();
      
      PathListType::Pointer pathList = filter->GetOutput();
      PathListIteratorType pathListIt = pathList->Begin();

      std::ofstream file;
      file.open(outfname);
      unsigned int counter = 0;

      while(pathListIt!=pathList->End())
	{
	  file<<"Path "<<counter<<": ";
	  for(VertexIteratorType vIt = pathListIt.Get()->GetVertexList()->Begin();
	      vIt!=pathListIt.Get()->GetVertexList()->End();
	      ++vIt)
	    {
	      if(vIt!=pathListIt.Get()->GetVertexList()->Begin())
		{
		  file<<", ";
		}
	      file<<vIt.Value();
	    }
	  file<<std::endl;
	  ++pathListIt;
	  ++counter;
	}
      file.close();
    }
  catch( itk::ExceptionObject & err ) 
    { 
    std::cout << "Exception itk::ExceptionObject thrown !" << std::endl; 
    std::cout << err << std::endl; 
    return EXIT_FAILURE;
    } 
  catch( ... ) 
    { 
    std::cout << "Unknown exception thrown !" << std::endl; 
    return EXIT_FAILURE;
    } 
  return EXIT_SUCCESS;
}
