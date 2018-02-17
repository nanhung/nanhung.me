library(ggplot2)
temp <- paste("bold(sigma)")
p <- ggplot(NULL, aes(x = 1, y = 1)) + ylim(0.8, 1.2) +
  annotate("text", 1, 1, label = temp, color="white",
           size = 99, parse = TRUE) +
  theme(panel.background = element_rect(fill = "red"),
        axis.title = element_blank(), axis.ticks = element_blank(),
        axis.text = element_blank())

ggsave("logo.png", width = 5, height = 5, dpi = 96)