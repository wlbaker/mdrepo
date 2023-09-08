
require( rJava )
require( tools )  # for the help system
require( ggplot2 )


# these don't appear to have any effect in scripts run through the engine?
options(error=traceback)
options(show.error.locations = TRUE)
options(device = "JavaGD")
options(max.print = 1000 )

.jinit()

app <- J("idea.tsoffline.AppUtil")$getInstance()
filter <- J("idea.tsoffline.filter.FilterUtil")$getInstance()
data <- J("idea.tsoffline.model.DerivedUtil")$getInstance()
gui <- J("idea.GuiUtil")

'+.jobjRef' <- function (e1, e2 ) { 
	add( e1, e2)
}

'-.jobjRef' <- function (e1, e2 ) { 
	subtract( e1, e2)
}

'mean.jobjRef' <- function (e1 ) { 
	data$mean(sig1)
}

int <- function( from ) {
	class(from) <- "integer"
	from
}

I <- function( from ) {
	.jnew("java.lang.Integer", as.character(from) )
}

D <- function( from ) {
	if( length( from ) == 0 ) {
		from <- -9999.0
	} 		
	.jnew("java.lang.Double", as.character(from) )
}

setAs( from="numeric", to="jobjRef", I )

# --------------------
# API Convenience functions
# --------------------

create_annotation_layer <- function( layer_name, color, source ) {
	
	model <- J("idea.tsoffline.AppModel")
	
	layer <- model$getAnnotationLayer( layer_name )
	if( is.null( layer ) ) { 
		sig <- model$addAnnotationLayer( layer_name, color, source )
		layer <- sig$getLayer()
	}
	
	layer
}



# -------------------
# What you need to know to make a working help system...
# -------------------

print.help_files_with_topic <- function( t ) {
	topic <- attr( t, "topic" )
	pkg <- gsub( "package:", "", find( topic ) )
	e <- new.env(parent=emptyenv())
	hd <- dirname( as.character(t) )
	hf <- file.path(hd, pkg )
	
	lazyLoad( hf, e )

	out <- textConnection( "htmlt", "w" )
	Rd2HTML( get( topic, e ), out=out )
	close(out)
	
	message <- paste(htmlt, collapse = "\n")
	
	gui$showMessage( message, FALSE )
}

add <- function( sig1, sig2 ) {
	sig3 <- data$add( sig1, sig2 )
}

subtract <- function( sig1, sig2 ) {
	sig3 <- data$subtract( sig1, sig2 )
}

MA3 <- function( sig1, ... ) {
	dest <- filter$generate( sig1, "MA3", NULL );
}

MA5 <- function( sig1, ... ) {
	dest <- filter$generate( sig1, "MA5", NULL );
}

theme_dramatic_black <- function(base_size = 12, base_family = ""){
    theme_grey(base_size = base_size, base_family = base_family) %+replace%
        theme(
            panel.background = element_rect(fill = NA, color="white"),
            plot.background = element_rect(fill = "black"),
            axis.title.y=element_text(color="white"),
            axis.title.x=element_text(color="white"),
            axis.text.x=element_text(color="white"),
            axis.text.y=element_text(color="white"),
            legend.key=element_rect(color=NA, fill = NA),
            legend.text=element_text(color="white"),
            legend.background=element_rect(color="black", fill="black"),
		    legend.position = "none",
            strip.background=element_rect(color="white", fill = NA),
            strip.text = element_text(color="white"),
            panel.grid.minor = element_line(color=NA),
            panel.grid.major = element_line(color=NA)
#            panel.grid.major = element_line(size = 0.1, color = "white")
            )
}

# Multiple plot function
#
# ggplot objects can be passed in ..., or to plotlist (as a list of ggplot objects)
# - cols:   Number of columns in layout
# - layout: A matrix specifying the layout. If present, 'cols' is ignored.
#
# If the layout is something like matrix(c(1,2,3,3), nrow=2, byrow=TRUE),
# then plot 1 will go in the upper left, 2 will go in the upper right, and
# 3 will go all the way across the bottom.
#
multiplot <- function(..., plotlist=NULL, file, cols=1, layout=NULL) {
  library(grid)

  # Make a list from the ... arguments and plotlist
  plots <- c(list(...), plotlist)

  numPlots = length(plots)

  # If layout is NULL, then use 'cols' to determine layout
  if (is.null(layout)) {
    # Make the panel
    # ncol: Number of columns of plots
    # nrow: Number of rows needed, calculated from # of cols
    layout <- matrix(seq(1, cols * ceiling(numPlots/cols)),
                    ncol = cols, nrow = ceiling(numPlots/cols))
  }

 if (numPlots==1) {
    print(plots[[1]])

  } else {
    # Set up the page
    grid.newpage()
    pushViewport(viewport(layout = grid.layout(nrow(layout), ncol(layout))))

    # Make each plot, in the correct location
    for (i in 1:numPlots) {
      # Get the i,j matrix positions of the regions that contain this subplot
      matchidx <- as.data.frame(which(layout == i, arr.ind = TRUE))

      print(plots[[i]], vp = viewport(layout.pos.row = matchidx$row,
                                      layout.pos.col = matchidx$col))
    }
  }
}

