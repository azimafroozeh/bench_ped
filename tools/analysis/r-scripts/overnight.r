library(ggplot2)
library(sqldf)

d = read.csv.sql('results_64x10.txt', sep='\t', sql="select * from file where level >= 1 and after_size > 1000 and col_type != 'string' ")
d = d[sample(nrow(d), 10000), ]
d = sqldf("
select *, cast(exp(cast(log(after_size) as integer)) as integer) as size_order from d
")

## ggplot(aes(x=estimated_cf, y = actual_cf), data=d) +
##     geom_point(aes(size=unique_count/650000)) +
##     geom_line(data=data.frame(estimated_cf=c(1, 100), actual_cf=c(1, 100))) + scale_size_continuous(range = c(0.1, 10)) +
##     facet_grid(scheme_name ~ size_order) +
##     scale_x_log10() +
##     scale_y_log10() +
##     theme_bw()


ggplot(aes(x=estimated_cf, y = actual_cf), data=d) +
    geom_point(size=0.3) +
    geom_line(data=data.frame(estimated_cf=c(1, 1000), actual_cf=c(1, 1000))) +
    facet_grid(scheme_name ~ .) +
    scale_x_log10() +
    scale_y_log10() +
    theme_bw()



# playground
d = read.csv.sql('/data/mt-compression/code/release/kb_min_w_cascades.tsv', sep='\t', sql="select * from file ")



sqldf("select distinct d1.col_type,d1.block_i, d1.col_name, d1.scheme_name || '|' || d2.scheme_name  || ',' || d2.comment || '|' || d3.scheme_name   || ',' || d3.comment as comb
 from d d1, d d2, d d3 where d1.block_i=d2.block_i and d2.block_i = d3.block_i and d1.col_name = d2.col_name and d2.col_name = d3.col_name and d2.level = d1.level + 1 and d3.level = d2.level + 1 order by  d1.block_i, d1.col_name desc limit 10")





sqldf("select d1.*, d2.*
 from d d1, d d2, d d3 where d1.block_i=d2.block_i and d1.rel_name=d2.rel_name  and d1.col_name = d2.col_name and d1.level = 1 and d1.scheme_name='X_PBP' and d2.level = d1.level + 1  limit 10")
