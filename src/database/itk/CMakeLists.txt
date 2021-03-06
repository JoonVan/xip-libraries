# Copyright Siemens Corporate Research Inc. 2007
# Author Sylvain Jaume <sylvain.jaume@siemens.com>

project(itk)

#--------------------------------------------------------------------
# Define the header files
#
set(HEADERS
  SoItkArray.h
  SoItkBinaryBallStructuringElement.h
  SoItkBinaryCrossStructuringElement.h
  SoItkCenteredRigid2DTransform.h
  SoItkComposeMFDataImage.h
  SoItkConvertDicomToItkImage.h
  SoItkConvertItkImageToXipImage.h
  SoItkConvertItkPointSetToMFVec3f.h
  SoItkConvertMFDicomToItkImage.h
  SoItkConvertXipImageToItkImage.h
  SoItkFastMarchingImageFilter.h
  SoItkFunctionBase.h
  SoItkImageFileReader.h
  SoItkImageFileWriter.h
  SoItkImageFunction.h
  SoItkImageRegistrationMethod.h
  SoItkImageToImageMetric.h
  SoItkImportImageFilter.h
  SoItkInterpolateImageFunction.h
  SoItkInterpolator.h
  SoItkLinearInterpolateImageFunction.h
  SoItkMatrix.h
  SoItkMatrixOffsetTransformBase.h
  SoItkMeanSquaresImageToImageMetric.h
  SoItkNeighborhood.h
  SoItkNodeContainer.h
  SoItkNonLinearOptimizer.h
  SoItkOptimizer.h
  SoItkPointSet.h
  SoItkRegularStepGradientDescentBaseOptimizer.h
  SoItkRegularStepGradientDescentOptimizer.h
  SoItkRigid2DTransform.h
  SoItkSeedImage.h
  SoItkSingleValuedNonLinearOptimizer.h
  SoItkTransform.h
  SoItkVectorImage.h
  generated/SoItkAbsImageFilter.h
  generated/SoItkAbsoluteValueDifferenceImageFilter.h
  generated/SoItkAccumulateImageFilter.h
  generated/SoItkAcosImageFilter.h
  generated/SoItkAdaptiveHistogramEqualizationImageFilter.h
  generated/SoItkAddImageFilter.h
  generated/SoItkAndImageFilter.h
  generated/SoItkAnisotropicDiffusionImageFilter.h
  generated/SoItkAnisotropicFourthOrderLevelSetImageFilter.h
  generated/SoItkAntiAliasBinaryImageFilter.h
  generated/SoItkApproximateSignedDistanceMapImageFilter.h
  generated/SoItkAsinImageFilter.h
  generated/SoItkAtan2ImageFilter.h
  generated/SoItkAtanImageFilter.h
  generated/SoItkBSplineCenteredL2ResampleImageFilterBase.h
  generated/SoItkBSplineCenteredResampleImageFilterBase.h
  generated/SoItkBSplineDecompositionImageFilter.h
  generated/SoItkBSplineDownsampleImageFilter.h
  generated/SoItkBSplineResampleImageFilterBase.h
  generated/SoItkBSplineUpsampleImageFilter.h
  generated/SoItkBilateralImageFilter.h
  generated/SoItkBinaryDilateImageFilter.h
  generated/SoItkBinaryErodeImageFilter.h
  generated/SoItkBinaryFunctorImageFilter.h
  generated/SoItkBinaryMagnitudeImageFilter.h
  generated/SoItkBinaryMaskToNarrowBandPointSetFilter.h
  generated/SoItkBinaryMedianImageFilter.h
  generated/SoItkBinaryMinMaxCurvatureFlowImageFilter.h
  generated/SoItkBinaryPruningImageFilter.h
  generated/SoItkBinaryThinningImageFilter.h
  generated/SoItkBinaryThresholdImageFilter.h
  generated/SoItkBinomialBlurImageFilter.h
  generated/SoItkBlackTopHatImageFilter.h
  generated/SoItkBoundedReciprocalImageFilter.h
  generated/SoItkCannyEdgeDetectionImageFilter.h
  generated/SoItkCannySegmentationLevelSetImageFilter.h
  generated/SoItkCastImageFilter.h
  generated/SoItkChangeInformationImageFilter.h
  generated/SoItkCheckerBoardImageFilter.h
  generated/SoItkClosingByReconstructionImageFilter.h
  generated/SoItkCollidingFrontsImageFilter.h
  generated/SoItkConfidenceConnectedImageFilter.h
  generated/SoItkConnectedComponentImageFilter.h
  generated/SoItkConnectedThresholdImageFilter.h
  generated/SoItkConstantPadImageFilter.h
  generated/SoItkConstrainedValueAdditionImageFilter.h
  generated/SoItkConstrainedValueDifferenceImageFilter.h
  generated/SoItkContourDirectedMeanDistanceImageFilter.h
  generated/SoItkContourMeanDistanceImageFilter.h
  generated/SoItkCosImageFilter.h
  generated/SoItkCropImageFilter.h
  generated/SoItkCurvatureAnisotropicDiffusionImageFilter.h
  generated/SoItkCurvatureFlowImageFilter.h
  generated/SoItkCurvesLevelSetImageFilter.h
  generated/SoItkDanielssonDistanceMapImageFilter.h
  generated/SoItkDenseFiniteDifferenceImageFilter.h
  generated/SoItkDerivativeImageFilter.h
  generated/SoItkDifferenceImageFilter.h
  generated/SoItkDilateObjectMorphologyImageFilter.h
  generated/SoItkDirectedHausdorffDistanceImageFilter.h
  generated/SoItkDiscreteGaussianImageFilter.h
  generated/SoItkDivideImageFilter.h
  generated/SoItkDoubleThresholdImageFilter.h
  generated/SoItkErodeObjectMorphologyImageFilter.h
  generated/SoItkExpImageFilter.h
  generated/SoItkExpNegativeImageFilter.h
  generated/SoItkExpandImageFilter.h
  generated/SoItkExtractImageFilter.h
  generated/SoItkFastIncrementalBinaryDilateImageFilter.h
  #generated/SoItkFastMarchingImageFilter.h
  generated/SoItkFiniteDifferenceImageFilter.h
  generated/SoItkFlipImageFilter.h
  generated/SoItkGeodesicActiveContourLevelSetImageFilter.h
  generated/SoItkGeodesicActiveContourShapePriorLevelSetImageFilter.h
  #generated/SoItkGetAverageSliceImageFilter.h
  generated/SoItkGradientAnisotropicDiffusionImageFilter.h
  generated/SoItkGradientMagnitudeImageFilter.h
  generated/SoItkGradientMagnitudeRecursiveGaussianImageFilter.h
  generated/SoItkGrayscaleConnectedClosingImageFilter.h
  generated/SoItkGrayscaleConnectedOpeningImageFilter.h
  generated/SoItkGrayscaleDilateImageFilter.h
  generated/SoItkGrayscaleErodeImageFilter.h
  generated/SoItkGrayscaleFillholeImageFilter.h
  generated/SoItkGrayscaleFunctionDilateImageFilter.h
  generated/SoItkGrayscaleFunctionErodeImageFilter.h
  generated/SoItkGrayscaleGeodesicDilateImageFilter.h
  generated/SoItkGrayscaleGeodesicErodeImageFilter.h
  generated/SoItkGrayscaleGrindPeakImageFilter.h
  generated/SoItkGrayscaleMorphologicalClosingImageFilter.h
  generated/SoItkGrayscaleMorphologicalOpeningImageFilter.h
  generated/SoItkHConcaveImageFilter.h
  generated/SoItkHConvexImageFilter.h
  generated/SoItkHMaximaImageFilter.h
  generated/SoItkHMinimaImageFilter.h
  generated/SoItkHardConnectedComponentImageFilter.h
  generated/SoItkHausdorffDistanceImageFilter.h
  generated/SoItkHistogramMatchingImageFilter.h
  generated/SoItkImageSource.h
  generated/SoItkImageToImageFilter.h
  generated/SoItkImageToMeshFilter.h
  generated/SoItkInPlaceImageFilter.h
  generated/SoItkIntensityWindowingImageFilter.h
  generated/SoItkInterpolateImageFilter.h
  generated/SoItkIsolatedConnectedImageFilter.h
  generated/SoItkIsolatedWatershedImageFilter.h
  generated/SoItkIsotropicFourthOrderLevelSetImageFilter.h
  generated/SoItkJoinSeriesImageFilter.h
  generated/SoItkLaplacianImageFilter.h
  generated/SoItkLaplacianRecursiveGaussianImageFilter.h
  generated/SoItkLaplacianSegmentationLevelSetImageFilter.h
  generated/SoItkLaplacianSharpeningImageFilter.h
  #generated/SoItkLazyEdgeDetectionImageFilter3D.h
  generated/SoItkLog10ImageFilter.h
  generated/SoItkLogImageFilter.h
  generated/SoItkMaskImageFilter.h
  generated/SoItkMaskNegatedImageFilter.h
  generated/SoItkMaskNeighborhoodOperatorImageFilter.h
  generated/SoItkMaximumImageFilter.h
  generated/SoItkMeanImageFilter.h
  generated/SoItkMedianImageFilter.h
  generated/SoItkMeshSource.h
  generated/SoItkMinMaxCurvatureFlowImageFilter.h
  generated/SoItkMinimumImageFilter.h
  generated/SoItkMinimumMaximumImageFilter.h
  generated/SoItkMirrorPadImageFilter.h
  generated/SoItkMorphologyImageFilter.h
  generated/SoItkMultiResolutionPyramidImageFilter.h
  generated/SoItkMultiplyImageFilter.h
  generated/SoItkNaryAddImageFilter.h
  generated/SoItkNaryFunctorImageFilter.h
  generated/SoItkNaryMaximumImageFilter.h
  generated/SoItkNeighborhoodConnectedImageFilter.h
  generated/SoItkNeighborhoodOperatorImageFilter.h
  generated/SoItkNoiseImageFilter.h
  generated/SoItkNonThreadedShrinkImageFilter.h
  generated/SoItkNormalizeImageFilter.h
  generated/SoItkNormalizedCorrelationImageFilter.h
  generated/SoItkNotImageFilter.h
  generated/SoItkObjectMorphologyImageFilter.h
  generated/SoItkOpeningByReconstructionImageFilter.h
  generated/SoItkOrImageFilter.h
  generated/SoItkOtsuMultipleThresholdsImageFilter.h
  generated/SoItkOtsuThresholdImageFilter.h
  generated/SoItkPadImageFilter.h
  generated/SoItkPasteImageFilter.h
  generated/SoItkPermuteAxesImageFilter.h
  generated/SoItkProcessObject.h
  generated/SoItkReconstructionByDilationImageFilter.h
  generated/SoItkReconstructionByErosionImageFilter.h
  generated/SoItkRecursiveGaussianImageFilter.h
  generated/SoItkRecursiveSeparableImageFilter.h
  generated/SoItkReflectImageFilter.h
  generated/SoItkRegionGrowImageFilter.h
  generated/SoItkRegionOfInterestImageFilter.h
  generated/SoItkRelabelComponentImageFilter.h
  generated/SoItkResampleImageFilter.h
  generated/SoItkRescaleIntensityImageFilter.h
  generated/SoItkSTAPLEImageFilter.h
  generated/SoItkScalarImageKmeansImageFilter.h
  generated/SoItkSegmentationLevelSetImageFilter.h
  generated/SoItkShapeDetectionLevelSetImageFilter.h
  generated/SoItkShapePriorSegmentationLevelSetImageFilter.h
  generated/SoItkShiftScaleImageFilter.h
  generated/SoItkShrinkImageFilter.h
  generated/SoItkSigmoidImageFilter.h
  generated/SoItkSignedDanielssonDistanceMapImageFilter.h
  generated/SoItkSimpleContourExtractorImageFilter.h

  generated/SoItkSinImageFilter.h
  generated/SoItkSmoothingRecursiveGaussianImageFilter.h
  generated/SoItkSobelEdgeDetectionImageFilter.h
  generated/SoItkSparseFieldFourthOrderLevelSetImageFilter.h
  generated/SoItkSparseFieldLevelSetImageFilter.h
  generated/SoItkSqrtImageFilter.h
  generated/SoItkSquareImageFilter.h
  generated/SoItkSquaredDifferenceImageFilter.h
  generated/SoItkStatisticsImageFilter.h
  generated/SoItkSubtractImageFilter.h
  generated/SoItkTanImageFilter.h
  generated/SoItkTernaryAddImageFilter.h
  generated/SoItkTernaryFunctorImageFilter.h
  generated/SoItkTernaryMagnitudeImageFilter.h
  generated/SoItkTernaryMagnitudeSquaredImageFilter.h
  generated/SoItkThresholdImageFilter.h
  generated/SoItkThresholdSegmentationLevelSetImageFilter.h
  generated/SoItkTileImageFilter.h
  generated/SoItkTobogganImageFilter.h
  generated/SoItkUnaryFunctorImageFilter.h
  generated/SoItkUnsharpMaskLevelSetImageFilter.h
  generated/SoItkVotingBinaryHoleFillingImageFilter.h
  generated/SoItkVotingBinaryImageFilter.h
  generated/SoItkVotingBinaryIterativeHoleFillingImageFilter.h
  generated/SoItkWatershedImageFilter.h
  generated/SoItkWeightedAddImageFilter.h
  generated/SoItkWhiteTopHatImageFilter.h
  generated/SoItkWrapPadImageFilter.h
  generated/SoItkXorImageFilter.h
  generated/SoItkZeroCrossingBasedEdgeDetectionImageFilter.h
  generated/SoItkZeroCrossingImageFilter.h
  generated/itkWrapInit.h)


