library(ggplot2)
library(sqldf)
library(Cairo)
library(stringr)

d = read.csv.sql('./total_compression_factor.tsv', sep=',', sql="select * from file ")
d = sqldf("select d1.type, d1.size, d2.size / d1.size as cf from d d1,d d2 where d2.type='Binary' and d1.type<>'Binary'")
d

gg <- ggplot(aes(x=reorder(type, cf), y=cf), data=d) +
    geom_bar(stat='identity') +
    theme_bw() +
    labs(title=" ", y="Compression Ratio", x="Columnar Storage", caption="") +
    scale_x_discrete(labels = function(x) str_wrap(str_replace_all(x, "_nl_" , " "),
                                                 width = 10))  +
    geom_text(aes(label = paste0(round(size, 1), "\nGiB")), position = position_dodge(0.9),
              vjust = 1.2, color = "white", size=3) +
    theme(
        panel.background = element_rect(fill = "transparent",colour = NA),
        plot.background = element_rect(fill = "transparent",colour = NA)
        )
CairoPDF("../../../../text/img/CompressionRatioCompairson.pdf", width = 5.5, height =3, bg="transparent")
print(gg)
dev.off()
plot(gg)