GRADIENT_BLACK_TO_WHITE <- c("#000000",	# 0
	"#0a0a0a",	# 1
	"#141414",	# 2
	"#1e1e1e",	# 3
	"#282828",	# 4
	"#333333",	# 5
	"#3d3d3d",	# 6
	"#474747",	# 7
	"#515151",	# 8
	"#5b5b5b",	# 9
	"#666666",	# 10
	"#707070",	# 11
	"#7a7a7a",	# 12
	"#848484",	# 13
	"#8e8e8e",	# 14
	"#999999",	# 15
	"#a3a3a3",	# 16
	"#adadad",	# 17
	"#b7b7b7",	# 18
	"#c1c1c1",	# 19
	"#cccccc",	# 20
	"#d6d6d6",	# 21
	"#e0e0e0",	# 22
	"#eaeaea",	# 23
	"#f4f4f4")	# 24
GRADIENT_BLUE_TO_RED <-	c( "#0000ff",	# 0
	"#0a00f4",	# 1
	"#1400ea",	# 2
	"#1e00e0",	# 3
	"#2800d6",	# 4
	"#3300cc",	# 5
	"#3d00c1",	# 6
	"#4700b7",	# 7
	"#5100ad",	# 8
	"#5b00a3",	# 9
	"#660099",	# 10
	"#70008e",	# 11
	"#7a0084",	# 12
	"#84007a",	# 13
	"#8e0070",	# 14
	"#990066",	# 15
	"#a3005b",	# 16
	"#ad0051",	# 17
	"#b70047",	# 18
	"#c1003d",	# 19
	"#cc0033",	# 20
	"#d60028",	# 21
	"#e0001e",	# 22
	"#ea0014",	# 23
	"#f4000a")	# 24
GRADIENT_GREEN_YELLOW_ORANGE_RED <-	c( "#00ff00",	# 0
	"#1eff00",	# 1
	"#3dff00",	# 2
	"#5cff00",	# 3
	"#7aff00",	# 4
	"#99ff00",	# 5
	"#b8ff00",	# 6
	"#d7ff00",	# 7
	"#f5ff00",	# 8
	"#fffa00",	# 9
	"#fff300",	# 10
	"#ffed00",	# 11
	"#ffe600",	# 12
	"#ffdf00",	# 13
	"#ffd900",	# 14
	"#ffd200",	# 15
	"#ffcb00",	# 16
	"#ffbe00",	# 17
	"#ffa600",	# 18
	"#ff8e00",	# 19
	"#ff7600",	# 20
	"#ff5d00",	# 21
	"#ff4500",	# 22
	"#ff2d00",	# 23
	"#ff1500")	# 24
GRADIENT_HEAT <- c("#000000",	# 0
	"#100000",	# 1
	"#210000",	# 2
	"#320000",	# 3
	"#430000",	# 4
	"#540000",	# 5
	"#640000",	# 6
	"#730200",	# 7
	"#810600",	# 8
	"#8f0a00",	# 9
	"#9d0d00",	# 10
	"#ab1100",	# 11
	"#b91500",	# 12
	"#c52103",	# 13
	"#cf3509",	# 14
	"#d9490f",	# 15
	"#e35e15",	# 16
	"#ed721b",	# 17
	"#f78621",	# 18
	"#ff9a2e",	# 19
	"#ffab51",	# 20
	"#ffbb74",	# 21
	"#ffcc96",	# 22
	"#ffddb9",	# 23
	"#ffeedc")	# 24
GRADIENT_HOT <-	c("#000000",	# 0
	"#110000",	# 1
	"#220000",	# 2
	"#340000",	# 3
	"#450000",	# 4
	"#570000",	# 5
	"#780000",	# 6
	"#9a0000",	# 7
	"#bb0000",	# 8
	"#dd0000",	# 9
	"#ff0000",	# 10
	"#ff2800",	# 11
	"#ff5000",	# 12
	"#ff7800",	# 13
	"#ffa000",	# 14
	"#ffc800",	# 15
	"#ffd300",	# 16
	"#ffde00",	# 17
	"#ffe900",	# 18
	"#fff400",	# 19
	"#ffff00",	# 20
	"#ffff33",	# 21
	"#ffff66",	# 22
	"#ffff99",	# 23
	"#ffffcc")	# 24
