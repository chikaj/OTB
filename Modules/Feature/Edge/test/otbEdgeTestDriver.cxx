#include "otbTestMain.h"
void RegisterTests()
{
  REGISTER_TEST(otbPixelSuppressionByDirectionNew);
  REGISTER_TEST(otbEdgeDetectorImageFilter);
  REGISTER_TEST(otbHorizontalSobelVectorImageFilterNewTest);
  REGISTER_TEST(otbHorizontalSobelVectorImageFilterTest);
  REGISTER_TEST(otbAssymmetricFusionOfLineDetector);
  REGISTER_TEST(otbLocalHoughDraw);
  REGISTER_TEST(otbAssociativeSymmetricalSum);
  REGISTER_TEST(otbPersistentVectorizationFilterNew);
  REGISTER_TEST(otbLineCorrelationDetectorNew);
  REGISTER_TEST(otbPersistentVectorizationFilter);
  REGISTER_TEST(otbEdgeDensityImageFilter);
  REGISTER_TEST(otbLineCorrelationDetector);
  REGISTER_TEST(otbSobelVectorImageFilterNewTest);
  REGISTER_TEST(otbSobelVectorImageFilterTest);
  REGISTER_TEST(otbAssociativeSymmetricalSumNew);
  REGISTER_TEST(otbHoughTransform2DLinesImageTest);
  REGISTER_TEST(otbPixelSuppressionByDirection);
  REGISTER_TEST(otbLocalHoughNew);
  REGISTER_TEST(otbEdgeDetectorImageFilterNew);
  REGISTER_TEST(otbEdgeDensityImageFilterNew);
  REGISTER_TEST(otbLocalHough);
  REGISTER_TEST(otbExtractSegments);
  REGISTER_TEST(otbExtractSegmentsNew);
  REGISTER_TEST(otbAssymmetricFusionOfLineDetectorNew);
  REGISTER_TEST(otbLineRatioDetector);
  REGISTER_TEST(otbTouziEdgeDetectorDirection);
  REGISTER_TEST(otbTouziEdgeDetectorNew);
  REGISTER_TEST(otbVerticalSobelVectorImageFilterNewTest);
  REGISTER_TEST(otbVerticalSobelVectorImageFilterTest);
  REGISTER_TEST(otbStreamingLineSegmentDetectorNew);
  REGISTER_TEST(otbStreamingLineSegmentDetector);
  REGISTER_TEST(otbLineRatioDetectorNew);
  REGISTER_TEST(otbTouziEdgeDetector);
  REGISTER_TEST(otbLineRatioDetectorLinear);
  REGISTER_TEST(otbLineSegmentDetectorNew);
  REGISTER_TEST(otbLineSegmentDetector);
  REGISTER_TEST(otbLineSegmentDetector_8b_16b_compare);
  REGISTER_TEST(otbLineCorrelationDetectorLinear);
  REGISTER_TEST(otbLineDetectorBaseNew);
  REGISTER_TEST(otbFillGapsFilter);
  REGISTER_TEST(otbFillGapsFilterNew);
}