#--------------------------------------------------------------------
# Define the source files
#
set(SOURCES
  SbItkNodeContainer.cpp
  SoItkArray.cpp
  SoItkBinaryBallStructuringElement.cpp
  SoItkBinaryCrossStructuringElement.cpp
  SoItkCenteredRigid2DTransform.cpp
  SoItkComposeMFDataImage.cpp
  #SoItkConvertDicomToItkImage.cpp
  SoItkConvertItkImageToXipImage.cpp
  SoItkConvertItkPointSetToMFVec3f.cpp
  #SoItkConvertMFDicomToItkImage.cpp
  SoItkConvertXipImageToItkImage.cpp
  SoItkDataArray.cpp
  SoItkDataDecorator.cpp
  SoItkDataImage.cpp
  SoItkDataImageMetric.cpp
  SoItkDataInterpolator.cpp
  SoItkDataMatrix.cpp
  SoItkDataNeighborhood.cpp
  SoItkDataOptimizer.cpp
  SoItkDataPointSet.cpp
  SoItkDataTransform.cpp
  SoItkFastMarchingImageFilter.cpp
  SoItkFunctionBase.cpp
  SoItkImageFileReader.cpp
  SoItkImageFileWriter.cpp
  SoItkImageFunction.cpp
  SoItkImageRegistrationMethod.cpp
  SoItkImageToImageMetric.cpp
  SoItkImportImageFilter.cpp
  SoItkInterpolateImageFunction.cpp
  SoItkInterpolator.cpp
  SoItkLinearInterpolateImageFunction.cpp
  SoItkMFDataImage.cpp
  SoItkMatrix.cpp
  SoItkMatrixOffsetTransformBase.cpp
  SoItkMeanSquaresImageToImageMetric.cpp
  SoItkNeighborhood.cpp
  SoItkNodeContainer.cpp
  SoItkNonLinearOptimizer.cpp
  SoItkOptimizer.cpp
  SoItkPointSet.cpp
  SoItkRegularStepGradientDescentBaseOptimizer.cpp
  SoItkRegularStepGradientDescentOptimizer.cpp
  SoItkRigid2DTransform.cpp
  SoItkSFDataArray.cpp
  SoItkSFDataDecorator.cpp
  SoItkSFDataImage.cpp
  SoItkSFDataImageMetric.cpp
  SoItkSFDataInterpolator.cpp
  SoItkSFDataMatrix.cpp
  SoItkSFDataNeighborhood.cpp
  SoItkSFDataOptimizer.cpp
  SoItkSFDataPointSet.cpp
  SoItkSFDataTransform.cpp
  SoItkSFNodeContainer.cpp
  SoItkSeedImage.cpp
  SoItkSingleValuedNonLinearOptimizer.cpp
  SoItkTransform.cpp
  SoItkVectorImage.cpp
  xipivitk.cpp
  generated/SoItkAbsImageFilter.cpp
  generated/SoItkAbsoluteValueDifferenceImageFilter.cpp
  generated/SoItkAccumulateImageFilter.cpp
  generated/SoItkAcosImageFilter.cpp
  generated/SoItkAdaptiveHistogramEqualizationImageFilter.cpp
  generated/SoItkAddImageFilter.cpp
  generated/SoItkAndImageFilter.cpp
  generated/SoItkAnisotropicDiffusionImageFilter.cpp
  generated/SoItkAnisotropicFourthOrderLevelSetImageFilter.cpp
  generated/SoItkAntiAliasBinaryImageFilter.cpp
  generated/SoItkApproximateSignedDistanceMapImageFilter.cpp
  generated/SoItkAsinImageFilter.cpp
  generated/SoItkAtan2ImageFilter.cpp
  generated/SoItkAtanImageFilter.cpp
  generated/SoItkBSplineCenteredL2ResampleImageFilterBase.cpp
  generated/SoItkBSplineCenteredResampleImageFilterBase.cpp
  generated/SoItkBSplineDecompositionImageFilter.cpp
  generated/SoItkBSplineDownsampleImageFilter.cpp
  generated/SoItkBSplineResampleImageFilterBase.cpp
  generated/SoItkBSplineUpsampleImageFilter.cpp
  generated/SoItkBilateralImageFilter.cpp
  generated/SoItkBinaryDilateImageFilter.cpp
  generated/SoItkBinaryErodeImageFilter.cpp
  generated/SoItkBinaryFunctorImageFilter.cpp
  generated/SoItkBinaryMagnitudeImageFilter.cpp
  generated/SoItkBinaryMaskToNarrowBandPointSetFilter.cpp
  generated/SoItkBinaryMedianImageFilter.cpp
  generated/SoItkBinaryMinMaxCurvatureFlowImageFilter.cpp
  generated/SoItkBinaryPruningImageFilter.cpp
  generated/SoItkBinaryThinningImageFilter.cpp
  generated/SoItkBinaryThresholdImageFilter.cpp
  generated/SoItkBinomialBlurImageFilter.cpp
  generated/SoItkBlackTopHatImageFilter.cpp
  generated/SoItkBoundedReciprocalImageFilter.cpp
  generated/SoItkCannyEdgeDetectionImageFilter.cpp
  generated/SoItkCannySegmentationLevelSetImageFilter.cpp
  generated/SoItkCastImageFilter.cpp
  generated/SoItkChangeInformationImageFilter.cpp
  generated/SoItkCheckerBoardImageFilter.cpp
  generated/SoItkClosingByReconstructionImageFilter.cpp
  generated/SoItkCollidingFrontsImageFilter.cpp
  generated/SoItkConfidenceConnectedImageFilter.cpp
  generated/SoItkConnectedComponentImageFilter.cpp
  generated/SoItkConnectedThresholdImageFilter.cpp
  generated/SoItkConstantPadImageFilter.cpp
  generated/SoItkConstrainedValueAdditionImageFilter.cpp
  generated/SoItkConstrainedValueDifferenceImageFilter.cpp
  generated/SoItkContourDirectedMeanDistanceImageFilter.cpp
  generated/SoItkContourMeanDistanceImageFilter.cpp
  generated/SoItkCosImageFilter.cpp
  generated/SoItkCropImageFilter.cpp
  generated/SoItkCurvatureAnisotropicDiffusionImageFilter.cpp
  generated/SoItkCurvatureFlowImageFilter.cpp
  generated/SoItkCurvesLevelSetImageFilter.cpp
  generated/SoItkDanielssonDistanceMapImageFilter.cpp
  generated/SoItkDenseFiniteDifferenceImageFilter.cpp
  generated/SoItkDerivativeImageFilter.cpp
  generated/SoItkDifferenceImageFilter.cpp
  generated/SoItkDilateObjectMorphologyImageFilter.cpp
  generated/SoItkDirectedHausdorffDistanceImageFilter.cpp
  generated/SoItkDiscreteGaussianImageFilter.cpp
  generated/SoItkDivideImageFilter.cpp
  generated/SoItkDoubleThresholdImageFilter.cpp
  generated/SoItkErodeObjectMorphologyImageFilter.cpp
  generated/SoItkExpImageFilter.cpp
  generated/SoItkExpNegativeImageFilter.cpp
  generated/SoItkExpandImageFilter.cpp
  generated/SoItkExtractImageFilter.cpp
  generated/SoItkFastIncrementalBinaryDilateImageFilter.cpp
  #generated/SoItkFastMarchingImageFilter.cpp
  generated/SoItkFiniteDifferenceImageFilter.cpp
  generated/SoItkFlipImageFilter.cpp
  generated/SoItkGeodesicActiveContourLevelSetImageFilter.cpp
  generated/SoItkGeodesicActiveContourShapePriorLevelSetImageFilter.cpp
  #generated/SoItkGetAverageSliceImageFilter.cpp
  generated/SoItkGradientAnisotropicDiffusionImageFilter.cpp
  generated/SoItkGradientMagnitudeImageFilter.cpp
  generated/SoItkGradientMagnitudeRecursiveGaussianImageFilter.cpp
  generated/SoItkGrayscaleConnectedClosingImageFilter.cpp
  generated/SoItkGrayscaleConnectedOpeningImageFilter.cpp
  generated/SoItkGrayscaleDilateImageFilter.cpp
  generated/SoItkGrayscaleErodeImageFilter.cpp
  generated/SoItkGrayscaleFillholeImageFilter.cpp
  generated/SoItkGrayscaleFunctionDilateImageFilter.cpp
  generated/SoItkGrayscaleFunctionErodeImageFilter.cpp
  generated/SoItkGrayscaleGeodesicDilateImageFilter.cpp
  generated/SoItkGrayscaleGeodesicErodeImageFilter.cpp
  generated/SoItkGrayscaleGrindPeakImageFilter.cpp
  generated/SoItkGrayscaleMorphologicalClosingImageFilter.cpp
  generated/SoItkGrayscaleMorphologicalOpeningImageFilter.cpp
  generated/SoItkHConcaveImageFilter.cpp
  generated/SoItkHConvexImageFilter.cpp
  generated/SoItkHMaximaImageFilter.cpp
  generated/SoItkHMinimaImageFilter.cpp
  generated/SoItkHardConnectedComponentImageFilter.cpp
  generated/SoItkHausdorffDistanceImageFilter.cpp
  generated/SoItkHistogramMatchingImageFilter.cpp
  generated/SoItkImageSource.cpp
  generated/SoItkImageToImageFilter.cpp
  generated/SoItkImageToMeshFilter.cpp
  generated/SoItkInPlaceImageFilter.cpp
  generated/SoItkIntensityWindowingImageFilter.cpp
  generated/SoItkInterpolateImageFilter.cpp
  generated/SoItkIsolatedConnectedImageFilter.cpp
  generated/SoItkIsolatedWatershedImageFilter.cpp
  generated/SoItkIsotropicFourthOrderLevelSetImageFilter.cpp
  generated/SoItkJoinSeriesImageFilter.cpp
  generated/SoItkLaplacianImageFilter.cpp
  generated/SoItkLaplacianRecursiveGaussianImageFilter.cpp
  generated/SoItkLaplacianSegmentationLevelSetImageFilter.cpp
  generated/SoItkLaplacianSharpeningImageFilter.cpp
  #generated/SoItkLazyEdgeDetectionImageFilter3D.cpp
  generated/SoItkLog10ImageFilter.cpp
  generated/SoItkLogImageFilter.cpp
  generated/SoItkMaskImageFilter.cpp
  generated/SoItkMaskNegatedImageFilter.cpp
  generated/SoItkMaskNeighborhoodOperatorImageFilter.cpp
  generated/SoItkMaximumImageFilter.cpp
  generated/SoItkMeanImageFilter.cpp
  generated/SoItkMedianImageFilter.cpp
  generated/SoItkMeshSource.cpp
  generated/SoItkMinMaxCurvatureFlowImageFilter.cpp
  generated/SoItkMinimumImageFilter.cpp
  generated/SoItkMinimumMaximumImageFilter.cpp
  generated/SoItkMirrorPadImageFilter.cpp
  generated/SoItkMorphologyImageFilter.cpp
  generated/SoItkMultiResolutionPyramidImageFilter.cpp
  generated/SoItkMultiplyImageFilter.cpp
  generated/SoItkNaryAddImageFilter.cpp
  generated/SoItkNaryFunctorImageFilter.cpp
  generated/SoItkNaryMaximumImageFilter.cpp
  generated/SoItkNeighborhoodConnectedImageFilter.cpp
  generated/SoItkNeighborhoodOperatorImageFilter.cpp
  generated/SoItkNoiseImageFilter.cpp
  generated/SoItkNonThreadedShrinkImageFilter.cpp
  generated/SoItkNormalizeImageFilter.cpp
  generated/SoItkNormalizedCorrelationImageFilter.cpp
  generated/SoItkNotImageFilter.cpp
  generated/SoItkObjectMorphologyImageFilter.cpp
  generated/SoItkOpeningByReconstructionImageFilter.cpp
  generated/SoItkOrImageFilter.cpp
  generated/SoItkOtsuMultipleThresholdsImageFilter.cpp
  generated/SoItkOtsuThresholdImageFilter.cpp
  generated/SoItkPadImageFilter.cpp
  generated/SoItkPasteImageFilter.cpp
  generated/SoItkPermuteAxesImageFilter.cpp
  generated/SoItkProcessObject.cpp
  generated/SoItkReconstructionByDilationImageFilter.cpp
  generated/SoItkReconstructionByErosionImageFilter.cpp
  generated/SoItkRecursiveGaussianImageFilter.cpp
  generated/SoItkRecursiveSeparableImageFilter.cpp
  generated/SoItkReflectImageFilter.cpp
  generated/SoItkRegionGrowImageFilter.cpp
  generated/SoItkRegionOfInterestImageFilter.cpp
  generated/SoItkRelabelComponentImageFilter.cpp
  generated/SoItkResampleImageFilter.cpp
  generated/SoItkRescaleIntensityImageFilter.cpp
  generated/SoItkSTAPLEImageFilter.cpp
  generated/SoItkScalarImageKmeansImageFilter.cpp
  generated/SoItkSegmentationLevelSetImageFilter.cpp
  generated/SoItkShapeDetectionLevelSetImageFilter.cpp
  generated/SoItkShapePriorSegmentationLevelSetImageFilter.cpp
  generated/SoItkShiftScaleImageFilter.cpp
  generated/SoItkShrinkImageFilter.cpp
  generated/SoItkSigmoidImageFilter.cpp
  generated/SoItkSignedDanielssonDistanceMapImageFilter.cpp
  generated/SoItkSimpleContourExtractorImageFilter.cpp

  generated/SoItkSinImageFilter.cpp
  generated/SoItkSmoothingRecursiveGaussianImageFilter.cpp
  generated/SoItkSobelEdgeDetectionImageFilter.cpp
  generated/SoItkSparseFieldFourthOrderLevelSetImageFilter.cpp
  generated/SoItkSparseFieldLevelSetImageFilter.cpp
  generated/SoItkSqrtImageFilter.cpp
  generated/SoItkSquareImageFilter.cpp
  generated/SoItkSquaredDifferenceImageFilter.cpp
  generated/SoItkStatisticsImageFilter.cpp
  generated/SoItkSubtractImageFilter.cpp
  generated/SoItkTanImageFilter.cpp
  generated/SoItkTernaryAddImageFilter.cpp
  generated/SoItkTernaryFunctorImageFilter.cpp
  generated/SoItkTernaryMagnitudeImageFilter.cpp
  generated/SoItkTernaryMagnitudeSquaredImageFilter.cpp
  generated/SoItkThresholdImageFilter.cpp
  generated/SoItkThresholdSegmentationLevelSetImageFilter.cpp
  generated/SoItkTileImageFilter.cpp
  generated/SoItkTobogganImageFilter.cpp
  generated/SoItkUnaryFunctorImageFilter.cpp
  generated/SoItkUnsharpMaskLevelSetImageFilter.cpp
  generated/SoItkVotingBinaryHoleFillingImageFilter.cpp
  generated/SoItkVotingBinaryImageFilter.cpp
  generated/SoItkVotingBinaryIterativeHoleFillingImageFilter.cpp
  generated/SoItkWatershedImageFilter.cpp
  generated/SoItkWeightedAddImageFilter.cpp
  generated/SoItkWhiteTopHatImageFilter.cpp
  generated/SoItkWrapPadImageFilter.cpp
  generated/SoItkXorImageFilter.cpp
  generated/SoItkZeroCrossingBasedEdgeDetectionImageFilter.cpp
  generated/SoItkZeroCrossingImageFilter.cpp
  generated/itkWrapInit.cpp)

