library(ggplot2)
library(sqldf)
library(Cairo)


d = read.csv.sql('./varying_sample_parameter.csv', sep=',', sql="select * from file ")
# 16425.8046875 is the optimal db2_after_size
d = sqldf("
select total/16425.8046875 cf, round(tuples*100.0/65536.0,2) as pct , * from d
")
d$cf = round((d$cf -1) * 100,1)
gg <- ggplot(aes(x = pct, y = cf), data=d) +
    geom_point(size=2, shape=4) +
    theme_bw() +
    scale_y_continuous(breaks=c(0,1,2,3,4,5,6,7)) +
    scale_x_continuous(trans = 'log10', breaks=c(0, 1,2,4,8)) +
    geom_smooth(se = FALSE, size= 0.5) +
    labs (x = 'sample size relative to chunk [%]', y = 'size overhead [%]') +
        theme(
        panel.background = element_rect(fill = "transparent",colour = NA),
        plot.background = element_rect(fill = "transparent",colour = NA)
        )
g1 <- subset(d, length == 64 & count == 10)
gg <- gg + geom_point(data=g1,size=8.0, shape=1, colour="red") + geom_text(data=g1, label="10x64", vjust=3)
CairoPDF("../../../../text/img/VaryingSampleSize.pdf", width = 5.5, height = 2.5)
print(gg)
dev.off()
plot(gg)
