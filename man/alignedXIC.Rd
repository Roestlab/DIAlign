% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/merge_chromatogram.R
\name{alignedXIC}
\alias{alignedXIC}
\title{Create an aligned chromatogram}
\usage{
alignedXIC(
  XIC,
  indices,
  method = "spline",
  polyOrd = 4,
  kernelLen = 9,
  splineMethod = "fmm"
)
}
\arguments{
\item{XIC}{(data-frame) first column is time, second column is intensity.}

\item{indices}{(integer) vector of monotonically increasing integers.}

\item{method}{(string) must be either "spline", "sgolay" or "linear".}

\item{polyOrd}{(integer) must be less than kernelLen.}

\item{kernelLen}{(integer) must be an odd integer.}

\item{splineMethod}{(string) must be either "fmm" or "natural".}
}
\value{
(dataframe) has two columns:
\item{time}{(numeric)}
\item{intensity}{(numeric)}
}
\description{
Modifies chromatogram to have the same length as indices. Imputes missing values with appropriate method.
Time and intensity for the flanking missing indices are set as NA.
}
\examples{
data(XIC_QFNNTDIVLLEDFQK_3_DIAlignR, package="DIAlignR")
data(alignObj_DIAlignR, package="DIAlignR")
XICs.ref <- XIC_QFNNTDIVLLEDFQK_3_DIAlignR[["hroest_K120809_Strep0\%PlasmaBiolRepl2_R04_SW_filt"]][["4618"]]
alignedIndices <- cbind(alignObj_DIAlignR@indexA_aligned, alignObj_DIAlignR@indexB_aligned)
colnames(alignedIndices) <- c("indexAligned.ref", "indexAligned.eXp")
alignedIndices[, 1:2][alignedIndices[, 1:2] == 0] <- NA_integer_
\dontrun{
plot(alignedXIC(XICs.ref[[1]], alignedIndices[,"indexAligned.ref"]), type = "l")
}
}
\seealso{
\code{\link{childXIC}, \link{imputeChromatogram}}
}
\author{
Shubham Gupta, \email{shubh.gupta@mail.utoronto.ca}

ORCID: 0000-0003-3500-8152

License: (c) Author (2020) + GPL-3
Date: 2020-05-23
}
\keyword{internal}
