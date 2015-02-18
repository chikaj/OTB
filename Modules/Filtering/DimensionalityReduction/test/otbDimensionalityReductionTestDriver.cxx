#include "otbTestMain.h"
void RegisterTests()
{
  REGISTER_TEST(otbNormalizeInnerProductPCAImageFilterNew);
  REGISTER_TEST(otbFastICAInternalOptimizerVectorImageFilterNewTest);
  REGISTER_TEST(otbFastICAImageFilterNewTest);
  REGISTER_TEST(otbFastICAImageFilterTest);
  REGISTER_TEST(otbNormalizeInnerProductPCAImageFilter);
  REGISTER_TEST(otbMaximumAutocorrelationFactorImageFilterNew);
  REGISTER_TEST(otbMaximumAutocorrelationFactorImageFilter);
  REGISTER_TEST(otbMNFImageFilterNewTest);
  REGISTER_TEST(otbMNFImageFilterTest);
  REGISTER_TEST(otbInnerProductPCAImageFilter);
  REGISTER_TEST(otbEstimateInnerProductPCAImageFilterNew);
  REGISTER_TEST(otbEstimateInnerProductPCAImageFilter);
  REGISTER_TEST(otbPCAImageFilterNewTest);
  REGISTER_TEST(otbPCAImageFilterTest);
  REGISTER_TEST(otbAngularProjectionSetImageFilterTest);
  REGISTER_TEST(otbAngularProjectionSetImageFilterNew);
  REGISTER_TEST(otbNAPCAImageFilterNewTest);
  REGISTER_TEST(otbNAPCAImageFilterTest);
  REGISTER_TEST(otbInnerProductPCAImageFilterNew);
  REGISTER_TEST(otbSparseWvltToAngleMapperListFilterNew);
  REGISTER_TEST(otbAngularProjectionImageFilterNew);
  REGISTER_TEST(otbAngularProjectionImageFilterTest);
  REGISTER_TEST(otbSparseWvltToAngleMapperListFilterNewTest);
}
