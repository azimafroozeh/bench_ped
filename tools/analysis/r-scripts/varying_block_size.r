library(ggplot2)
library(sqldf)
library(Cairo)

d = read.csv.sql('./varying_block_size.csv', sep=',', sql="select 122676.0/total_size cf,* from file")
d$block_exp = log2(d$block_size)
d

g1 <- subset(d, block_size == 65536)
gg <- ggplot(aes(x=block_size, y = cf), data=d) +
#    geom_bar(stat='identity') +
    geom_point() +
    theme_bw() +
    geom_line() +
    scale_x_continuous(trans='log2', labels = as.character(d$label), breaks = d$block_size) +
    labs(x='block size', y = 'compression ratio') +
    theme(
        panel.background = element_rect(fill = "transparent",colour = NA),
        plot.background = element_rect(fill = "transparent",colour = NA)
        )
gg <- gg + geom_point(data=g1,size=8.0, shape=1, colour="red") + geom_text(data=g1, label=expression(paste("2"^"16")), vjust=3)
CairoPDF("../../../../text/img/VaryingBlockSize.pdf", width = 5.5, height = 3, bg="transparent")
print(gg)
dev.off()

plot(gg)