#--------------------------------------------------------------------
# Setup option for building with ITK_PATENTED
option(BUILD_WITH_ITK_PATENTED
  "Build XIP ITK Wrapper with patented ITK algorithms" OFF)
mark_as_advanced(BUILD_WITH_ITK_PATENTED)

# Add headers and sources if building with ITK_PATENTED
if(BUILD_WITH_ITK_PATENTED)
  set(HEADERS ${HEADERS}
    generated/SoItkSimpleFuzzyConnectednessImageFilterBase.h
    generated/SoItkSimpleFuzzyConnectednessScalarImageFilter.h

  )
  set(SOURCES ${SOURCES}
    generated/SoItkSimpleFuzzyConnectednessImageFilterBase.cpp
    generated/SoItkSimpleFuzzyConnectednessScalarImageFilter.cpp
  )
endif(BUILD_WITH_ITK_PATENTED)

#--------------------------------------------------------------------
# Find the Insight Toolkit libraries
#
if(${CMAKE_BINARY_DIR} MATCHES release)
	
  if(CMAKE_CL_64)
    find_package(ITK REQUIRED PATHS
		${CMAKE_SOURCE_DIR}/../xipext-win32-vs8-release/ITK/lib/InsightToolkit)
  endif(CMAKE_CL_64)

  if(WIN32 AND NOT CMAKE_CL_64)
    find_package(ITK REQUIRED PATHS
		${CMAKE_SOURCE_DIR}/../xipext-win32-vs8-release/ITK/lib/InsightToolkit)
  endif(WIN32 AND NOT CMAKE_CL_64)

  if(DARWIN)
    find_package(ITK REQUIRED PATHS
    ${CMAKE_SOURCE_DIR}/../xipext-mac-xcode-release/ITK/lib/InsightToolkit)
  endif(DARWIN)

  if(UNIX AND NOT DARWIN)
    find_package(ITK REQUIRED PATHS
    ${CMAKE_SOURCE_DIR}/../xipext-linux-32bit-release/ITK/lib/InsightToolkit)
  endif(UNIX AND NOT DARWIN)

