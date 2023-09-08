
if( !app.isCapturing() ) {
   dest.setDisplayMessage("Capture OFF", "Waiting...");
} else {

  var bt_prompt = "";

  var vigileo = app.getDevice( String("Vigileo") );
  var v_event = vigileo.getEvent( "NumericsEvent" );
  var v_block = null;
  if( v_event != null ) {
    v_block = v_event.getNumericsBlock();
  }
  var bt_item = null;
  var bt = null;
  if( v_block !== null ) {
    bt_item = v_block.getItem( String("Bnn.n" ) );
  }
  
  if( bt_item != null ) {
    bt_prompt = " BT: "
    bt = bt_item.getValue();
  }

  var hr_item = block.getItem( String( "ecg.hr" ) );
  var sys_item = block.getItem( String( "art.sys" ) );
  var dia_item = block.getItem( String( "art.dia" ) );
  var map_item = block.getItem( String( "art.mean" ) );
  var ta_item = block.getItem( String( "tbasic.a" ) );
  var sdm = "<???>";
  var ta = "<???>";
  if( sys_item !== null ) {
    sdm = "" + sys_item.getValue() + "/" + dia_item.getValue() + "/" + map_item.getValue();
  }
  if( ta_item !== null && bt == null ) {
    bt_prompt = " T: "
    ta = ta_item.getValue();
    bt = ta;
  }

  if( hr_item === null ) { 
  } else {
    dest.setDisplayMessage( "HR: " + hr_item.getValue() + bt_prompt + bt, "S/D/M: " + sdm );
  }

}