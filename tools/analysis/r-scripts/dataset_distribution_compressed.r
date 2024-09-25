library(ggplot2)
library(sqldf)
library(Cairo)
library(stringr)
library(scales)

df <- data.frame(
  type = c("Integer", "Double", "String"),
  size = c(2483, 6474, 8011),
  pos = c(1, 2, 3)
  )
bp <- ggplot(df, aes(x="", y=size, fill=type))+
geom_bar(width = 1, stat = "identity")
pie <- bp + coord_polar("y", start=0)
pie <- pie + theme_classic() +
    geom_text(aes(y = size, label = paste0(percent(size/16970),"\n",round(size/1024,1)," GiB")), size= 2.5, label.size = 0,color="white", fill="white", position = position_stack(vjust= 0.5)) +
    theme(axis.line = element_blank(),
          axis.text = element_blank(),
          axis.ticks = element_blank(),
          plot.title = element_blank(),
          legend.title = element_text()) +
    labs(x = NULL, y = NULL, fill="Data Type") +
    scale_fill_manual(values=c( "#111111","#555555","#999999")) +
    theme(
        panel.background = element_rect(fill = "transparent",colour = NA),
        plot.background = element_rect(fill = "transparent",colour = NA)
        )
gg <- pie
CairoPDF("../../../../text/img/CompressedDatasetDistribution.pdf", width = 5.5, height =3, bg="transparent")
print(gg)
dev.off()
plot(gg)
