# DIALOG SIGNAL WAVEFORM LVP.Source.Signal
# DIALOG PROMPT Layer.Name

pressure_sig <- app$getParam("SIGNAL", "LVP.Source.Signal" )
# pressure_sig <- app$getSignalByName( "LVP" )

layer_name <- app$getParam("PROMPT", "Layer.Name" )
# max_code <- app$getParam("PROMPT", "LVP(dp/dt).Max.Code" )
# min_code <- app$getParam("PROMPT", "LVP(dp/dt).Min.Code" )


#
# Main
#


create_formula_layer <- function( layer_name, color, source ) {
	
	
	layer <- app$getSignalByName( layer_name )
	if( is.null( layer ) ) { 
		sig <- model$addFormula( layer_name, color, source )
		layer <- sig$getLayer()
	}
	
	layer
}

layer <- create_formula_layer( layer_name, Color$RED, "derivative(${LVP})" )



# layer$addAttribute("@enum_by", "none" )
# layer$addAttribute("@displayState", "3");
# layer$addAttribute( "@maxCode", max_code )
# layer$addAttribute( "@minCode", min_code )

# rm( pressure_sig, canvas, layer )

