set(TEST_DRIVER otbTestDriver
    --add-before-env PYTHONPATH        "${OTBSWIGWrapper_BINARY_DIR}/src"
    --add-before-env PYTHONPATH        $<TARGET_FILE_DIR:_otbApplication>
    --add-before-env ITK_AUTOLOAD_PATH $<TARGET_FILE_DIR:otbapp_Smoothing> )

add_test( NAME pyTvSmoothing
          COMMAND ${TEST_DRIVER} Execute
                  ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/PythonSmoothingTest.py
                  ${OTB_DATA_ROOT}/Input/ToulouseExtract_WithGeom.tif
                  ${TEMP}/pyTvSmoothing_ )

add_test( NAME pyTvRescale
          COMMAND ${TEST_DRIVER} Execute
                  ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/PythonRescaleTest.py
                  ${OTB_DATA_ROOT}/Input/ToulouseExtract_WithGeom.tif
                  ${TEMP}/pyTvRescale)

add_test( NAME pyTvHyperspectralUnmixingUCLS
          COMMAND ${TEST_DRIVER} Execute
                  ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/PythonHyperspectralUnmixing1.py
                  ${OTB_DATA_ROOT}/Input/Hyperspectral/synthetic/hsi_cube.tif
                  ${TEMP}/pyTvHyperspectralUnmixing_ucls.tif
                  ${OTB_DATA_ROOT}/Input/Hyperspectral/synthetic/endmembers.tif
                  ucls
                  )

add_test( NAME pyTvBug440
          COMMAND ${TEST_DRIVER} Execute
                  ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Bug440.py
                  ${OTB_DATA_ROOT}/Input/scene.png
                  ${TEMP}/pyTvBug440Output.tif
                  )

add_test( NAME pyTvBug804
          COMMAND ${TEST_DRIVER} Execute
                  ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Bug804.py
                  )

add_test( NAME pyTvBug823
          COMMAND ${TEST_DRIVER} Execute
                  ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Bug823.py
                  )

add_test( NAME pyTvBug736
          COMMAND ${TEST_DRIVER}
                  --compare-image ${NOTOL}
                    ${BASELINE}/apTvRIRadiometricVegetationIndices.tif
                    ${TEMP}/pyTvBug736Output.tif
                  Execute
                  ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/Bug736.py
                  ${OTB_DATA_ROOT}/Input/veryverySmallFSATSW.tif
                  ${TEMP}/pyTvBug736Output.tif
                  )

add_test( NAME pyTvBandMathOutXML
          COMMAND ${TEST_DRIVER} Execute
                  ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/PythonOutXMLTest.py
                  ${OTB_DATA_ROOT}/Input/verySmallFSATSW_r.tif
                  ${OTB_DATA_ROOT}/Input/verySmallFSATSW_nir.tif
                  ${OTB_DATA_ROOT}/Input/verySmallFSATSW.tif
                  ${TEMP}/pyTvBandMathOutXML.tif
                  ${TEMP}/pyTvBandMathOutXML.xml
                  )

add_test( NAME pyTvBandMathInXML
          COMMAND ${TEST_DRIVER} Execute
                  ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/PythonInXMLTest.py
                  ${INPUTDATA}/pyTvBandMathInXML.xml
                  ${OTB_DATA_ROOT}/Input/verySmallFSATSW_r.tif
                  ${OTB_DATA_ROOT}/Input/verySmallFSATSW_nir.tif
                  ${OTB_DATA_ROOT}/Input/verySmallFSATSW.tif
                  ${TEMP}/pyTvBandMathInXML.tif
                  )

