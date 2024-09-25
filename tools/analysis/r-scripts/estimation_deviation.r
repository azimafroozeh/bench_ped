library(ggplot2)
library(sqldf)
library(Cairo)

d = read.csv.sql('../git-ignore/results_65536_64x10.txt', sep='\t', sql="select * from file where level >= 1 and  col_type != 'string' and after_size > 1000 and scheme_name not in ('UNCOMPRESSED', 'X_FOR')")
d = d[sample(nrow(d), 10000), ]
d = sqldf("
select *, cast(exp(cast(log(after_size) as integer)) as integer) as size_order from d
")

d$scheme_name[d$scheme_name == 'X_FBP'] <- "FBP"
d$scheme_name[d$scheme_name == 'X_DECIMAL'] <- "Decimal"
d$scheme_name[d$scheme_name == 'X_DICT'] <- "DICT"
d$scheme_name[d$scheme_name == 'X_FREQUENCY'] <- "Frequency"
d$scheme_name[d$scheme_name == 'X_HACKY'] <- "Two Way"
d$scheme_name[d$scheme_name == 'X_PBP'] <- "PBP"
d$scheme_name[d$scheme_name == 'X_RLE'] <- "RLE"
d$scheme_name <- factor(d$scheme_name, levels=c("FBP", "PBP", "DICT", "RLE", "Frequency", "Decimal", "Two Way"))
gg <- ggplot(aes(x=estimated_cf, y = actual_cf), data=d) +
    geom_point(size=0.1) +
    geom_line(data=data.frame(estimated_cf=c(1, 1000), actual_cf=c(1, 1000))) +
    facet_grid(rows = vars(scheme_name)) +
    scale_y_log10() +
    theme_bw() +
    labs(x='estimated compression ratio', y = 'actual compression ratio') +
    scale_x_continuous(trans='log10')
CairoPDF("../../../../text/img/EstimationAccuracy.pdf", height = 9, width = 5.5)
print(gg)
dev.off()

plot(gg)
