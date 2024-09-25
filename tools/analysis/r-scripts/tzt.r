library(ggplot2)
library(sqldf)
library(Cairo)

d = read.csv.sql('./fsst.tsv', sep='\t', sql="select * from file")

d = sqldf("select rel_name, count(*) as count, avg(before_pool) as avg_pool, col_name, round(avg(before_pool) * 1.0 / avg(after_pool),1) as cf from d group by rel_name,col_name")

sqldf("select * from d limit 10")

kbs = c(0.5, 1,2,4,8,16,32,64,128)
lbs = paste0(kbs, " KiB")
kbs = kbs * 1024

gg <- ggplot(aes(x=avg_pool, y = cf), data=d) +
    geom_jitter(size = 0.3) + #, aes(color = rel_name)
    theme_bw() +
    geom_smooth(method ='auto', se=FALSE, size =0.5) +
#    scale_x_log10() +
    scale_x_continuous( trans='log10',breaks = kbs, labels=lbs) +
    coord_cartesian(xlim = c(512,1024, 256*1024)) +
    geom_vline(xintercept = 16*1024,  color = 'red', size) +
#    annotate("rect", xmin = 16*1024, xmax = 256*1024, ymin=0,ymax=100,
#           alpha = .5) +
    labs(x='strings pool size', y = 'compression ratio') +
    theme(
        panel.background = element_rect(fill = "transparent",colour = NA),
        plot.background = element_rect(fill = "transparent",colour = NA)
        )
gg
CairoPDF("../../../../text/img/TZT.pdf", width = 5.5, height = 3, bg ="transparent")
print(gg)
dev.off()

plot(gg)



% strings pool space consumption relative to the total %
sp = read.csv.sql('./fsst.tsv', sep='\t', sql="select * from file")
sqldf("select * from sp limit 10")
%65%
sqldf("select 100.0 * sum(before_pool)/ sum(after_col - after_pool + before_pool) from sp limit 10")

sqldf("select 100.0 * sum(after_pool)/ sum(after_col) from sp limit 10")

sqldf("select (sum(before_pool - after_pool))/1024.0/1024/1024 from sp limit 10")

%47%
