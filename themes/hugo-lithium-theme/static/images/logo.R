library(ggplot2)
temp <- paste("bold(Lambda)")
p <- ggplot(NULL, aes(x = 1, y = 1)) + ylim(0.8, 1.2) +
  annotate("text", 1, 1, label = temp, color="white",
           size = 90, parse = TRUE) +
  theme_bw() +
  theme(panel.background = element_rect(fill = "red"),
        panel.grid.major = element_blank(),
        panel.grid.minor = element_blank(),
        axis.title = element_blank(), axis.ticks = element_blank(),
        axis.text = element_blank())

ggsave("logo.png", width = 5, height = 5, dpi = 96)