GRADIENT_MAROON_TO_GOLD <-	c("#a00000",	# 0
	"#a30a00",	# 1
	"#a71400",	# 2
	"#ab1e00",	# 3
	"#af2800",	# 4
	"#b33300",	# 5
	"#b63d00",	# 6
	"#ba4700",	# 7
	"#be5100",	# 8
	"#c25b00",	# 9
	"#c66600",	# 10
	"#c97000",	# 11
	"#cd7a00",	# 12
	"#d18400",	# 13
	"#d58e00",	# 14
	"#d99900",	# 15
	"#dca300",	# 16
	"#e0ad00",	# 17
	"#e4b700",	# 18
	"#e8c100",	# 19
	"#eccc00",	# 20
	"#efd600",	# 21
	"#f3e000",	# 22
	"#f7ea00",	# 23
	"#fbf400")	# 24
GRADIENT_RAINBOW <-	c( "#b520ff",	# 0
	"#9019ff",	# 1
	"#6c13ff",	# 2
	"#480cff",	# 3
	"#2406ff",	# 4
	"#0000ff",	# 5
	"#0033cc",	# 6
	"#006699",	# 7
	"#009966",	# 8
	"#00cc33",	# 9
	"#00ff00",	# 10
	"#33ff00",	# 11
	"#66ff00",	# 12
	"#99ff00",	# 13
	"#ccff00",	# 14
	"#ffff00",	# 15
	"#fff400",	# 16
	"#ffe900",	# 17
	"#ffde00",	# 18
	"#ffd300",	# 19
	"#ffc800",	# 20
	"#ffa000",	# 21
	"#ff7800",	# 22
	"#ff5000",	# 23
	"#ff2800")	# 24
GRADIENT_RED_TO_GREEN <- c( "#ff0000",	# 0
	"#f40a00",	# 1
	"#ea1400",	# 2
	"#e01e00",	# 3
	"#d62800",	# 4
	"#cc3300",	# 5
	"#c13d00",	# 6
	"#b74700",	# 7
	"#ad5100",	# 8
	"#a35b00",	# 9
	"#996600",	# 10
	"#8e7000",	# 11
	"#847a00",	# 12
	"#7a8400",	# 13
	"#708e00",	# 14
	"#669900",	# 15
	"#5ba300",	# 16
	"#51ad00",	# 17
	"#47b700",	# 18
	"#3dc100",	# 19
	"#33cc00",	# 20
	"#28d600",	# 21
	"#1ee000",	# 22
	"#14ea00",	# 23
	"#0af400")	# 24
GRADIENT_ROY <- c( "#ff0000",	# 0
	"#ff1000",	# 1
	"#ff2000",	# 2
	"#ff3000",	# 3
	"#ff4000",	# 4
	"#ff5000",	# 5
	"#ff6000",	# 6
	"#ff7000",	# 7
	"#ff8000",	# 8
	"#ff9000",	# 9
	"#ffa000",	# 10
	"#ffb000",	# 11
	"#ffc000",	# 12
	"#ffca00",	# 13
	"#ffce00",	# 14
	"#ffd300",	# 15
	"#ffd700",	# 16
	"#ffdb00",	# 17
	"#ffe000",	# 18
	"#ffe400",	# 19
	"#ffe900",	# 20
	"#ffed00",	# 21
	"#fff100",	# 22
	"#fff600",	# 23
	"#fffa00")	# 24


#
# placed here to put the function definition in the global namespace...used
# by Waterfall-contour
#

panel.3d.contour <- function(x, y, z, rot.mat, distance, nlevels = 20, zlim.scaled, ...) {
         add.line <- trellis.par.get("add.line")
         panel.3dwire(x, y, z, rot.mat, distance, zlim.scaled = zlim.scaled, ...)
         clines <- contourLines(x, y, matrix(z, nrow = length(x),
        	 byrow = TRUE), nlevels = nlevels)
    	 for (ll in clines) {
         	m <- ltransform3dto3d(rbind(ll$x, ll$y, zlim.scaled[2]),
             rot.mat, distance)
         	panel.lines(m[1, ], m[2, ], col = add.line$col,
             lty = add.line$lty, lwd = add.line$lwd)
    	 }
}
	
	