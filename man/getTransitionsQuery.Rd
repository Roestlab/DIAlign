% Generated by roxygen2: do not edit by hand
% Please edit documentation in R/get_osw_query.R
\name{getTransitionsQuery}
\alias{getTransitionsQuery}
\title{Get transitions from a SQLite file}
\usage{
getTransitionsQuery(runType = "DIA_Proteomics")
}
\arguments{
\item{runType}{(char) This must be one of the strings "DIA_proteomics", "DIA_Metabolomics".}
}
\value{
SQL query to be searched.
}
\description{
Query is generated to identify features and their transitions below a FDR cut-off from a run.
Order of transition intensity is kept same as the order of their Ids in \code{\link{getPrecursorsQuery}}.
}
\seealso{
\code{\link{fetchTransitionsFromRun}, \link{getPrecursorsQueryID}, \link{getPrecursorsQuery}}
}
\author{
Shubham Gupta, \email{shubh.gupta@mail.utoronto.ca}

ORCID: 0000-0003-3500-8152

License: (c) Author (2020) + GPL-3
Date: 2020-11-15
}
\keyword{internal}