else(${CMAKE_BINARY_DIR} MATCHES release)

  if(CMAKE_CL_64)
    find_package(ITK REQUIRED PATHS
    ${CMAKE_SOURCE_DIR}/../xipext-win64-vs8-debug/ITK/lib/InsightToolkit)
  endif(CMAKE_CL_64)

  if(WIN32 AND NOT CMAKE_CL_64)
    find_package(ITK REQUIRED PATHS
    ${CMAKE_SOURCE_DIR}/../xipext-win32-vs8-debug/ITK/lib/InsightToolkit)
  endif(WIN32 AND NOT CMAKE_CL_64)

  if(DARWIN)
    find_package(ITK REQUIRED PATHS
    ${CMAKE_SOURCE_DIR}/../xipext-mac-xcode-debug/ITK/lib/InsightToolkit)
  endif(DARWIN)

  if(UNIX AND NOT DARWIN)
    find_package(ITK REQUIRED PATHS
    ${CMAKE_SOURCE_DIR}/../xipext-linux-32bit-debug/ITK/lib/InsightToolkit)
  endif(UNIX AND NOT DARWIN)

endif(${CMAKE_BINARY_DIR} MATCHES release)

find_package(ITK)
#include(${ITK_USE_FILE})

if(WIN32)
if(NOT ${ITK_VERSION_MAJOR}.${ITK_VERSION_MINOR} EQUAL 3.8)
  message(FATAL_ERROR "ITK 3.8 Required. Found ITK version "
					${ITK_VERSION_MAJOR}.${ITK_VERSION_MINOR})
