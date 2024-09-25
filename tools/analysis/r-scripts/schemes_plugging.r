library(ggplot2)
library(sqldf)
library(stringr)
library(Cairo)


d = read.csv.sql('./schemes_plugging.csv', sep=',', sql="select * from file ")


integer = sqldf("select d1.*, d2.size/d1.size as factor from d d1, d d2 where d1.type='integer' and d2.type=d1.type and d2.variant='Binary'")
gg <- ggplot(aes(x=reorder(variant, n), y=factor), data=integer) +
    geom_bar(stat='identity') +
    theme_bw() +
    theme( axis.text.x = element_text(angle = 45, vjust=0.5)) +
    scale_y_continuous(breaks=c(1,2,3,4,5,6,7,8,9)) +
    scale_x_discrete(labels = function(x) str_wrap(str_replace_all(x, "_nl_" , " "),
                                                 width = 5)) +
    labs(y="Compression Ratio", x="Schemes Pool", caption="") +
    geom_text(aes(label = paste0(round(size/1024, 1), "\n")), position = position_dodge(0.9),
              vjust = 1.2, color = "white", size = 3) +
    theme(
        panel.background = element_rect(fill = "transparent",colour = NA),
        plot.background = element_rect(fill = "transparent",colour = NA)
        )
CairoPDF("../../../../text/img/PluggingSchemesInteger.pdf", width = 3.5, height =4.5, bg="transparent")
print(gg)
dev.off()
plot(gg)


double = sqldf("select d1.*, d2.size/d1.size as factor from d d1, d d2 where d1.type='double' and d2.type=d1.type and d2.variant='Binary'")
gg <- ggplot(aes(x=reorder(variant, n), y=factor), data=double) +
    geom_bar(stat='identity') +
    theme_bw() +
    theme( axis.text.x = element_text(angle = 45, vjust=0.5)) +
    scale_y_continuous(breaks=c(1,2,3,4,5,6,7,8,9)) +
    scale_x_discrete(labels = function(x) str_wrap(str_replace_all(x, "_nl_" , " "),
                                                 width = 5)) +
    labs(y="Compression Ratio", x="Schemes Pool", caption="") +
    geom_text(aes(label = paste0(round(size/1024, 1), "\n")), position = position_dodge(0.9),
              vjust = 1.2, color = "white", size=3) +
    theme(
        panel.background = element_rect(fill = "transparent",colour = NA),
        plot.background = element_rect(fill = "transparent",colour = NA)
        )
CairoPDF("../../../../text/img/PluggingSchemesDouble.pdf", width= 3.5, height =4.5, bg="transparent")
print(gg)
dev.off()
plot(gg)


string = sqldf("select d1.*, d2.size/d1.size as factor from d d1, d d2 where d1.type='string' and d2.type=d1.type and d2.variant='Binary'")
gg <- ggplot(aes(x=reorder(variant, n), y=factor), data=string) +
    geom_bar(stat='identity') +
    theme_bw() +
    theme( axis.text.x = element_text(angle = 45, vjust=0.5)) +
    scale_y_continuous(breaks=c(1,3,5,7,9,11)) +
    scale_x_discrete(labels = function(x) str_wrap(str_replace_all(x, "_nl_" , " "),
                                                 width = 5)) +
    labs(y="Compression Ratio", x="Schemes Pool", caption="") +
    geom_text(aes(label = paste0(round(size/1024, 1), "\n")), position = position_dodge2(0.9),
              vjust = 1.2, color = "white", size=3) +
    theme(
        panel.background = element_rect(fill = "transparent",colour = NA),
        plot.background = element_rect(fill = "transparent",colour = NA)
        )
CairoPDF("../../../../text/img/PluggingSchemesString.pdf", width= 3.5, height =4.5, bg="transparent")
print(gg)
dev.off()

plot(gg)
