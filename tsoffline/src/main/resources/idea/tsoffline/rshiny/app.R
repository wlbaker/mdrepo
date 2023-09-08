# Hello World

library( shiny )

ui <- fluidPage(
	h1("Hello World!"),
	sidebarLayout(
		sidebarPanel(
			selectInput("dataset", "Choose a dataset: ",
				choices=ls("package:datasets"),
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