endif(NOT ${ITK_VERSION_MAJOR}.${ITK_VERSION_MINOR} EQUAL 3.8)
else(WIN32)
if(${ITK_VERSION_MAJOR}.${ITK_VERSION_MINOR} LESS 3.12)
  message(FATAL_ERROR "At least ITK 3.12 Required. Found ITK version "
					${ITK_VERSION_MAJOR}.${ITK_VERSION_MINOR})
endif(${ITK_VERSION_MAJOR}.${ITK_VERSION_MINOR} LESS 3.12)
endif(WIN32)
#--------------------------------------------------------------------
# Define compiler flags
#
if(WIN32)
  add_definitions(-DXIPIVITK_EXPORTS)
else(WIN32)
  add_definitions(-DHAVE_CONFIG_H)
endif(WIN32)

if(BUILD_WITH_ITK_PATENTED)
  add_definitions(-DBUILD_WITH_ITK_PATENTED)
endif(BUILD_WITH_ITK_PATENTED)

#--------------------------------------------------------------------
# Define the include directories
#
include_directories(${ITK_INCLUDE_DIRS})

#--------------------------------------------------------------------
# Define the link directories
#
link_directories(${ITK_LIBRARY_DIRS})

#--------------------------------------------------------------------
# Compile the library
#
if(BUILD_SHARED_LIBS)
  add_library(xipivitk SHARED ${HEADERS} ${SOURCES})
