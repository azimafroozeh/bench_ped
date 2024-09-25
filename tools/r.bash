#!/usr/bin/env bash

sudo apt-get install r-base
R -e "install.packages('devtools', repos = 'http://cran.us.r-project.org')"
R -e "install.packages('knitr', repos = 'http://cran.us.r-project.org')"
R -e "install.packages('ggplot2', repos = 'http://cran.us.r-project.org')"
R -e "install.packages('ggalt', repos = 'http://cran.us.r-project.org')"

R -e "install.packages(c('devtools','mplot', 'googleVis'), repos = 'http://cran.us.r-project.org'); require(devtools); install_github('ramnathv/rCharts')"

# https://stat.ethz.ch/R-manual/R-devel/library/base/html/colnames.html
