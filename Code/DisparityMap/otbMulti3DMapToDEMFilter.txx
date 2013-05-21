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
#ifndef __otbMulti3DMapToDEMFilter_txx
#define __otbMulti3DMapToDEMFilter_txx

#include "otbMulti3DMapToDEMFilter.h"
#include "itkImageRegionConstIteratorWithIndex.h"
#include "itkImageRegionIterator.h"
#include "itkNumericTraits.h"
#include "otbStreamingStatisticsVectorImageFilter.h"

namespace otb
{

template<class T3DImage, class TMaskImage, class TOutputDEMImage>
Multi3DMapToDEMFilter<T3DImage, TMaskImage, TOutputDEMImage>::Multi3DMapToDEMFilter()
{
  // Set the number of inputs (1 image one optional mask)
  this->SetNumberOfInputs(2);
  this->SetNumberOfRequiredInputs(1);
  this->m_MapKeywordLists.resize(1);
  m_DEMGridStep = 10.0;
  // Set the outputs
  this->SetNumberOfOutputs(1);
  this->SetNthOutput(0, TOutputDEMImage::New());
  // Default DEM reconstruction parameters
  m_MapSplitterList = SplitterListType::New();

  //m_NoDataValue = itk::NumericTraits<DEMPixelType>::NonpositiveMin();
  m_NoDataValue = 0; //TODO replace this value by Max or Min
  m_CellFusionMode = otb::CellFusionMode::MAX;

}

template<class T3DImage, class TMaskImage, class TOutputDEMImage>
Multi3DMapToDEMFilter<T3DImage, TMaskImage, TOutputDEMImage>::~Multi3DMapToDEMFilter()
{
}

template<class T3DImage, class TMaskImage, class TOutputDEMImage>
void Multi3DMapToDEMFilter<T3DImage, TMaskImage, TOutputDEMImage>::SetNumberOf3DMaps(unsigned int nb)
{
  if (nb > 0)
    {
    this->SetNumberOfInputs(2 * nb);
    this->m_MapKeywordLists.resize(nb);
    }
}

template<class T3DImage, class TMaskImage, class TOutputDEMImage>
unsigned int Multi3DMapToDEMFilter<T3DImage, TMaskImage, TOutputDEMImage>::GetNumberOf3DMaps()
{
  return this->GetNumberOfInputs() / 2;
}

template<class T3DImage, class TMaskImage, class TOutputDEMImage>
void Multi3DMapToDEMFilter<T3DImage, TMaskImage, TOutputDEMImage>::Set3DMapInput(unsigned int index,
                                                                                 const T3DImage * map)
{
  if ((2 * (index + 1)) > this->GetNumberOfInputs())
    {
    itkExceptionMacro(<<"Index is greater than the number of images");
    }
  // Process object is not const-correct so the const casting is required.
  this->SetNthInput(2 * index, const_cast<T3DImage *> (map));
}

template<class T3DImage, class TMaskImage, class TOutputDEMImage>
void Multi3DMapToDEMFilter<T3DImage, TMaskImage, TOutputDEMImage>::SetMapKeywordList(unsigned int index,
                                                                                     const ImageKeywordListType kwl)
{
  if (this->m_MapKeywordLists.size() > index)
    {
    this->m_MapKeywordLists[index] = kwl;
    }
}

template<class T3DImage, class TMaskImage, class TOutputDEMImage>
const typename Multi3DMapToDEMFilter<T3DImage, TMaskImage, TOutputDEMImage>::ImageKeywordListType &
Multi3DMapToDEMFilter<T3DImage, TMaskImage, TOutputDEMImage>::GetMapKeywordList(unsigned int index) const
{
  if (this->m_MapKeywordLists.size() <= index)
    {
    itkExceptionMacro(<<"Keywordlist index is outside the container");
    }
  return this->m_MapKeywordLists[index];
}

template<class T3DImage, class TMaskImage, class TOutputDEMImage>
void Multi3DMapToDEMFilter<T3DImage, TMaskImage, TOutputDEMImage>::SetMaskInput(unsigned int index,
                                                                                const TMaskImage * mask)
{
  if ((2 * (index + 1)) > this->GetNumberOfInputs())
    {
    itkExceptionMacro(<<"Index is greater than the number of images");
    }
  // Process object is not const-correct so the const casting is required.
  this->SetNthInput(2 * index + 1, const_cast<TMaskImage *> (mask));
}

template<class T3DImage, class TMaskImage, class TOutputDEMImage>
const T3DImage *
Multi3DMapToDEMFilter<T3DImage, TMaskImage, TOutputDEMImage>::Get3DMapInput(unsigned int index) const
{
  if ((2 * (index + 1)) > this->GetNumberOfInputs())
    {
    return NULL;
    }
  return static_cast<const T3DImage *> (this->itk::ProcessObject::GetInput(2 * index));
}

template<class T3DImage, class TMaskImage, class TOutputDEMImage>
const TMaskImage *
Multi3DMapToDEMFilter<T3DImage, TMaskImage, TOutputDEMImage>::GetMaskInput(unsigned int index) const
{
  if ((2 * (index + 1)) > this->GetNumberOfInputs())
    {
    return NULL;
    }
  return static_cast<const TMaskImage *> (this->itk::ProcessObject::GetInput(2 * index + 1));
}

template<class T3DImage, class TMaskImage, class TOutputDEMImage>
const TOutputDEMImage *
Multi3DMapToDEMFilter<T3DImage, TMaskImage, TOutputDEMImage>::GetDEMOutput() const
{
  if (this->GetNumberOfOutputs() < 1)
    {
    return 0;
    }
  return static_cast<const TOutputDEMImage *> (this->itk::ProcessObject::GetOutput(0));
}

template<class T3DImage, class TMaskImage, class TOutputDEMImage>
TOutputDEMImage *
Multi3DMapToDEMFilter<T3DImage, TMaskImage, TOutputDEMImage>::GetDEMOutput()
{
  if (this->GetNumberOfOutputs() < 1)
    {
    return 0;
    }
  return static_cast<TOutputDEMImage *> (this->itk::ProcessObject::GetOutput(0));
}

template<class T3DImage, class TMaskImage, class TOutputDEMImage>
void Multi3DMapToDEMFilter<T3DImage, TMaskImage, TOutputDEMImage>::GenerateOutputInformation()
{

  //compute DEM extent union of 3D map extent

  TOutputDEMImage * outputPtr = this->GetDEMOutput();

  // DEM BBox
  itk::NumericTraits<DEMPixelType>::max();
  double box_xmin = itk::NumericTraits<DEMPixelType>::max();
  double box_xmax = itk::NumericTraits<DEMPixelType>::NonpositiveMin();
  double box_ymin = itk::NumericTraits<DEMPixelType>::max();
  double box_ymax = itk::NumericTraits<DEMPixelType>::NonpositiveMin();

  //min val
  //max val

  //compute extent for each image
  // this is done using sensor model

  //m_MapMinVal.resize(this->GetNumberOf3DMaps());
  //m_MapMaxVal.resize(this->GetNumberOf3DMaps());
  // m_MapMinVal.SetSize(3);
  // m_MapMinVal.Fill(0.);
  // m_MapMaxVal.SetSize(3);
  // m_MapMaxVal.Fill(0.);

  for (unsigned int k = 0; k < this->GetNumberOf3DMaps(); ++k)
    {
    T3DImage *imgPtr = const_cast<T3DImage *> (this->Get3DMapInput(k));

    //TODO set KWL from input KWL

    // Set-up a transform to use the DEMHandler
    typedef otb::GenericRSTransform<> RSTransform2DType;
    RSTransform2DType::Pointer mapToGroundTransform = RSTransform2DType::New();
    mapToGroundTransform->SetInputKeywordList(this->GetMapKeywordList(k));
    mapToGroundTransform->InstanciateTransform();

    // left image
    typename InputMapType::SizeType inputSize = imgPtr->GetLargestPossibleRegion().GetSize();

    // Min/Max stats have to be computed (this is done using sensor model )
    //typename StreamingMinMaxVImageFilterType::Pointer statsEstimator = StreamingMinMaxVImageFilterType::New();
    // statsEstimator->SetInput(imgPtr);
    //statsEstimator->Update();
    //m_MapMinVal[k]=statsEstimator->GetMinimum();
    //m_MapMaxVal[k]=statsEstimator->GetMaximum();

    //std::cout<<"minval "<<m_MapMinVal[k]<<std::endl;
    //std::cout<<"maxval "<<m_MapMaxVal[k]<<std::endl;


    typename InputMapType::PointType tmpPoint;
    tmpPoint = imgPtr->GetOrigin();
    RSTransform2DType::OutputPointType ul = mapToGroundTransform->TransformPoint(tmpPoint);

    tmpPoint[0] = (imgPtr->GetOrigin())[0] + (imgPtr->GetSpacing())[0] * static_cast<double> (inputSize[0]);
    tmpPoint[1] = (imgPtr->GetOrigin())[1];
    RSTransform2DType::OutputPointType ur = mapToGroundTransform->TransformPoint(tmpPoint);

    tmpPoint[0] = (imgPtr->GetOrigin())[0] + (imgPtr->GetSpacing())[0] * static_cast<double> (inputSize[0]);
    tmpPoint[1] = (imgPtr->GetOrigin())[1] + (imgPtr->GetSpacing())[1] * static_cast<double> (inputSize[1]);
    RSTransform2DType::OutputPointType lr = mapToGroundTransform->TransformPoint(tmpPoint);

    tmpPoint[0] = (imgPtr->GetOrigin())[0];
    tmpPoint[1] = (imgPtr->GetOrigin())[1] + (imgPtr->GetSpacing())[1] * static_cast<double> (inputSize[1]);
    RSTransform2DType::OutputPointType ll = mapToGroundTransform->TransformPoint(tmpPoint);

    // std::cout<<"coord "<<ul<<" "<<ur<<" "<<ll<<" "<<lr<<std::endl;
    double xmin = std::min(std::min(std::min(ul[0], ur[0]), lr[0]), ll[0]);
    double xmax = std::max(std::max(std::max(ul[0], ur[0]), lr[0]), ll[0]);
    double ymin = std::min(std::min(std::min(ul[1], ur[1]), lr[1]), ll[1]);
    double ymax = std::max(std::max(std::max(ul[1], ur[1]), lr[1]), ll[1]);

    //std::cout<<"xmin "<<xmin<<" xmax "<<xmax<<" ymin "<<ymin<<" ymax "<<ymax<<std::endl;

    box_xmin = std::min(box_xmin, xmin);
    box_xmax = std::max(box_xmax, xmax);
    box_ymin = std::min(box_ymin, ymin);
    box_ymax = std::max(box_ymax, ymax);

    }

  //std::cout<<"BBOX "<<box_xmin<<" "<<box_xmax<<" "<<box_ymin<<" "<<box_ymax<<std::endl;


  // Choose origin
  typename TOutputDEMImage::PointType outOrigin;
  outOrigin[0] = box_xmin;
  outOrigin[1] = box_ymax;
  outputPtr->SetOrigin(outOrigin);

  // Compute step :
  // TODO : use a clean RS transform instead
  typename TOutputDEMImage::SpacingType outSpacing;
  //std::cout<<" GrisStep "<<m_DEMGridStep<<std::endl;
  outSpacing[0] = 57.295779513 * m_DEMGridStep / (6378137.0 * vcl_cos((box_ymin + box_ymax) * 0.5 * 0.01745329251));
  outSpacing[1] = -57.295779513 * m_DEMGridStep / 6378137.0;
  outputPtr->SetSpacing(outSpacing);

  //std::cout << "outSpacing " << outSpacing << std::endl;
  // Compute output size
  typename TOutputDEMImage::RegionType outRegion;
  outRegion.SetIndex(0, 0);
  outRegion.SetIndex(1, 0);
  outRegion.SetSize(0, static_cast<unsigned int> ((box_xmax - box_xmin) / vcl_abs(outSpacing[0])+1));
  //TODO JGT check the size
  outRegion.SetSize(1, static_cast<unsigned int> ((box_ymax - box_ymin) / vcl_abs(outSpacing[1])));

  outputPtr->SetLargestPossibleRegion(outRegion);
  outputPtr->SetNumberOfComponentsPerPixel(1);

}

template<class T3DImage, class TMaskImage, class TOutputDEMImage>
void Multi3DMapToDEMFilter<T3DImage, TMaskImage, TOutputDEMImage>::GenerateInputRequestedRegion()
{

  for (unsigned int k = 0; k < this->GetNumberOf3DMaps(); ++k)
    {
    //set requested to largest and check that mask has the same size
    T3DImage *imgPtr = const_cast<T3DImage *> (this->Get3DMapInput(k));

    RegionType largest = imgPtr->GetLargestPossibleRegion();

    imgPtr->SetRequestedRegionToLargestPossibleRegion();

    TMaskImage *mskPtr = const_cast<TMaskImage *> (this->GetMaskInput(k));
    if (mskPtr)
      {
      if (mskPtr->GetLargestPossibleRegion() != largest)
        {
        itkExceptionMacro(<<"mask and map at position "<<k<<" have a different largest region");
        }
      mskPtr->SetRequestedRegion(largest);
      }
    if (this->m_MapKeywordLists[k].GetSize() == 0)
      {
      itkExceptionMacro(<< "Keywordlist of image at position "<<k<<" is empty");
      }

    }
}

template<class T3DImage, class TMaskImage, class TOutputDEMImage>
void Multi3DMapToDEMFilter<T3DImage, TMaskImage, TOutputDEMImage>::BeforeThreadedGenerateData()
{
  const TOutputDEMImage * outputDEM = this->GetDEMOutput();

  //create splits
  // for each map we check if the input region can be splitted into threadNb
  m_NumberOfSplit.resize(this->GetNumberOf3DMaps());

  unsigned int maximumRegionsNumber = 1;

  for (unsigned int k = 0; k < this->GetNumberOf3DMaps(); ++k)
    {
    m_MapSplitterList->PushBack(SplitterType::New());
    T3DImage *imgPtr = const_cast<T3DImage *> (this->Get3DMapInput(k));

    typename T3DImage::RegionType requestedRegion = imgPtr->GetRequestedRegion();

    unsigned int regionsNumber = m_MapSplitterList->GetNthElement(k)->GetNumberOfSplits(requestedRegion,
                                                                                        this->GetNumberOfThreads());

    m_NumberOfSplit[k] = regionsNumber;
    otbMsgDevMacro( "map " << k << " will be splitted into " << regionsNumber << " regions" );

    if (maximumRegionsNumber < regionsNumber) maximumRegionsNumber = regionsNumber;

    }

  m_TempDEMRegions.clear();
  m_TempDEMAccumulatorRegions.clear();
  //m_ThreadProcessed.resize(maximumRegionsNumber);

  for (unsigned int i = 0; i < maximumRegionsNumber; i++)
    {
    //m_ThreadProcessed[i] = 0;
    typename TOutputDEMImage::Pointer tmpImg = TOutputDEMImage::New();
    tmpImg->SetNumberOfComponentsPerPixel(1); //Two components for mean calculus ?
    tmpImg->SetRegions(outputDEM->GetRequestedRegion());
    tmpImg->Allocate();

    tmpImg->FillBuffer(m_NoDataValue);
    m_TempDEMRegions.push_back(tmpImg);

    typename AccumulatorImageType::Pointer tmpImg2 = AccumulatorImageType::New();
    tmpImg2->SetNumberOfComponentsPerPixel(1); //Two components for mean calculus ?
    tmpImg2->SetRegions(outputDEM->GetRequestedRegion());
    tmpImg2->Allocate();

    tmpImg2->FillBuffer(0.);
    m_TempDEMAccumulatorRegions.push_back(tmpImg2);
    }
}

template<class T3DImage, class TMaskImage, class TOutputDEMImage>
void Multi3DMapToDEMFilter<T3DImage, TMaskImage, TOutputDEMImage>::ThreadedGenerateData(
                                                                                        const RegionType & outputRegionForThread,
                                                                                        int threadId)
{
  //m_ThreadProcessed[threadId]=1;
  TOutputDEMImage * outputPtr = this->GetOutput();

  typename OutputImageType::PointType pointRef;
  typename OutputImageType::PointType pointRefStep;
  typename OutputImageType::RegionType requestedRegion = outputPtr->GetRequestedRegion();

  // typename OutputImageType::PointType point2D;
  // point2D[0] = position[0];
  // point2D[1] = position[1];
  // itk::ContinuousIndex<double,2> continuousOrigin;
  // continuousOrigin[0]=0;
  // continuousOrigin[1]=0;

  // outputPtr->TransformContinuousIndexToPhysicalPoint(continuousOrigin,point2D);
  //typename TOutputDEMImage::PointType outOrigin=outputPtr->GetOrigin();
  // std::cout<<"diff with origin for index 0 "<<point2D[0]-outOrigin[0]<<" "<<point2D[1]-outOrigin[1]<<std::endl;
  // continuousOrigin[0]=0.5;
  // continuousOrigin[1]=0.5;

  //outputPtr->TransformContinuousIndexToPhysicalPoint(continuousOrigin,point2D);

  // std::cout<<"diff with origin for index 0.5 "<<point2D[0]-outOrigin[0]<<" "<<point2D[1]-outOrigin[1]<<std::endl;


  // if(threadId==1)
  // {
  typename TOutputDEMImage::SpacingType step = outputPtr->GetSpacing();

  //convert requested region to Long/Lat

  typename TOutputDEMImage::SizeType size = requestedRegion.GetSize();

  typename TOutputDEMImage::IndexType index = requestedRegion.GetIndex();
  outputPtr->TransformIndexToPhysicalPoint(index, pointRef);
  InputInternalPixelType regionLong1 = pointRef[0];
  InputInternalPixelType regionLat1 = pointRef[1];
  InputInternalPixelType regionLong2 = pointRef[0] + size[0] * step[0];
  InputInternalPixelType regionLat2 = pointRef[1] + size[1] * step[1];
  InputInternalPixelType minLong = std::min(regionLong1, regionLong2);
  InputInternalPixelType minLat = std::min(regionLat1, regionLat2);
  InputInternalPixelType maxLong = std::max(regionLong1, regionLong2);
  InputInternalPixelType maxLat = std::max(regionLat1, regionLat2);

  // std::cout<<"size "<<size<<" index"<<index<<std::endl;
  //  std::cout<<"minLong "<<minLong<<" maxLong "<<maxLong<<std::endl;
  //  std::cout<<"minLat "<<minLat<<" maxLat "<<maxLat<<std::endl;

  TOutputDEMImage * tmpDEM = NULL;
  AccumulatorImageType *tmpAcc = NULL;
  typename TOutputDEMImage::RegionType outputRequestedRegion = outputPtr->GetRequestedRegion();

  typename T3DImage::RegionType splitRegion;

  itk::ImageRegionConstIterator<InputMapType> mapIt;
  for (unsigned int k = 0; k < this->GetNumberOf3DMaps(); ++k)
    {
    T3DImage *imgPtr = const_cast<T3DImage *> (this->Get3DMapInput(k));
    TMaskImage *mskPtr = const_cast<TMaskImage *> (this->GetMaskInput(k));
    typename T3DImage::RegionType requestedRegion = imgPtr->GetRequestedRegion();

    if (static_cast<unsigned int> (threadId) < m_NumberOfSplit[k])
      {
      splitRegion = m_MapSplitterList->GetNthElement(k)->GetSplit(threadId, m_NumberOfSplit[k],
                                                                  imgPtr->GetRequestedRegion());
      tmpDEM = m_TempDEMRegions[threadId];
      tmpAcc = m_TempDEMAccumulatorRegions[threadId];
      }
    else
      {
      std::cout << "not splitted " << std::endl;
      return;
      }

    mapIt = itk::ImageRegionConstIterator<InputMapType>(imgPtr, splitRegion);
    mapIt.GoToBegin();
    itk::ImageRegionConstIterator<MaskImageType> maskIt;
    bool useMask = false;
    if (mskPtr)
      {
      useMask = true;
      maskIt = itk::ImageRegionConstIterator<MaskImageType>(mskPtr, splitRegion);
      maskIt.GoToBegin();
      }

    // std::cout<<"usemask"<<useMask<<std::endl;
    while (!mapIt.IsAtEnd())
      {
      // check mask value if any
      if (useMask)
        {
        if (!(maskIt.Get() > 0))
          {
          ++mapIt;
          ++maskIt;
          continue;
          }
        }

      MapPixelType position = mapIt.Get();

      //test if position is in DEM BBOX

      bool isInDEM = (position[0] >= minLong) && (position[0] < maxLong) && (position[1] >= minLat) && (position[1]
          < maxLat);

      // Is point inside DEM area ?
      typename OutputImageType::PointType point2D;
      point2D[0] = position[0];
      point2D[1] = position[1];
      itk::ContinuousIndex<double, 2> continuousIndex;

      outputPtr->TransformPhysicalPointToContinuousIndex(point2D, continuousIndex);
      typename OutputImageType::IndexType cellIndex;
      cellIndex[0] = static_cast<int> (vcl_floor(continuousIndex[0]));
      cellIndex[1] = static_cast<int> (vcl_floor(continuousIndex[1]));

      //index from physical
      typename OutputImageType::IndexType physCellIndex;
      //double CellIndexLong=(position[0]-outOrigin[0])/step[0];
      //double CellIndexLat=(position[1]-outOrigin[1])/step[1];
      typename OutputImageType::IndexType cellIndex2;
      //cellIndex2[0] = static_cast<int>(vcl_floor(CellIndexLong));
      //cellIndex2[1] = static_cast<int>(vcl_floor(CellIndexLat));

      //physCellIndex[0]=
      //
      //if((cellIndex2[0]!=cellIndex[0]) ||(cellIndex2[1]!=cellIndex[1]) )
      // {

      //  std::cout<<"long lat "<<CellIndexLong<<" "<<CellIndexLat<<std::endl;
      //  std::cout<<"index "<<continuousIndex<<std::endl;

      // }


      //  if (outputRequestedRegion.IsInside(cellIndex)!=isInDEM)
      //       {
      //    std::cout<<std::endl<<"!!!!!!!!!!!!!!"<<std::endl<<std::endl;

      //     std::cout<<"position[0]-minLong "<<position[0]-minLong<<std::endl;
      //     std::cout<<"index "<<continuousIndex<<std::endl;
      //    std::cout<<"long lat "<<CellIndexLong<<" "<<CellIndexLat<<std::endl;
      //           std::cout<<"position"<<position<<" cellIndex "<<cellIndex<<" IsInside "<<isInDEM<<" "<<outputRequestedRegion.IsInside(cellIndex)<<std::endl;
      //         std::cout<<"position"<<position<<" output origin "<<outputPtr->GetOrigin()<<std::endl;
      //         std::cout<<"diff "<<position[0]-outputPtr->GetOrigin()[0]<<" "<<position[1]-outputPtr->GetOrigin()[1]<<std::endl;
      // Set-up a transform to use the DEMHandler
      //        typedef otb::GenericRSTransform<> RSTransform2DType;
      //        RSTransform2DType::Pointer mapToGroundTransform = RSTransform2DType::New();
      //        mapToGroundTransform->SetInputKeywordList(this->GetMapKeywordList(k));
      //        mapToGroundTransform->InstanciateTransform();
      //        typename InputMapType::PointType tmpPoint;
      //           tmpPoint = imgPtr->GetOrigin();
      //           RSTransform2DType::OutputPointType ul = mapToGroundTransform->TransformPoint(tmpPoint);
      //             std::cout<<"position"<<position<<" output origin "<<ul<<std::endl;
      //             std::cout<<"diff "<<position[0]-ul[0]<<" "<<position[1]-ul[1]<<std::endl;

      // Add point to its corresponding cell (keep maximum)
      //  DEMPixelType cellHeight = static_cast<DEMPixelType>(position[2]);
      //if (cellHeight > tmpDEM->GetPixel(cellIndex) && cellHeight < static_cast<DEMPixelType>(m_ElevationMax))
      //  {
      // tmpDEM->SetPixel(cellIndex,cellHeight);
      //   }
      //    }

      if (outputRequestedRegion.IsInside(cellIndex))
        {

        // Add point to its corresponding cell (keep maximum)
        DEMPixelType cellHeight = static_cast<DEMPixelType> (position[2]);
        //if (cellHeight > tmpDEM->GetPixel(cellIndex) && cellHeight < static_cast<DEMPixelType>(m_ElevationMax))
        //  {
        // tmpDEM->SetPixel(cellIndex,tmpDEM->GetPixel(cellIndex)+1);

        AccumulatorPixelType accPixel = tmpAcc->GetPixel(cellIndex);
        tmpAcc->SetPixel(cellIndex, tmpAcc->GetPixel(cellIndex) + 1);

        if (accPixel == 0)
          {
          tmpDEM->SetPixel(cellIndex, cellHeight);
          }
        else
          {
          DEMPixelType cellCurrentValue = tmpDEM->GetPixel(cellIndex);

          switch (this->m_CellFusionMode)
            {
            case otb::CellFusionMode::MIN:
              {
              if (cellHeight < cellCurrentValue)
                {
                tmpDEM->SetPixel(cellIndex, cellHeight);
                }
              }
              break;
            case otb::CellFusionMode::MAX:
              {
              if (cellHeight > cellCurrentValue)
                {
                tmpDEM->SetPixel(cellIndex, cellHeight);
                }
              }
              break;
            case otb::CellFusionMode::MEAN:
              {
              tmpDEM->SetPixel(cellIndex, cellCurrentValue + cellHeight);
              }
              break;
            case otb::CellFusionMode::ACC:
              {
              }
              break;
            default:

              itkExceptionMacro(<< "Unexpected value cell fusion mode :"<<this->m_CellFusionMode)
          ;
              break;
            }
          }

        //   }
        }

      ++mapIt;

      if (useMask) ++maskIt;

      }

    }
}

template<class T3DImage, class TMaskImage, class TOutputDEMImage>
void Multi3DMapToDEMFilter<T3DImage, TMaskImage, TOutputDEMImage>::AfterThreadedGenerateData()
{
  TOutputDEMImage * outputDEM = this->GetOutput();

  //check is that case can occur
  if (m_TempDEMRegions.size() < 1)
    {
    outputDEM->FillBuffer(m_NoDataValue);
    return;
    }

  itk::ImageRegionIterator<OutputImageType> outputDEMIt(outputDEM, outputDEM->GetRequestedRegion());
  itk::ImageRegionIterator<OutputImageType> firstDEMIt(m_TempDEMRegions[0], outputDEM->GetRequestedRegion());
  itk::ImageRegionIterator<AccumulatorImageType> firstDEMAccIt(m_TempDEMAccumulatorRegions[0],
                                                               outputDEM->GetRequestedRegion());
  //we use the first accumulator as global accumulator over tmpAcc for mean calculus

  outputDEMIt.GoToBegin();
  firstDEMIt.GoToBegin();
  firstDEMAccIt.GoToBegin();
  // Copy first DEM

  /*if(!m_ThreadProcessed[0])
   {
   itkWarningMacro(<< "Thread : 0  Have not been executed");
   }*/

  while (!outputDEMIt.IsAtEnd() && !firstDEMIt.IsAtEnd() && !firstDEMAccIt.IsAtEnd())
    {

    AccumulatorPixelType accPixel = firstDEMAccIt.Get();
    //useless test tempDEm is initialized with NoDataValue
    if (accPixel == 0)
      {
      outputDEMIt.Set(m_NoDataValue);
      }
    else
      {

      outputDEMIt.Set(firstDEMIt.Get());
      }

    if ((this->m_CellFusionMode == otb::CellFusionMode::MEAN) && (m_TempDEMRegions.size() == 1))
      {
      outputDEMIt.Set(firstDEMIt.Get() / static_cast<DEMPixelType> (accPixel));
      }
    if (this->m_CellFusionMode == otb::CellFusionMode::ACC)
      {
      outputDEMIt.Set(static_cast<DEMPixelType> (accPixel));
      }
    ++outputDEMIt;
    ++firstDEMIt;
    ++firstDEMAccIt;
    }

  // Check DEMs from other threads and keep the maximum elevation
  for (unsigned int i = 1; i < m_TempDEMRegions.size(); i++)
    {

    /*if(!m_ThreadProcessed[i])
     {
     itkWarningMacro(<< "Thread : "<<i<<" Have not been executed");
     }*/

    itk::ImageRegionIterator<OutputImageType> tmpDEMIt(m_TempDEMRegions[i], outputDEM->GetRequestedRegion());
    itk::ImageRegionIterator<AccumulatorImageType> tmpDEMAccIt(m_TempDEMAccumulatorRegions[i],
                                                               outputDEM->GetRequestedRegion());

    outputDEMIt.GoToBegin();
    tmpDEMIt.GoToBegin();
    tmpDEMAccIt.GoToBegin();
    firstDEMAccIt.GoToBegin(); //Global Accumulator
    while (!outputDEMIt.IsAtEnd() && !tmpDEMIt.IsAtEnd() && !tmpDEMAccIt.IsAtEnd() && !firstDEMAccIt.IsAtEnd())
      {

      // get the accumulator value
      AccumulatorPixelType accPixel = tmpDEMAccIt.Get();
      if (accPixel != 0)
        {

        DEMPixelType cellCurrentValue = outputDEMIt.Get();
        DEMPixelType cellHeight = tmpDEMIt.Get();
        switch (this->m_CellFusionMode)
          {
          case otb::CellFusionMode::MIN:
            {
            if ((cellHeight < cellCurrentValue) || (cellCurrentValue == m_NoDataValue))
              {
              outputDEMIt.Set(cellHeight);

              }
            }
            break;
          case otb::CellFusionMode::MAX:
            {
            if ((cellHeight > cellCurrentValue) || (cellCurrentValue == m_NoDataValue))
              {
              outputDEMIt.Set(cellHeight);
              }
            }
            break;
          case otb::CellFusionMode::MEAN:
            {

            outputDEMIt.Set(
                            cellCurrentValue * static_cast<DEMPixelType> (cellCurrentValue != m_NoDataValue)
                                + cellHeight);
            firstDEMAccIt.Set(firstDEMAccIt.Get() + accPixel);

            //divide sum by global accumulator
            /*   if (i == m_TempDEMRegions.size() - 1)
             {
             outputDEMIt.Set(outputDEMIt.Get() / static_cast<DEMPixelType> (firstDEMAccIt.Get()));
             }*/

            }
            break;
          case otb::CellFusionMode::ACC:
            {
            firstDEMAccIt.Set(firstDEMAccIt.Get() + accPixel);
            // global accumulator
            /*   if (i == m_TempDEMRegions.size() - 1)
             {
             outputDEMIt.Set(static_cast<DEMPixelType> (firstDEMAccIt.Get()));
             }*/
            }
            break;

          default:

            itkExceptionMacro(<< "Unexpected value cell fusion mode :"<<this->m_CellFusionMode)
        ;
            break;
          }
        }

      if (i == (m_TempDEMRegions.size() - 1))
        {
        if (this->m_CellFusionMode == otb::CellFusionMode::MEAN)
          {
          if (static_cast<DEMPixelType> (firstDEMAccIt.Get()) != 0)
            {
            outputDEMIt.Set(outputDEMIt.Get() / static_cast<DEMPixelType> (firstDEMAccIt.Get()));
            }
          else
            {
            outputDEMIt.Set(m_NoDataValue);
            }
          }
        else
          if (this->m_CellFusionMode == otb::CellFusionMode::ACC)
            {
            outputDEMIt.Set(static_cast<DEMPixelType> (firstDEMAccIt.Get()));
            }

        }
      ++outputDEMIt;
      ++tmpDEMIt;
      ++tmpDEMAccIt;
      ++firstDEMAccIt;
      }

    }

}

}


#endif