else(BUILD_SHARED_LIBS)
  add_library(xipivitk STATIC ${HEADERS} ${SOURCES})
endif(BUILD_SHARED_LIBS)

set_target_properties(xipivitk
  PROPERTIES VERSION ${XIP_VERSION_STRING}
  SOVERSION ${XIP_VERSION_STRING})

#--------------------------------------------------------------------
# Link the library
#
target_link_libraries(xipivitk
  ${XIP_CORE_LIBRARY}
  ${ITK_LIBRARIES})

add_dependencies(xipivitk xipivcore)
  
if(WIN32 AND NOT BORLAND)
  target_link_libraries(xipivitk
    Ws2_32
    wsock32
    Snmpapi)
endif(WIN32 AND NOT BORLAND)

#--------------------------------------------------------------------
# Install the library
#
install(TARGETS xipivitk
  RUNTIME DESTINATION bin/release CONFIGURATIONS Release
  ARCHIVE DESTINATION lib/release CONFIGURATIONS Release
  LIBRARY DESTINATION lib/release CONFIGURATIONS Release
  BUNDLE  DESTINATION lib/release CONFIGURATIONS Release)

install(TARGETS xipivitk
  RUNTIME DESTINATION bin/debug   CONFIGURATIONS Debug
  ARCHIVE DESTINATION lib/debug   CONFIGURATIONS Debug
  LIBRARY DESTINATION lib/debug   CONFIGURATIONS Debug
  BUNDLE  DESTINATION lib/debug   CONFIGURATIONS Debug)

if(WIN32)
  install(FILES ${LIBRARY_OUTPUT_PATH}/debug/xipivitk${CMAKE_DEBUG_POSTFIX}.pdb
    DESTINATION bin/debug CONFIGURATIONS Debug)
endif(WIN32)
