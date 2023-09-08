# Overlay

library( shiny )

ui <- fluidPage(
	h1("Segmented Overlap Plotter"),
	sidebarLayout(
		sidebarPanel(
			selectInput("dataset", "Choose a segmentation: ",
				choices=data$getSignals()
				),
			selectInput("dataset", "Choose a signal: ",
				choices=data$getSignals(),
				selected="pressure")
		),
		mainPanel(
			verbatimTextOutput("dump"),
			plotOutput("plot")
		)
	)
)

server <- function( input, output, session ) {
	output$dump <- renderPrint({
		dataset <- get(input$dataset, "package:datasets", inherits=FALSE)
		str(dataset)
	})
	output$plot <- renderPlot({
		dataset <- get(input$dataset, "package:datasets", inherits=FALSE)
		plot(dataset)
	})
}

shinyApp(ui, server )
